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

#ifndef _INCLUDE_LIBAISUTIL_SOCKET_UNIX_H_
# define _INCLUDE_LIBAISUTIL_SOCKET_UNIX_H_ 1

extern "C" {
# include <sys/types.h>
# include <sys/socket.h>
};

# include <aisutil/socket/domain-unix.h>
# include <aisutil/socket/type-stream.h>

namespace AIS {
   namespace Util {
      //! Unix socket class
      class SocketUNIX : public SocketDomainUNIX, public SocketTypeSTREAM {
       private:
	 //! Constructor used when creating a new connection via accept()
	 SocketUNIX(const int newFD, 
		    const Socket::blockSize_type newReadBlockSize,
		    const sockaddr_un& newLocalAddress, 
		    const sockaddr_un& newRemoteAddress)
	   : Socket(newFD),
	     SocketDomainUNIX(newLocalAddress, newRemoteAddress),
	     SocketTypeSTREAM(newReadBlockSize)
	   { setNonBlocking(); };
	 
       public:
	 //! Standard constructor
	 SocketUNIX(void)
	   : Socket(::socket(PF_UNIX, SOCK_STREAM, 0))
	   { setNonBlocking(); };
	 
	 //! Destructor
	 ~SocketUNIX(void)
	   {};
	 
	 //! Accept a connection on this socket
	 Socket* accept(void);
      }; // class SocketUNIX
   }; // namespace Util
}; // namespace AIS
   
#endif // _INCLUDE_LIBAISUTIL_SOCKET_UNIX_H_
