/* $Id$
 * StringTokens class
 * 
 * Copyright (c) 1999,2000,2002,2003 Alien Internet Services
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

#include "aisutil/string/tokens.h"

using namespace AISutil;


/* tokenCounter - Helper for the countTokens function below
 * Original 23/09/2002 pickle
 */
struct tokenCounter {
   unsigned int counter;			// Our counting integer
   char lastChar;				// The last char we saw
   
   // Constructor
   tokenCounter(void)
     : counter(1),
       lastChar(0)
     {};
   
   // The function that does all the work.. sort of..
   inline void operator()(const char& thisChar) {
      if (isspace(thisChar) && !isspace(lastChar)) {
	 counter++;
      }
      lastChar = thisChar;
   }
};


/* countTokens - Count the number of tokens (checking for whitespace only)
 * Original 08/02/1999 pickle
 * 23/09/2002 pickle - Switch to for_each()
 */
unsigned int StringTokens::countTokens(void) const
{
   if (empty()) {
      return 0;
   }

   return (std::for_each(begin(), end(), tokenCounter())).counter;
}


/* tokenCounterGeneric - Helper for the countTokens() using a given delimiter
 * Original 23/09/2002 pickle
 */
struct tokenCounterGeneric {
   const char delimiter;			// The delimiter to look for
   unsigned int counter;			// Our counting integer

   // Constructor
   tokenCounterGeneric(const char d)
     : delimiter(d),
       counter(1)
     {};
   
   // The function that does all the work.. sort of..
   inline void operator()(const char& c) {
      if (c == delimiter) {
	 counter++;
      }
   }
};


/* countTokens - Count the number of tokens (using a specific delimiter)
 * Original 08/02/1999 pickle
 * 23/09/2002 pickle - Switch to for_each()
 */
unsigned int StringTokens::countTokens(const char delimiter) const
{
   if (empty()) {
      return 0;
   }

   return (std::for_each(begin(), end(),
			 tokenCounterGeneric(delimiter))).counter;
}


/* nextToken - [Various Forms] Grab the next token
 * Original 08/02/1999 pickle
 * 08/02/2000 mro0 - Fixed -1 bug
 * 11/03/2002 pickle - Converted for std::string
 */
String StringTokens::nextToken(void)
{
   String::size_type startPosition = position;
   
   while ((startPosition < length()) && isspace(data()[startPosition])) {
      startPosition++;
   }
   
   for (String::size_type endPosition = startPosition; endPosition < length(); 
	endPosition++) {
      if (isspace(data()[endPosition])) {
	 position = endPosition + 1;
	 return substr(startPosition, endPosition - startPosition);
      }
   }
   
   position = length();
   return substr(startPosition, length() - startPosition);
}

String StringTokens::nextToken(const char delimiter)
{
   // Save our existing location
   String::size_type startPosition = position;
   
   // Locate the character
   position = find(delimiter, position);
   
   // Check the position
   if (position == (String::size_type)-1) {
      position = length();
   }
   
   // Return the snippet
   return substr(startPosition, position++ - startPosition);
}


/* nextColonToken - Get the next token, or the rest, depending on a :
 * Original 11/08/2001 pickle
 */
String StringTokens::nextColonToken(void)
{
   if (position == length()) {
      return "";
   }
   
   if (data()[position] == ':') {
      String::size_type startPos = position + 1;
      position = length();
      return substr(startPos, length() - startPos);
   }
   
   return nextToken();
}
