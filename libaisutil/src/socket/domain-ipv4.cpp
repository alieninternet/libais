/* $Id$
 * IPv4 domain
 * 
 * Copyright (c) 1999,2002,2003 Alien Internet Services
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

#include <cstring>

extern "C" {
#ifdef HAVE_SYS_SOCKET_H
# include <sys/socket.h>
#endif
#ifdef HAVE_NETINET_IN_H
# include <netinet/in.h>
#endif
#ifdef HAVE_ARPA_INET_H
# include <arpa/inet.h>
#endif
};

# include "aisutil/socket/domain-ipv4.h"

using namespace AISutil;


/* SocketDomainIPv4 - Blank boring constructor!
 * Original 06/02/1999 simonb
 */
SocketDomainIPv4::SocketDomainIPv4(void)
{
   // Clean the addresses
   (void)memset(&remoteAddress, 0, sizeof(remoteAddress));
   (void)memset(&localAddress, 0, sizeof(localAddress));
   
   // Fix the address family types
   remoteAddress.sin_family = localAddress.sin_family = AF_INET;
   
   // Set the default addresses ("anything")
   remoteAddress.sin_addr.s_addr = localAddress.sin_addr.s_addr = INADDR_ANY;
}


/* SocketDomainIPv4 - Constructor used when accept()ing a connection
 * Original 06/07/2002 simonb
 */
SocketDomainIPv4::SocketDomainIPv4(const sockaddr_in& newLocalAddress,
				   const sockaddr_in& newRemoteAddress)
{
   (void)memcpy(&localAddress, &newLocalAddress, sizeof(localAddress));
   (void)memcpy(&remoteAddress, &newRemoteAddress, sizeof(remoteAddress));
}


/* setAddress - Set the given address in the given address structure
 * Original 03/07/2002 simonb
 */
bool SocketDomainIPv4::setAddress(sockaddr_in& addr, 
				  const std::string& addrstr)
{
   // Try to process the IP, checking if it worked okay
   if (inet_aton(addrstr.c_str(), &addr.sin_addr) != 0) {
      return true;
   }

   setErrorMessage();
   return false;
}


/* setAddress - Copy the given address over the given address structure
 * Original 03/07/2002 simonb
 */
bool SocketDomainIPv4::setAddress(sockaddr_in& addr,
				  const sockaddr_in& newaddr)
{
   // Copy it!
   (void)memcpy(&addr, &newaddr, sizeof(addr));
   
   // It worked.. well at least we will presume it is okay
   return true;
}


/* setAddress - Copy the given address over the given address structure's
 * Original 05/07/2002 simonb
 */
bool SocketDomainIPv4::setAddress(sockaddr_in& addr, const in_addr& newaddr)
{
   // Copy it!
   (void)memcpy(&addr.sin_addr, &newaddr, sizeof(addr.sin_addr));
   
   // It worked.. well at least we will presume it is okay
   return true;
}


/* setPort - Set the given port in the given address structure
 * Original 03/07/2002 simonb
 */
bool SocketDomainIPv4::setPort(sockaddr_in& addr, const int port)
{
   // Make sure the port is within an acceptable range (0..65534)
   if ((port >= 0) && (port <= 65534)) {
      addr.sin_port = htons(port);
      return true;
   }

   setErrorMessage("Port must be between 0 and 65536");
   return false;
}


/* bind - Bind a socket to its port
 * Original 03/07/2002 simonb
 */
bool SocketDomainIPv4::bind(void)
{
   if (::bind(getFD(), (sockaddr*)&localAddress, sizeof(localAddress)) == 0) {
      return true;
   }
   
   setErrorMessage();
   return false;
}


/* connect - Connect this socket
 * Original 03/07/2002 simonb
 */
bool SocketDomainIPv4::connect(void)
{
   if (::connect(getFD(), (sockaddr*)&remoteAddress,
		 sizeof(localAddress)) == 0) {
      return true;
   }
   
   setErrorMessage();
   return false;
}
