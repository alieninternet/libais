dnl $Id$
dnl AutoConf configuration script for LibAISutil
dnl
dnl Copyright (c) 2001,2002,2003 Alien Internet Services
dnl
dnl This file is a part of LibAISutil.
dnl 
dnl LibAISutil is free software; you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 2 of the License, or
dnl (at your option) any later version.
dnl 
dnl LibAISutil is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl 
dnl You should have received a copy of the GNU General Public License
dnl along with LibAISutil; if not, write to the Free Software
dnl Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


dnl -------------------------------------------------------------------------
dnl  Getting ready to configure...
dnl -------------------------------------------------------------------------
dnl Initialise the autoconf/automake things
AC_INIT([LibAISutil], [1.3.pre], [libaisutil@alien.net.au])
AM_INIT_AUTOMAKE([1.6.1 foreign no-installinfo no-installman nostdinc subdir-objects])
AC_COPYRIGHT([Portions Copyright (c) 2001,2002 Alien Internet Services])
AC_PREREQ(2.57)
AC_CONFIG_AUX_DIR(config)
AM_CONFIG_HEADER(include/config.h)
AC_REVISION([$Revision$])

dnl Determine our version information.
dnl These should not be touched as they define the version of this software
dnl from an 'official' standpoint - only the developers who should touch 
dnl them .. uhh.. should touch them :)
VERSION_MAJOR=1
VERSION_MINOR=3
VERSION_EXTRA=.pre

LIB_VERSION=1
LIB_REVISION=1
LIB_AGE=0

dnl Export our version information
AC_DEFINE(LIBAISUTIL_VERSION_NAME, "LibAISutil",
          [Package name (untouched)])
AC_DEFINE_UNQUOTED(LIBAISUTIL_VERSION_MAJOR, $VERSION_MAJOR,
                   [Major version number])
AC_DEFINE_UNQUOTED(LIBAISUTIL_VERSION_MINOR, $VERSION_MINOR,
                   [Minor version number])
AC_DEFINE_UNQUOTED(LIBAISUTIL_VERSION_EXTRA, "$VERSION_EXTRA",
                   [Optional additional version info])
AC_DEFINE_UNQUOTED(LIBAISUTIL_VERSION_STRING,
                   "$VERSION_MAJOR.$VERSION_MINOR$VERSION_EXTRA",
                   [Compiled version string for convenience sake])
AC_SUBST(LIB_VERSION)
AC_DEFINE_UNQUOTED(LIBAISUTIL_LIB_VERSION, $LIB_VERSION,
                   [Library version number])
AC_SUBST(LIB_REVISION)
AC_DEFINE_UNQUOTED(LIBAISUTIL_LIB_REVISION, $LIB_REVISION,
                   [Library revision number])
AC_SUBST(LIB_AGE)
AC_DEFINE_UNQUOTED(LIBAISUTIL_LIB_AGE, $LIB_AGE,
                   [Library age number])


dnl -------------------------------------------------------------------------
dnl  Checking for programs we need
dnl -------------------------------------------------------------------------
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LN_S
AC_CHECK_PROG(RM, rm, rm -f, del)
AC_CHECK_PROG(LD, ld, ld)
AC_CACHE_SAVE


dnl -------------------------------------------------------------------------
dnl  Checking compiler and system characteristics
dnl -------------------------------------------------------------------------
dnl AC_AIX
dnl AC_MINIX
dnl AC_ISC_POSIX
AC_SYS_LONG_FILE_NAMES
AC_EXEEXT
AC_OBJEXT
AC_C_BIGENDIAN
AC_C_CONST
AC_C_INLINE
AC_CACHE_SAVE


dnl -------------------------------------------------------------------------
dnl  Configure libtool utility
dnl -------------------------------------------------------------------------
AC_DISABLE_FAST_INSTALL
AC_LIBTOOL_DLOPEN
dnl AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL


dnl -------------------------------------------------------------------------
dnl  Checking structures and types
dnl -------------------------------------------------------------------------
AC_TYPE_SIZE_T
AC_CACHE_SAVE


dnl -------------------------------------------------------------------------
dnl  Checking for header files
dnl -------------------------------------------------------------------------
AC_HEADER_STDC
AC_HEADER_DIRENT
AC_CHECK_HEADERS( \
	arpa/inet.h \
	fcntl.h \
	fnmatch.h \
	netdb.h \
	netinet/in.h \
	netipx/ipx.h \
	sys/types.h \
	sys/socket.h \
	sys/un.h \
	unistd.h \
		)
AC_CACHE_SAVE


dnl -------------------------------------------------------------------------
dnl  Checking for libraries and specific library functions
dnl -------------------------------------------------------------------------
AC_FUNC_FNMATCH
AC_CHECK_FUNCS(
	inet_ntoa \
	memset \
	socket \
		)

