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

#ifndef _INCLUDE_AISUTIL_SOCKET_DOMAIN_IP_H_
# define _INCLUDE_AISUTIL_SOCKET_DOMAIN_IP_H_

# include <aisutil/socket/socket.h>

namespace AIS {
   namespace Util {
      namespace Socket {
	 /*!
	  * \brief Internet Protocol (IP) socket domain base
	  * 
	  * This is a base class for the IP (Internet Protocol) set of
	  * protocols, and contains routines common to all IP protocol
	  * versions.
	  */
	 class DomainIP : virtual public Socket {
	  protected:
	    //! Constructor
	    DomainIP(void)
	      {};
	 
	  public:
	    //! Destructor
	    virtual ~DomainIP(void)
	      {};
	 }; // class DomainIP
      }; // namespace Socket
   }; // namespace Util
}; // namespace AIS

#endif // _INCLUDE_AISUTIL_SOCKET_DOMAIN_IP_H_
