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

#ifndef _INCLUDE_AISUTIL_SOCKET_DOMAIN_IPV6_H_
# define _INCLUDE_AISUTIL_SOCKET_DOMAIN_IPV6_H_ 1

# include <aisutil/socket/socket.h>

# include <iostream>

extern "C" {
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
};

namespace AIS {
   namespace Util {
      namespace Socket {
	 //! IPv6 Socket Domain
	 class DomainIPv6 : virtual public Socket {
	  private:
	    sockaddr_in6 localAddress;
	    sockaddr_in6 remoteAddress;
	    
	    // Set the given address in the given address structure
	    const bool setAddress(sockaddr_in6& addr,
				  const std::string& addrstr);
	    const bool setAddress(sockaddr_in6& addr,
				  const sockaddr_in6& newaddr);
	    const bool setAddress(sockaddr_in6& addr,
				  const in6_addr& newaddr);
	    
	    // Set the given port in the given address structure
	    const bool setPort(sockaddr_in6& addr, const int port);
	    
	  protected:
	    //! Constructor
	    DomainIPv6(void);
	    
	    //! Constructor used when creating a new connection via accept()
	    explicit DomainIPv6(const sockaddr_in6& newLocalAddress, 
				const sockaddr_in6& newRemoteAddress);
	 
	  public:
	    //! Destructor
	    virtual ~DomainIPv6(void)
	      {};
	    
	    //! Return the local address
	    const sockaddr_in6& getLocalAddressRef(void) const
	      { return localAddress; };
	    
	    //! Return the remote address
	    const sockaddr_in6& getRemoteAddressRef(void) const
	      { return remoteAddress; };
	    
	    // Return the local address
	    const sockaddr& getLocalAddress(socklen_t& addrlen) const
	      {
		 addrlen = sizeof(localAddress);
		 return (sockaddr&)localAddress;
	      };
	    
	    // Return the remote address
	    const sockaddr& getRemoteAddress(socklen_t& addrlen) const
	      {
		 addrlen = sizeof(remoteAddress);
		 return (sockaddr&)remoteAddress;
	      };
	    
	    // Return the local address (as a string)
	    const std::string getLocalAddress(void) const;
	    
	    // Return the remote address (as a string)
	    const std::string getRemoteAddress(void) const;
	    
	    // Return the local port
	    const int getLocalPort(void) const
	      { return ntohs(localAddress.sin6_port); };
	    
	    // Return the remote port
	    const int getRemotePort(void) const
	      { return ntohs(remoteAddress.sin6_port); };
	    
	    // Set the local address
	    const bool setLocalAddress(const std::string& address)
	      { return setAddress(localAddress, address); };
	    
	    //! Set the local address (any other types we may support)
	    template <class T>
	      const bool setLocalAddress(const T& address)
		{ return setAddress(localAddress, address); };
	    
	    // Set the remote address
	    const bool setRemoteAddress(const std::string& address)
	      { return setAddress(remoteAddress, address); };
	    
	    //! Set the remote address (any other types we may support)
	    template <class T>
	      const bool setRemoteAddress(const T& address)
		{ return setAddress(remoteAddress, address); };
	    
	    // Set the local port
	    const bool setLocalPort(const int port)
	      { return setPort(localAddress, port); };
	    
	    // Set the remote port
	    const bool setRemotePort(const int port)
	      { return setPort(remoteAddress, port); };
	    
	    // Bind a socket its port
	    const bool bind(void);
	    
	    // Connect this socket (unavailable on some socket types)
	    const bool connect(void);
	 }; // class DomainIPv6
      }; // namespace Socket
   }; // namespace Util
}; // namespace AIS

#endif // _INCLUDE_AISUTIL_SOCKET_DOMAIN_IPV6_H_
