# $Id$
# Top make rules
#


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
	include/aisutil/config/data.h \
	include/aisutil/config/parser.h \
	include/aisutil/socket/domain-ipv4.h \
	include/aisutil/socket/domain-ipv6.h \
	include/aisutil/socket/domain-ipx.h \
	include/aisutil/socket/domain-unix.h \
	include/aisutil/socket/domain.h \
	include/aisutil/socket/ipv4-tcp.h \
	include/aisutil/socket/ipv6-tcp.h \
	include/aisutil/socket/ipx-spx.h \
	include/aisutil/socket/socket.h \
	include/aisutil/socket/sockets.h \
	include/aisutil/socket/type-seqpacket.h \
	include/aisutil/socket/type-stream.h \
	include/aisutil/socket/type.h \
	include/aisutil/socket/unix.h \
	include/aisutil/string/mask.h \
	include/aisutil/string/string.h \
	include/aisutil/string/tokens.h \
	include/aisutil/config.h \
	include/aisutil/aisutilconf.h \
	include/aisutil/socket.h \
	include/aisutil/string.h \
	include/aisutil/version.h \
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
	src/version.cpp



# Stuff that needs to go into the distribution but isn't implied
EXTRA_DIST=\
	include/aisutil/aisutilconf.h.in


	
# Stuff we don't want distributed
dist-hook:
	rm -rf $(distdir)/include/aisutil/aisutilconf.h
