/* $Id$
 * IPX/SPX transport
 * 
 * Copyright (c) 2001,2003 Alien Internet Services
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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

extern "C" {
#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif
#ifdef HAVE_SYS_SOCKET_H
# include <sys/socket.h>
#endif
};

#ifdef LIBAISUTIL_DEBUG_ASSERT
# include <cassert>
#endif

#include "aisutil/socket/ipx-spx.h"

using namespace AISutil;


/* accept - Accept a new connection on a socket
 * Original 02/01/2001 simonb
 */
Socket* SocketIPXSPX::accept(void)
{
#ifdef LIBAISUTIL_DEBUG_ASSERT
   // Make sure our file descriptor is real..
   assert(isOkay());
#endif
   
   struct sockaddr_ipx addr;
   socklen_t addrlen = sizeof(addr);
   
   int newFD = ::accept(getFD(), (sockaddr*)&addr, &addrlen);

   // Make sure that worked..
   if (newFD < 0) {
      // Return a null pointer
      setErrorMessage();
      return 0;
   }
   
#ifdef LIBAISUTIL_DEBUG_ASSERT
   // Make sure what we receive is really what we were expecting..
   assert(addrlen == sizeof(addr));
#endif
   
   // Return with the fresh socket
   return new SocketIPXSPX(newFD, getLocalAddressRef(), addr);
}
