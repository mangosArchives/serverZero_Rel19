#
# This code is part of MaNGOS. Contributor & Copyright details are in AUTHORS/THANKS.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

# CMake policies
cmake_minimum_required(VERSION 2.8)

#-----------------------------------------------------------------------------
# Ensure we print configuration summary only on the initial CMake run
if(NOT EXECUTABLE_OUTPUT_PATH)
    set(FIRST_RUN "TRUE")
endif(NOT EXECUTABLE_OUTPUT_PATH)

#-----------------------------------------------------------------------------
# We provide a few modules for our own needs to find and configure uncommon
# software on which we depend.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#-----------------------------------------------------------------------------
# We do build in Release mode by default to provide the fastest build
# experience.
set(CMAKE_BUILD_TYPE_INIT "Release")

#-----------------------------------------------------------------------------
# If quiet output for Makefiles is desired, set this to ON. 'make -s' is an
# alternative.
# set_property(GLOBAL PROPERTY RULE_MESSAGES OFF)

#-----------------------------------------------------------------------------
# Global compile definitions since add_definitions() adds for all.
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS_DEBUG           DEBUG _DEBUG)
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS_RELEASE         NDEBUG)
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS_MINSIZEREL      NDEBUG)
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS_RELWITHDEBINFO  NDEBUG)

#-----------------------------------------------------------------------------
# Set policies

# see "cmake --help-policy CMP0003"
# So library linking is more sane
cmake_policy(SET CMP0003 NEW)

# see "cmake --help-policy CMP0005"
# So BUILDINFO and MANGOSPATH strings are automatically quoted
cmake_policy(SET CMP0005 NEW)

# see "cmake --help-policy CMP0010"
# So syntax problems are errors
cmake_policy(SET CMP0010 NEW)

# see "cmake --help-policy CMP0014"
# Input directories must have CMakeLists.txt
cmake_policy(SET CMP0014 NEW)

#-----------------------------------------------------------------------------
# Initialize project.

project(mangos-zero C CXX)

set(APPLICATION_NAME            ${PROJECT_NAME})
set(APPLICATION_VERSION_MAJOR   "0")
set(APPLICATION_VERSION_MINOR   "18")
set(APPLICATION_VERSION_RELEASE "1")
set(APPLICATION_VERSION         "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}.${APPLICATION_VERSION_RELEASE}")

#-----------------------------------------------------------------------------
# Initialize Doxygen module and prepare the Doxygen template
SET(DOXYFILE_SOURCE_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/src/)
SET(DOXYFILE_LATEX          OFF)
include(UseDoxygen)

#-----------------------------------------------------------------------------
# Redirect output files
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin CACHE INTERNAL "" FORCE)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib CACHE INTERNAL "" FORCE)

#-----------------------------------------------------------------------------
# Set default config options

# mangos-zero internal features
option(WITH_DEBUG_OUTPUT    "Enable mangos-zero debug output (only enable for development)"                 OFF)
option(WITH_GIT_ID          "Build git database update helper"                                              OFF)
mark_as_advanced(WITH_GIT_ID)

# dont want people disabling this unless they really know what they are doing.
option(WITH_MAP_TOOLS       "Build map extractors and generators"                                           ON)
mark_as_advanced(WITH_MAP_TOOLS)

# mangos-zero database bindings
option(WITH_MYSQL           "Enable MySQL database backend"                                                 ON)
option(WITH_POSTGRESQL      "Enable PostgreSQL database backend"                                            OFF)

# mangos-zero language bindings
option(WITH_MOD_LUA         "Enable Lua scripting (requires Lua 5.1)"                                       OFF)
option(WITH_MOD_SCRIPTDEV2  "Enable the scripting library"                                                  OFF)

# Modifiers
option(WITH_MOD_SOAP        "Enable SOAP bindings (export data e.g. for a website)"                         OFF)
option(WITH_MOD_CLI         "Enable command line interface"                                                 OFF)
option(WITH_MOD_REMOTE      "Enable remote access (remote administration)"                                  OFF)
option(WITH_RECAST_DEMO     "Build the Recast movement map viewer application"                              OFF)