AC_CACHE_CHECK([for a working C++ Standard Template Library],
 libaisutil_cv_lib_stl_ok,[
  AC_LANG_CPLUSPLUS
  AC_TRY_RUN([
	#include <string>
	#include <list>
	#include <map>
	
	int main(void)
	{
	   std::string foo;
	   foo = "Hello";
	
	   std::list <int> l;
	   l.clear();
	   
	   std::map <int, int> m;
	   m.clear();
	}
   ],[
     libaisutil_cv_lib_stl_ok=yes
   ],[
     libaisutil_cv_lib_stl_ok=no
   ])
 ])
if test "$libaisutil_cv_lib_stl_ok" = "no"; then
  AC_MSG_ERROR([Sorry, you need a working Standard Template Library])
fi

AC_CACHE_CHECK([for std::string::clear()],
 libaisutil_cv_lib_stl_string_clear,[
  AC_LANG_CPLUSPLUS
  AC_TRY_RUN([
	#include <string>
	
	int main(void)
	{
	   std::string foo("test");
	   foo.clear();
	   if (!foo.empty()) {
	      exit(1); // eek
	   }
	}
   ],[
     libaisutil_cv_lib_stl_string_clear=yes
   ],[
     libaisutil_cv_lib_stl_string_clear=no
   ])
 ])
if test "$libaisutil_cv_lib_stl_string_clear" = "yes"; then
  AC_SUBST(LIBAISUTIL_DEFINE__LIBAISUTIL_STL_STRING_CLEAR,
           ["# define LIBAISUTIL_STL_STRING_CLEAR 1"])
else
  AC_SUBST(LIBAISUTIL_DEFINE__LIBAISUTIL_STL_STRING_CLEAR,
           ["/* # define LIBAISUTIL_STL_STRING_CLEAR */"])
fi

AC_CACHE_CHECK([for an SGI compliant hash capability in your STL],
 libaisutil_cv_lib_stl_sgi_hash,[
  AC_LANG_CPLUSPLUS
  AC_TRY_RUN([
	#include <hash_map>

	int main(void)
 	{
	   std::hash_map <int, int> hm;
	   hm.clear();
	}
   ],[
     libaisutil_cv_lib_stl_sgi_hash=yes
   ],[
     libaisutil_cv_lib_stl_sgi_hash=no
   ])
 ])
if test "$libaisutil_cv_lib_stl_sgi_hash" = "yes"; then
  AC_SUBST(LIBAISUTIL_DEFINE__LIBAISUTIL_STL_HAS_HASH,
           ["# define LIBAISUTIL_STL_HAS_HASH 1"])
else
  AC_SUBST(LIBAISUTIL_DEFINE__LIBAISUTIL_STL_HAS_HASH,
           ["/* # define LIBAISUTIL_STL_HAS_HASH */"])
fi

AC_CACHE_SAVE


dnl -------------------------------------------------------------------------
dnl  Determining compilation configuration parameters
dnl -------------------------------------------------------------------------
dnl Maintainer mode?
AM_MAINTAINER_MODE

dnl
dnl Which transports do we require
dnl
AC_MSG_CHECKING([transport-tcp-ipv4 parameter])
AC_ARG_ENABLE(transport-tcp-ipv4,
              AC_HELP_STRING([--disable-transport-tcp-ipv4],
                             [Disable TCP/IPv4 sockets]),
 [
   if test "$enableval" = "no"; then
     AC_MSG_RESULT(no)
   else
     AC_MSG_RESULT(yes)
     libaisutil_test_compile_socket_ipv4_tcp=yes
     libaisutil_test_compile_socket_domain_ipv4=yes
     libaisutil_test_compile_socket_type_stream=yes
   fi
 ],[
   AC_MSG_RESULT([yes (default)])
   libaisutil_test_compile_socket_ipv4_tcp=yes
   libaisutil_test_compile_socket_domain_ipv4=yes
   libaisutil_test_compile_socket_type_stream=yes
 ])
if test "$libaisutil_test_compile_socket_ipv4_tcp" = "yes"; then
  AC_SUBST(LIBAISUTIL_DEFINE__LIBAISUTIL_HAVE_SOCKET_IPV4_TCP,
           ["# define LIBAISUTIL_HAVE_SOCKET_IPV4_TCP 1"])
else
  AC_SUBST(LIBAISUTIL_DEFINE__LIBAISUTIL_HAVE_SOCKET_IPV4_TCP,
           ["/* # define LIBAISUTIL_HAVE_SOCKET_IPV4_TCP */"])
fi

AC_MSG_CHECKING([transport-tcp-ipv6 parameter])
AC_ARG_ENABLE(transport-tcp-ipv6,
              AC_HELP_STRING([--enable-transport-tcp-ipv6],
                             [Enable TCP/IPv6 sockets]),
 [
   if test "$enableval" = "no"; then
     AC_MSG_RESULT(no)
   else
     AC_MSG_RESULT(yes)
     libaisutil_test_compile_socket_ipv6_tcp=yes
     libaisutil_test_compile_socket_domain_ipv6=yes
     libaisutil_test_compile_socket_type_stream=yes
   fi
 ],[
   AC_MSG_RESULT([no (default)])
 ])
