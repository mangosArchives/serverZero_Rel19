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
# Define the vmap-extractor application
file(GLOB sources *.cpp)
file(GLOB headers *.h)

set(vmap_extractor_LIB_SRCS ${sources} ${headers})

mangos_source_group(${vmap_extractor_LIB_SRCS})

include_directories(
    ${ZLIB_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/dep/libmpq/
    ${CMAKE_CURRENT_SOURCE_DIR}/loadlib/
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

#-----------------------------------------------------------------------------
# Build the vmap-extractor application
add_executable(vmap-extractor ${vmap_extractor_LIB_SRCS})
target_link_libraries(vmap-extractor mpq ${BZIP2_LIBRARIES} ${ZLIB_LIBRARIES})
install(TARGETS vmap-extractor DESTINATION ${BIN_DIR})

if(WIN32)
    # Disabled for now. GnuWin32-zlib does not need this
    # set(BUILD_PROPERTIES "-DZLIB_WINAPI" )
    # set_target_properties(vmap-extractor PROPERTIES COMPILE_FLAGS ${BUILD_PROPERTIES})
endif()