#-----------------------------------------------------------------------------
# Check for conflicting/unsupported configurations
if(NOT WITH_MYSQL AND NOT WITH_POSTGRESQL)
    message(FATAL_ERROR "At least one of WITH_MYSQL or WITH_POSTGRESQL must be enabled!")
endif(NOT WITH_MYSQL AND NOT WITH_POSTGRESQL)

if(NOT WITH_MAP_TOOLS AND WITH_RECAST_DEMO)
    message(FATAL_ERROR "WITH_MAP_TOOLS must be enabled to build WITH_RECAST_DEMO!")
endif(NOT WITH_MAP_TOOLS AND WITH_RECAST_DEMO)

if(NOT ${CMAKE_BUILD_TYPE} STREQUAL "Debug" AND WITH_DEBUG_OUTPUT)
    message(FATAL_ERROR "It is not recommeded to build mangos-zero with debug output in a non-development release.")
endif()
option(ACE_USE_EXTERNAL      "Use external ACE"                             OFF)
if(PCHSupport_FOUND AND WIN32) # TODO: why only enable it on windows by default?
  option(PCH                 "Use precompiled headers"                       ON)
else()
  option(PCH                 "Use precompiled headers"                      OFF)
endif()
# TODO: options that should be checked/created:
#option(CLI                  "With CLI"                                      ON)
#option(RA                   "With Remote Access"                           OFF)
#option(SQL                  "Copy SQL files"                               OFF)
#option(TOOLS                "Build tools"                                  OFF)

# Output description of this script
message("")
message(
  "This script builds the MaNGOS server.
  Options that can be used in order to configure the process:
    CMAKE_INSTALL_PREFIX    Path where the server should be installed to
    PCH                     Use precompiled headers
    DEBUG                   Debug mode
    INCLUDE_BINDINGS_DIR    Include a script library in src/bindings/ with the
                            defined name. the name must corespond to the name of
                            the folder and the folder must contain a valid
                            CMakeLists.txt
    TBB_USE_EXTERNAL        Use external TBB
    USE_STD_MALLOC          Use standard malloc instead of TBB
    ACE_USE_EXTERNAL        Use external ACE
  To set an option simply type -D<OPTION>=<VALUE> after 'cmake <srcs>'.
  Also, you can specify the generator with -G. see 'cmake --help' for more details
  For example: cmake .. -DDEBUG=1 -DCMAKE_INSTALL_PREFIX=/opt/mangos"
)
message("")

if(WITH_MOD_LUA AND WITH_MOD_SCRIPTDEV2)
    message(FATAL_ERROR "Lua and ScriptDev2 can not be used in parallel. Disable Lua or ScriptDev2.")
endif()

#-----------------------------------------------------------------------------
# Initialize un-cached vars, avoid unused warning
# linux only, not cached
set(WITH_BINRELOC OFF)

# TODO: allow other compilers under windows in the future
if(WIN32 AND NOT MSVC)
  message(FATAL_ERROR
    "Under Windows other compiler than Microsoft Visual Studio are not supported."
  )
endif()

# TODO: remove this in the future! it has only been added to make the switch easier for end users
if(PREFIX)
  message(FATAL_ERROR "The parameter PREFIX has been removed. Please re-run CMake and use CMAKE_INSTALL_PREFIX instead to define your installation location!")
endif()

# TODO: use MSVC_CXX_ARCHITECTURE_ID instead to identify platform on windows (not required on other systems)
# find platform: required to build 3rd party libraries w/o CMake files
find_package(Platform REQUIRED)
# Find out what system we use to include the needed libs
if(WIN32)
  if(PLATFORM MATCHES X86) # 32-bit
    set(DEP_ARCH win32)
  else() # 64-bit
    set(DEP_ARCH x64)
  endif()
endif()

# find Git: used to get the revision number
find_package(Git)

