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
# Build the mangos-zero vmap library
add_subdirectory(vmap)

#-----------------------------------------------------------------------------
# Build the mangos-zero auctionhousebot library
add_subdirectory(AuctionHouseBot)

#-----------------------------------------------------------------------------
# Build the mangos-zero battleground library
add_subdirectory(BattleGround)

#-----------------------------------------------------------------------------
# Build the mangos-zero outdoor PvP library
add_subdirectory(OutdoorPvP)

#-----------------------------------------------------------------------------
# Build the mangos-zero movement library
add_subdirectory(movement)

#-----------------------------------------------------------------------------
# Define the game library
file(GLOB sources *.cpp)
file(GLOB headers *.h)

set(game_LIB_SRCS ${sources} ${headers})

mangos_source_group(${game_LIB_SRCS})

include_directories(
    ${ACE_INCLUDE_DIRS}
    ${MYSQL_INCLUDE_DIR}
    ${OPENSSL_INCLUDE_DIR}
    ${ZLIB_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/dep/include/g3dlite/
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Detour/Include/
    ${CMAKE_SOURCE_DIR}/src/framework/
    ${CMAKE_SOURCE_DIR}/src/shared/
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/vmap/
    ${CMAKE_CURRENT_SOURCE_DIR}/AuctionHouseBot/
    ${CMAKE_CURRENT_SOURCE_DIR}/BattleGround/
    ${CMAKE_CURRENT_SOURCE_DIR}/OutdoorPvP/
    ${CMAKE_CURRENT_SOURCE_DIR}/movement/
    ${CMAKE_BINARY_DIR}
    ${CMAKE_BINARY_DIR}/src/shared/
)

#-----------------------------------------------------------------------------
# Build the game library
add_library(mangos-game STATIC ${game_LIB_SRCS})
target_link_libraries(mangos-game mangos-auctionhouse-bot mangos-battleground mangos-outdoor-pvp mangos-movement mangos-vmap mangos-shared mangos-framework Detour g3dlite ${ACE_LIBRARIES} ${MYSQL_LIBRARIES} ${OPENSSL_LIBRARIES} ${ZLIB_LIBRARIES})

if(UNIX)
  # Both systems don't have libdl and don't need them
  if (NOT (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD" OR CMAKE_SYSTEM_NAME STREQUAL "NetBSD"))
    target_link_libraries(mangos-game dl)
  endif()
endif()

add_dependencies(mangos-game revision.h)
