/* $Id$
 * Configuration data base class
 * 
 * Copyright (c) 2002 Alien Internet Services
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

# include <vector>

namespace AISutil {
   class ConfigData;
};

# include <aisutil/string/string.h>
# include <aisutil/config/parser.h>

namespace AISutil {
   class ConfigData {
    public:
      typedef std::vector < String > textBuffer_type;

      // Constructor
      ConfigData(void) 
	{};
      
      // Destructor
      virtual ~ConfigData(void)
	{};
      
      // Variable definition handlers
      static LIBAISUTIL_CONFIG_VARIABLE_HANDLER(varHandleBoolean);
      static LIBAISUTIL_CONFIG_VARIABLE_HANDLER(varHandleHostName);
      static LIBAISUTIL_CONFIG_VARIABLE_HANDLER(varHandleString);
      static LIBAISUTIL_CONFIG_VARIABLE_HANDLER(varHandleStringOneWord);
      static LIBAISUTIL_CONFIG_VARIABLE_HANDLER(varHandleUnsignedChar);
      static LIBAISUTIL_CONFIG_VARIABLE_HANDLER(varHandleUnsignedCharNoZero);
      static LIBAISUTIL_CONFIG_VARIABLE_HANDLER(varHandleUnsignedShort);
      static LIBAISUTIL_CONFIG_VARIABLE_HANDLER(varHandleUnsignedShortNoZero);
      static LIBAISUTIL_CONFIG_VARIABLE_HANDLER(varHandleUnsignedLong);
      static LIBAISUTIL_CONFIG_VARIABLE_HANDLER(varHandleUnsignedLongNoZero);
   };
}; // namespace AISutil

#endif // _INCLUDE_LIBAISUTIL_CONFIG_DATA_H_
   
   
