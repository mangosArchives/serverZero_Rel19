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

set(EXECUTABLE_NAME mmap-generator)

ADD_DEFINITIONS(-DMMAP_GENERATOR -DNO_CORE_FUNCS)

IF(DEBUG)
    ADD_DEFINITIONS( -DDEBUG )
ENDIF()

# zlib
if(WIN32 AND MSVC)
    ADD_DEFINITIONS( -DNO_vsnprintf )
ENDIF()

include_directories(
    ${CMAKE_SOURCE_DIR}/dep/include/g3dlite
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Detour/Include
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Recast/Include
    ${CMAKE_SOURCE_DIR}/dep/src/zlib
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/shared
    ${CMAKE_SOURCE_DIR}/src/game
    ${CMAKE_SOURCE_DIR}/src/game/vmap
    ${CMAKE_SOURCE_DIR}/src/framework
)

add_library(zlib
    ${CMAKE_SOURCE_DIR}/dep/src/zlib/adler32.c
    ${CMAKE_SOURCE_DIR}/dep/src/zlib/compress.c
    ${CMAKE_SOURCE_DIR}/dep/src/zlib/crc32.c
    ${CMAKE_SOURCE_DIR}/dep/src/zlib/deflate.c
    ${CMAKE_SOURCE_DIR}/dep/src/zlib/example.c
    ${CMAKE_SOURCE_DIR}/dep/src/zlib/gzio.c
    ${CMAKE_SOURCE_DIR}/dep/src/zlib/infback.c
    ${CMAKE_SOURCE_DIR}/dep/src/zlib/inffast.c
    ${CMAKE_SOURCE_DIR}/dep/src/zlib/inflate.c
    ${CMAKE_SOURCE_DIR}/dep/src/zlib/inftrees.c
    ${CMAKE_SOURCE_DIR}/dep/src/zlib/trees.c
    ${CMAKE_SOURCE_DIR}/dep/src/zlib/uncompr.c
    ${CMAKE_SOURCE_DIR}/dep/src/zlib/zutil.c
)

add_library(Detour
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Detour/Source/DetourAlloc.cpp
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Detour/Source/DetourCommon.cpp
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Detour/Source/DetourNavMesh.cpp
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Detour/Source/DetourNavMeshBuilder.cpp
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Detour/Source/DetourNavMeshQuery.cpp
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Detour/Source/DetourNode.cpp
)

add_library(Recast
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Recast/Source/Recast.cpp
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Recast/Source/RecastAlloc.cpp
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Recast/Source/RecastArea.cpp
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Recast/Source/RecastContour.cpp
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Recast/Source/RecastFilter.cpp
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Recast/Source/RecastMesh.cpp
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Recast/Source/RecastMeshDetail.cpp
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Recast/Source/RecastRasterization.cpp
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Recast/Source/RecastRegion.cpp
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/IntermediateValues.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/generator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MapBuilder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TerrainBuilder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/VMapExtensions.cpp
)

add_executable( ${EXECUTABLE_NAME} ${SOURCES} )
target_link_libraries( ${EXECUTABLE_NAME} g3dlite vmap Detour Recast zlib )
install(TARGETS ${EXECUTABLE_NAME} DESTINATION ${BIN_DIR})
