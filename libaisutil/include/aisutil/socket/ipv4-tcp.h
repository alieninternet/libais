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

#ifndef _INCLUDE_AISUTIL_SOCKET_IPV4_TCP_H_
# define _INCLUDE_AISUTIL_SOCKET_IPV4_TCP_H_ 1

extern "C" {
# include <sys/types.h>
# include <sys/socket.h>
};

# include <aisutil/socket/domain-ipv4.h>
# include <aisutil/socket/type-stream.h>

namespace AIS {
   namespace Util {
      /*!
       * \brief TCP/IPv4 socket class
       * 
       * \ingroup Sockets
       */
      class SocketIPv4TCP : public SocketDomainIPv4, public SocketTypeSTREAM {
       private:
	 //! Constructor used when creating a new connection via accept()
	 explicit SocketIPv4TCP(const int newFD, 
				const Socket::blockSize_type newReadBlockSize,
				const sockaddr_in& newLocalAddress, 
				const sockaddr_in& newRemoteAddress)
	   : Socket(newFD),
	     SocketDomainIPv4(newLocalAddress, newRemoteAddress),
	     SocketTypeSTREAM(newReadBlockSize)
	   { setNonBlocking(); };
	 
       public:
	 //! Standard constructor
	 SocketIPv4TCP(void)
	   : Socket(::socket(PF_INET, SOCK_STREAM, Socket::getProtocol("TCP")))
	   { setNonBlocking(); };
	 
	 //! Destructor
	 ~SocketIPv4TCP(void)
	   {};
	 
	 //! Accept a connection on this socket
	 Socket* accept(void);
      }; // class SocketIPv4TCP
   }; // namespace Util
}; // namespace AIS
   
#endif // _INCLUDE_AISUTIL_SOCKET_IPV4_TCP_H_
