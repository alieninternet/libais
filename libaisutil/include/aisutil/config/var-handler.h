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

#ifndef _INCLUDE_LIBAISUTIL_CONFIG_VAR_HANDLER_H_
# define _INCLUDE_LIBAISUTIL_CONFIG_VAR_HANDLER_H_ 1

# include <aisutil/config/handler.h>

namespace AIS {
   namespace Util {
      namespace Config {
	 /*!
	  * \brief Configuration data variable handler functoid base class
	  *
	  * This functoid is designed for variables. If you have a particular
	  * type of data in your data class that this library does not have
	  * a handler for, you will be wanting to create your own handler by
	  * making a new functoid class inheriting from this base class.
	  * 
	  * When the configuration parser hits a definition it recognises,
	  * it gathers up the data defined in the configuration file and
	  * passes it on to the handling functoid defined in the definition
	  * tables for that particular configuration segment.
	  * 
	  * Armed with all the information you need to process the data
	  * given in the configuration file, you can do what you need with
	  * it (convert it, munge it, send it to extraterrestrial life forms
	  * for probing) and feed the appropriate value into the variable
	  * pointed to by the variable pointer.
	  */
	 class VariableHandler : public Handler {
	  protected:
	    //! Default constructor
	    VariableHandler(void)
	      {};

	  public:
	    //! Destructor
	    virtual ~VariableHandler(void)
	      {};

	  private:
	    //! Process function
	    virtual const bool process(void) = 0;
	    
	    //! Validity function
	    virtual const bool check(void) const
	      { return true; /* Presume OK */ };
	    
	  public:
	    //! The handler
	    virtual const bool handle(void)
	      { return false; /* !!! */ };
	 }; // class VariableHandler
      }; // namespace Config
   }; // namespace Util
}; // namespace AIS

#endif // _INCLUDE_LIBAISUTIL_CONFIG_VAR_HANDLER_H_
