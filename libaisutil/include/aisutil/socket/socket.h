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

// We should simply include ostream here, but some compilers do not have it!!
# include <iostream>
# include <string>
# include <cerrno>
# include <cstring>
# include <cstdio>

extern "C" {
# include <sys/socket.h>
# include <unistd.h>
};

namespace AIS {
   namespace Util {
      namespace Socket {
	 //! Socket base class
	 class Socket {
	  public:
	    typedef unsigned int blockSize_type;
	    
	  private:
	    //! File descriptor
	    const int fd;
	    
	    //! An error message :)
	    const char* errorMessage;
	    
	  protected:
	    //! Constructor
	    explicit Socket(int newFD = -1)
	      : fd(newFD),
	        errorMessage("No error")
	      {};
	    
	    //! Set the error message to the given errno value's string
	    void setErrorMessage(const char* errorString)
	      { errorMessage = errorString; };
	    
	    //! The lazy way of setting the error message :)
	    void setErrorMessage(void)
	      { setErrorMessage(sys_errlist[errno]); };
	    
	    //! Get a protocol's number (really only valid for IP protocols)
	    static const int getProtocol(const char* const name);
	    
	    //! Set socket NON-BLOCKING so it doesn't slow us down
	    void setNonBlocking(void);
	    
	  public:
	    //! Destructor
	    virtual ~Socket(void)
	      { (void)close(); };
	    
	    //! Get the file descriptor
	    int getFD(void) const
	      { return fd; };
	    
	    //! Still this socket okay? (Rough, only false if we are set up wrong)
	    const bool isOkay(void) const
	      { return (fd >= 0); };
	    
	    //! Turn on re-usable address to save binding time (USE WITH CAUTION!)
	    const bool setReuseAddress(void);
	    
	    //! Close the socket
	    virtual const bool close(void)
	      { return (::close(fd) == 0); };
	    
	    //! Return the local address
	    virtual const sockaddr&
	      getLocalAddress(socklen_t& addrlen) const = 0;
	    
	    //! Return the remote address
	    virtual const sockaddr&
	      getRemoteAddress(socklen_t& addrlen) const = 0;
	    
	    //! Return the local address (as a string)
	    virtual const std::string getLocalAddress(void) const = 0;
	    
	    //! Return the remote address (as a string)
	    virtual const std::string getRemoteAddress(void) const = 0;
	    
	    //! Return the local port
	    virtual const int getLocalPort(void) const = 0;
	    
	    //! Return the remote port
	    virtual const int getRemotePort(void) const = 0;
	    
	    //! Set the local address
	    virtual const bool
	      setLocalAddress(const std::string& address) = 0;
	    
	    //! Set the remote address
	    virtual const bool
	      setRemoteAddress(const std::string& address) = 0;
	    
	    //! Set the local port
	    virtual const bool setLocalPort(const int port) = 0;
	    
	    //! Set the remote port
	    virtual const bool setRemotePort(const int port) = 0;
	    
	    //! Bind a socket its port
	    virtual const bool bind(void) = 0;
	    
	    //! Connect this socket
	    virtual const bool connect(void) = 0;
	    
	    //! Write data to this socket (returns the number of octets written)
	    virtual const int write(const std::string& data) = 0;
	    
	    //! Read data from this socket
	    virtual const bool read(std::ostream& databuff) = 0;
	    
	    //! Return the block size per read
	    virtual const blockSize_type getReadBlockSize(void) const = 0;
	    
	    //! Return some information about this socket, if any
	    virtual const std::string getInfo(void) const
	      { return std::string(); };
	    
	    /*!
	     * \brief Has an error occured?
	     * 
	     * Determine whether an operation (the last operation performed)
	     * caused an error
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
	     */
	    const char* const getErrorMessage(void) const
	      { return errorMessage; };
	 }; // class Socket
      }; // namespace Socket
   }; // namespace Util
}; // namespace AIS

#endif // _INCLUDE_LIBAISUTIL_SOCKET_SOCKET_H_
