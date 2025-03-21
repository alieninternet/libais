/* $Id$
 *
 * Copyright (c) 2002,2003,2004 Alien Internet Services
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

#ifndef _INCLUDE_LIBAISUTIL_CONFIG_DATA_H_
# define _INCLUDE_LIBAISUTIL_CONFIG_DATA_H_ 1

# include <aisutil/config/definitions.h>
# include <aisutil/config/errors.h>

namespace AIS {
   namespace Util {
      namespace Config {
	 /*!
	  * \brief Configuration data class
	  * 
	  * This is the configuration data class, used to store your
	  * configuration data for use primarily during program run-time.
	  */
	 class Config {
	  private:
	    //! Definitions table, which is bound to data held in this class
	    const defTable_ptr definitions;

	    //! Error reporting mechanism
	    ErrorReporter* const errorReporter;
	    
	    
	  protected:
	    /*!
	     * \brief Default constructor
	     * 
	     */
	    Config(const defTable_ptr _definitions,
		   ErrorReporter* const _errorReporter = 0)
	      : definitions(_definitions),
	        errorReporter(_errorReporter)
	      {};


	  public:
	    //! Destructor
	    virtual ~Config(void)
	      {};
	 }; // class Config
      }; // namespace Config
   }; // namespace Util
}; // namespace AIS

#endif // _INCLUDE_LIBAISUTIL_CONFIG_DATA_H_
