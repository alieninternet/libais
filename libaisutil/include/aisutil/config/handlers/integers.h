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

#ifndef _INCLUDE_LIBAISUTIL_CONFIG_HANDLERS_INTEGERS_H_
# define _INCLUDE_LIBAISUTIL_CONFIG_HANDLERS_INTEGERS_H_ 1

# include <aisutil/config/var-handler.h>

namespace AIS {
   namespace Util {
      namespace Config {
	 /*!
	  * \brief Template for handling integers
	  * 
	  * This is a template for handling integers great and small, signed
	  * and unsigned.
	  */
	 template <typename T>
	   class HandleInteger : virtual public VariableHandler {
	  public:
	    //! Default constructor
	    HandleInteger(void)
	      {};

	    //! Destructor
	    virtual ~HandleInteger(void)
	      {};
	    
	    
	    //! The handler
	    virtual const bool handler(void)
	      { return false; };
	 }; // class HandleInteger
	 

	 typedef HandleInteger<signed char> HandleSignedChar;
	 typedef HandleInteger<unsigned char> HandleUnsignedChar;
	 typedef HandleInteger<signed short> HandleSignedShort;
	 typedef HandleInteger<unsigned short> HandleUnsignedShort;
	 typedef HandleInteger<signed int> HandleSignedInt;
	 typedef HandleInteger<unsigned int> HandleUnsignedInt;
	 typedef HandleInteger<signed long> HandleSignedLong;
	 typedef HandleInteger<unsigned long> HandleUnsignedLong;
	 typedef HandleInteger<signed long long> HandleSignedLongLong;
	 typedef HandleInteger<unsigned long long> HandleUnsignedLongLong;
      }; // namespace Config
   }; // namespace Util
}; // namespace AIS

#endif // _INCLUDE_LIBAISUTIL_CONFIG_HANDLERS_INTEGERS_H_
