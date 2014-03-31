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
# Define the mpq library
file(GLOB sources *.c)
file(GLOB headers *.h)

if(WIN32 AND MSVC)
    file(GLOB win_headers ${CMAKE_CURRENT_SOURCE_DIR}/win/)
    set(mpq_LIB_SRCS ${sources} ${headers} ${win_headers})
else()
    set(mpq_LIB_SRCS ${sources} ${headers})
endif()

mangos_source_group(${mpq_LIB_SRCS})

include_directories(
    ${BZIP2_INCLUDE_DIR}
    ${ZLIB_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

if(WIN32 AND MSVC)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/win/)
endif()

#-----------------------------------------------------------------------------
# Generate config.h, libmpq.pc, libmpq-config
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h)

#-----------------------------------------------------------------------------
# Build the mpq library
if(WIN32)
    add_library(mpq STATIC ${mpq_LIB_SRCS})
else()
    add_library(mpq SHARED ${mpq_LIB_SRCS})
endif()
target_link_libraries(mpq ${BZIP2_LIBRARIES} ${ZLIB_LIBRARIES})
set_target_properties(mpq PROPERTIES VERSION "0.4.2")

if(WIN32)
    # Disabled for now. GnuWin32-zlib does not need this
    # set(BUILD_PROPERTIES "-DZLIB_WINAPI" )
    # set_target_properties(mpq PROPERTIES COMPILE_FLAGS ${BUILD_PROPERTIES})
endif()

#-----------------------------------------------------------------------------
# Install files
install(TARGETS mpq
    DESTINATION ${LIBS_DIR}
    LIBRARY DESTINATION ${LIBS_DIR}
)
install(FILES mpq.h
    DESTINATION include/libmpq
)
