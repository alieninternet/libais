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

#ifndef _INCLUDE_LIBAISUTIL_SOCKET_STATEFUL_TYPE_H_
# define _INCLUDE_LIBAISUTIL_SOCKET_STATEFUL_TYPE_H_ 1

# include <aisutil/socket/socket.h>

/*!
 * \brief The default listen() backlog
 * 
 * This is the default value for the backlog parameter for listen()
 * 
 * This can be changed, and is only defined for convenience through-out the
 * headers.
 */
# define LIBAISUTIL_SOCKET_DEFAULT_LISTEN_BACKLOG		5

namespace AIS {
   namespace Util {
      namespace Socket {
	 //! Stateful/reliable socket type base class
	 class StatefulType : virtual public Socket {
	  protected:
	    //! Constructor
	    explicit StatefulType(void)
	      {};
	    
	  public:
	    //! Destructor
	    virtual ~StatefulType(void)
	      {};
	    
	    //! Listen on socket (only valid on SOCK_STREAM and SOCK_SEQPACKET types)
	    virtual const bool
	      listen(const int backlog =
		     LIBAISUTIL_SOCKET_DEFAULT_LISTEN_BACKLOG);
	    
	    /*!
	     * \brief Accept a new connection on this socket
	     * 
	     * \warning This will return a \b null-pointer (value of 0) if
	     *    the accept failed
	     * \return A newly allocated socket, of the same type and similar
	     * \retval 0 Accepting a new connection failed
	     */
	    virtual Socket* accept(void) = 0;
	 }; // class StatefulType
      }; // namespace Socket
   }; // namespace Util
}; // namespace AIS

#endif // _INCLUDE_LIBAISUTIL_SOCKET_STATEFUL_TYPE_H_
