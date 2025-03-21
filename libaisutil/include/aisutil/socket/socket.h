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

#ifndef _INCLUDE_LIBAISUTIL_SOCKET_SOCKET_H_
# define _INCLUDE_LIBAISUTIL_SOCKET_SOCKET_H_ 1

/*! \file
 * \brief Socket base class
 * 
 * This file contains the base class for the socket classes.
 */

// We should simply include ostream here, but some compilers do not have it?
# include <string>
# include <cerrno>
# include <cstring>
# include <cstdio>

extern "C" {
# include <sys/types.h>
# include <sys/socket.h>
# include <unistd.h>
};


namespace AIS {
   namespace Util {
      namespace Socket {
	 /*!
	  * \brief Socket base class
	  * 
	  * The Domain and Type bases are derived from this, the generic
	  * interface to a socket. This does not take into consideration very
	  * much about a socket, other than it has an address and data can be
	  * sent/read from the socket.
	  *
	  * Note that this socket class does not include any functions
	  * specific to reliable transport types, or stateful sockets. Being
	  * a specific \e type of a socket, you should see StatefulType for
	  * functions such as StatefulType::listen() and
	  * StatefulType::accept().
	  */
	 class Socket {
	  public:
	    /*!
	     * \brief The 'block size' type.
	     * 
	     * This defines a standard type for block lengths.
	     */
	    typedef unsigned int blockSize_type;

	    /*!
	     * \brief A port type.
	     * 
	     * A type of a port (a number)
	     */
	    typedef int port_type;
	    
	  private:
	    /*!
	     * \brief File descriptor
	     * 
	     * This is an \e integer which defines a \e file within this
	     * current process. The Socket class takes control of the file
	     * descriptor to avoid it being incorrectly dereferenced or
	     * zeroed inappropriately.
	     * 
	     * Users of other platforms will need to understand that under
	     * *NIX, <em>everything is a file</em>, since in generic terms a
	     * file is something which can be read and written to. Under this
	     * principle, sockets are so considered to be files.
	     */
	    int fd;
	    
	    /*!
	     * \brief An error message
	     * 
	     * This contains a pointer to an error message
	     * 
	     * \deprecated This will probably disappear sometime in the future
	     */
	    const char* errorMessage;
	    
	  protected:
	    /*!
	     * \brief Constructor
	     * 
	     * Construct a new 'Socket' using the given file descriptor
	     */
	    explicit Socket(const int newFD = -1)
	      : fd(newFD),
	        errorMessage("No error")
	      { (void)setNonBlockingFlag(); };
	    
	    
	    /*!
	     * \brief Set the error message to the given string
	     *
	     * Set the \a errorMessage to the given \p errorString.
	     * 
	     * \param errorString A \b static \b const string
	     * \deprecated This will probably disappear sometime in the future
	     */
	    void setErrorMessage(const char* const errorString)
	      { errorMessage = errorString; };
	    
	    /*!
	     * \brief The lazy way of setting the error message :)
	     * 
	     * Set the \a errorMessage to a message associated with errno.
	     * 
	     * \deprecated This will probably disappear sometime in the future
	     */
	    void setErrorMessage(void)
	      { setErrorMessage(sys_errlist[errno]); };
	    
	    
	    /*!
	     * \brief Get a protocol's number
	     * 
	     * Return the protocol number as determined by the protocols file
	     * (\e /etc/protocols or similar). This is essentially a neat
	     * wrapper for getprotobyname().
	     * 
	     * \note This is really only valid for IP protocols
	     * \param name The name of the protocol
	     * \return The protocol number
	     */
	    static const int getProtocol(const char* const name);

	    
	    /*!
	     * \brief Set a socket option (an integer)
	     * 
	     * \param option The option to set using setsockopt()
	     * \param value The value to set the option to. 
	     * \param level The layer level the \p option corresponds to. The
	     *    default is to set the option at the socket level. Check the
	     *    setsockopt() <em>man page</em> for more details.
	     * \return The status of the operation
	     * \retval true The option was set successfully
	     * \retval false The option could not be set
	     */
	    const bool setSockoptInt(const int option,
				     const int value,
				     const int level = SOL_SOCKET);
	    
	    
	    /*!
	     * \brief Set a socket option (an boolean)
	     * 
	     * \param option The option to set using setsockopt()
	     * \param toggle The option's flag setting (true/on or false/off)
	     * \param level The layer level the \p option corresponds to. The
	     *    default is to set the option at the socket level. Check the
	     *    setsockopt() <em>man page</em> for more details.
	     * \return The status of the operation
	     * \retval true The option was set successfully
	     * \retval false The option could not be set
	     */
	    const bool setSockoptFlag(const int option,
				      const bool toggle,
				      const int level = SOL_SOCKET)
	      { return setSockoptInt(option, (toggle ? 1 : 0), level); };


