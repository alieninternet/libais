/* $Id$
 * String class
 * 
 * Copyright (c) 1996,1999,2001,2002 Alien Internet Services
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

namespace AISutil {
   class String : public std::string {
    public:
      // The magic constructors
      String(void) : std::string("") {};
      String(char c) : std::string(&c) {};
      template <class Ta> String(Ta const a) 
	: std::string(a) 
	  {};
      template <class Ta, class Tb> String(Ta const a, Tb const b) 
	: std::string(a, b)
	  {};
      
      // Destructor
      virtual ~String(void) 
	{};
      
      // Convert the entire string to lower-case
      String toLower(void) const;
      
      // Convert the entire string to upper-case
      String toUpper(void) const;
      
      // toLower() with IRC chars
      String IRCtoLower(void) const;
      
      // Convert something via stringstream
      template <class T> static String convert(T const in) {
	 std::ostringstream out;
	 out << in;
	 return out.str();
      };
      
      // Convert to an integer
      int toInt(void) const {
	 return atoi(c_str());
      };
      
      // Convert to a long integer
      long toLong(void) const {
	 return atol(c_str());
      };
      
      // Convert to a double
      double toDouble(void) const {
	 return atof(c_str());
      };
      
      String prepad(size_type, char) const;
      
      String trim(void) const;
      String trimQuotes(void) const;

# ifndef LIBAISUTIL_STL_STRING_CLEAR
      // Supply the 'clear' function if it is unavailable on this system
      void clear(void)
	{ (*this) = ""; };
# endif
   };
}; // namespace AISutil
 

# ifdef LIBAISUTIL_STL_HAS_HASH
// STL hash template specialisation for our String class
template<> struct std::hash<AISutil::String>
{
   // STL Hash operator
   size_t operator()(AISutil::String const &str) const {
      char const *s = str.c_str();
      size_t size = 0; // Should we offset this?
      
      /* Run through the string; Note the last number should be a prime 
       * for minimising collisions. Everywhere I read people seem to like 
       * magic number 17 as a generic prime, so I have followed the 
       * fashion :)
       */
      for (; *s; s++) {
	 size = (size * 17) ^ *s;
      }
      
      return size;
   };
};
# endif // LIBAISUTIL_STL_HAS_HASH

#endif // _INCLUDE_LIBAISUTIL_STRING_STRING_H_
