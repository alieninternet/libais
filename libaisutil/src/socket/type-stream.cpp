/* $Id$
 * 
 * Copyright (c) 1999,2002,2003 Alien Internet Services
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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <cerrno>

extern "C" {
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
};

#ifdef LIBAISUTIL_DEBUG_ASSERT
# include <cassert>
#endif

#include "aisutil/socket/type-stream.h"

using namespace AIS::Util::Socket;


/* write - Write text to a socket
 * Original 07/02/1999 pickle
 */
const int TypeSTREAM::write(const std::string& data)
{
#ifdef LIBAISUTIL_DEBUG_ASSERT
   // Make sure the file descriptor is really valid
   assert(isOkay());
#endif
   
   // Send the data (making sure ALL of the data is sent)
   if (::write(getFD(),
	       data.c_str(), data.length()) == (int)data.length()) {
      return data.length();
   }

   setErrorMessage();
   return 0;
}


/* read - Read a line from the socket
 * Original 09/02/1999 pickle
 * 03/07/2002 pickle - Rewrote to read in chunks, as it should have originally!
 */
const bool TypeSTREAM::read(std::ostream& databuff)
{
#ifdef LIBAISUTIL_DEBUG_ASSERT
   // Make sure the file descriptor is really valid
   assert(isOkay());
   
   // Make sure the stringstream is happy to deal with I/O operators
   assert(databuff.good());
#endif

   // Read a slab
   int count = ::read(getFD(), buffer, bufferSize);

   // Did we read anything?
   if (count > 0) {
      // Append the buffer to the string stream
      (void)databuff.write(buffer, count);
      
      // Smile at our calling function
      return true;
   }
   
   // Work out what happened..
   switch (count) {
    case EINTR: // We got interrupted by a signal, but that is okay
    case EAGAIN: // There was nothing to read - odd, but also okay
      // We read nothing, but no harm done
      return true;
   }

   // Presume an unhappy ending.. (make pouty faces)
   setErrorMessage();
   return false;
}

