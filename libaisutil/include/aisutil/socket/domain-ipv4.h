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

#ifndef _INCLUDE_AISUTIL_SOCKET_DOMAIN_IPV4_H_
# define _INCLUDE_AISUTIL_SOCKET_DOMAIN_IPV4_H_

# include <aisutil/socket/domain.h>

# include <iostream>

extern "C" {
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
};

namespace AIS {
   namespace Util {
      //! IPv4 Socket Domain
      class SocketDomainIPv4 : public SocketDomain {
       private:
	 sockaddr_in localAddress;
	 sockaddr_in remoteAddress;
	 
	 // Set the given address in the given address structure
	 bool setAddress(sockaddr_in& addr, const std::string& addrstr);
	 bool setAddress(sockaddr_in& addr, const sockaddr_in& newaddr);
	 bool setAddress(sockaddr_in& addr, const in_addr& newaddr);
	 
	 // Set the given port in the given address structure
	 bool setPort(sockaddr_in& addr, const int port);
	 
       protected:
	 //! Constructor
	 SocketDomainIPv4(void);
	 
	 //! Constructor used when creating a new connection via accept()
	 SocketDomainIPv4(const sockaddr_in& newLocalAddress, 
			  const sockaddr_in& newRemoteAddress);
	 
       public:
	 //! Destructor
	 virtual ~SocketDomainIPv4(void)
	   {};
	 
	 //! Return the local address
	 const sockaddr_in& getLocalAddressRef(void) const
	   { return localAddress; };
	 
	 //! Return the remote address
	 const sockaddr_in& getRemoteAddressRef(void) const
	   { return remoteAddress; };
	 
	 //! Return the local address
	 const sockaddr& getLocalAddress(socklen_t& addrlen) const
	   { addrlen = sizeof(localAddress); return (sockaddr&)localAddress; };
	 
	 //! Return the remote address
	 const sockaddr& getRemoteAddress(socklen_t& addrlen) const
	   { addrlen = sizeof(remoteAddress); return (sockaddr&)remoteAddress; };
	 
	 //! Return the local address (as a string)
	 std::string getLocalAddress(void) const
	   { return inet_ntoa(localAddress.sin_addr); };
	 
	 //! Return the remote address (as a string)
	 std::string getRemoteAddress(void) const
	   { return inet_ntoa(remoteAddress.sin_addr); };
	 
	 //! Return the local port
	 int getLocalPort(void) const
	   { return ntohs(localAddress.sin_port); };
	 
	 //! Return the remote port
	 int getRemotePort(void) const
	   { return ntohs(remoteAddress.sin_port); };
	 
	 //! Set the local address
	 bool setLocalAddress(const std::string& address)
	   { return setAddress(localAddress, address); };
	 
	 //! Set the local address (any other types we may support)
	 template <class T> bool setLocalAddress(const T& address)
	   { return setAddress(localAddress, address); };
	 
	 //! Set the remote address
	 bool setRemoteAddress(const std::string& address)
	   { return setAddress(remoteAddress, address); };
	 
	 //! Set the remote address (any other types we may support)
	 template <class T>
	   bool setRemoteAddress(const T& address)
	     { return setAddress(remoteAddress, address); };
	 
	 //! Set the local port
	 bool setLocalPort(const int port)
	   { return setPort(localAddress, port); };
	 
	 //! Set the remote port
	 bool setRemotePort(const int port)
	   { return setPort(remoteAddress, port); };
	 
	 //! Bind a socket its port
	 bool bind(void);
	 
	 //! Connect this socket (unavailable on some socket types)
	 bool connect(void);
      }; // class SocketDomainIPv4
   }; // namespace Util
}; // namespace AIS
   
#endif // _INCLUDE_AISUTIL_SOCKET_DOMAIN_IPV4_H_
