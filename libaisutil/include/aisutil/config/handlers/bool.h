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

#ifndef _INCLUDE_LIBAISUTIL_CONFIG_HANDLERS_BOOL_H_
# define _INCLUDE_LIBAISUTIL_CONFIG_HANDLERS_BOOL_H_ 1

# include <aisutil/config/var-handler.h>

namespace AIS {
   namespace Util {
      namespace Config {
	 /*!
	  * \brief Handle a boolean value
	  * 
	  * Convert a word into a boolean value, for example "yes", "true"
	  * and "1" all equal a boolean value of \e true.
	  */
	 class HandleBool : virtual public VariableHandler {
	  public:
	    //! Default constructor
	    HandleBool(void)
	      {};

	    //! Destructor
	    virtual ~HandleBool(void)
	      {};
	    
	    
	    //! The handler
	    virtual const bool handle(void)
	      { return false; };
	 }; // class HandleBool
      }; // namespace Config
   }; // namespace Util
}; // namespace AIS

#endif // _INCLUDE_LIBAISUTIL_CONFIG_HANDLERS_BOOL_H_
