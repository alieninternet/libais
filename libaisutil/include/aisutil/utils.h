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
      //! Miscellaneous utilities
      /*! This is a collection of miscellaneous utilities which don't fit in
       * elsewhere.
       */
      namespace Utils {
	 //! Confirm that the given string, encoded in UTF-8, is valid
	 /*! Validate a UTF-8 string. The given string must be encoded using
	  * UTF-8. This will validate by looking for out-of-range encodings,
	  * redundant encodings, or invalid and/or incomplete sequences.
	  * 
	  * \param str The string you wish to validate
	  * \return Will return true if the string is valid, false if invalid
	  */
	 extern const bool validateUTF8(const std::string& str);
	 
	 //! Convert the given word (as a string) to a boolean value
	 /*! Attempt to convert the given word into a boolean value. This will
	  * convert words such as 'true', 'false', 'on', 'off', 'yes', and 'no'
	  * into their appropriate boolean counterparts. If the string given
	  * is a number, a positive number will return true, while a value of
	  * zero or less will return false.
	  *
	  * If the word is unknown, or is ambiguous, then the result will not
	  * be returned, and a value of -1 will be returned.
	  * 
	  * \param word A single word, or number.
	  * \return 0 for false, 1 for true, and -1 for unknown.
	  */
	 extern const int toBool(const std::string& word);
	 
	 //! Convert the given integer to another base (up to base 85)
	 /*! This will convert the given integer into another base, and return
	  * it as a string. Any base up to 85 can be used.
	  *
	  * Conversions beyond base-36 (sexatrigesimal) must be handled in a
	  * case-sensitive manner, as latin digits and upper-case simple latin
	  * letters will have been used up. Lower-case latin letters are used
	  * from base-36 to base-62 (duosexagesimal). Beyond base-62, however,
	  * symbols from the ASCII character set are used.
	  * 
	  * The resultant string is guaranteed to be ASCII compatible (7-bit).
	  * 
	  * Note that this is NOT RFC3548 compliant (Base16, Base32 or Base64).
	  * 
	  * \return The converted number as a String, without any padding.
	  */
	 extern const String baseXStr(unsigned long number,
				      const unsigned char base,
				      const bool networkByteOrder = false);
      }; // namespace Utils
   }; // namespace Util
}; // namespace AIS
   
#endif // _INCLUDE_AISUTIL_UTILS_H_
