/* $Id$
 * 
 * Copyright (c) 1996,1999,2001,2002,2003,2004 Alien Internet Services
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

#ifndef _INCLUDE_LIBAISUTIL_STRING_STRING_H_
# define _INCLUDE_LIBAISUTIL_STRING_STRING_H_ 1

/*! \file
 * \brief Supplementary string routines (for std::string)
 * 
 * This file contains routines designed to supplement std::string.
 */

# include <aisutil/aisutilconf.h>

# include <string>
# include <sstream>
# include <iostream>
# include <cstdlib>
# include <ctime>

# ifdef LIBAISUTIL_STL_HAS_HASH
#  include <hash_map>
# endif

namespace AIS {
   namespace Util {
      /*!
       * \brief Our String class, which provides a few more handy procedures
       * 
       * \ingroup Strings
       */
      class String : public std::string {
       public:
	 //! The magic constructors
	 String(void) : std::string("") {};
	 String(char c) : std::string(&c) {};
	 template <typename Ta>
	   String(const Ta& a) 
	     : std::string(a) 
	     {};
	 template <typename Ta, typename Tb>
	   String(const Ta& a, const Tb& b) 
	     : std::string(a, b)
	     {};
	 
	 //! Destructor
	 virtual ~String(void) 
	   {};
	 
	 /*!
	  * \brief Convert the entire string to lower-case
	  * 
	  * This will convert all letters within the string to lower case,
	  * and return a new string reflecting it as such.
	  * 
	  * \return The string, converted to lower-case
	  */
	 const String toLower(void) const;
	 
	 /*!
	  * \brief Convert the entire string to upper-case
	  * 
	  * Similar to toLower(), this will change the case of all letters
	  * within the string to upper case.
	  * 
	  * \return The string, converted to upper-case
	  */ 
	 const String toUpper(void) const;
	 
	 /*!
	  * \brief Convert something to a std::string
	  * 
	  * Using std::ostringstream, this convenience routine will convert
	  * almost anything provided as its \p input into a std::string.
	  * 
	  * \param input Something to convert to a string
	  * \return A string representing whatever was giving as the \p input
	  */
	 template <typename T>
	   static const std::string convert(const T& input) 
	     {
		std::ostringstream out;
		out << input;
		return out.str();
	     };
	 
	 /*!
	  * \brief Convert to an integer
	  * 
	  * \warning Since this is merely a wrapper for std::atoi(), no
	  *    error checking is provided.
	  * \return An integer
	  * \retval 0 The string could not be converted
	  */
	 const int toInt(void) const 
	   { return std::atoi(c_str()); };
	 
	 /*! 
	  * \brief Convert to a long integer
	  * 
	  * \warning Since this is merely a wrapper for std::atol(), no
	  *    error checking is provided.
	  * \return An integer
	  * \retval 0 The string could not be converted
	  */
	 const long toLong(void) const
	   { return std::atol(c_str()); };
	 
	 /*!
	  * \brief Convert to a double
	  * 
	  * \warning Since this is merely a wrapper for std::atoi(), no
	  *    error checking is provided.
	  * \return An integer
	  * \retval 0 The string could not be converted
	  */
	 const double toDouble(void) const 
	   { return std::atof(c_str()); };
	 
	 /*!
	  * \brief Pad the beginning of the string
	  * 
	  * This will pre-pad the beginning of the string with \p c characters
	  * so that the length of the returned string is equal to or greater
	  * than \p n characters.
	  * 
	  * If the string's length() is greater than \p n, the string returned
	  * will be identical. No cropping will be performed.
	  * 
	  * \param n The number of characters the length of the string should
	  *    <em>at least</em> be equal to.
	  * \param c The character to pre-pad the string with. This defaults
	  *    to using spaces.
	  * \return The string (pre-padded)
	  */
	 const String prepad(const size_type n, const char c = ' ') const;
	 
	 /*!
	  * \brief Trim white-space
	  * 
	  * Remove all white-space from the beginning and the end of this
	  * string (as determined by std::isspace()).
	  * 
	  * \return A new string with white-space trimmed from the beginning
	  *    and the end of the string
	  */
	 const String trim(void) const;
	 
	 /*!
	  * \brief Trim quotes
	  * 
	  * This will remove quotation marks from the file of various types,
	  * such as \e ", \e ', and \e `.
	  * 
	  * \return A new string without its surrounding quotes
	  */
	 const String trimQuotes(void) const;
	 
# ifndef LIBAISUTIL_STL_STRING_CLEAR
	 /*!
	  * \brief Supply the 'clear' function
	  * 
	  * If the implementation of std::string on this system does not
	  * include std::string::clear(), this dirty hack will replace it so
	  * you can safely use it in your programs. Some older compilers do
	  * not provide it.
	  */
	 void clear(void)
	   { (*this) = ""; };
# endif
      }; // class String
   }; // namespace Util
}; // namespace AIS


# ifdef LIBAISUTIL_STL_HAS_HASH
//! STL hash template specialisation for our String class
template<> struct std::hash<AIS::Util::String>
{
   // STL Hash operator
   const size_t operator()(const AIS::Util::String& str) const {
      char const* s = str.c_str();
      size_t size = 0; // Should we offset this?
      
      /* Run through the string; Note the last number should be a prime 
       * for minimising collisions. Everywhere I read people seem to like 
       * magic number 17 as a generic prime, so I have followed the 
       * fashion :)
       */
      for (; *s != 0; ++s) {
	 size = (size * 17) ^ *s;
      }
      
      return size;
   };
};
# endif // LIBAISUTIL_STL_HAS_HASH

#endif // _INCLUDE_LIBAISUTIL_STRING_STRING_H_
