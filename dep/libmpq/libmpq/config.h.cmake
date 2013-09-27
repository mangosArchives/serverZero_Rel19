#ifndef _LIBMPQ_CONFIG_H
#define _LIBMPQ_CONFIG_H

/* Define to 1 if you have the <dlfcn.h> header file. */
#cmakedefine HAVE_DLFCN_H 1

/* Define to 1 if fseeko (and presumably ftello) exists and is declared. */
#cmakedefine HAVE_FSEEKO 1

/* Define to 1 if you have the <inttypes.h> header file. */
#cmakedefine HAVE_INTTYPES_H 1

/* Define to 1 if you have the `bz2' library (-lbz2). */
#cmakedefine HAVE_LIBBZ2 1

/* Define to 1 if you have the `z' library (-lz). */
#cmakedefine HAVE_LIBZ 1

/* Define to 1 if you have the <memory.h> header file. */
#cmakedefine HAVE_MEMORY_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#cmakedefine HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#cmakedefine HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#cmakedefine HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#cmakedefine HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#cmakedefine HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#cmakedefine HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#cmakedefine HAVE_UNISTD_H 1

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#cmakedefine LT_OBJDIR

/* Name of package */
#cmakedefine PACKAGE "${PACKAGE}"

/* Define to the address where bug reports for this package should be sent. */
#cmakedefine PACKAGE_BUGREPORT "${PACKAGE_BUGREPORT}"

/* Define to the full name of this package. */
#cmakedefine PACKAGE_NAME "${PACKAGE_NAME}"

/* Define to the full name and version of this package. */
#cmakedefine PACKAGE_STRING "${PACKAGE_STRING}"

/* Define to the one symbol short name of this package. */
#cmakedefine PACKAGE_TARNAME "${PACKAGE_TARNAME}"

/* Define to the home page for this package. */
#cmakedefine PACKAGE_URL "${PACKAGE_URL}"

/* Define to the version of this package. */
#cmakedefine PACKAGE_VERSION "${PACKAGE_VERSION}"

/* Define to 1 if you have the ANSI C header files. */
#cmakedefine STDC_HEADERS 1

/* Version number of package */
#cmakedefine VERSION "${VERSION}"

/* Number of bits in a file offset, on hosts where this is settable. */
#cmakedefine _FILE_OFFSET_BITS ${_FILE_OFFSET_BITS}

/* Define to 1 to make fseeko visible on some hosts (e.g. glibc 2.2). */
#cmakedefine _LARGEFILE_SOURCE 1

/* Define for large files, on AIX-style hosts. */
#cmakedefine _LARGE_FILES 1

#endif