# check if the platform supports precomiled headers
find_package(PCHSupport)

# TODO: remove this (refactor ACE & TBB CMake code)
# VS100 uses MSBuild.exe instead of devenv.com, so force it to use devenv.com
if(WIN32 AND MSVC_VERSION MATCHES 1600)
  find_package(VisualStudio2010)
endif()

# Override configuration-types - we don't use anything else than debug and release
if(CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_CONFIGURATION_TYPES Release Debug)
  set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING
    "Reset the configurations to what we need"
    FORCE)
endif()

set(BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)
set(CONF_DIR ${CMAKE_INSTALL_PREFIX}/etc)
# If win32 put it in the bin dir not lib
if(WIN32)
  set(LIBS_DIR ${CMAKE_INSTALL_PREFIX}/bin)
else()
  set(LIBS_DIR ${CMAKE_INSTALL_PREFIX}/lib)
endif()

# For Unix systems set the rpath so that libraries are found
set(CMAKE_INSTALL_RPATH ${LIBS_DIR})
set(CMAKE_INSTALL_NAME_DIR ${LIBS_DIR})
# Run out of build tree
set(CMAKE_BUILD_WITH_INSTALL_RPATH OFF)

# Find needed packages and if necessery abort if something important is missing
unset(ACE_INCLUDE_DIR CACHE)
unset(ACE_LIBRARIES CACHE)
unset(ACE_LIBRARIES_DIR CACHE)
unset(ACE_INCLUDE_DIR)
unset(ACE_LIBRARIES)
unset(ACE_LIBRARIES_DIR)
if(ACE_USE_EXTERNAL)
  find_package(ACE)
  if(NOT ACE_FOUND)
    message(FATAL_ERROR
      "This project requires ACE installed when ACE_USE_EXTERNAL is set. Please download the ACE Micro Release Kit from http://download.dre.vanderbilt.edu/ and install it. If this script didn't find ACE and it was correctly installed please set ACE_ROOT to the correct path."
    )
  endif()
  if(EXISTS ${ACE_INCLUDE_DIR}/ace/Stack_Trace.h)
    set(HAVE_ACE_STACK_TRACE_H ON) # config.h.cmake
  endif()
else()
  include(cmake/ImportACE.cmake)
endif()

if(USE_TBB_MALLOC)
  unset(TBB_INCLUDE_DIR CACHE)
  unset(TBB_LIBRARIES CACHE)
  unset(TBB_LIBRARIES_DIR CACHE)
  unset(TBB_INCLUDE_DIR)
  unset(TBB_LIBRARIES)
  unset(TBB_LIBRARIES_DIR)
  if(TBB_USE_EXTERNAL)
    find_package(TBB)
    if(NOT TBB_FOUND)
      message(FATAL_ERROR
        "This project requires TBB installed when TBB_USE_EXTERNAL is set. Please download the TBB Stable Release from http://www.threadingbuildingblocks.org/ and install it. If this script didn't find TBB and it was correctly installed please set TBB_ROOT to the correct path."
      )
    endif()
  else()
    include(cmake/ImportTBB.cmake)
  endif()
endif()

# Win32 delivered packages
if(WIN32)
  set(MYSQL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/dep/include/mysql)
  set(MYSQL_LIBRARY ${CMAKE_SOURCE_DIR}/dep/lib/${DEP_ARCH}_release/libmySQL.lib)
  set(MYSQL_DEBUG_LIBRARY ${CMAKE_SOURCE_DIR}/dep/lib/${DEP_ARCH}_debug/libmySQL.lib)
  set(OPENSSL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/dep/include/openssl)
  set(OPENSSL_LIBRARIES ${CMAKE_SOURCE_DIR}/dep/lib/${DEP_ARCH}_release/libeay32.lib)
  set(OPENSSL_DEBUG_LIBRARIES ${CMAKE_SOURCE_DIR}/dep/lib/${DEP_ARCH}_debug/libeay32.lib)
  # zlib is build
endif()

