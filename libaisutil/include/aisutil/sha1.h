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
      struct SHA1 {
	 //! A digest. SHA1 returns 160 bits, this makes it easier to manage.
	 union digest_type {
	    unsigned char u_char[20];
	    signed char s_char[20];
	    unsigned long u_long[5];
	    
	    
	    //! Boolean equality operator
	    const bool operator==(const digest_type& rhs) const
	      {
		 return ((u_long[0] == rhs.u_long[0]) &&
			 (u_long[1] == rhs.u_long[1]) &&
			 (u_long[2] == rhs.u_long[2]) &&
			 (u_long[3] == rhs.u_long[3]) &&
			 (u_long[4] == rhs.u_long[4]));
	      };
	    
	    //! Not equal-to operator
	    const bool operator!=(const digest_type& rhs) const
	      { return (!((*this) == rhs)); };

	 
	    //! Assignment operator (from a 'time_t')
	    const digest_type& operator=(const digest_type& rhs)
	      {
		 return 
		   *(static_cast<const digest_type*>
		     (memcpy((void*)this, (const void*)&rhs, 20)));
	      };
	    

	    //! Convert an SHA1 digest output to particular base
	    const std::string toStr(const unsigned char base,
				    const std::string::size_type pad);
	 };
	 
	 //! An empty digest
	 static const digest_type nullDigest;
	 
	 //! SHA1 digest from a string
	 static digest_type generate(const std::string& line);
      }; // namespace SHA1
   }; // namespace Util
}; // namespace AIS
   
#endif // _INCLUDE_AISUTIL_SHA1_H_
   
