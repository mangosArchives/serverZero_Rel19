# This code is part of MaNGOS. Contributor & Copyright details are in AUTHORS/THANKS.
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

# uncomment next line to disable debug mode
# ADD_DEFINITIONS("-DIOMAP_DEBUG")
# ADD_DEFINITIONS("-DNO_CORE_FUNCS")

set(EXECUTABLE_NAME vmap-assembler)

include_directories(
  ${CMAKE_SOURCE_DIR}/src/shared
  ${CMAKE_SOURCE_DIR}/src/game/vmap
  ${CMAKE_SOURCE_DIR}/dep/include/g3dlite
  ${CMAKE_SOURCE_DIR}/dep/ACE_wrappers
  ${CMAKE_SOURCE_DIR}/src/framework
  ${CMAKE_SOURCE_DIR}/src/framework
  ${ACE_INCLUDE_DIR}
  ${CMAKE_BINARY_DIR}
)

add_library(vmap
	${CMAKE_SOURCE_DIR}/src/game/vmap/BIH.cpp
	${CMAKE_SOURCE_DIR}/src/game/vmap/VMapManager2.cpp
	${CMAKE_SOURCE_DIR}/src/game/vmap/MapTree.cpp
	${CMAKE_SOURCE_DIR}/src/game/vmap/TileAssembler.cpp
	${CMAKE_SOURCE_DIR}/src/game/vmap/WorldModel.cpp
	${CMAKE_SOURCE_DIR}/src/game/vmap/ModelInstance.cpp
)

target_link_libraries(vmap shared framework g3dlite z ${ACE_LIBRARIES})

add_executable(${EXECUTABLE_NAME} vmap_assembler.cpp)
target_link_libraries(${EXECUTABLE_NAME} vmap)
install(TARGETS ${EXECUTABLE_NAME} DESTINATION ${BIN_DIR})

# add_executable(vmap_test coordinate_test.cpp)
# target_link_libraries(vmap_test vmap)
