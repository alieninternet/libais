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

#include "config.h"

#include <cstring>
#include <cstdio>

extern "C" {
#ifdef HAVE_SYS_SOCKET_H
# include <sys/socket.h>
#endif
#ifdef HAVE_SYS_UN_H
# include <sys/un.h>
#endif
};

#include "aisutil/socket/domain-unix.h"

using namespace AIS::Util::Socket;

// If UNIX_PATH_MAX is still undefined, presume the normal 108 char value
#ifndef UNIX_PATH_MAX
# define UNIX_PATH_MAX 108
#endif


/* DomainUNIX - Blank boring constructor!
 * Original 13/05/2002 pickle
 */
DomainUNIX::DomainUNIX(void)
{
#ifdef HAVE_MEMSET
   // Clean the addresses
   (void)memset(&remoteAddress, 0, sizeof(remoteAddress));
   (void)memset(&localAddress, 0, sizeof(localAddress));
#endif
   
   // Fix the address family types
   remoteAddress.sun_family = localAddress.sun_family = AF_UNIX;
}


/* DomainUNIX - Constructor used when accept()ing a connection
 * Original 06/07/2002 pickle
 */
DomainUNIX::DomainUNIX(const sockaddr_un& _localAddress,
		       const sockaddr_un& _remoteAddress)
{
   (void)memcpy(&localAddress, &_localAddress, sizeof(localAddress));
   (void)memcpy(&remoteAddress, &_remoteAddress, sizeof(remoteAddress));
}


/* ~DomainUNIX - Destroy the pipe file
 * Original 16/07/2003 pickle
 */
DomainUNIX::~DomainUNIX(void)
{
   // Close the socket
   (void)::close(getFD());
   
   // Remove the unix file, we made one, and only if we can..
   if (localAddress.sun_path[0] != '\0') {
      (void)::remove(localAddress.sun_path);
   }
}


/* setAddress - Set the given address in the given address structure
 * Original 03/07/2002 pickle
 */
const bool DomainUNIX::setAddress(sockaddr_un& addr, 
				  const std::string& newaddr)
{
   // Make sure the length is appropriate
   if (newaddr.length() <= UNIX_PATH_MAX) {
      // Set the address
      (void)memcpy(addr.sun_path, newaddr.data(), newaddr.length());
      
      // The address was OK, return happily
      return true;
   }

   setErrorMessage("Address is too long");
   return false;
}


/* bind - Bind a socket to its port
 * Original 03/07/2002 pickle
 */
const bool DomainUNIX::bind(void)
{
   if (::bind(getFD(), (sockaddr*)&localAddress, sizeof(localAddress)) == 0) {
      return true;
   }
   
   setErrorMessage();
   return false;
}


/* connect - Connect this socket
 * Original 03/07/2002 pickle
 */
const bool DomainUNIX::connect(void)
{
   if (::connect(getFD(), (sockaddr*)&remoteAddress,
		 sizeof(localAddress)) == 0) {
      return true;
   }
   
   setErrorMessage();
   return false;
}