	    //@{
	    /*!
	     * \brief Retrieve the the status of the given sockopts option
	     * 
	     * \param flag The option to check using getsockopt()
	     * \param level The level to check for the option. The default is
	     *    the socket level. See the getsockopt() <em>man page</em>
	     *    for more info.
	     * \return The boolean value of the option
	     * \retval 1 The option is set (on)
	     * \retval 0 The option is not set (off)
	     * \retval -1 The status of the option is indeterminate or an
	     *    error occurred
	     */
	    const int getSockoptInt(const int flag,
				    const int level = SOL_SOCKET) const;
	    const signed int getSockoptFlag(const int flag,
					    const int level = SOL_SOCKET) const
	      {
		 const int value = getSockoptInt(flag, level);
		 return ((value > 0) ? 1 : value);
	      };
	    //@}


	  public:
	    /*!
	     * \brief Destructor
	     * 
	     * Destroy the socket. This will make sure the socket is closed
	     * neatly by calling ::close().
	     */
	    virtual ~Socket(void)
	      { (void)::close(fd); };

	    
	    /*!
	     * \brief Get the file descriptor
	     * 
	     * Return the current value of the file descriptor (\a fd). The
	     * file descriptor is protected to avoid it being dereferenced
	     * or otherwise clobbered unintentionally.
	     * 
	     * \return The file descriptor
	     * \retval -1 The file descriptor is \e invalid or \e uninitialised
	     */
	    const int getFD(void) const
	      { return fd; };
	    
	    /*!
	     * \brief Still this socket okay?
	     *
	     * This is a method to \b roughly determine whether or not the
	     * socket is considered healthy. Essentially, it checks to see
	     * if the file descriptor pointing to the \e real socket (as far
	     * as the operating system is concerned) is valid.
	     * 
	     * \return Whether we are okay or not
	     * \retval true The socket seems to be okay
	     * \retval false The socket is not okay
	     */
	    const bool isOkay(void) const
	      { return (fd >= 0); };

	    
	    /*!
	     * \brief Set socket as \e non-blocking
	     * 
	     * This is to set the socket as \e non-blocking as not to slow down
	     * operations.
	     * 
	     * \note Non-blocking is the default behavior for Socket's.
	     * 
	     * \param toggle Whether you want non-blocking mode on or off
	     * \return The status of the operation
	     * \retval true The operation was successful
	     * \retval false The operation was unsuccessful, or the feature is
	     *    unsupported on this system
	     */
	    const bool setNonBlockingFlag(const bool toggle = true);

	    /*!
	     * \brief Determine if the socket is in \e non-blocking mode
	     * 
	     * \return Whether the socket is in non-blocking mode
	     * \retval 1 Operations performed on the socket will not block
	     * \retval 0 Operations performed on the socket will block
	     * \retval -1 Unable to determine the non-blocking status
	     */
	    const signed int getNonBlockingFlag(void) const;


