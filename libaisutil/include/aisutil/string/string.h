/* $Id$
 * 
 * Copyright (c) 1996,1999,2001,2002,2003 Alien Internet Services
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
      //! Our String class, which provides a few more handy procedures
      class String : public std::string {
       public:
	 //! The magic constructors
	 String(void) : std::string("") {};
	 String(char c) : std::string(&c) {};
	 template <class Ta>
	   String(const Ta& a) 
	     : std::string(a) 
	     {};
	 template <class Ta, class Tb>
	   String(const Ta& a, const Tb& b) 
	     : std::string(a, b)
	     {};
	 
	 //! Destructor
	 virtual ~String(void) 
	   {};
	 
	 //! Convert the entire string to lower-case
	 String toLower(void) const;
	 
	 //! Convert the entire string to upper-case
	 String toUpper(void) const;
	 
	 //! Convert something via stringstream
	 template <class T>
	   static String convert(const T& in) 
	     {
		std::ostringstream out;
		out << in;
		return out.str();
	     };
	 
	 //! Convert to an integer
	 int toInt(void) const 
	   { return atoi(c_str()); };
	 
	 //! Convert to a long integer
	 long toLong(void) const
	   { return atol(c_str()); };
	 
	 //! Convert to a double
	 double toDouble(void) const 
	   { return atof(c_str()); };
	 
	 //! Pad the beginning of the string so it equates to the given length
	 String prepad(const size_type n, const char c = ' ') const;
	 
	 //! Trim white-space from the string
	 String trim(void) const;
	 
	 //! Trim quotes (", ' and `) from the string
	 String trimQuotes(void) const;
	 
# ifndef LIBAISUTIL_STL_STRING_CLEAR
	 //! Supply the 'clear' function if it is unavailable on this system
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
   size_t operator()(AIS::Util::String const &str) const {
      char const *s = str.c_str();
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
