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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <cctype>

# ifdef HAVE_FNMATCH
// Define this if you want to use fnmatch() instead of our match() routines
// .. which we want to do, because I broke our match() routines and cbf'd
// fixing them for now :(
#  define USING_FNMATCH
#  ifdef USING_FNMATCH
extern "C" {
#   include <fnmatch.h>
}
#  endif
# endif

#include "aisutil/string/mask.h"

using namespace AISutil;


/* match - Do the actual match check
 * Original 15/02/1996 pickle
 * 18/07/1998 pickle - Ported from pascal to C++
 * 20/07/1998 pickle - Changed String to char const
 * 07/09/2001 pickle - Partial rewrite for more speed (no damned recursion!!)
 */
bool StringMask::match(char const *m, char const *n)
{
#ifdef USING_FNMATCH
   return (fnmatch(m, n, 0) == 0);
#else
   bool escaped = false;
   
   // sanity check for strings, the neat way returning true/false
   if (!*m) {
      // Of course if they are both null then this is a match
      if (!*n) {
	 return true;
      } else {
	 return false;
      }
   } else {
      if (!*n) {
	 return false;
      }
   }
   
   // While the string is valid, run through it
   while (*m) {
      // Check if this is being escaped
      if (escaped) {
	 // Next character for both strings
	 m++;
	 n++;
	 
	 escaped = false;
      } else {
	 // Check what to do with this character
	 switch (*m) {
	  case '*': // Anything goes metacharacter
	    // Loop until the next character is NOT the astericks metacharacter
	    while (*m && (*m == '*')) {
	       m++;
	    }
	    
	    // Loop until the given string ends or we find a matching char
	    while (*n && (*n != *m)) {
	       n++;
	    }
	    
	    /* If the next char is the null, bail out now and say true since the
	     * rest of the line will of course match
	     */
	    if (!*m && !*n) {
	       return true;
	    }
	    
	    continue;
	  case '?': // Skip one char metacharacter
	    // If the string is broken already, this cannot count as a char.
	    if (!*n) {
	       return false;
	    }
	    
	    m++;
	    n++;
	    
	    // If both the next chars are nulls, this obviously worked OK
	    if (!*m && !*n) {
	       return true;
	    }

	    continue;
	  case '\\': // Escape character
	    escaped = true;
	  default:
	    // Check if these two characters match in both strings
	    if (*m != *n) {
	       return false;
	    }
	    
	    // Next character for both strings
	    m++;
	    n++;
	    
	    // If both of these are at the end of line, naturally they are OK!
	    if (!*m && !*n) {
	       return true;
	    }
	 }
      }
   }
   
   return false;
#endif
}
