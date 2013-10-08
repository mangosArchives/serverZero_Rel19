# - Try to find MySQL
# Once done this will define
#
#  MYSQL_FOUND          - system has MySQL
#  MYSQL_INCLUDE_DIR    - the MySQL include directory
#  MYSQL_LIBRARIES      - Link these to use MySQL
#  MYSQL_LIB_DIR        - Path to MYSQL_LIBRARIES

if(WIN32)
   find_path(MYSQL_INCLUDE_DIR
      NAMES mysql.h
      PATHS $ENV{MYSQL_INCLUDE_DIR}
            $ENV{MYSQL_DIR}/include
            $ENV{ProgramFiles}/MySQL/*/include
            $ENV{SystemDrive}/MySQL/*/include
            "[HKEY_LOCAL_MACHINE\\SOFTWARE\\MySQL AB\\MySQL Server 5.0;Location]/include"
            "[HKEY_LOCAL_MACHINE\\SOFTWARE\\MySQL AB\\MySQL Server 5.1;Location]/include"
            "[HKEY_LOCAL_MACHINE\\SOFTWARE\\MySQL AB\\MySQL Server 5.5;Location]/include"
            "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\MySQL AB\\MySQL Server 5.0;Location]/include"
            "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\MySQL AB\\MySQL Server 5.1;Location]/include"
            "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\MySQL AB\\MySQL Server 5.5;Location]/include"
            "c:/msys/local/include"
      DOC "MySQL development headers"
   )
else(WIN32)
   find_path(MYSQL_INCLUDE_DIR
      NAMES mysql.h
      PATHS $ENV{MYSQL_INCLUDE_DIR}
            $ENV{MYSQL_DIR}/include
            /usr/local/mysql/include
            /opt/mysql/mysql/include
      PATH_SUFFIXES mysql
      DOC "MySQL development headers"
   )
endif(WIN32)

if(WIN32)
   if (${CMAKE_BUILD_TYPE})
    string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_TOLOWER)
   endif()

   # path suffix for debug/release mode
   # binary_dist: mysql binary distribution
   # build_dist: custom build
   if(CMAKE_BUILD_TYPE_TOLOWER MATCHES "debug")
      set(binary_dist debug)
      set(build_dist Debug)
   else(CMAKE_BUILD_TYPE_TOLOWER MATCHES "debug")
      ADD_DEFINITIONS(-DDBUG_OFF)
      set(binary_dist opt)
      set(build_dist Release)
   endif(CMAKE_BUILD_TYPE_TOLOWER MATCHES "debug")

   # find_library(MYSQL_LIBRARIES NAMES mysqlclient
   find_library(MYSQL_LIBRARIES
      NAMES libmysql
      PATHS $ENV{MYSQL_DIR}/lib/${binary_dist}
            $ENV{MYSQL_DIR}/libmysql/${build_dist}
            $ENV{MYSQL_DIR}/client/${build_dist}
            $ENV{ProgramFiles}/MySQL/*/lib/
            $ENV{SystemDrive}/MySQL/*/lib/
            "[HKEY_LOCAL_MACHINE\\SOFTWARE\\MySQL AB\\MySQL Server 5.0;Location]/lib/"
            "[HKEY_LOCAL_MACHINE\\SOFTWARE\\MySQL AB\\MySQL Server 5.1;Location]/lib/"
            "[HKEY_LOCAL_MACHINE\\SOFTWARE\\MySQL AB\\MySQL Server 5.5;Location]/lib/"
            "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\MySQL AB\\MySQL Server 5.0;Location]/lib/"
            "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\MySQL AB\\MySQL Server 5.1;Location]/lib/"
            "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\MySQL AB\\MySQL Server 5.5;Location]/lib/"
            "c:/msys/local/include"
      DOC   "MySQL client libraries"
   )
else(WIN32)
   # find_library(MYSQL_LIBRARIES NAMES mysqlclient
   find_library(MYSQL_LIBRARIES
      NAMES libmysql
      PATHS $ENV{MYSQL_DIR}/libmysql_r/.libs
            $ENV{MYSQL_DIR}/lib
            $ENV{MYSQL_DIR}/lib/mysql
            /usr/local/mysql/lib
            /opt/mysql/mysql/lib
      PATH_SUFFIXES mysql
      DOC   "MySQL client libraries"
   )
endif(WIN32)

if(WIN32)
   set(MYSQL_LIB_PATHS
      $ENV{MYSQL_DIR}/lib/opt
      $ENV{MYSQL_DIR}/client/release
      $ENV{ProgramFiles}/MySQL/*/lib
      $ENV{SystemDrive}/MySQL/*/lib
   )
   find_library(MYSQL_LIBRARIES
      NAMES mysqlclient
      PATHS ${MYSQL_LIB_PATHS}
      DOC   "MySQL client libraries"
   )
else(WIN32)
   set(MYSQL_LIB_PATHS
      $ENV{MYSQL_DIR}/libmysql_r/.libs
      $ENV{MYSQL_DIR}/lib
      $ENV{MYSQL_DIR}/lib/mysql
      /usr/local/mysql/lib
      /opt/mysql/mysql/lib
      PATH_SUFFIXES
      mysql
   )
   find_library(MYSQL_LIBRARIES
      NAMES mysqlclient
      PATHS ${MYSQL_LIB_PATHS}
      DOC   "MySQL client libraries"
   )
endif(WIN32)

if(MYSQL_LIBRARIES)
   get_filename_component(MYSQL_LIB_DIR ${MYSQL_LIBRARIES} PATH)
endif(MYSQL_LIBRARIES)

set( CMAKE_REQUIRED_INCLUDES ${MYSQL_INCLUDE_DIR} )

mark_as_advanced(MYSQL_INCLUDE_DIR MYSQL_LIBRARIES)

if(MYSQL_INCLUDE_DIR AND EXISTS "${MYSQL_INCLUDE_DIR}/mysql_version.h")
   file( STRINGS "${MYSQL_INCLUDE_DIR}/mysql_version.h" MYSQL_VERSION_H REGEX "^#define[ \t]+MYSQL_SERVER_VERSION[ \t]+\"[^\"]+\".*$" )
   string( REGEX REPLACE "^.*MYSQL_SERVER_VERSION[ \t]+\"([^\"]+)\".*$" "\\1" MYSQL_VERSION_STRING "${MYSQL_VERSION_H}" )
endif()

if(MYSQL_INCLUDE_DIR AND MYSQL_LIBRARIES)
   set(MYSQL_FOUND TRUE)
   message(STATUS "Found MySQL: ${MYSQL_INCLUDE_DIR}, ${MYSQL_LIBRARIES}")
else(MYSQL_INCLUDE_DIR AND MYSQL_LIBRARIES)
   set(MYSQL_FOUND FALSE)
   message(STATUS "MySQL not found.")
endif(MYSQL_INCLUDE_DIR AND MYSQL_LIBRARIES)

# handle the QUIETLY and REQUIRED arguments and set MYSQL_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MYSQL REQUIRED_VARS MYSQL_LIBRARIES MYSQL_INCLUDE_DIR VERSION_VAR MYSQL_VERSION_STRING)
