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
#ifdef HAVE_SYS_SOCKET_H
# include <sys/socket.h>
#endif
};

# include "aisutil/socket/stateful-type.h"

using namespace AIS::Util::Socket;


/* listen - Listen on a socket (valid on SOCK_STREAM and SOCK_SEQPACKET types)
 * Original 09/01/2001 pickle
 */
const bool StatefulType::listen(const int backlog)
{ 
   if (::listen(getFD(), backlog) == 0) {
      return true;
   }
   
   setErrorMessage();
   return false;
}
