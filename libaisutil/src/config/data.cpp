/* $Id$
 * 'ConfigData' class definitions (variable handlers)
 *
 * Copyright (c) 2002,2003 Alien Internet Services
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

#include <algorithm>
#include <cerrno>
#include <cstdlib>

#ifdef LIBAISUTIL_DEBUG_ASSERT
# include <cassert>
#endif

#include "aisutil/config/data.h"

using namespace AISutil;


/* varHandleBoolean - Handle a 'bool' (use first value)
 * Original 13/04/2002 simonb
 */
LIBAISUTIL_CONFIG_VARIABLE_HANDLER(ConfigData::varHandleBoolean)
{
#ifdef LIBAISUTIL_DEBUG_ASSERT
   assert(dataVariable != 0);
#endif
     
   // Check if the values list is empty
   if (values.empty()) {
      // Make a presumption...
      dataClass.*((bool ConfigData::*)dataVariable) = true;
      return true;
   }
   
   String boolStr = values.front().toUpper();
   
   // Try to (roughly) determine what boolean value this has
   if ((boolStr == "YES") ||
       (boolStr == "ON") ||
       (boolStr == "TRUE") ||
       (boolStr == "1")) {
      dataClass.*((bool ConfigData::*)dataVariable) = true;
      return true;
   } else if ((boolStr == "NO") ||
	      (boolStr == "OFF") ||
	      (boolStr == "FALSE") ||
	      (boolStr == "0")) {
      dataClass.*((bool ConfigData::*)dataVariable) = false;
      return true;
   }
   
   // Set the error string and return cranky
   errString = '\'' + values.front() + "' is not a valid boolean value";
   return false;
}


/* varHandleHostName - Handle a hostname (use first value + additional checks)
 * Original 13/04/2002 simonb
 */
LIBAISUTIL_CONFIG_VARIABLE_HANDLER(ConfigData::varHandleHostName)
{
#ifdef LIBAISUTIL_DEBUG_ASSERT
   assert(dataVariable != 0);
#endif

   // Check if the values list is empty
   if (values.empty()) {
      // Clear it
      (dataClass.*((String ConfigData::*)dataVariable)).clear();
      return true;
   }
   
   const char *name = values.front().c_str();
   const char *nameStart = name;
   
   for (; *name != '\0'; name++) {
      /* Check the hostname according to STD-0013 rules on host names. I am
       * unaware of how this effects the internationalisation of domain names
       * (IDN) such as names with extended characters...
       */
      if ((*name != '.') &&
	  (*name != '-') &&
	  !isalnum(*name)) {
	 // Construct an error string and return as if we just chopped onions
	 if (isprint(*name)) {
	    errString = String("Unfriendly character in hostname ('") + 
	      *name + "\')";
	 } else {
	    errString = "Unfriendly character in hostname (#" +
	      String::convert((int)*name) + ')';
	 }
	 return false;
      }
      
      // Check for a repeated dot if it is safe
      if (name > nameStart) {
	 if ((*name == '.') && (*(name - 1) == '.')) {
	    // Be cranky
	    errString = "Illegal repeated '.' in hostname";
	    return false;
	 }
      }
   }
   
   // Set it happily
   dataClass.*((String ConfigData::*)dataVariable) = values.front();
      
   return true;
}


// Make a string from a list of values
struct valuesToString {
   String &str;
   
   valuesToString(String &s)
     : str(s)
     {
	str.clear();
     }
   
   // This appends a value to the string, with spaces between values
   void operator()(const String &val) {
      if (!str.empty()) {
	 str += ' ';
      }
      str += val;
   }
};


/* varHandleString - Handle a 'String' (uses all entries on the line)
 * Original 12/04/2002 simonb
 */
LIBAISUTIL_CONFIG_VARIABLE_HANDLER(ConfigData::varHandleString)
{
#ifdef LIBAISUTIL_DEBUG_ASSERT
   assert(dataVariable != 0);
#endif
     
   if (!values.empty()) {
      // Run through the list of values
      std::for_each(values.begin(), values.end(), 
		    valuesToString(dataClass.*(((String ConfigData::*)
						dataVariable))));
   } else {
      // Presume they wanted the string to be empty..      
      (dataClass.*((String ConfigData::*)dataVariable)).clear();
   }

   return true;
}


/* varHandleStringOneWord - Handle a single word from a string
 * Original 22/09/2002 simonb
 */
