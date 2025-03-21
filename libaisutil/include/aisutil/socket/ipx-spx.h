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

#ifndef _INCLUDE_LIBAISUTIL_SOCKET_IPX_SPX_H_
# define _INCLUDE_LIBAISUTIL_SOCKET_IPX_SPX_H_ 1

extern "C" {
# include <sys/types.h>
# include <sys/socket.h>
# include <netipx/ipx.h>
};

# include <aisutil/socket/domain-ipx.h>
# include <aisutil/socket/type-seqpacket.h>

// If the SPX protocol number is not defined, define it!
# ifndef NSPROTO_SPX
/*!
 * \brief The SPX protocol number
 * 
 * This value was sourced from the Novell developer website
 */
#  define NSPROTO_SPX	1256
# endif

/*!
 * \brief The IPX/SPX packet size
 * 
 * This is the length of the read buffer. This SEEMS low but it's really the
 * safest value to use with IPX/SPX (especially passing through very old IPX
 * routers, etc).
 * 
 * Because we use SOCK_SEQPACKET here, we must read this size no matter what.
 * 
 * Note that Novell do specify a 'safe' size for SPX running over 802.2 media,
 * that being 1454 bytes. Unfortunately we cannot rely on it because Novell
 * ALSO warn us that older applications (including third-party routers) will
 * limit this to 512 or 1024 bytes. Novell calls this a 'traditional
 * implementation of SPX'. Again, this becomes a safe size.
 * 
 * As a result of forcing this, SPX-II's automatic negotiation of the best
 * packet size is wasted here rather unfortunately.
 */
# define LIBAISUTIL_SOCKET_IPX_SPX_PACKET_SIZE	512

namespace AIS {
   namespace Util {
      namespace Socket {
	 /*!
	  * \brief IPX/SPX socket class
	  * 
	  * \ingroup Sockets
	  */
	 class SocketIPXSPX : public DomainIPX, public TypeSEQPACKET {
	  private:
	    //! Constructor used when creating a new connection via accept()
	    explicit SocketIPXSPX(const int newFD,
				  const sockaddr_ipx& newLocalAddress,
				  const sockaddr_ipx& newRemoteAddress)
	      : Socket(newFD),
	        DomainIPX(newLocalAddress, newRemoteAddress),
	        TypeSEQPACKET(LIBAISUTIL_SOCKET_IPX_SPX_PACKET_SIZE)
	      {};
	 
	  public:
	    //! Standard constructor
	    SocketIPXSPX(void)
	      : Socket(::socket(PF_IPX, SOCK_SEQPACKET, NSPROTO_SPX)),
	        TypeSEQPACKET(LIBAISUTIL_SOCKET_IPX_SPX_PACKET_SIZE)
	      {};
	    
	    //! Destructor
	    ~SocketIPXSPX(void)
	      {};
	    
	    // Accept a connection on this socket
	    StatefulType* const accept(void);
	 }; // class SocketIPXSPX
      }; // namespace Socket
   }; // namespace Util
}; // namespace AIS
   
#endif // _INCLUDE_LIBAISUTIL_SOCKET_IPX_SPX_H_
