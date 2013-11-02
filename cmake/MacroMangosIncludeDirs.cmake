# Nicer makefiles with -I/1/foo/ instead of -I/1/2/3/../../foo/
# use it instead of include_directories()
macro(mangos_include_dirs
    includes)
    set(_ALL_INCS "")
    foreach(_INC ${ARGV})
        get_filename_component(_ABS_INC ${_INC} ABSOLUTE)
        list(APPEND _ALL_INCS ${_ABS_INC})
        # for checking for invalid includes, disable for regular use
        ##if(NOT EXISTS "${_ABS_INC}/")
        ##  message(FATAL_ERROR "Include not found: ${_ABS_INC}/")
        ##endif()
    endforeach()
    include_directories(${_ALL_INCS})
    unset(_INC)
    unset(_ABS_INC)
    unset(_ALL_INCS)
endmacro()
