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
# Define the framework library
set(sources
    Policies/ObjectLifeTime.cpp

    Utilities/EventProcessor.cpp
)
set(headers
    Dynamic/FactoryHolder.h
    Dynamic/ObjectRegistry.h

    GameSystem/Grid.h
    GameSystem/GridLoader.h
    GameSystem/GridReference.h
    GameSystem/GridRefManager.h
    GameSystem/NGrid.h
    GameSystem/TypeContainer.h
    GameSystem/TypeContainerFunctions.h
    GameSystem/TypeContainerVisitor.h

    Platform/CompilerDefs.h
    Platform/Define.h

    Policies/CreationPolicy.h
    Policies/ObjectLifeTime.h
    Policies/Singleton.h
    Policies/ThreadingModel.h

    Utilities/ByteConverter.h
    Utilities/Callback.h
    Utilities/EventProcessor.h
    Utilities/LinkedList.h
    Utilities/LinkedReference/Reference.h
    Utilities/LinkedReference/RefManager.h
    Utilities/TypeList.h
    Utilities/UnorderedMapSet.h
)

set(framework_LIB_SRCS ${sources} ${headers})

mangos_source_group(${framework_LIB_SRCS})

include_directories(
    ${ACE_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

#-----------------------------------------------------------------------------
# Build the framework library
add_library(mangos-framework STATIC ${framework_LIB_SRCS})
target_link_libraries(mangos-framework ${ACE_LIBRARIES})

set(BUILD_PROPERTIES "")
if(${CMAKE_BUILD_TYPE} MATCHES Debug)
    set(BUILD_PROPERTIES "${BUILD_PROPERTIES} -DMANGOS_DEBUG")
    set_target_properties(mangos-framework PROPERTIES COMPILE_FLAGS ${BUILD_PROPERTIES})
endif()
