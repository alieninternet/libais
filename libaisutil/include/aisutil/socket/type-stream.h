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

#ifndef _INCLUDE_LIBAISUTIL_SOCKET_TYPE_STREAM_H_
# define _INCLUDE_LIBAISUTIL_SOCKET_TYPE_STREAM_H_ 1

# include <aisutil/socket/stateful-type.h>

# include <iostream>


/*!
 * \brief Default length of the read buffer
 *
 * This is the \e default length of the read buffer. This is also the number
 * of bytes to attempt to grab per read() call. This can easily be changed
 * using the constructor, and is defined for convenience.
 */
# define LIBAISUTIL_SOCKET_STREAM_DEFAULT_BUFFER_SIZE	2048


namespace AIS {
   namespace Util {
      namespace Socket {
	 //! Stream socket type
	 class TypeSTREAM : public StatefulType {
	  private:
	    const Socket::blockSize_type bufferSize;
	    char* buffer;
	    
	  protected:
	    //! Constructor
	    explicit TypeSTREAM(const Socket::blockSize_type bs =
				LIBAISUTIL_SOCKET_STREAM_DEFAULT_BUFFER_SIZE)
	      : bufferSize(bs), 
	        buffer(0)
	      { buffer = new char[bs]; };
	 
	  public:
	    //! Destructor
	    virtual ~TypeSTREAM(void)
	      { delete[] buffer; };
	    
	    // Write data to this socket
	    const int write(const std::string& data);
	    
	    // Read data from this socket
	    const std::string::size_type read(std::string& buffer);
	    
	    // Return the block size per read
	    const blockSize_type getReadBlockSize(void) const
	      { return bufferSize; };
	 }; // class TypeSTREAM
      }; // namespace Socket
   }; // namespace Util
}; // namespace AIS
   
#endif // _INCLUDE_LIBAISUTIL_SOCKET_TYPE_STREAM_H_