# *nix-specific packages
if(UNIX)
  find_package(MySQL REQUIRED)
  find_package(OpenSSL REQUIRED)
  find_package(ZLIB REQUIRED)
endif()

# Add uninstall script and target
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY
)

add_custom_target(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
)

# Find core revision
if(GIT_EXECUTABLE)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    OUTPUT_VARIABLE GIT_REVISION
    RESULT_VARIABLE GIT_RESULT
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  if(GIT_RESULT)
    set(GIT_REVISION "Git repository not found")
  endif()
else()
  set(GIT_REVISION "Git not found")
endif()

message(STATUS "MaNGOS-Core revision  : ${GIT_REVISION}")
message(STATUS "Install server to     : ${CMAKE_INSTALL_PREFIX}")

if(DEFINED INCLUDE_BINDINGS_DIR AND INCLUDE_BINDINGS_DIR)
  # check if the directory exists
  if(NOT IS_DIRECTORY ${CMAKE_SOURCE_DIR}/src/bindings/${INCLUDE_BINDINGS_DIR})
    message(FATAL_ERROR "Could not find the script library which was supposed to be: " ${CMAKE_SOURCE_DIR}/src/bindings/${INCLUDE_BINDINGS_DIR})
  endif()
  # check if it really contains a CMakeLists.txt
  if(NOT EXISTS ${CMAKE_SOURCE_DIR}/src/bindings/${INCLUDE_BINDINGS_DIR}/CMakeLists.txt)
    message(FATAL_ERROR "The script library does not contain a CMakeLists.txt!")
  endif()
  message(STATUS "Build script library  : Yes (using ${INCLUDE_BINDINGS_DIR})")
else()
  message(STATUS "Build script library  : No")
endif()

# if(CLI)
#   message(STATUS "Build with CLI        : Yes (default)")
#   add_definitions(-DENABLE_CLI)
# else()
#   message(STATUS "Build with CLI        : No")
# endif()

# if(RA)
#   message(STATUS "* Build with RA         : Yes")
#   add_definitions(-DENABLE_RA)
# else(RA)
#   message(STATUS "* Build with RA         : No  (default)")
# endif(RA)

if(PCH AND NOT PCHSupport_FOUND)
  set(PCH 0 CACHE BOOL
    "Use precompiled headers"
    FORCE)
  message(WARNING "No PCH for your system possible but PCH was set to 1. Resetting it."
  )
endif()
if(PCH)
  message(STATUS "Use PCH               : Yes")
else()
  message(STATUS "Use PCH               : No")
endif()

if(DEBUG)
  message(STATUS "Build in debug-mode   : Yes")
  set(CMAKE_BUILD_TYPE Debug)
else()
  set(CMAKE_BUILD_TYPE Release)
  message(STATUS "Build in debug-mode   : No  (default)")
endif()
# Handle debugmode compiles (this will require further work for proper WIN32-setups)
if(UNIX)
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
endif()

# Set warning levels for different builds
if(UNIX)
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} --no-warnings")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} --no-warnings")
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wfatal-errors -Wextra")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wfatal-errors -Wextra")
elseif(WIN32)
  # Disable warnings in Visual Studio 8 and above and add /MP
  if(MSVC AND NOT CMAKE_GENERATOR MATCHES "Visual Studio 7")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /wd4996 /wd4355 /wd4244 /wd4985 /wd4267 /MP")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /wd4996 /wd4355 /wd4244 /wd4267 /MP")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /wd4996 /wd4355 /wd4244 /wd4985 /wd4267 /MP")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /wd4996 /wd4355 /wd4244 /wd4985 /wd4267 /MP")
  endif()
endif()

# if(SQL)
#   message(STATUS "Install SQL-files     : Yes")
# else()
#   message(STATUS "Install SQL-files     : No  (default)")
# endif()

# if(TOOLS)
#   message(STATUS "Build map/vmap tools  : Yes")
# else()
#   message(STATUS "Build map/vmap tools  : No  (default)")
# endif()

