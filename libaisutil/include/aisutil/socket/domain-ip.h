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

#ifndef _INCLUDE_AISUTIL_SOCKET_DOMAIN_IP_H_
# define _INCLUDE_AISUTIL_SOCKET_DOMAIN_IP_H_

# include <aisutil/socket/socket.h>

namespace AIS {
   namespace Util {
      namespace Socket {
	 /*!
	  * \brief Internet Protocol (IP) socket domain base
	  * 
	  * This is a base class for the IP (Internet Protocol) set of
	  * protocols, and contains routines common to all IP protocol
	  * versions.
	  */
	 class DomainIP : virtual public Socket {
	  protected:
	    //! Constructor
	    DomainIP(void)
	      {};
	 
	  public:
	    //! Destructor
	    virtual ~DomainIP(void)
	      {};
	    
	    
	    /*!
	     * \brief Change the maximum hop count (TTL) on this socket
	     *
	     * This will modify the maximum hop counter, or <em>Time To
	     * Live</em> (\e TTL), sent on packets \e sent from this socket.
	     * 
	     * Since this counter is decreased by \e 1 each time it passes
	     * through another host or router, this counter determines the
	     * maximum number of hosts the packet can be sent through before
	     * it expires. When the counter reaches \e 0, the packet is
	     * destroyed.
	     *
	     * \warning Setting this too high can cause dangerous circular
	     *    problems if there are routing problems. Setting this too low
	     *    will cause unnecessary packet destruction (and failed
	     *    transmission).
	     * \param hops The new maximum hop count to set on this socket.
	     *    Setting a value of -1 \e may reset the hop count back to the
	     *    system default.
	     * \return The status of the operation
	     * \retval The hop count was changed successfully
	     * \retval The hop count could not be changed, or it was invalid
	     */
	    virtual const bool setMaximumHopCount(const int hops) = 0;
	    
	    /*!
	     * \brief Return the maximum hop count (TTL) on this socket
	     * 
	     * This will return the maximum hops, or <em>Time To Live</em>
	     * (\e TTL), set on packets sent from this socket.
	     * 
	     * \return The maximum hop count currently set on this socket
	     * \retval -1 The hop count could not be determined
	     */
	    virtual const int getMaximumHopCount(void) const = 0;
	 }; // class DomainIP
      }; // namespace Socket
   }; // namespace Util
}; // namespace AIS

#endif // _INCLUDE_AISUTIL_SOCKET_DOMAIN_IP_H_
