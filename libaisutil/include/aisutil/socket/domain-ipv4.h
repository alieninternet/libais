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

# include <aisutil/socket/socket.h>

# include <iostream>

extern "C" {
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
};

namespace AIS {
   namespace Util {
      namespace Socket {
	 //! IPv4 Socket Domain
	 class DomainIPv4 : virtual public Socket {
	  private:
	    //! The local address of this socket
	    sockaddr_in localAddress;
	    
	    //! The remote address of this socket
	    sockaddr_in remoteAddress;
	    
	    //@{
	    //! Set the given address in the given address structure
	    const bool setAddress(sockaddr_in& addr,
				  const char* const newaddr);
	    const bool setAddress(sockaddr_in& addr,
				  const std::string& newaddr)
	      { return setAddress(addr, newaddr.c_str()); };
	    const bool setAddress(sockaddr_in& addr,
				  const sockaddr_in& newaddr);
	    const bool setAddress(sockaddr_in& addr,
				  const in_addr& newaddr);
	    //@}
	    
	    //! Set the given port in the given address structure
	    const bool setPort(sockaddr_in& addr, const int port);
	    
	  protected:
	    //! Constructor
	    DomainIPv4(void);
	    
	    /*!
	     * \brief Constructor
	     * 
	     * This is used when creating a new connection via accept()
	     * 
	     * \param _localAddress The local address to set
	     * \param _remoteAddress The remote address to set
	     */
	    explicit DomainIPv4(const sockaddr_in& _localAddress,
				const sockaddr_in& _remoteAddress);
	 
	  public:
	    //! Destructor
	    virtual ~DomainIPv4(void)
	      {};
	    
	    /*!
	     * \brief Return the local address
	     * 
	     * \return The local address in its native form
	     */
	    const sockaddr_in& getLocalAddressRef(void) const
	      { return localAddress; };
	    
	    /*!
	     * \brief Return the remote address
	     * 
	     * \return The remote address in its native form
	     */
	    const sockaddr_in& getRemoteAddressRef(void) const
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
	    const std::string getLocalAddress(void) const
	      { return inet_ntoa(localAddress.sin_addr); };
	    
	    // Return the remote address (as a string)
	    const std::string getRemoteAddress(void) const
	      { return inet_ntoa(remoteAddress.sin_addr); };
	    
	    // Return the local port
	    const int getLocalPort(void) const
	      { return ntohs(localAddress.sin_port); };
	    
	    // Return the remote port
	    const int getRemotePort(void) const
	      { return ntohs(remoteAddress.sin_port); };
	    
	    // Set the local address
	    const bool setLocalAddress(const std::string& address)
	      { return setAddress(localAddress, address); };
	    
	    /*!
	     * \brief Set the local address
	     * 
	     * \overload
	     * \copydoc setLocalAddress(const std::string& address)
	     */
	    template <class T>
	      const bool setLocalAddress(const T& address)
		{ return setAddress(localAddress, address); };
	    
	    // Set the remote address
	    const bool setRemoteAddress(const std::string& address)
	      { return setAddress(remoteAddress, address); };
	    
	    /*!
	     * \brief Set the remote address
	     * 
	     * \overload
	     * \copydoc setRemoteAddress(const std::string& address)
	     */
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
	 }; // class DomainIPv4
      }; // namespace Socket
   }; // namespace Util
}; // namespace AIS
   
#endif // _INCLUDE_AISUTIL_SOCKET_DOMAIN_IPV4_H_
