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

/*! \file
 * \brief SHA1 hashing algorithms
 * 
 * This file contains an implementation of the <em>Secure Hash Algorithm 1</em>
 * (SHA1) as described by \e RFC-3174.
 */

# include <string>
# include <cstring>

namespace AIS {
   namespace Util {
      /*!
       * \brief SHA1 routines
       *
       * These are basic SHA1 routines, as described by \e RFC-3174. The
       * structure itself contains a \e digest, generated from the given
       * string upon construction. Comparison between the 
       * 
       * These routines were originally designed with <em>hashed passwords</em>
       * as the primary goal, therefore there's an emphasis on comparisons of
       * digests here.
       */
      struct SHA1_Digest {
	 //! SHA1 returns 160 bits, this makes it easier to manage.
	 union {
	    unsigned char u_char[20];		//!< 20 unsigned chars
	    signed char s_char[20];		//!< 20 signed chars
	    unsigned long u_long[5];		//!< 5 unsigned longs
	 }; // union {anonymous}

	 
	 /*!
	  * \brief Blank constructor
	  * 
	  * Nobody should want an empty digest to be created, though. If you
	  * need to test if a digest is empty or zeroed, you should use the
	  * isNull() function rather than comparing your digest with a blank
	  * one.
	  */
	 explicit SHA1_Digest(void);
	 
	 /*!
	  * \brief Constructor
	  * 
	  * Construct a new digest from the given \p data. The \p data will be
	  * used to generate the digest contained within this structure.
	  *
	  * \param data A raw string of octets to \e hash
	  * \param length The length of the data (in bytes)
	  */
	 explicit SHA1_Digest(const void* const data, unsigned int length);
	 
	 /*!
	  * \brief Constructor
	  * 
	  * Construct a new digest from the given \p data. The \p data will be
	  * used to generate the digest contained within this structure.
	  * 
	  * \param data A byte string of octets to \e hash
	  */
	 explicit SHA1_Digest(const std::string& data);
	 
	 /*!
	  * \brief Constructor
	  * 
	  * Construct a new digest from the given \p data. The \p data will be
	  * used to generate the digest contained within this structure.
	  * 
	  * \param data A wide-string of to \e hash
	  */
	 explicit SHA1_Digest(const std::wstring& data);

	 //! Destructor
	 ~SHA1_Digest(void)
	   {};
	 
	 
	 /*!
	  * \brief Boolean equality operator
	  *
	  * Compare this digest to the given digest (in \p rhs) to test for
	  * equality.
	  * 
	  * \param rhs
	  * \return A boolean value representing the equality of the digests
	  * \retval true The digests are considered to be equal
	  * \retval false The digests are not equal
	  */
	 const bool operator==(const SHA1_Digest& rhs) const
	   {
	      return ((u_long[0] == rhs.u_long[0]) &&
		      (u_long[1] == rhs.u_long[1]) &&
		      (u_long[2] == rhs.u_long[2]) &&
		      (u_long[3] == rhs.u_long[3]) &&
		      (u_long[4] == rhs.u_long[4]));
	   };
	    
	 /*!
	  * \brief Not equal-to operator
	  *
	  * Check if this digest is not equal to the one given in the \p rhs
	  * field.
	  * 
	  * \param rhs The digest to compare to this one
	  * \return A boolean value representing the inequality of the digests
	  * \retval true The digests are considered to not be equal
	  * \retval false The digests are considered equal
	  */
	 const bool operator!=(const SHA1_Digest& rhs) const
	   { return (!((*this) == rhs)); };
	 

	 /*!
	  * \brief Return true if this digest is empty
	  *
	  * If the digest is empty, or \e null, it could have been caused by
	  * an error (ie. empty string), or simply the default constructor.
	  * Never the less, it is often necessary to see if a digest is of
	  * any value. This will return true if the digest has not been
	  * initialised.
	  * 
	  * \return A boolean representing whether or not the digest is empty
	  * \retval true The digest is zeroed
	  * \retval false The digest \e possibly contains a valid SHA1 hash
	  */
	 const bool isNull(void) const
	   { 
	      return ((u_long[0] == 0) &&
		      (u_long[1] == 0) &&
		      (u_long[2] == 0) &&
		      (u_long[3] == 0) &&
		      (u_long[4] == 0));
	   };

	 
	 /*!
	  * \brief Convert an SHA1 digest output to particular base
	  * 
	  * There is almost always a necessity to convert the digest into a
	  * form which is meaningful in text files or anything ultimately
	  * displayed to the end-user.
	  * 
	  * This function provides a facility for you to convert the digest
	  * into an appropriate string for just such a purpose. Ultimately,
	  * this is just a convenient wrapper for Utils::baseXStr() to
	  * support the large size of the digest.
	  * 
	  * \param base
	  * \param pad
	  * \return A string representing the digest in the given base
	  */
	 const std::string toStr(const unsigned char base,
				 const std::string::size_type pad);
      }; // struct SHA1_Digest
   }; // namespace Util
}; // namespace AIS
   
#endif // _INCLUDE_AISUTIL_SHA1_H_
