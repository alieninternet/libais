/* $Id$
 * IPv6 domain
 * 
 * Copyright (c) 2001,2002,2003 Alien Internet Services
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
#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif
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

#include "aisutil/socket/domain-ipv6.h"

using namespace AISutil;


// This is used by the address to string translators (not very thread safe?)
static char addrbuff[INET6_ADDRSTRLEN + 1];


/* SocketDomainIPv6 - Blank boring constructor!
 * Original 19/08/2001 pickle
 */
SocketDomainIPv6::SocketDomainIPv6(void)
{
   // Clean the addresses
   (void)memset(&remoteAddress, 0, sizeof(remoteAddress));
   (void)memset(&localAddress, 0, sizeof(localAddress));
   
   // Fix the address family types
   remoteAddress.sin6_family = localAddress.sin6_family = AF_INET6;
   
   // Set the default addresses ("anything")
   (void)memcpy(&remoteAddress.sin6_addr, &in6addr_any, sizeof(in6addr_any));
   (void)memcpy(&localAddress.sin6_addr, &in6addr_any, sizeof(in6addr_any));
}

  
/* SocketDomainIPv6 - Constructor used when accept()ing a connection
 * Original 06/07/2002 pickle
 */
SocketDomainIPv6::SocketDomainIPv6(const sockaddr_in6& newLocalAddress,
				   const sockaddr_in6& newRemoteAddress)
{
   (void)memcpy(&localAddress, &newLocalAddress, sizeof(localAddress));
   (void)memcpy(&remoteAddress, &newRemoteAddress, sizeof(remoteAddress));
}


/* getRemoteAddressStr - Return the remote address as a string
 * Original 19/08/2001 pickle
 */
std::string SocketDomainIPv6::getRemoteAddress(void) const
{
   return inet_ntop(AF_INET6, &remoteAddress.sin6_addr, addrbuff,
		    INET6_ADDRSTRLEN + 1);
}


/* getLocalAddressStr - Return the local address as a string
 * Original 19/08/2001 pickle
 */
std::string SocketDomainIPv6::getLocalAddress(void) const
{
   return inet_ntop(AF_INET6, &localAddress.sin6_addr, addrbuff,
		    INET6_ADDRSTRLEN + 1);
}


/* setAddress - Set the given address in the given address structure
 * Original 03/07/2002 pickle
 */
bool SocketDomainIPv6::setAddress(sockaddr_in6& addr, 
				  const std::string& addrstr)
{
   // Try to process the IP, checking if it worked okay
   if (inet_pton(AF_INET6, addrstr.c_str(), &addr.sin6_addr) != 0) {
      return true;
   }

   setErrorMessage();
   return false;
}


/* setAddress - Copy the given address over the given address structure
 * Original 03/07/2002 pickle
 */
bool SocketDomainIPv6::setAddress(sockaddr_in6& addr,
				  const sockaddr_in6& newaddr)
{
   // Copy it!
   (void)memcpy(&addr, &newaddr, sizeof(addr));
   
   // It worked.. well at least we will presume it is okay
   return true;
}


/* setAddress - Copy the given address over the given address structure's
 * Original 05/07/2002 pickle
 */
bool SocketDomainIPv6::setAddress(sockaddr_in6& addr, const in6_addr& newaddr)
{
   // Copy it!
   (void)memcpy(&addr.sin6_addr, &newaddr, sizeof(addr.sin6_addr));
   
   // It worked.. well at least we will presume it is okay
   return true;
}


/* setPort - Set the given port in the given address structure
 * Original 03/07/2002 pickle
 */
bool SocketDomainIPv6::setPort(sockaddr_in6& addr, const int port)
{
   // Make sure the port is within an acceptable range (0..65534)
   if ((port >= 0) && (port <= 65534)) {
      addr.sin6_port = htons(port);
      return true;
   }

   setErrorMessage("Port must be between 0 and 65536");
   return false;
}


/* bind - Bind a socket to its port
 * Original 03/07/2002 pickle
 */
bool SocketDomainIPv6::bind(void)
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
bool SocketDomainIPv6::connect(void)
{
   if (::connect(getFD(), (sockaddr*)&remoteAddress,
		 sizeof(localAddress)) == 0) {
      return true;
   }
   
   setErrorMessage();
   return false;
}
