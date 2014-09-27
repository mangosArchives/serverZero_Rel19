# This code is part of MaNGOS. Contributor & Copyright details are in AUTHORS/THANKS.
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

set(LIBRARY_NAME game)

add_definitions(-DDT_POLYREF64)

include_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}/AuctionHouseBot"
  "${CMAKE_CURRENT_SOURCE_DIR}/BattleGround"
  "${CMAKE_CURRENT_SOURCE_DIR}/ChatCommands"
  "${CMAKE_CURRENT_SOURCE_DIR}/MotionGenerators"
  "${CMAKE_CURRENT_SOURCE_DIR}/Object"
  "${CMAKE_CURRENT_SOURCE_DIR}/OutdoorPvP"
  "${CMAKE_CURRENT_SOURCE_DIR}/References"
  "${CMAKE_CURRENT_SOURCE_DIR}/Server"
  "${CMAKE_CURRENT_SOURCE_DIR}/Tools"
  "${CMAKE_CURRENT_SOURCE_DIR}/vmap"
  "${CMAKE_CURRENT_SOURCE_DIR}/WorldHandlers"
  "${CMAKE_SOURCE_DIR}/dep/include/g3dlite"
  "${CMAKE_SOURCE_DIR}/dep/recastnavigation/Detour"
  "${CMAKE_SOURCE_DIR}/dep/recastnavigation/"
  "${CMAKE_SOURCE_DIR}/dep/include"
  "${CMAKE_SOURCE_DIR}/src/shared"
  "${CMAKE_SOURCE_DIR}/src/framework"
  "${CMAKE_BINARY_DIR}"
  "${CMAKE_BINARY_DIR}/src/shared"
  "${MYSQL_INCLUDE_DIR}"
  "${ACE_INCLUDE_DIR}"
)

if(PCH)
  include_directories("${CMAKE_CURRENT_BINARY_DIR}")
endif()

set(LIBRARY_SRCS
  pchdef.cpp
  pchdef.h
)

#AH Bot group
file(GLOB SRC_AHBOT AuctionHouseBot/*.cpp AuctionHouseBot/*.h)
  LIST(APPEND LIBRARY_SRCS ${SRC_AHBOT})
  source_group("AhBot" FILES ${SRC_AHBOT})

#Battlegrounds group
file(GLOB SRC_BATTLEGROUND BattleGround/*.cpp BattleGround/*.h)
  LIST(APPEND LIBRARY_SRCS ${SRC_BATTLEGROUND})
  source_group("BattleGround" FILES ${SRC_BATTLEGROUND})

#Chat Commands group
file(GLOB SRC_CHAT_COMMANDS ChatCommands/*.cpp ChatCommands/*.h)
  LIST(APPEND LIBRARY_SRCS ${SRC_CHAT_COMMANDS})
  source_group("Chat Commands" FILES ${SRC_CHAT_COMMANDS})

#Motion Generator group
file(GLOB SRC_MOTION_GEN MotionGenerators/*.cpp MotionGenerators/*.h)
  LIST(APPEND LIBRARY_SRCS ${SRC_MOTION_GEN})
  source_group("Motion generators" FILES ${SRC_MOTION_GEN})

#Movement group
file(GLOB SRC_MOVEMENT movement/*.cpp movement/*.h)
  LIST(APPEND LIBRARY_SRCS ${SRC_MOVEMENT})
  source_group("Movement" FILES ${SRC_MOVEMENT})

#Object group
file(GLOB SRC_OBJECT Object/*.cpp Object/*.h)
  LIST(APPEND LIBRARY_SRCS ${SRC_OBJECT})
  source_group("Object" FILES ${SRC_OBJECT})	

#Outdoors PvP group
file(GLOB SRC_OUTDOOR_PVP OutdoorPvP/*.cpp OutdoorPvP/*.h)
  LIST(APPEND LIBRARY_SRCS ${SRC_OUTDOOR_PVP})
  source_group("Outdoor PvP" FILES ${SRC_OUTDOOR_PVP})

#References group
file(GLOB SRC_REFERENCES References/*.cpp References/*.h)
  LIST(APPEND LIBRARY_SRCS ${SRC_REFERENCES})
  source_group("References" FILES ${SRC_REFERENCES})

#Server group
file(GLOB SRC_SERVER Server/*.cpp Server/*.h)
  LIST(APPEND LIBRARY_SRCS ${SRC_SERVER})
  source_group("Server" FILES ${SRC_SERVER})
	
#Tools group
file(GLOB SRC_TOOL Tools/*.cpp Tools/*.h)
  LIST(APPEND LIBRARY_SRCS ${SRC_TOOL})
  source_group("Tool" FILES ${SRC_TOOL})

#VMap group
file(GLOB SRC_VMAPS vmap/*.cpp vmap/*.h)
  LIST(APPEND LIBRARY_SRCS ${SRC_VMAPS})
  source_group("VMaps" FILES ${SRC_VMAPS})
	
#World and Handlers group
file(GLOB SRC_WORLD_HANDLERS WorldHandlers/*.cpp WorldHandlers/*.h)
  LIST(APPEND LIBRARY_SRCS ${SRC_WORLD_HANDLERS})
  source_group("World/Handlers" FILES ${SRC_WORLD_HANDLERS})

add_library(${LIBRARY_NAME} STATIC ${LIBRARY_SRCS})

target_link_libraries(${LIBRARY_NAME}
  shared
  detour
)

if(UNIX)
  # Both systems don't have libdl and don't need them
  if (NOT (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD" OR CMAKE_SYSTEM_NAME STREQUAL "NetBSD"))
    target_link_libraries(${LIBRARY_NAME} dl)
  endif()
endif()

add_dependencies(${LIBRARY_NAME} revision.h)

if(NOT ACE_USE_EXTERNAL)
  add_dependencies(${LIBRARY_NAME} ace)
endif()

# Generate precompiled header
if(PCH)
  if(MSVC OR XCODE)
    if(MSVC)
      set(game_pch "${CMAKE_CURRENT_SOURCE_DIR}/pchdef.cpp")
    endif()
    add_native_precompiled_header(${LIBRARY_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/pchdef.h)
  elseif(CMAKE_COMPILER_IS_GNUCXX)
    add_precompiled_header(${LIBRARY_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/pchdef.h)
    if(NOT ACE_USE_EXTERNAL)
      add_dependencies(game_pch_dephelp ace)
    endif()
  endif()
endif()

add_subdirectory(AuctionHouseBot)

if(SCRIPT_LIB_SD2)
  include_directories("${CMAKE_SOURCE_DIR}/src/modules/SD2")
  target_link_libraries(${LIBRARY_NAME} mangosscript)
  add_dependencies(${LIBRARY_NAME} mangosscript)
endif()

#Eluna specific start
if(SCRIPT_LIB_ELUNA)
# install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/modules/Eluna/extensions DESTINATION ${BIN_DIR}/lua_scripts/)
  include_directories(
    "${CMAKE_SOURCE_DIR}/dep/lualib"
    "${CMAKE_SOURCE_DIR}/src/modules/Eluna"
  )

  target_link_libraries(${LIBRARY_NAME} LuaEngine)
  target_link_libraries(${LIBRARY_NAME} lualib)
endif()
#Eluna specific end
