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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <cctype>
#include <algorithm>

#include "aisutil/string/string.h"

using namespace AISutil;


/* toLower - Convert an entire string to lower case
 * Original ??/07/1996 pickle
 * 26/02/2002 pickle - Converted for use with std::string
 */
String String::toLower() const
{
   String result(length(), 0);
   (void)std::transform(begin(), end(), result.begin(), tolower);
   return result;
}


/* toUpper - Convert an entire string to upper case
 * Original ??/07/1996 pickle
 * 26/02/2002 pickle - Converted for use with std::string
 */
String String::toUpper() const
{
   String result(length(), 0);
   (void)std::transform(begin(), end(), result.begin(), toupper);
   return result;
}


/* prepad - Make string exactly n by cropping or adding spaces to the start
 * Original 06/03/1999 pickle
 * 27/02/2002 pickle - Converted for std::string
 */
String String::prepad(const size_type n, const char c) const
{
   std::string result(*this);

   while (result.length() < n) {
      result = c + result;
   }

   return result;
}


/* trim - Trim away spaces, tabs, and CR/LF's from the start/end of a string
 * Original 06/03/1999 pickle
 * 10/03/2002 pickle - Converted for std::string
 */
String String::trim(void) const
{
   size_type s = 0;
   size_type e = length();

   while ((s < e) && 
	  ((data()[s] == ' ') || 
	   (data()[s] == '\t') || 
	   (data()[s] == '\r') ||
	   (data()[s] == '\n'))) {
      ++s;
   }
   
   while ((e > s) && 
	  ((data()[e - 1] == ' ') || 
	   (data()[e - 1] == '\t') ||
	   (data()[e - 1] == '\r') ||
	   (data()[e - 1] == '\n'))) {
      --e;
   }

   return substr(s, e - s);
}


/* trimQuotes - Same as regular trim(), but for removing ' and "'s
 * Original 11/08/2001 pickle
 * 10/03/2002 pickle - Converted for std::string
 */
String String::trimQuotes(void) const
{
   size_type s = 0;
   size_type e = length();

   while ((s < e) && 
	  ((data()[s] == ' ') ||
	   (data()[s] == '\'') || 
	   (data()[s] == '"'))) {
      ++s;
   }
   
   while ((e > s) && 
	  ((data()[e - 1] == ' ') ||
	   (data()[e - 1] == '\'') ||
	   (data()[e - 1] == '"'))) {
      --e;
   }
   
   return substr(s, e - s);
}