LIBAISUTIL_CONFIG_VARIABLE_HANDLER(ConfigData::varHandleStringOneWord)
{
#ifdef LIBAISUTIL_DEBUG_ASSERT
   assert(dataVariable != 0);
#endif

   if (!values.empty()) {
      // Ensure we are only grabbing one word..
      String::size_type gap = values.front().find(' ');
      
      // Assign the value
      dataClass.*((String ConfigData::*)dataVariable) = 
	values.front().substr(0, gap);
   } else {
      // Presume they wanted the string to be empty..      
      (dataClass.*((String ConfigData::*)dataVariable)).clear();
   }

   return true;
}


/* varHandleUnsignedChar - Handle an unsigned char
 * Original 13/04/2002 simonb
 */
LIBAISUTIL_CONFIG_VARIABLE_HANDLER(ConfigData::varHandleUnsignedChar)
{
#ifdef LIBAISUTIL_DEBUG_ASSERT
   assert(dataVariable != 0);
#endif

   // Check if the values list is empty
   if (values.empty()) {
      // Make a presumption...
      dataClass.*((unsigned char ConfigData::*)dataVariable) = 1;
      return true;
   }

   char *endChar;

   // Convert the number
   unsigned long num = strtoul(values.front().c_str(), &endChar, 10);

   // Check if we did not end at a the null (end of the string)
   if (*endChar != '\0') {
      // Construct an error string and return as if we just chopped onions
      if (isprint(*endChar)) {
	 errString = String("Unfriendly character in number ('") + 
	   *endChar + "\')";
      } else {
	 errString = "Unfriendly character in number (#" +
	   String::convert((int)*endChar) + ')';
      }
      return false;
   }
   
   // Check the number is ok
   if ((num == ULONG_MAX) || (num > 255) || (errno == ERANGE)) {
      errString = "Number " + String::convert(num) + 
	" is not within the range 0 to 255 inclusive";
      return false;
   }
   
   // Must be ok - set it
   dataClass.*((unsigned char ConfigData::*)dataVariable) = num;
   
   return true;
}


/* varHandleUnsignedCharNoZero - Handle an unsigned char (0 is invalid)
 * Original 13/04/2002 simonb
 */
LIBAISUTIL_CONFIG_VARIABLE_HANDLER(ConfigData::varHandleUnsignedCharNoZero)
{
#ifdef LIBAISUTIL_DEBUG_ASSERT
   assert(dataVariable != 0);
#endif

   // Check if the values list is empty
   if (values.empty()) {
      // Make a presumption...
      dataClass.*((unsigned char ConfigData::*)dataVariable) = 1;
      return true;
   }

   char *endChar;

   // Convert the number
   unsigned long num = strtoul(values.front().c_str(), &endChar, 10);

   // Check if we did not end at a the null (end of the string)
   if (*endChar != '\0') {
      // Construct an error string and return as if we just chopped onions
      if (isprint(*endChar)) {
	 errString = String("Unfriendly character in number ('") + 
	   *endChar + "\')";
      } else {
	 errString = "Unfriendly character in number (#" +
	   String::convert((int)*endChar) + ')';
      }
      return false;
   }
   
   // Check the number is ok
   if ((num == ULONG_MAX) || (num == 0) || (num > 255) || (errno == ERANGE)) {
      errString = "Number " + String::convert(num) + 
	" is not within the range 1 to 255 inclusive";
      return false;
   }
   
   // Must be ok - set it
   dataClass.*((unsigned char ConfigData::*)dataVariable) = num;
   
   return true;
}


/* varHandleUnsignedShort - Handle an unsigned short
 * Original 13/04/2002 simonb
 */
LIBAISUTIL_CONFIG_VARIABLE_HANDLER(ConfigData::varHandleUnsignedShort)
{
#ifdef LIBAISUTIL_DEBUG_ASSERT
   assert(dataVariable != 0);
#endif
     
   // Check if the values list is empty
   if (values.empty()) {
      // Make a presumption...
      dataClass.*((unsigned short ConfigData::*)dataVariable) = 0;
      return true;
   }

   char *endChar;

   // Convert the number
   unsigned long num = strtoul(values.front().c_str(), &endChar, 10);

   // Check if we did not end at a the null (end of the string)
   if (*endChar != '\0') {
      // Construct an error string and return as if we just chopped onions
      if (isprint(*endChar)) {
	 errString = String("Unfriendly character in number ('") + 
	   *endChar + "\')";
      } else {
	 errString = "Unfriendly character in number (#" +
	   String::convert((int)*endChar) + ')';
      }
      return false;
   }
   
   // Check the number is ok
   if ((num == ULONG_MAX) || (num > 65535) || (errno == ERANGE)) {
      errString = "Number " + String::convert(num) + 
	" is not within the range 0 to 65535 inclusive";
      return false;
   }
   
   // Must be ok - set it
   dataClass.*((unsigned short ConfigData::*)dataVariable) = num;

   return true;
}


