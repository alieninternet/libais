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

#ifndef _INCLUDE_AISUTIL_SOCKET_DOMAIN_UNIX_H_
# define _INCLUDE_AISUTIL_SOCKET_DOMAIN_UNIX_H_ 1

# include <aisutil/socket/socket.h>

# include <iostream>

extern "C" {
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/un.h>
};

namespace AIS {
   namespace Util {
      namespace Socket {
	 //! Unix Socket Domain
	 class DomainUNIX : virtual public Socket {
	  private:
	    //! The local address of this socket
	    sockaddr_un localAddress;

	    //! The remote address of this socket
	    sockaddr_un remoteAddress;

	    //! Set the given address in the given address structure
	    const bool setAddress(sockaddr_un& addr,
				  const std::string& newaddr);
	    
	  protected:
	    //! Constructor
	    DomainUNIX(void);
	    
	    /*!
	     * \brief Constructor
	     * 
	     * This is used when creating a new connection via accept()
	     * 
	     * \param _localAddress The local address to set
	     * \param _remoteAddress The remote address to set
	     */
	    explicit DomainUNIX(const sockaddr_un& _localAddress,
				const sockaddr_un& _remoteAddress);
	    
	  public:
	    //! Destructor
	    virtual ~DomainUNIX(void);
	    
	    /*!
	     * \brief Return the local address
	     * 
	     * \return The local address in its native form
	     */
	    const sockaddr_un& getLocalAddressRef(void) const
	      { return localAddress; };
	    
	    /*!
	     * \brief Return the remote address
	     * 
	     * \return The remote address in its native form
	     */
	    const sockaddr_un& getRemoteAddressRef(void) const
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
	      { return localAddress.sun_path; };
	    
	    // Return the remote address (as a string)
	    const std::string getRemoteAddress(void) const
	      { return remoteAddress.sun_path; };
	    
	    // Set the local address
	    const bool setLocalAddress(const std::string& address)
	      { return setAddress(localAddress, address); };
	    
	    // Set the remote address
	    const bool setRemoteAddress(const std::string& address)
	      { return setAddress(remoteAddress, address); };
	    
	    // Bind a socket its port
	    const bool bind(void);
	    
	    // Connect this socket (unavailable on some socket types)
	    const bool connect(void);
	 }; // class DomainUNIX
      }; // namespace Socket
   }; // namespace Util
}; // namespace AIS
   
#endif // _INCLUDE_AISUTIL_SOCKET_DOMAIN_UNIX_H_
