# - Try to find Termcap
# Once done this will define
#
#  TERMCAP_FOUND        - system has Termcap
#  TERMCAP_INCLUDE_DIR  - the Termcap include directory
#  TERMCAP_LIBRARIES    - Link these to use Termcap

FIND_PATH(TERMCAP_INCLUDE_DIR bzlib.h )

FIND_LIBRARY(TERMCAP_LIBRARIES NAMES termcap )

# handle the QUIETLY and REQUIRED arguments and set TERMCAP_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Termcap DEFAULT_MSG TERMCAP_LIBRARIES TERMCAP_INCLUDE_DIR)

IF (TERMCAP_FOUND)
    MESSAGE(STATUS "Found GNU termcap: ${TERMCAP_INCLUDE_DIR}, ${TERMCAP_LIBRARIES}")
ENDIF (TERMCAP_FOUND)

MARK_AS_ADVANCED(TERMCAP_INCLUDE_DIR TERMCAP_LIBRARIES)
