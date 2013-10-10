# ScriptDev2 is an extension for mangos-zero providing enhanced features for
# area triggers, creatures, game objects, instances, items, and spells beyond
# the default database scripting in mangos-zero.
#
# Copyright (C) 2006-2013 ScriptDev2 <http://www.scriptdev2.com/>
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
# Define the scriptdev2 library
file(GLOB_RECURSE sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.h)
file(GLOB_RECURSE headers RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)

set(mangosscript_LIB_SRCS ${sources} ${headers})

mangos_source_group(${mangosscript_LIB_SRCS})

include_directories(
    ${ACE_INCLUDE_DIRS}
    ${MYSQL_INCLUDE_DIR}
    # ${OPENSSL_INCLUDE_DIR}
    # ${ZLIB_INCLUDE_DIR}
    # ${CMAKE_SOURCE_DIR}/dep/include/g3dlite/
    # ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Detour/Include/
    ${CMAKE_SOURCE_DIR}/src/framework/
    ${CMAKE_SOURCE_DIR}/src/shared/
    ${CMAKE_SOURCE_DIR}/src/game/
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/base/
    ${CMAKE_CURRENT_SOURCE_DIR}/system/
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_BINARY_DIR}
    ${CMAKE_BINARY_DIR}/src/shared/
)

#-----------------------------------------------------------------------------
# Dump generated headers and add custom target for version control information
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config-sd2.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-sd2.h)

#-----------------------------------------------------------------------------
# Build the scriptdev2 library
add_library(mangosscript SHARED ${mangosscript_LIB_SRCS})
# target_link_libraries(mangos-game mangos-auctionhouse-bot mangos-battleground mangos-outdoor-pvp mangos-movement mangos-vmap mangos-shared mangos-framework Detour g3dlite ${ACE_LIBRARIES} ${MYSQL_LIBRARIES} ${OPENSSL_LIBRARIES} ${ZLIB_LIBRARIES})

#-----------------------------------------------------------------------------
# Build and install the scriptdev2 files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/scriptdev2.conf.dist.cmake ${CMAKE_CURRENT_BINARY_DIR}/scriptdev2.conf.dist)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/scriptdev2.conf.dist DESTINATION ${CONF_DIR})

install(TARGETS mangosscript
    DESTINATION ${LIBS_DIR}
    LIBRARY DESTINATION ${LIBS_DIR}
)
