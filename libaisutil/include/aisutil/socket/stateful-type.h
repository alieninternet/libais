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


	    /*!
	     * \brief Toggle sending keep-alive packets for this socket
	     * 
	     * Keep-alive packets can be sent to literally keep a connection
	     * alive. Almost all transport implementations simply send a 'ping'
	     * keep-alive packet, and expect a 'pong' to be returned sometime
	     * soon after. Most implementations will only send these packets
	     * if the connection has gone quiet, to reduce unnecessary traffic.
	     * 
	     * Keep-alives can generate slightly more traffic on a connection,
	     * but can be invaluable on potentially quiet socket connections
	     * which may be terminated by a peer system if they are determined
	     * to be \e too quiet.
	     * 
	     * \param toggle The new value for the keep-alive flag
	     * \return The status of the operation
	     * \retval true The keep-alive flag was changed successfully
	     * \retval false The flag could not be changed, or is unsupported
	     *    on this system
	     */
	    const bool setKeepAliveFlag(const bool toggle = true)
	      { return setSockoptFlag(SO_KEEPALIVE, toggle); };

	    /*!
	     * \brief Determine if keep-alive packets are being sent
	     * 
	     * \return The current value of the keep-alives flag
	     * \retval 1 Keep-alive packets will be sent on this socket
	     * \retval 0 Keep-alive packets are not enabled for this socket
	     * \retval -1 Unable to determine the status of this flag
	     */
	    const signed int getKeepAliveFlag(void) const
	      { return getSockoptFlag(SO_KEEPALIVE); };


	    /*!
	     * \brief Start listening on the socket
	     * 
	     * This will begin 'listening' on the socket. When the socket is
	     * listening, other sockets will be able to connect() to this one.
	     * When a socket is pending connection to this one, the socket will
	     * act as if new data needs to be read. Once this has happened,
	     * you can create a new socket representing that connection by
	     * using accept().
	     *
	     * Depending on the socket type, you may need to set the local
	     * port with setLocalPort(), and/or the local address with
	     * setLocalAddress(), and bind() the socket. Failure to do so
	     * will certainly result in this call returning an error.
	     * 
	     * \return The status of the operation
	     * \retval true The socket is now in the \e listening state
	     * \retval false The socket could not be put in the \e listening
	     *    state
	     */
	    virtual const bool
	      listen(const int backlog =
		     LIBAISUTIL_SOCKET_DEFAULT_LISTEN_BACKLOG);
	    
	    /*!
	     * \brief Accept a new connection on this socket
	     *
	     * When a new connection is pending on the socket, this will
	     * \e accept the new connection and create a the new socket
	     * representing it. The new socket will have similar properties
	     * to this one (flags, etc), and will share the same local address
	     * and/or port, if applicable.
	     * 
	     * The new socket will have a remote address and port, reflecting
	     * those representing the remote end of the connection.
	     * 
	     * \warning This will return a \b null-pointer (value of 0) if
	     *    the accept failed
	     * \return A newly allocated socket
	     * \retval 0 Accepting a new connection failed
	     */
	    virtual StatefulType* const accept(void) = 0;
	 }; // class StatefulType
      }; // namespace Socket
   }; // namespace Util
}; // namespace AIS

#endif // _INCLUDE_LIBAISUTIL_SOCKET_STATEFUL_TYPE_H_
