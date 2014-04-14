# mangos-zero is a full featured server for World of Warcraft in its vanilla
# version, supporting clients for patch 1.12.x.
#
# Copyright (C) 2005-2014  MaNGOS project <http://getmangos.eu>
#
# ***** BEGIN GPL LICENSE BLOCK *****
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
# ***** END GPL LICENSE BLOCK *****
#
# World of Warcraft, and all World of Warcraft or Warcraft art, images,
# and lore are copyrighted by Blizzard Entertainment, Inc.

include(MacroMangosSourceGroup)

#-----------------------------------------------------------------------------
# Define the realmd application
file(GLOB sources *.cpp)
file(GLOB headers *.h)

set(realmd_LIB_SRCS ${sources} ${headers})

mangos_source_group(${realmd_LIB_SRCS})

include_directories(
    ${ACE_INCLUDE_DIRS}
    ${MYSQL_INCLUDE_DIR}
    ${OPENSSL_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/src/framework/
    ${CMAKE_SOURCE_DIR}/src/shared/
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_BINARY_DIR}
    ${CMAKE_BINARY_DIR}/src/shared/
)

#-----------------------------------------------------------------------------
# Build the realmd application
add_executable(realmd ${realmd_LIB_SRCS})
target_link_libraries(realmd mangos-framework mangos-shared ${ACE_LIBRARIES} ${MYSQL_LIBRARIES} ${OPENSSL_LIBRARIES})

set(BUILD_PROPERTIES "")
if(${CMAKE_BUILD_TYPE} MATCHES Debug)
    set(BUILD_PROPERTIES "${BUILD_PROPERTIES} -DMANGOS_DEBUG")
    set_target_properties(realmd PROPERTIES COMPILE_FLAGS ${BUILD_PROPERTIES})
endif()

install(TARGETS realmd DESTINATION ${BIN_DIR})

add_dependencies(realmd revision.h)

#-----------------------------------------------------------------------------
# Build and install the realmd configuration
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/realmd.conf.dist.cmake ${CMAKE_CURRENT_BINARY_DIR}/realmd.conf.dist)
if(WIN32)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/realmd.conf.dist DESTINATION ${BIN_DIR})
else()
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/realmd.conf.dist DESTINATION ${CONF_DIR})
endif()
