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

include(CheckIncludeFile)
include(CheckFunctionExists)
include(CheckCSourceRuns)

set(VERSION "0.4.2")

#-----------------------------------------------------------------------------
# Check for required headers
if(NOT WIN32)
  CHECK_INCLUDE_FILE(dlfcn.h HAVE_DLFCN_H)
  CHECK_INCLUDE_FILE(inttypes.h HAVE_INTTYPES_H)
  CHECK_INCLUDE_FILE(memory.h HAVE_MEMORY_H)
  CHECK_INCLUDE_FILE(stdint.h HAVE_STDINT_H)
  CHECK_INCLUDE_FILE(stdlib.h HAVE_STDLIB_H)
  CHECK_INCLUDE_FILE(strings.h HAVE_STRINGS_H)
  CHECK_INCLUDE_FILE(string.h HAVE_STRING_H)
  CHECK_INCLUDE_FILE(sys/stat.h HAVE_SYS_STAT_H)
  CHECK_INCLUDE_FILE(sys/types.h HAVE_SYS_TYPES_H)
  CHECK_INCLUDE_FILE(unistd.h HAVE_UNISTD_H)
endif()

#-----------------------------------------------------------------------------
# Check for required functions
if(NOT WIN32)
  CHECK_FUNCTION_EXISTS(fseeko HAVE_FSEEKO)
endif()

#-----------------------------------------------------------------------------
# LFS Check (thanks to Kitware Systems)
if(NOT WIN32)
  CHECK_C_SOURCE_RUNS("
      #define _LARGEFILE_SOURCE
      #define _LARGEFILE64_SOURCE
      #define _LARGE_FILES
      #define _FILE_OFFSET_BITS 64
      #include <sys/types.h>
      #include <sys/stat.h>
      #include <assert.h>
      #include <stdio.h>

      int main(int argc, char **argv)
      {
        /* check that off_t can hold 2^63 - 1 and perform basic operations... */
      #define OFF_T_64 (((off_t) 1 << 62) - 1 + ((off_t) 1 << 62))
        if (OFF_T_64 % 2147483647 != 1)
          return 1;

        // stat breaks on SCO OpenServer
        struct stat buf;
        stat( argv[0], &buf );
        if (!S_ISREG(buf.st_mode))
          return 2;

        FILE *file = fopen( argv[0], \"r\" );
        off_t offset = ftello( file );
        fseek( file, offset, SEEK_CUR );
        fclose( file );
        return 0;
      }" TEST_LFS_WORKS)

  if (TEST_LFS_WORKS)
      set(_LARGEFILE_SOURCE 1)
      set(_LARGEFILE64_SOURCE 1)
      set(_LARGE_FILES 1)
      set(_FILE_OFFSET_BITS 64)
      set(LFS_CFLAGS -D_LARGE_FILES=1)
  endif (TEST_LFS_WORKS)
endif()
#-----------------------------------------------------------------------------
# libmpq.pc, libmpq-config
if (NOT WIN32)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libmpq.pc.in.cmake ${CMAKE_CURRENT_BINARY_DIR}/libmpq.pc @ONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libmpq-config.in.cmake ${CMAKE_CURRENT_BINARY_DIR}/libmpq-config  @ONLY)
endif()

#-----------------------------------------------------------------------------
# Install files
if (NOT WIN32)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libmpq.pc DESTINATION lib/pkgconfig)
  install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/libmpq-config DESTINATION bin)
endif()

#-----------------------------------------------------------------------------
# Add sources
add_subdirectory(libmpq)