# Some small tweaks for Visual Studio 7 and above.
if(MSVC)
  # Mark 32 bit executables large address aware so they can use > 2GB address space
  if(PLATFORM MATCHES X86)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LARGEADDRESSAWARE")
  endif()
endif()

set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH ${LIBS_DIR})
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# Generate revision-extractor
set(GENREV_SRC
  src/tools/genrevision/genrevision.cpp
)

add_executable(genrev
  ${GENREV_SRC}
)

get_target_property(GENERATE_EXE genrev LOCATION)
add_custom_target("revision.h" ALL
  COMMAND ${GENERATE_EXE} ${CMAKE_SOURCE_DIR}
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
  DEPENDS genrev
)

if(WIN32)
  install(
    FILES
      ${CMAKE_SOURCE_DIR}/dep/lib/${DEP_ARCH}_release/libeay32.dll
      ${CMAKE_SOURCE_DIR}/dep/lib/${DEP_ARCH}_release/libmySQL.dll
    DESTINATION ${LIBS_DIR}
    CONFIGURATIONS Release
  )
  install(
    FILES
      ${CMAKE_SOURCE_DIR}/dep/lib/${DEP_ARCH}_debug/libeay32.dll
      ${CMAKE_SOURCE_DIR}/dep/lib/${DEP_ARCH}_debug/libmySQL.dll
    DESTINATION ${LIBS_DIR}
    CONFIGURATIONS Debug
  )
  if(PLATFORM MATCHES X86)
    # Copy dll's Windows needs
    install(
      FILES
        ${CMAKE_SOURCE_DIR}/dep/lib/win32_release/dbghelp.dll
      DESTINATION ${LIBS_DIR}
      CONFIGURATIONS Release
    )
    install(
      FILES
        ${CMAKE_SOURCE_DIR}/dep/lib/win32_debug/dbghelp.dll
      DESTINATION ${LIBS_DIR}
      CONFIGURATIONS Debug
    )
  endif()
endif()

if(XCODE)
  if(PLATFORM MATCHES X86)
    set(CMAKE_OSX_ARCHITECTURES i386)
  else()
    set(CMAKE_OSX_ARCHITECTURES x86_64)
  endif()
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h)

add_subdirectory(dep) # TODO: add vmap extractor build support

# Add definitions for all build types
# Don't place this above 'dep' subdirectory! Because of defines build will crash.
set(DEFINITIONS
  DO_MYSQL
  HAVE_CONFIG_H
  VERSION="${MANGOS_VERSION}"
  SYSCONFDIR="${CONF_DIR}/"
)
set(DEFINITIONS_RELEASE NDEBUG)
set(DEFINITIONS_DEBUG _DEBUG MANGOS_DEBUG)
if(WIN32)
  set(DEFINITIONS ${DEFINITIONS} WIN32 _WIN32)
  set(DEFINITIONS_RELEASE ${DEFINITIONS_RELEASE} _CRT_SECURE_NO_WARNINGS)
endif()
if(USE_STD_MALLOC)
  set(DEFINITIONS ${DEFINITIONS} USE_STANDARD_MALLOC)
endif()

if(WITH_MYSQL)
    find_package(MySQL REQUIRED)
endif(WITH_MYSQL)

if(WITH_POSTGRESQL)
    find_package(PostgreSQL REQUIRED)
endif(WITH_POSTGRESQL)

if(WITH_MOD_LUA)
    find_package(Lua51 REQUIRED)
endif(WITH_MOD_LUA)

#-----------------------------------------------------------------------------
# Extra compile flags

#-------------------------------------------------------------------------------
# Global Defines

#-----------------------------------------------------------------------------
# Dump generated headers and add custom target for version control information
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake ${CMAKE_BINARY_DIR}/config.h)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/revision.h.cmake ${CMAKE_BINARY_DIR}/revision.h)

add_subdirectory(src)
# if(SQL)
#   add_subdirectory(sql)
# endif()

#For doxygen
add_subdirectory(doc)
