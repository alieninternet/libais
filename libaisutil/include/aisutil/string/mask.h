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

# include <aisutil/string/string.h>

namespace AISutil {
   //! String mask class, used to match strings using metachars (* and ?)
   class StringMask : public String {
    public:
      //! Blank Constructor
      StringMask(void)
	{};

      //! Constructor
      template <class T>
	StringMask(const T& a)
	  : String(a) 
	  {};
      
      //! Destructor
      ~StringMask(void)
	{};
      
      
      //! Check string match
      const bool matchesCase(const char* str) const;
      
      //! Check string match
      const bool matchesCase(const std::string& str) const
	{ return matchesCase(str.c_str()); };
      
      
      //! Check string match (case-insensitive)
      const bool matches(const char* str) const;
      
      //! Check string match (case-insensitive)
      const bool matches(const std::string& str) const
	{ return matches(str.c_str()); }
   };
}; // namespace AISutil

#endif // _INCLUDE_LIBAISUTIL_STRING_STRINGMASK_H_
