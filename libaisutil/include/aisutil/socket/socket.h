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

//! This is the default value for the backlog parameter for listen()
# define LIBAISUTIL_SOCKET_DEFAULT_LISTEN_BACKLOG		5

namespace AISutil {
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
      Socket(int newFD = -1)
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
      static int getProtocol(const char* const name);

      //! Set socket NON-BLOCKING so it doesn't slow us down
      void setNonBlocking(void);
      
    public:
      //! Destructor
      virtual ~Socket(void)
	{ close(); };
      
      //! Get the file descriptor
      int getFD(void) const
	{ return fd; };
      
      //! Still this socket okay? (Rough, only false if we are set up wrong)
      const bool isOkay(void) const
	{ return (fd >= 0); };

      //! Turn on re-usable address to save binding time (USE WITH CAUTION!)
      bool setReuseAddress(void);
	
      //! Listen on socket (only valid on SOCK_STREAM and SOCK_SEQPACKET types)
      virtual bool listen(int backlog =
			  LIBAISUTIL_SOCKET_DEFAULT_LISTEN_BACKLOG);

      //! Close socket
      virtual void close(void)
	{ ::close(fd); };

      //! Return the local address
      virtual const sockaddr& getLocalAddress(socklen_t& addrlen) const = 0;
      
      //! Return the remote address
      virtual const sockaddr& getRemoteAddress(socklen_t& addrlen) const = 0;
      
      //! Return the local address (as a string)
      virtual std::string getLocalAddress(void) const = 0;
      
      //! Return the remote address (as a string)
      virtual std::string getRemoteAddress(void) const = 0;
      
      //! Return the local port
      virtual int getLocalPort(void) const = 0;

      //! Return the remote port
      virtual int getRemotePort(void) const = 0;

      //! Set the local address
      virtual bool setLocalAddress(const std::string& address) = 0;
      
      //! Set the remote address
      virtual bool setRemoteAddress(const std::string& address) = 0;
      
      //! Set the local port
      virtual bool setLocalPort(const int port) = 0;
      
      //! Set the remote port
      virtual bool setRemotePort(const int port) = 0;
      
      //! Bind a socket its port
      virtual bool bind(void) = 0;
  
      //! Connect this socket
      virtual bool connect(void) = 0;
      
      /*! Accept a connection on this socket (Don't forget to delete after use!)
       * Warning! This will return a NULL pointer (value of 0) if the accept
       * failed. Be sure to check it before using!!
       */
      virtual Socket* accept(void) = 0;
      
      //! Write data to this socket (returns the number of octets written)
      virtual const int write(const std::string& data) = 0;

      //! Read data from this socket
      virtual bool read(std::ostream& databuff) = 0;

      //! Return the block size per read
      virtual blockSize_type getReadBlockSize(void) const = 0;
      
      //! Return some information about this socket, if any
      virtual std::string getInfo(void) const
	{ return std::string(); };
      
      //! Return the error message
      const char* const getErrorMessage(void) const
	{ return errorMessage; };
   }; // class Socket
}; // namespace AISutil

#endif // _INCLUDE_LIBAISUTIL_SOCKET_SOCKET_H_
