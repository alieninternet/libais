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

#ifndef _INCLUDE_AISUTIL_UTILS_H_
# define _INCLUDE_AISUTIL_UTILS_H_ 1

# include <string>
# include <aisutil/string.h>

namespace AIS {
   namespace Util {
      //! Utility stuff - little tid bits and what not..
      namespace Utils {
	 //! Confirm that the given string, encoded in UTF-8, is valid
	 extern const bool validateUTF8(const std::string& str);
	 
	 //! Convert the given word (as a string) to a boolean value
	 extern const int toBool(const std::string& word);
	 
	 //! Convert the given integer to another base (up to base 85)
	 extern const String baseXStr(unsigned long number,
				      const unsigned char base,
				      const bool networkByteOrder = false);
      }; // namespace Utils
   }; // namespace Util
}; // namespace AIS
   
#endif // _INCLUDE_AISUTIL_UTILS_H_
