/* $Id$
 * String class
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

#include "aisutil/string/string.h"

using namespace AISutil;


/* toLower - Convert an entire string to lower case
 * Original ??/07/1996 simonb
 * 26/02/2002 simonb - Converted for use with std::string
 */
String String::toLower() const
{
   char *temp = new char[length() + 1];
   
   for (register unsigned int i = (length() + 1); i--;) {
      temp[i] = tolower(c_str()[i]);
   }
   
   String result(temp);
   delete temp;
   
   return result;
}


/* toUpper - Convert an entire string to upper case
 * Original ??/07/1996 simonb
 * 26/02/2002 simonb - Converted for use with std::string
 */
String String::toUpper() const
{
   char *temp = new char[length() + 1];
   
   for (register unsigned int i = (length() + 1); i--;) {
      temp[i] = toupper(c_str()[i]);
   }
   
   String result(temp);
   delete temp;

   return result;
}


/* IRCtoLower - Convert to lowercase while considering irc chars (eg {} and [])
 * Original 12/08/2001 simonb
 * 26/02/2002 simonb - Converted for use with std::string
 */
String String::IRCtoLower() const
{
   char *temp = new char[length() + 1];
   
   for (register unsigned int i = (length() + 1); i--;) {
      char ch = c_str()[i];
      switch (ch) {
       case '[':
	 temp[i] = '{';
	 continue;
       case ']':
	 temp[i] = '}';
	 continue;
       case '\\':
	 temp[i] = '|';
	 continue;
       case '~':
	 temp[i] = '^';
	 continue;
       default:
	 temp[i] = tolower(ch);
      }
   }
   
   String result(temp);
   delete temp;
   
   return result;
}


/* prepad - Make string exactly n by cropping or adding spaces to the start
 * Original 06/03/1999 simonb
 * 27/02/2002 simonb - Converted for std::string
 */
String String::prepad(size_type n, char c) const
{
   std::string result = c_str();

   while (result.length() < n) {
      result = c + result;
   }

   return result;
}


/* trim - Trim away spaces, tabs, and CR/LF's from the start/end of a string
 * Original 06/03/1999 simonb
 * 10/03/2002 simonb - Converted for std::string
 */
String String::trim(void) const
{
   size_type s = 0;
   size_type e = length();

   while ((s < e) && 
	  ((c_str()[s] == ' ') || 
	   (c_str()[s] == '\t') || 
	   (c_str()[s] == '\r') ||
	   (c_str()[s] == '\n'))) {
      s++;
   }
   
   while ((e > s) && 
	  ((c_str()[e - 1] == ' ') || 
	   (c_str()[e - 1] == '\t') ||
	   (c_str()[e - 1] == '\r') ||
	   (c_str()[e - 1] == '\n'))) {
      e--;
   }

   return substr(s, e - s);
}


/* trimQuotes - Same as regular trim(), but for removing ' and "'s
 * Original 11/08/2001 simonb
 * 10/03/2002 simonb - Converted for std::string
 */
String String::trimQuotes(void) const
{
   size_type s = 0;
   size_type e = length();

   while ((s < e) && 
	  ((c_str()[s] == ' ') ||
	   (c_str()[s] == '\'') || 
	   (c_str()[s] == '"'))) {
      s++;
   }
   
   while ((e > s) && 
	  ((c_str()[e - 1] == ' ') ||
	   (c_str()[e - 1] == '\'') ||
	   (c_str()[e - 1] == '"'))) {
      e--;
   }
   
   return substr(s, e - s);
}
