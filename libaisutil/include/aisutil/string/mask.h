/* $Id$
 * 
 * Copyright (c) 1996,1998,2001,2003 Alien Internet Services
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

#ifndef _INCLUDE_LIBAISUTIL_STRING_STRINGMASK_H_
# define _INCLUDE_LIBAISUTIL_STRING_STRINGMASK_H_ 1

/*! \file
 * \brief Simple metachar based mask routines
 * 
 * This file contains the StringMask class, which contains rudimentary mask
 * matching routines.
 */

# include <aisutil/string/string.h>

namespace AIS {
   namespace Util {
      /*!
       * \brief String mask class, used to match strings using metachars
       *
       * This special string class is designed to hold a \e mask, containing
       * metachars (<em>'*'</em> and <em>'?'</em>)
       * 
       * \ingroup Strings
       */
      class StringMask : public String {
       public:
	 /*!
	  * \brief Default Constructor
	  * 
	  * This will create a 'blank' mask which will match everything.
	  */
	 StringMask(void)
	   : String("*")
	   {};

	 /*!
	  * \brief Constructor
	  * 
	  * Construct a mask from the given string
	  * 
	  * \param mask A string to be stored (should be a mask)
	  */
	 template <class T>
	   StringMask(const T& mask)
	     : String(mask)
	     {};
	 
	 //! Destructor
	 ~StringMask(void)
	   {};
	 

	 //@{
	 /*!
	  * \brief Check string match (case-sensitive)
	  * 
	  * Check the given \p string against the mask stored within this
	  * class. The check will \b case-sensitive.
	  * 
	  * \param string A string to check against the stored mask
	  * \return A value representing whether the match was successful
	  * \retval true The given \p string matches the mask
	  * \retval false The given \p string does not match the mask
	  */
	 const bool matchesCase(const char* string) const;

	 const bool matchesCase(const std::string& string) const
	   { return matchesCase(string.c_str()); };
	 //@}
	 
	 
	 //@{
	 /*!
	  * \brief Check string match (case-insensitive)
	  * 
	  * Similar to matchesCase(), this will check the given \p string
	  * against the stored mask. The difference is that this will perform
	  * a \b case-insensitive match (ie. 'A' and 'a' will be considered
	  * equal).
	  * 
	  * \param string A string to check against the stored mask
	  * \return A value representing whether the match was successful
	  * \retval true The given \p string matches the mask
	  * \retval false The given \p string does not match the mask
	  */
	 const bool matches(const char* string) const;

	 const bool matches(const std::string& string) const
	   { return matches(string.c_str()); }
	 //@}
      }; // class StringMask
   }; // namespace Util
}; // namespace AIS

#endif // _INCLUDE_LIBAISUTIL_STRING_STRINGMASK_H_