if test "$libaisutil_test_compile_socket_ipv6_tcp" = "yes"; then
  AC_SUBST(LIBAISUTIL_DEFINE__LIBAISUTIL_HAVE_SOCKET_IPV6_TCP,
           ["# define LIBAISUTIL_HAVE_SOCKET_IPV6_TCP 1"])
else
  AC_SUBST(LIBAISUTIL_DEFINE__LIBAISUTIL_HAVE_SOCKET_IPV6_TCP,
           ["/* # define LIBAISUTIL_HAVE_SOCKET_IPV6_TCP */"])
fi

AC_MSG_CHECKING([transport-ipx-spx parameter])
AC_ARG_ENABLE(transport-ipx-spx,
              AC_HELP_STRING([--enable-transport-ipx-spx],
                             [Enable IPX/SPX sockets]),
 [
   if test "$enableval" = "no"; then
     AC_MSG_RESULT(no)
   else
     AC_MSG_RESULT(yes)
     libaisutil_test_compile_socket_ipx_spx=yes
     libaisutil_test_compile_socket_domain_ipx=yes
     libaisutil_test_compile_socket_type_seqpacket=yes
   fi
 ],[
   AC_MSG_RESULT([no (default)])
 ])
if test "$libaisutil_test_compile_socket_ipx_spx" = "yes"; then
  AC_SUBST(LIBAISUTIL_DEFINE__LIBAISUTIL_HAVE_SOCKET_IPX_SPX,
           ["# define LIBAISUTIL_HAVE_SOCKET_IPX_SPX 1"])
else
  AC_SUBST(LIBAISUTIL_DEFINE__LIBAISUTIL_HAVE_SOCKET_IPX_SPX,
           ["/* # define LIBAISUTIL_HAVE_SOCKET_IPX_SPX */"])
fi

AC_MSG_CHECKING([transport-unix parameter])
AC_ARG_ENABLE(transport-unix,
              AC_HELP_STRING([--enable-transport-unix],
                             [Enable UNIX sockets]),
 [
   if test "$enableval" = "no"; then
     AC_MSG_RESULT(no)
   else
     AC_MSG_RESULT(yes)
     libaisutil_test_compile_socket_unix=yes
     libaisutil_test_compile_socket_domain_unix=yes
     libaisutil_test_compile_socket_type_stream=yes
   fi
 ],[
   AC_MSG_RESULT([no (default)])
 ])
if test "$libaisutil_test_compile_socket_unix" = "yes"; then
  AC_SUBST(LIBAISUTIL_DEFINE__LIBAISUTIL_HAVE_SOCKET_UNIX,
           ["# define LIBAISUTIL_HAVE_SOCKET_UNIX 1"])
else
  AC_SUBST(LIBAISUTIL_DEFINE__LIBAISUTIL_HAVE_SOCKET_UNIX,
           ["/* # define LIBAISUTIL_HAVE_SOCKET_UNIX */"])
fi

dnl Fix up variables for automake to work out what to compile...
AM_CONDITIONAL(LIBAISUTIL_COMPILE_SOCKET_DOMAIN_IPV4,
               [test x$libaisutil_test_compile_socket_domain_ipv4 = xyes])
AM_CONDITIONAL(LIBAISUTIL_COMPILE_SOCKET_DOMAIN_IPV6,
               [test x$libaisutil_test_compile_socket_domain_ipv6 = xyes])
AM_CONDITIONAL(LIBAISUTIL_COMPILE_SOCKET_DOMAIN_IPX,
               [test x$libaisutil_test_compile_socket_domain_ipx = xyes])
AM_CONDITIONAL(LIBAISUTIL_COMPILE_SOCKET_DOMAIN_UNIX,
               [test x$libaisutil_test_compile_socket_domain_unix = xyes])
AM_CONDITIONAL(LIBAISUTIL_COMPILE_SOCKET_TYPE_STREAM,
               [test x$libaisutil_test_compile_socket_type_stream = xyes])
AM_CONDITIONAL(LIBAISUTIL_COMPILE_SOCKET_TYPE_SEQPACKET,
               [test x$libaisutil_test_compile_socket_type_seqpacket = xyes])
AM_CONDITIONAL(LIBAISUTIL_COMPILE_SOCKET_IPV4_TCP,
               [test x$libaisutil_test_compile_socket_ipv4_tcp = xyes])
AM_CONDITIONAL(LIBAISUTIL_COMPILE_SOCKET_IPV6_TCP,
               [test x$libaisutil_test_compile_socket_ipv6_tcp = xyes])
AM_CONDITIONAL(LIBAISUTIL_COMPILE_SOCKET_IPX_SPX,
               [test x$libaisutil_test_compile_socket_ipx_spx = xyes])
AM_CONDITIONAL(LIBAISUTIL_COMPILE_SOCKET_UNIX,
               [test x$libaisutil_test_compile_socket_unix = xyes])


dnl -------------------------------------------------------------------------
dnl  Creating files
dnl -------------------------------------------------------------------------
LDFLAGS="$LDFLAGS_SAVE"
AC_SUBST(INCDIRS)
AC_OUTPUT([
	include/aisutil/aisutilconf.h
	Makefile
	include/Makefile
	])
