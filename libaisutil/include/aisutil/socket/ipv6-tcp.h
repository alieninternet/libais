/* $Id$
 * TCP/IPv6 transport
 * 
 * Copyright (c) 2002 Alien Internet Services
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

#ifndef _INCLUDE_AISUTIL_SOCKET_IPV6_TCP_H_
# define _INCLUDE_AISUTIL_SOCKET_IPV6_TCP_H_ 1

extern "C" {
# include <sys/types.h>
# include <sys/socket.h>
};

# include <aisutil/socket/domain-ipv6.h>
# include <aisutil/socket/type-stream.h>

namespace AISutil {
   class SocketIPv6TCP : public SocketDomainIPv6, public SocketTypeSTREAM {
    private:
      // Constructor used when creating a new connection via accept()
      SocketIPv6TCP(const int newFD, 
		    const Socket::blockSize_type newReadBlockSize,
		    const sockaddr_in6& newLocalAddress,
		    const sockaddr_in6& newRemoteAddress)
	: Socket(newFD),
          SocketDomainIPv6(newLocalAddress, newRemoteAddress),
          SocketTypeSTREAM(newReadBlockSize)
	{ setNonBlocking(); };
      
    public:
      // Standard constructor
      SocketIPv6TCP(void)
	: Socket(::socket(PF_INET6, SOCK_STREAM, Socket::getProtocol("TCP")))
	{ setNonBlocking(); };

      // Destructor
      ~SocketIPv6TCP(void)
	{};
      
      // Accept a connection on this socket
      Socket* accept(void);
   };
};
   
#endif // _INCLUDE_AISUTIL_SOCKET_IPV6_TCP_H_
