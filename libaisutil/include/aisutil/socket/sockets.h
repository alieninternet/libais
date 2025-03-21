/* $Id$
 * 
 * Copyright (c) 2002,2003 Alien Internet Services
 * 
 * This file is a part of LibAISutil.
 * 
 * LibAISutil is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * LibAISutil is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with LibAISutil; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _INCLUDE_LIBAISUTIL_SOCKET_SOCKETS_H_
# define _INCLUDE_LIBAISUTIL_SOCKET_SOCKETS_H_ 1

/*! \file
 * \brief Include available socket class headers
 * 
 * Depending on the system this library is configured/compiled for, you may
 * have support for all, some, or no socket types available within this
 * library.
 * 
 * This header is intended to be an aide when you need to use more than just
 * a specific type of socket, such as when you want to use IPv4 and/or IPv6
 * sockets in a program. This header will include all headers pertaining to
 * those socket types available within the library, as chosen at configuration
 * time.
 */

# include <aisutil/aisutilconf.h>

# ifdef LIBAISUTIL_HAVE_SOCKET_IPV4_TCP
#  include <aisutil/socket/ipv4-tcp.h>
# endif
# ifdef LIBAISUTIL_HAVE_SOCKET_IPV6_TCP
#  include <aisutil/socket/ipv6-tcp.h>
# endif
# ifdef LIBAISUTIL_HAVE_SOCKET_IPX_SPX
#  include <aisutil/socket/ipx-spx.h>
# endif
# ifdef LIBAISUTIL_HAVE_SOCKET_UNIX
#  include <aisutil/socket/unix.h>
# endif

#endif // _INCLUDE_LIBAISUTIL_SOCKET_SOCKETS_H_
