macro(mangos_source_group
    sources)

    # Group by location on disk
    source_group("Source Files" FILES CMakeLists.txt)

    foreach(_SRC ${sources})
        get_filename_component(_SRC_EXT ${_SRC} EXT)
        if((${_SRC_EXT} MATCHES ".h") OR
           (${_SRC_EXT} MATCHES ".hpp") OR
           (${_SRC_EXT} MATCHES ".hh"))
            source_group("Header Files" FILES ${_SRC})
        elseif((${_SRC_EXT} MATCHES ".rc") OR
            (${_SRC_EXT} MATCHES ".ico"))
            source_group("Resource Files" FILES ${_SRC})
        else()
            source_group("Source Files" FILES ${_SRC})
        endif()
    endforeach()

    unset(_SRC)
    unset(_SRC_EXT)
endmacro()
