/* $Id$
 * Socket protocol type virtuals
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

#ifndef _INCLUDE_LIBAISUTIL_SOCKET_TYPE_H_
# define _INCLUDE_LIBAISUTIL_SOCKET_TYPE_H_ 1

# include "aisutil/socket/socket.h"

namespace AISutil {
   class SocketType : virtual public Socket {
    public:
      // Destructor
      virtual ~SocketType(void)
	{};
      
      // Nothing else here yet..
   };
};
   
#endif // _INCLUDE_LIBAISUTIL_SOCKET_TYPE_H_