/* varHandleUnsignedShortNoZero - Handle an unsigned short (0 is invalid)
 * Original 13/04/2002 simonb
 */
LIBAISUTIL_CONFIG_VARIABLE_HANDLER(ConfigData::varHandleUnsignedShortNoZero)
{
#ifdef LIBAISUTIL_DEBUG_ASSERT
   assert(dataVariable != 0);
#endif
     
   // Check if the values list is empty
   if (values.empty()) {
      // Make a presumption...
      dataClass.*((unsigned short ConfigData::*)dataVariable) = 1;
      return true;
   }

   char *endChar;

   // Convert the number
   unsigned long num = strtoul(values.front().c_str(), &endChar, 10);

   // Check if we did not end at a the null (end of the string)
   if (*endChar != '\0') {
      // Construct an error string and return as if we just chopped onions
      if (isprint(*endChar)) {
	 errString = String("Unfriendly character in number ('") + 
	   *endChar + "\')";
      } else {
	 errString = "Unfriendly character in number (#" +
	   String::convert((int)*endChar) + ')';
      }
      return false;
   }
   
   // Check the number is ok
   if ((num == ULONG_MAX) || (num == 0) || (num > 65535) || 
       (errno == ERANGE)) {
      errString = "Number " + String::convert(num) + 
	" is not within the range 1 to 65535 inclusive";
      return false;
   }
   
   // Must be ok - set it
   dataClass.*((unsigned short ConfigData::*)dataVariable) = num;

   return true;
}


/* varHandleUnsignedLong - Handle an unsigned long
 * Original 13/04/2002 simonb
 */
LIBAISUTIL_CONFIG_VARIABLE_HANDLER(ConfigData::varHandleUnsignedLong)
{
#ifdef LIBAISUTIL_DEBUG_ASSERT
   assert(dataVariable != 0);
#endif
     
   // Check if the values list is empty
   if (values.empty()) {
      // Make a presumption...
      dataClass.*((unsigned long ConfigData::*)dataVariable) = 1;
      return true;
   }

   char *endChar;

   // Convert the number
   unsigned long num = strtoul(values.front().c_str(), &endChar, 10);

   // Check if we did not end at a the null (end of the string)
   if (*endChar != '\0') {
      // Construct an error string and return as if we just chopped onions
      if (isprint(*endChar)) {
	 errString = String("Unfriendly character in number ('") + 
	   *endChar + "\')";
      } else {
	 errString = "Unfriendly character in number (#" +
	   String::convert((int)*endChar) + ')';
      }
      return false;
   }
   
   // Check the number is ok
   if ((num == ULONG_MAX) || (errno == ERANGE)) {
      errString = "Number " + String::convert(num) + 
	" is not within the range 0 to 4294967295 inclusive";
      return false;
   }
   
   // Must be ok - set it
   dataClass.*((unsigned long ConfigData::*)dataVariable) = num;

   return true;
}


/* varHandleUnsignedLongNoZero - Handle an unsigned long (0 is invalid)
 * Original 13/04/2002 simonb
 */
LIBAISUTIL_CONFIG_VARIABLE_HANDLER(ConfigData::varHandleUnsignedLongNoZero)
{
#ifdef LIBAISUTIL_DEBUG_ASSERT
   assert(dataVariable != 0);
#endif
     
   // Check if the values list is empty
   if (values.empty()) {
      // Make a presumption...
      dataClass.*((unsigned long ConfigData::*)dataVariable) = 1;
      return true;
   }

   char *endChar;

   // Convert the number
   unsigned long num = strtoul(values.front().c_str(), &endChar, 10);

   // Check if we did not end at a the null (end of the string)
   if (*endChar != '\0') {
      // Construct an error string and return as if we just chopped onions
      if (isprint(*endChar)) {
	 errString = String("Unfriendly character in number ('") + 
	   *endChar + "\')";
      } else {
	 errString = "Unfriendly character in number (#" +
	   String::convert((int)*endChar) + ')';
      }
      return false;
   }
   
   // Check the number is ok
   if ((num == ULONG_MAX) || (num == 0) || (errno == ERANGE)) {
      errString = "Number " + String::convert(num) + 
	" is not within the range 1 to 4294967295 inclusive";
      return false;
   }
   
   // Must be ok - set it
   dataClass.*((unsigned long ConfigData::*)dataVariable) = num;

   return true;
}


