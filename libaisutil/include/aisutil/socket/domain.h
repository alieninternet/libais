/* $Id$
 * Protocol family (socket domain) virtuals
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

#ifndef _INCLUDE_AISUTIL_SOCKET_DOMAIN_H_
# define _INCLUDE_AISUTIL_SOCKET_DOMAIN_H_ 1

extern "C" {
# include <netdb.h>
};

# include <aisutil/socket/socket.h>

namespace AISutil {
   class SocketDomain : virtual public Socket {
    public:
      // Destructor
      virtual ~SocketDomain(void)
	{};
      
      // Return the local port
      virtual int getLocalPort(void) const
	{ return -1; };

      // Return the remote port
      virtual int getRemotePort(void) const
	{ return -1; };
      
      // Set the local port
      virtual bool setLocalPort(const int port)
	{ return false; };
      
      // Set the remote port
      virtual bool setRemotePort(const int port)
	{ return false; };
   };
};
   
#endif // _INCLUDE_AISUTIL_SOCKET_DOMAIN_H_
