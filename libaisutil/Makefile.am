# $Id$
# Top make rules
#


# Subdirs..
SUBDIRS=\
	include \
	.



# Include dir
INCLUDES=\
	-I$(top_builddir)/include



# Our target
lib_LTLIBRARIES=\
	libaisutil.la



# Work out anything we need to compile...
if LIBAISUTIL_COMPILE_SOCKET_DOMAIN_IPV4
 LIBAISUTIL_FILE_SOCKET_DOMAIN_IPV4=src/socket/domain-ipv4.cpp
endif
if LIBAISUTIL_COMPILE_SOCKET_DOMAIN_IPV6
 LIBAISUTIL_FILE_SOCKET_DOMAIN_IPV6=src/socket/domain-ipv6.cpp
endif
if LIBAISUTIL_COMPILE_SOCKET_DOMAIN_IPX
 LIBAISUTIL_FILE_SOCKET_DOMAIN_IPX=src/socket/domain-ipx.cpp
endif
if LIBAISUTIL_COMPILE_SOCKET_DOMAIN_UNIX
 LIBAISUTIL_FILE_SOCKET_DOMAIN_UNIX=src/socket/domain-unix.cpp
endif
if LIBAISUTIL_COMPILE_SOCKET_TYPE_STREAM
 LIBAISUTIL_FILE_SOCKET_TYPE_STREAM=src/socket/type-stream.cpp
endif
if LIBAISUTIL_COMPILE_SOCKET_TYPE_SEQPACKET
 LIBAISUTIL_FILE_SOCKET_TYPE_SEQPACKET=src/socket/type-seqpacket.cpp
endif
if LIBAISUTIL_COMPILE_SOCKET_IPV4_TCP
 LIBAISUTIL_FILE_SOCKET_IPV4_TCP=src/socket/ipv4-tcp.cpp
endif
if LIBAISUTIL_COMPILE_SOCKET_IPV6_TCP
 LIBAISUTIL_FILE_SOCKET_IPV6_TCP=src/socket/ipv6-tcp.cpp
endif
if LIBAISUTIL_COMPILE_SOCKET_IPX_SPX
 LIBAISUTIL_FILE_SOCKET_IPX_SPX=src/socket/ipx-spx.cpp
endif
if LIBAISUTIL_COMPILE_SOCKET_UNIX
 LIBAISUTIL_FILE_SOCKET_UNIX=src/socket/unix.cpp
endif


# Source files..
libaisutil_la_SOURCES=\
	src/config/data.cpp \
	src/config/parser.cpp \
	src/socket/socket.cpp \
	$(LIBAISUTIL_FILE_SOCKET_DOMAIN_IPV4) \
	$(LIBAISUTIL_FILE_SOCKET_DOMAIN_IPV6) \
	$(LIBAISUTIL_FILE_SOCKET_DOMAIN_IPX) \
	$(LIBAISUTIL_FILE_SOCKET_DOMAIN_UNIX) \
	$(LIBAISUTIL_FILE_SOCKET_TYPE_STREAM) \
	$(LIBAISUTIL_FILE_SOCKET_TYPE_SEQPACKET) \
	$(LIBAISUTIL_FILE_SOCKET_IPV4_TCP) \
	$(LIBAISUTIL_FILE_SOCKET_IPV6_TCP) \
	$(LIBAISUTIL_FILE_SOCKET_IPX_SPX) \
	$(LIBAISUTIL_FILE_SOCKET_UNIX) \
	src/string/string.cpp \
	src/string/tokens.cpp \
	src/string/mask.cpp \
	src/utils.cpp \
	src/version.cpp


# Flags used when linking the library
libaisutil_la_LDFLAGS=\
	-version-info @LIB_VERSION@:@LIB_REVISION@:@LIB_AGE@




# Stuff that needs to go into the distribution but isn't implied
EXTRA_DIST=\
	include/aisutil/aisutilconf.h.in


	
# Stuff we don't want distributed
dist-hook:
	rm -rf $(distdir)/include/aisutil/aisutilconf.h