	    /*!
	     * \brief Turn on re-usable addresses
	     * 
	     * This will enable the re-usable address flag (\e SO_REUSEADDR or
	     * similar) if it is available, in order to save bind()ing time.
	     * 
	     * This allows a socket to bind() to its local address, except
	     * when there is an active listening socket already bound to that
	     * address.
	     *
	     * With this unset, the socket may not bind() to an address/port
	     * without the address/port being totally unused.
	     * 
	     * \param toggle Whether you want \e SO_REUSEADDR on or off
	     * \return The status of the operation
	     * \retval true The operation was successful
	     * \retval false The operation was unsuccessful, or the feature is
	     *    unsupported on this system
	     */
	    const bool setReuseAddressFlag(const bool toggle = true)
	      { return setSockoptFlag(SO_REUSEADDR, toggle); };

	    /*!
	     * \brief Determine if the socket may reuse 
	     * 
	     * \return Whether the socket can reuse local addresses when
	     *    bind()ing
	     * \retval 1 bind() operations are allowed so long as no socket
	     *    is already listening on the local address and/or port set
	     * \retval 0 bind() operations are only allowed when nothing is
	     *    currently using the set local address and/or port
	     * \retval -1 Unable to determine the status of this flag
	     */
	    const signed int getReuseAddressFlag(void) const
	      { return getSockoptFlag(SO_REUSEADDR); };

	    
	    /*!
	     * \brief Toggle the status of the priority flag
	     * 
	     * The priority flag, when set, \e possibly changes the way data
	     * is sent to a remote host. For some operating systems, this
	     * means that, when set, the flag will cause the system to queue
	     * the packets ahead of other packets without this flag set.
	     * 
	     * Specifically for protocols which inherit from DomainIP (that
	     * is, <em>Internet Protocols</em>), this will modify the
	     * \e type-of-service (\e TOS) field's precedence level.
	     * 
	     * The change is \e permanent, in that it will effect all data
	     * sent while the flag is set, up until the point where the socket
	     * is destroyed, or the flag is unset.
	     * 
	     * This <b>does not</b> change the ordering of the packets sent,
	     * since that's totally up to the specific transport type used.
	     * 
	     * \param toggle The new status of the flag. There is no default
	     *    value here intentionally to avoid the priority flag being
	     *    over-used. If the flag was over-used, it would defeat the
	     *    purpose of the priority flag.
	     * \return The status of the operation
	     * \retval true The priority flag was changed
	     * \retval false The priority flag could not be changed
	     */
	    const bool setPriorityFlag(const bool toggle = false)
	      { return setSockoptFlag(SO_PRIORITY, toggle); };
	    
	    /*!
	     * \brief Get the status of the priority flag
	     * 
	     * Determine the current status of the priority flag.
	     * 
	     * \return The boolean value of the flag
	     * \retval 1 Sent packets are sent with the priority flag
	     * \retval 0 Sent packets are not sent with the priority flag
	     * \retval -1 The status of the priority flag could not be
	     *    determined
	     */
	    const signed int getPriorityFlag(void) const
	      { return getSockoptFlag(SO_PRIORITY); };


	    /*!
	     * \brief Toggle the single-hop flag
	     *
	     * When set, the single-hop flag restricts the packets sent via
	     * this socket to only be sent a <em>"single hop"</em> away. This
	     * means that packets can not be routed to remote destinations,
	     * and will only be received by hosts <em>directly connected</em>
	     * to this one.
	     *
	     * \param toggle The new status for the single hop flag
	     * \return The status of the operation
	     * \retval true The flag was successfully changed
	     * \retval false The flag could not be set, or is unsupported on
	     *    this system or socket type
	     */
	    const bool setSingleHopFlag(const bool toggle = false)
	      { return setSockoptFlag(SO_DONTROUTE, toggle); };

	    /*!
	     * \brief Determine the status of the single-hop flag
	     *
	     * \return The status of the single-hop flag
	     * \retval 1 Packets can only be sent to directly connected
	     *    destinations
	     * \retval 0 Packets are allowed to be routed to remote
	     *    destinations
	     * \retval -1 The status of the flag cannot be determined
	     */
	    const signed int getSingleHopFlag(void) const
	      { return getSockoptFlag(SO_DONTROUTE); };


