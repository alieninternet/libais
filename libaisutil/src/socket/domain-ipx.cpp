/* $Id$
 * IPX domain
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
#include <sstream>
#include <iomanip>

extern "C" {
#ifdef HAVE_NETIPX_IPX_H
# include <netipx/ipx.h>
#endif
#ifdef HAVE_NETINET_IN_H
# include <netinet/in.h>
#endif
};

#include "aisutil/socket/domain-ipx.h"

using namespace AISutil;


/* SocketDomainIPX - Blank boring constructor!
 * Original 19/08/2001 simonb
 */
SocketDomainIPX::SocketDomainIPX(void)
{
   // Clean the addresses
   (void)memset(&remoteAddress, 0, sizeof(remoteAddress));
   (void)memset(&localAddress, 0, sizeof(localAddress));
   
   // Fix the address family types
   remoteAddress.sipx_family = localAddress.sipx_family = AF_IPX;
   
   // Configure a default address ?
}


/* SocketDomainIPX - Constructor used when accept()ing a connection
 * Original 06/07/2002 simonb
 */
SocketDomainIPX::SocketDomainIPX(const sockaddr_ipx& newLocalAddress, 
				 const sockaddr_ipx& newRemoteAddress)
{
   (void)memcpy(&localAddress, &newLocalAddress, sizeof(localAddress));
   (void)memcpy(&remoteAddress, &newRemoteAddress, sizeof(remoteAddress));
}


/* makeAddressStr - Return the given address as a string
 * Original 02/07/2002 simonb
 * Note: This uses the popular address format "network:node" - fully padded
 */
std::string SocketDomainIPX::makeAddressStr(const sockaddr_ipx& addr)
{
   std::ostringstream out;
   
   out << std::setbase(16) << std::setfill('0') <<
     std::setw(8) << ntohl(addr.sipx_network) << ':' <<
     std::setw(2) << (unsigned int)addr.sipx_node[0];

   for (register unsigned int i = 0; ++i != 6;) {
      out << std::setw(2) << (unsigned int)addr.sipx_node[i];
   }
   
   return out.str();
}


/* setAddress - Set the given address in the given address structure
 * Original 03/07/2002 simonb
 */
bool SocketDomainIPX::setAddress(sockaddr_ipx& addr, 
				 const std::string& addrstr)
{
   // Duh. Me dumb. Me fix later.
   return false;
}


/* setAddress - Copy the given address over the given address structure
 * Original 03/07/2002 simonb
 */
bool SocketDomainIPX::setAddress(sockaddr_ipx& addr, 
				 const sockaddr_ipx& newaddr)
{
   // Copy it!
   (void)memcpy(&addr, &newaddr, sizeof(addr));
   
   // It worked.. well at least we will presume it is okay
   return true;
}


/* setPort - Set the given port in the given address structure
 * Original 03/07/2002 simonb
 */
bool SocketDomainIPX::setPort(sockaddr_ipx& addr, const int port)
{
   // Make sure the port is within an acceptable range (0x0001..0xFFFE)
   if ((port >= 0x0001) && (port <= 0xFFFE)) {
      addr.sipx_port = htons(port);
      return true;
   }
   
   setErrorMessage();
   return false;
}


/* bind - Bind a socket to its port
 * Original 03/07/2002 simonb
 */
bool SocketDomainIPX::bind(void)
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
bool SocketDomainIPX::connect(void)
{
   if (::connect(getFD(), (sockaddr*)&remoteAddress,
		 sizeof(localAddress)) == 0) {
      return true;
   }
   
   setErrorMessage();
   return false;
}
