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
	src/config/config.cpp \
	src/config/handle-misc.cpp \
	src/socket/socket.cpp \
	src/socket/stateful-type.cpp \
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
	src/sha1.cpp \
	src/time.cpp \
	src/utils.cpp \
	src/version.cpp


# Flags used when linking the library
libaisutil_la_LDFLAGS=\
	-version-info @LIB_VERSION@:@LIB_REVISION@:@LIB_AGE@




# Stuff that needs to go into the distribution but isn't implied
EXTRA_DIST=\
	include/aisutil/aisutilconf.h.in \
	test/README \
	test/test.conf


	
# Stuff we don't want distributed
dist-hook:
	rm -rf $(distdir)/include/aisutil/aisutilconf.h



##
##  Test suite
##

# The tests to run
TESTS=\
	test-config \
	test-peakcount \
	test-sha1 \
	test-string \
	test-stringmask \
	test-stringtokens \
	test-time \
	test-utils


# All of our tests are programs we need to build..
check_PROGRAMS=$(TESTS)


# Test programs' source files
test_config_SOURCES=\
	test/tests.h test/config.cpp
test_peakcount_SOURCES=\
	test/tests.h test/peakcount.cpp
test_sha1_SOURCES=\
	test/tests.h test/sha1.cpp
test_string_SOURCES=\
	test/tests.h test/string.cpp
test_stringmask_SOURCES=\
	test/tests.h test/stringmask.cpp
test_stringtokens_SOURCES=\
	test/tests.h test/stringtokens.cpp
test_time_SOURCES=\
	test/tests.h test/time.cpp
test_utils_SOURCES=\
	test/tests.h test/utils.cpp


# Test programs' libraries
test_config_LDADD=\
	libaisutil.la
#test_peakcount_LDADD=\
#	libaisutil.la
test_sha1_LDADD=\
	libaisutil.la
test_string_LDADD=\
	libaisutil.la
test_stringmask_LDADD=\
	libaisutil.la
test_stringtokens_LDADD=\
	libaisutil.la
test_time_LDADD=\
	libaisutil.la
test_utils_LDADD=\
	libaisutil.la