	    /*!
	     * \brief Toggle socket closure lingering
	     * 
	     * When lingering is turned on, closing the socket will not close
	     * and dump the data. Instead, the operating system will keep the
	     * socket \e lingering whilst either all the data pending to be
	     * sent on the socket is sent, or the maximum lingering time
	     * (\p seconds) has passed.
	     * 
	     * \param seconds This is the number of seconds to \e linger.
	     *    Specify \e 0 here to turn the flag off.
	     * \return The status of the operation
	     * \retval true The linger flag has been toggled and/or the linger
	     *    time has been changed
	     * \retval false The linger flag could not be changed, or the
	     *    linger seconds is invalid
	     */
	    const bool setLingerFlag(const int seconds = 0);

	    /*!
	     * \brief Determine whether lingering is set on the socket
	     *
	     * \return If set, a number greater than zero representing the
	     *    number of senders the socket will linger for after close()
	     *    is called.
	     * \retval 0 Lingering is turned off on this socket
	     * \retval -1 The closure lingering status could not be determined
	     */
	    const int getLingerFlag(void) const;


	    /*!
	     * \brief Close the socket
	     * 
	     * This will close the socket and make the file descriptor invalid
	     * to avoid conflict with a future file description allocation
	     * from the operating system.
	     * 
	     * \warning A successful closure of a socket does not guarantee
	     *    that all data you wanted to send just prior to closure was
	     *    sent, even using a reliable transport.
	     * \return Whether the socket was closed or not
	     * \retval true The socket closed successfully
	     * \retval false The socket was not closed
	     */
	    const bool close(void)
	      { 
		 if (::close(fd) == 0) {
		    fd = -1;
		    return true;
		 }
		 return false;
	      };

	    
	    /*!
	     * \brief Return the local address
	     * 
	     * \return The local address as a \e sockaddr structure
	     */
	    virtual const sockaddr&
	      getLocalAddress(socklen_t& addrlen) const = 0;
	    
	    /*!
	     * \brief Return the remote address
	     * 
	     * \return The remote address as a \e sockaddr structure
	     */
	    virtual const sockaddr&
	      getRemoteAddress(socklen_t& addrlen) const = 0;
	    
	    
	    /*!
	     * \brief Return the local address (as a string)
	     *
	     * \return The local address, converted to a string
	     */
	    virtual const std::string getLocalAddress(void) const = 0;
	    
	    /*!
	     * \brief Return the remote address (as a string)
	     * 
	     * \return The remote address, converted to a string
	     */
	    virtual const std::string getRemoteAddress(void) const = 0;
	    

	    /*!
	     * \brief Return the local port
	     * 
	     * \return The local port number
	     * \retval -1 Ports have no meaning for this socket type
	     */
	    virtual const int getLocalPort(void) const
	      { return -1; };
	    
	    /*!
	     * \brief Return the remote port
	     * 
	     * \return The remote port number
	     * \retval -1 Ports have no meaning for this socket type
	     */
	    virtual const int getRemotePort(void) const
	      { return -1; };
	    
	    
	    /*!
	     * \brief Set the local address
	     *
	     * \param address The new address to replace \a localAddress with
	     * \return The status of the operation
	     * \retval true The address was set successfully
	     * \retval false There was an error in setting the address, such
	     *    as the address was invalid for this socket domain
	     */
	    virtual const bool
	      setLocalAddress(const std::string& address) = 0;
	    
	    /*!
	     * \brief Set the remote address
	     * 
	     * \param address The new address to replace \a remoteAddress with
	     * \return The status of the operation
	     * \retval true The address was set successfully
	     * \retval false There was an error in setting the port, such
	     *    as the address was invalid for this socket domain
	     */
	    virtual const bool
	      setRemoteAddress(const std::string& address) = 0;

	    
	    /*!
	     * \brief Set the local port
	     * 
	     * \return The status of the operation
	     * \retval true The address was set successfully
	     * \retval false There was an error in setting the port, such
	     *    as the port number was out of range for this socket domain
	     */
	    virtual const bool setLocalPort(const port_type port)
	      { return false; };
	    
