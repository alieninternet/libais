/* $Id$
 * StringMask class
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
   class StringMask {
    private:
      // The mask itself
      const String mask;
      
      // Match checker
      static bool match(char const* m, char const* n);
      
    public:
      // Blank Constructor
      StringMask(void)
	: mask("")
	{};

      // Constructor (from a string)
      StringMask(const String& s)
	: mask(s)
	{};
      
      // Destructor
      ~StringMask(void)
	{};
      
      // Boolean equals operator
      bool operator==(const StringMask& sm) const 
	{ return mask == sm.mask; };
      
      // Boolean not-equals operator
      bool operator!=(const StringMask& sm) const 
	{ return mask != sm.mask; };
      
      // Return the mask
      const String& getMask(void) const 
	{ return mask; };
      
      // Check string match
      bool matches(const String& s) const 
	{ return match(mask.c_str(), s.c_str()); };
      bool matches(const char* s) const 
	{ return match(mask.c_str(), s); };
   };
}; // namespace AISutil

#endif // _INCLUDE_LIBAISUTIL_STRING_STRINGMASK_H_
