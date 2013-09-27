# mangos-zero is a full featured server for World of Warcraft in its vanilla
# version, supporting clients for patch 1.12.x.
#
# Copyright (C) 2005-2013  MaNGOS project <http://getmangos.com>
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
# Define the mangosd application
set(sources
    CliRunnable.cpp
    Main.cpp
    Master.cpp
    RASocket.cpp
    WorldRunnable.cpp
)
set(headers
    CliRunnable.h
    Master.h
    RASocket.h
    WorldRunnable.h
)

set(mangosd_LIB_SRCS ${sources} ${headers})

mangos_source_group(${mangosd_LIB_SRCS})

include_directories(
    ${ACE_INCLUDE_DIRS}
    ${MYSQL_INCLUDE_DIR}
    ${OPENSSL_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/src/framework/
    ${CMAKE_SOURCE_DIR}/src/shared/
    ${CMAKE_SOURCE_DIR}/src/game/
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_BINARY_DIR}
    ${CMAKE_BINARY_DIR}/src/shared/
)

if(WITH_MOD_SOAP)
    set(mangosd_LIB_SRCS ${mangosd_LIB_SRCS} MaNGOSsoap.cpp MaNGOSsoap.h soapC.cpp soapH.h soapServer.cpp soapStub.h)
    include_directories(
        ${CMAKE_SOURCE_DIR}/dep/include/gsoap/
    )
endif()

#-----------------------------------------------------------------------------
# Build the mangosd application
add_executable(mangosd ${mangosd_LIB_SRCS})
target_link_libraries(mangosd ${ACE_LIBRARIES} mangos-game mangos-auctionhouse-bot mangos-battleground mangos-outdoor-pvp mangos-movement mangos-vmap mangos-shared mangos-framework Detour g3dlite ${MYSQL_LIBRARIES} ${OPENSSL_LIBRARIES})

set(BUILD_PROPERTIES "-DHAVE_CONFIG_H")
if(WITH_MOD_SOAP)
    set(BUILD_PROPERTIES "${BUILD_PROPERTIES} -DENABLE_SOAP")
    target_link_libraries(mangosd gsoaplite)
endif()
set_target_properties(mangosd PROPERTIES COMPILE_FLAGS ${BUILD_PROPERTIES})

install(TARGETS mangosd DESTINATION ${BIN_DIR})

add_dependencies(mangosd revision.h)

#-----------------------------------------------------------------------------
# Build and install the mangosd configuration
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/mangosd.conf.dist.cmake ${CMAKE_CURRENT_BINARY_DIR}/mangosd.conf.dist)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/mangosd.conf.dist DESTINATION ${CONF_DIR})
