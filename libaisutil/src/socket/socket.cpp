/* $Id$
 * 
 * Copyright (c) 2000,2001,2002,2003 Alien Internet Services
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

extern "C" {
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif
#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif
#ifdef HAVE_SYS_SOCKET_H
# include <sys/socket.h>
#endif
#ifdef HAVE_NETDB_H
# include <netdb.h>
#endif
};

# include "aisutil/socket/socket.h"

using namespace AIS::Util::Socket;


/* Get a protocol's number (really only valid for IP protocols)
 * Original 04/07/2002 pickle
 */
const int Socket::getProtocol(const char* const name)
{
   protoent prot;
   prot = *getprotobyname(name);
   return prot.p_proto;
}

      
/* setNonBlocking - Set socket NON-BLOCKING so it doesn't slow us down
 * Original 18/12/2000 pickle
 * 05/07/2002 pickle - Cut down, the socket class now always sets non-blocking
 * 07/08/2003 pickle - Un-cut-down :) Users may revert back to blocking mode
 */
const bool Socket::setNonBlocking(const bool toggle)
{
   long flags = 0;
   
   // We first get the file descriptor flags
   if (fcntl(fd, F_GETFL, &flags) != 0) {
      if (toggle) {
	 // Set it
	 flags |= O_NONBLOCK;
      } else {
	 // Unset it
	 flags &= ~O_NONBLOCK;
      }
      
      // Do the change
      if (fcntl(fd, F_SETFL, flags) != -1) {
	 return true;
      }
   }
   
   // Presume an error occurred..
   setErrorMessage();
   return false;
}


/* getNonBlocking - Return the non-blocking setting
 * Original 07/08/2003 pickle
 */
const signed int Socket::getNonBlocking(void) const
{
   long flags = 0;
   
   // Get the file descriptor flags
   if (fcntl(fd, F_GETFL, &flags) == -1) {
      // An error occurred, so presume non-blocking
      return -1;
   }
   
   // Return the status of the non-blocking flag
   return ((flags & O_NONBLOCK) ? 1 : 0);
}


/* setReuseAddress - Set the given flag on the socket
 * Original 09/01/2001 pickle
 */
const bool Socket::setSockoptFlag(const int option, const bool toggle,
				  const int level)
{
   // Determine what the flag should be set to
   const int sockopts = (toggle ? 1 : 0);
   
   // Set the flag
   if (setsockopt(getFD(), level, option,
		  (void*)&sockopts, sizeof(sockopts)) == 0) {
      return true;
   }
   
   // Presume there was an error..
   setErrorMessage();
   return false;
}


/* getSockoptFlag - Return the status of the given socket flag
 * Original 07/08/2003 pickle
 */
const signed int
  Socket::getSockoptFlag(const int option, const int level) const
{
   int sockopts;
   socklen_t sockopts_len;
   
   // Try to obtain the flag
   if (getsockopt(getFD(), level, option,
		  (void*)&sockopts, &sockopts_len) == 0) {
      // Make sure this really is a flag.. the size should be an 'integer'
      if (sockopts_len == sizeof(sockopts)) {
	 // Return the value of the flag, quantised down to a simple boolean
	 return ((sockopts > 0) ? 1 : 0);
      }
   }
   
   // We couldn't get the flag..
   return -1;
}
