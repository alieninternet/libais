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

#ifndef _INCLUDE_LIBAISUTIL_CONFIG_ERRORS_H_
# define _INCLUDE_LIBAISUTIL_CONFIG_ERRORS_H_ 1

# include <string>

namespace AIS {
   namespace Util {
      namespace Config {
	 //! List of errors
	 namespace Errors {
	    enum errorCode_type {
	       Informational	= 0x0000, //!< Informational notice (not error)
		 
	       OutOfRange	= 0x0100, //!< Out of range error
	       BelowRange	= 0x0101, //!< Out of range: Below minimum
	       AboveRange	= 0x0102, //!< Out of range: Above minimum
	    
	       UnknownError	= 0xFFFF  //!< Unknown error
	    };
	 };
	 
	 
	 /*!
	  * \brief Error handler functoid
	  * 
	  */
	 class ErrorReporter {
	  protected:
	    //! Default constructor
	    ErrorReporter(void)
	      {};

	  public:
	    //! Destructor
	    virtual ~ErrorReporter(void)
	      {};
	    
	    
	    //! Reporting mechanism
	    virtual void report(const unsigned int LineNumber,
				const Errors::errorCode_type errorCode,
				const std::string& report)
	      {};
	 }; // class ErrorReporter
      }; // namespace Config
   }; // namespace Util
}; // namespace AIS

#endif // _INCLUDE_LIBAISUTIL_CONFIG_ERRORS_H_
