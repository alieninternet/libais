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

# include "aisutil/socket/domain-ipv4.h"

using namespace AIS::Util;


/* Get a protocol's number (really only valid for IP protocols)
 * Original 04/07/2002 pickle
 */
int Socket::getProtocol(const char* const name)
{
   protoent prot;
   prot = *getprotobyname(name);
   return prot.p_proto;
}

      
/* setNonBlocking - Set socket NON-BLOCKING so it doesn't slow us down
 * Original 18/12/2000 pickle
 * 05/07/2002 pickle - Cut down, the socket class now always sets non-blocking
 */
void Socket::setNonBlocking(void)
{
   long flags = 0;
   
   // We first get the file descriptor flags
   fcntl(fd, F_GETFL, &flags);
   
   // Set it
   fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}


/* setReuseAddress - Set socket SO_REUSEADDR to save binding time :)
 * Original 09/01/2001 pickle
 */
bool Socket::setReuseAddress(void)
{
   int sockopts = 1;
   
   if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
		  (char*)&sockopts, sizeof(sockopts)) == 0) {
      return true;
   }
   
   setErrorMessage();
   return false;
}


/* listen - Listen on a socket (valid on SOCK_STREAM and SOCK_SEQPACKET types)
 * Original 09/01/2001 pickle
 */
bool Socket::listen(int backlog)
{ 
   if (::listen(fd, backlog) == 0) {
      return true;
   }
   
   setErrorMessage();
   return false;
}
