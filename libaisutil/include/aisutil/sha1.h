/* $Id$
 * 
 * Copyright (c) 2001,2002,2003 KineIRCd Development Team
 * (See DEV-TEAM file for details)
 *
 * This file is a part of KineIRCd.
 * 
 * KineIRCd is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * KineIRCd is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with KineIRCd; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _INCLUDE_AISUTIL_SHA1_H_
# define _INCLUDE_AISUTIL_SHA1_H_ 1

# include <string>
# include <cstring>

namespace AIS {
   namespace Util {
      //! SHA1 routines
      struct SHA1_Digest {
	 union {
	    //! SHA1 returns 160 bits, this makes it easier to manage.
	    unsigned char u_char[20];		//!< 20 unsigned chars
	    signed char s_char[20];		//!< 20 signed chars
	    unsigned long u_long[5];		//!< 5 unsigned longs
	 }; // union {anonymous}

	 
	 //! Blank constructor (nobody should want a null digest, though)
	 SHA1_Digest(void);
	 
	 //! Constructor (from a string)
	 SHA1_Digest(const std::string& line);

	 //! Destructor
	 ~SHA1_Digest(void)
	   {};
	 
	 
	 //! Boolean equality operator
	 const bool operator==(const SHA1_Digest& rhs) const
	   {
	      return ((u_long[0] == rhs.u_long[0]) &&
		      (u_long[1] == rhs.u_long[1]) &&
		      (u_long[2] == rhs.u_long[2]) &&
		      (u_long[3] == rhs.u_long[3]) &&
		      (u_long[4] == rhs.u_long[4]));
	   };
	    
	 //! Not equal-to operator
	 const bool operator!=(const SHA1_Digest& rhs) const
	   { return (!((*this) == rhs)); };
	 

	 //! Return true if we are null (empty)
	 const bool isNull(void) const
	   { 
	      return ((u_long[0] == 0) &&
		      (u_long[1] == 0) &&
		      (u_long[2] == 0) &&
		      (u_long[3] == 0) &&
		      (u_long[4] == 0));
	   };

	 
	 //! Convert an SHA1 digest output to particular base
	 const std::string toStr(const unsigned char base,
				 const std::string::size_type pad);
      }; // struct SHA1_Digest
   }; // namespace Util
}; // namespace AIS
   
#endif // _INCLUDE_AISUTIL_SHA1_H_
