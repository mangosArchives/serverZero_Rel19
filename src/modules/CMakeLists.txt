#-----------------------------------------------------------------------------
# Build the mangos-zero script library if wished for
if(ENABLE_SD2)
    add_subdirectory(SD2)
endif()

#-----------------------------------------------------------------------------
# Build the Eluna library if wished for
if(ENABLE_ELUNA)
    add_subdirectory(Eluna)
endif()