	    /*!
	     * \brief Set the remote port
	     *
	     * \return The status of the operation
	     * \retval true The address was set successfully
	     * \retval false There was an error in setting the port, such
	     *    as the port number was out of range for this socket domain
	     */
	    virtual const bool setRemotePort(const port_type port)
	      { return false; };
	    
	    
	    /*!
	     * \brief Bind a socket
	     * 
	     * This will bind the socket to its currently set local address
	     * and port. If the socket is a StatefulType, it will then be ready
	     * to StatefulType::listen() for new connections.
	     * 
	     * \return The status of the operation
	     * \retval true The socket has been successfully
	     * \retval false The socket could not be bound for some reason,
	     *    such as the local address or port are invalid/uninitialised,
	     *    or the socket cannot be bound.
	     */
	    virtual const bool bind(void) = 0;
	    
	    
	    /*!
	     * \brief Connect this socket
	     * 
	     * Connect from the local address and port to the remote address
	     * and port.
	     * 
	     * \warning It's a common mistake to set a socket as non-blocking
	     *    and use connect(), and consider the connection as being
	     *    completed. In non-blocking mode, the return value of
	     *    connect() being true simply means the connection is \b in
	     *    \b progress, and not that it is complete.
	     * \return The status of the operation
	     * \retval true The socket is connected, or the connection is in
	     *    progress
	     * \retval false The socket could not connect.
	     */
	    virtual const bool connect(void) = 0;
	    
	    
	    /*! 
	     * \brief Write data to this socket
	     * 
	     * Send the given \p data through the socket.
	     * 
	     * \param data Raw data to be send to the remote recipient
	     * \return returns the number of \e octets written
	     * \retval -1 No data could be sent, as an error occured
	     */
	    virtual const int write(const std::string& data) = 0;
	    
	    /*!
	     * \brief Read data from this socket
	     * 
	     * This will read any pending data from the socket and place it
	     * in the given \p buffer parameter. The new data will be
	     * \e appended to the end of the \p buffer.
	     * 
	     * If the socket is set as non-blocking, and no data is waiting to
	     * be read on the socket, this operation will wait until there is
	     * at least an octet to read from the socket before returning.
	     * 
	     * \param buffer The buffer to \e append the read data to
	     * \return The number of bytes read (the length of \p databuff)
	     * \retval -1 The operation was unsuccessful
	     */
	    virtual const std::string::size_type read(std::string& buffer) = 0;
	    
	    
	    /*!
	     * \brief Return the block size per read
	     * 
	     * \return The maximum chunk of data per read() call
	     */
	    virtual const blockSize_type getReadBlockSize(void) const = 0;
	    
	    
	    /*!
	     * \brief Has an error occured?
	     * 
	     * Determine whether an operation has caused an error.
	     * 
	     * \return Whether an error has occurred or not
	     * \retval true The previous operation on the socket caused an
	     *    error
	     * \retval false There are no known errors.
	     */
	    const bool error(void) const
	      { return (errorMessage != 0); };
	    
	    /*!
	     * \brief Return the error message
	     * 
	     * Return a pointer to a \e null-terminated string explaining an
	     * error, if one had occured.
	     * 
	     * \warning The return value may in fact be a null-pointer, and as
	     *    such the value should be used cautiously. You may use error()
	     *    to see if an error has indeed occured and hence an error
	     *    message will be available.
	     * \return Return a pointer to a string
	     * \retval 0 There was no error
	     * \deprecated This will probably disappear sometime in the future
	     */
	    const char* const getErrorMessage(void) const
	      { return errorMessage; };
	 }; // class Socket
      }; // namespace Socket
   }; // namespace Util
}; // namespace AIS

#endif // _INCLUDE_LIBAISUTIL_SOCKET_SOCKET_H_
