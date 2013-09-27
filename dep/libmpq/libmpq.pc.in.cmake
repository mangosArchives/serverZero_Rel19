prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=${prefix}
libdir=${exec_prefix}/lib
includedir=${prefix}/include

Name: libmpq
Description: GPL version of the libmpq library
Version: @VERSION@
Libs: -L${libdir} -lmpq
Cflags: -I${includedir}/libmpq @LFS_CFLAGS@
