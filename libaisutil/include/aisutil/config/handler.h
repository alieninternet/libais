/* $Id$
 *
 * Copyright (c) 2004 Alien Internet Services
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

#ifndef _INCLUDE_LIBAISUTIL_CONFIG_HANDLER_H_
# define _INCLUDE_LIBAISUTIL_CONFIG_HANDLER_H_ 1

namespace AIS {
   namespace Util {
      namespace Config {
	 /*!
	  * \brief Configuration data handler functoid base class
	  * 
	  */
	 class Handler {
	  protected:
	    //! Default constructor
	    Handler(void)
	      {};

	  public:
	    //! Destructor
	    virtual ~Handler(void)
	      {};
	 }; // class Handler
      }; // namespace Config
   }; // namespace Util
}; // namespace AIS

#endif // _INCLUDE_LIBAISUTIL_CONFIG_HANDLER_H_
