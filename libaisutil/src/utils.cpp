/* $Id$
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

#include <cassert>

#include "aisutil/utils.h"
#include "aisutil/string/string.h"

using namespace AISutil;


/* validateUTF8 - Determine if the given UTF-8 sequence is valid
 * Original 22/03/2003 pickle
 * Note: We only check in accordance to Unicode 3.2; That is between U+0000 to
 *       U+10FFFF, which only forms 4-byte UTF-8 sequences (not the full 6-byte
 *       sequences). This should probably be re-evaluated sometime in the
 *       future, should this practise change.
 *       This is considerably larger than needs be, and needs to be optimised!
 */
const bool Utils::validateUTF8(const std::string& str)
{
   for (std::string::size_type i = 0; i < str.length(); i++) {
      // 0x00000000 -> 0x0000007F (one octet sequence)
      if ((str[i] & 0x80) == 0) {
	 // This is a single octet, so we know it's okay
	 continue;
      }
      
      // 0x00000080 -> 0x000007FF (two octet sequences)
      if ((str[i] >= '\302') && (str[i] <= '\337') &&
	  (str.length() >= (i + 1))) {
	 i++;
	 
	 // Check the second octet
	 if ((str[i] >= '\200') && (str[i] <= '\277')) {
	    continue;
	 }
      }
      
      // 0x00000800 -> 0x00001000 (three octet sequences)
      if ((str[i] >= '\340') && (str[i] <= '\357') &&
	  (str.length() >= (i + 2))) {
	 i++;
	 
	 // Check the second octet
	 if ((((str[i - 1] == '\340') && (str[i] >= '\240')) ||
	      (str[i] >= '\200')) &&
	     (str[i] <= '\277')) {
	    i++;
	    
	    // Check the third octet
	    if ((str[i] >= '\200') && (str[i] <= '\277')) {
	       continue;
	    }
	 }
      }
      
      // 0x00010000 -> 0x00100000 (four octet sequences)
      if ((str[i] >= '\360') && (str[i] <= '\364') &&
	  (str.length() >= (i + 3))) {
	 i++;
	 
	 // Check the second octet
	 if (((str[i - 1] == '\360') &&
	      (str[i] >= '\220') && (str[i] <= '\277')) ||
	     ((str[i - 1] == '\364') &&
	      (str[i] >= '\200') && (str[i] <= '\217')) ||
	     ((str[i] >= '\200') && (str[i] <= '\277'))) {
	    i += 2;
	    
	    // Check the third and forth octets
	    if ((str[i - 1] >= '\200') && (str[i - 1] <= '\277') &&
		(str[i] >= '\200') && (str[i] <= '\277')) {
	       continue;
	    }
	 }
      }
      
      // If we got here, the sequence is invalid
      return false;
   }
   
   // Presume it was okay
   return true;
}


/* toBool - Convert a string like 'yes' 'no' 'true' 'false' etc into boolean
 * Original 21/09/2001 pickle
 * 24/02/2003 pickle - Updated to include numeric values (1 = true, 0 = false)
 */
const int Utils::toBool(const std::string& word)
{
   String newWord = String(word).toUpper();
   
   if ((newWord == "YES") ||
       (newWord == "TRUE") ||
       (newWord == "ON") ||
       (newWord.toInt() > 0)) {
      return 1;
   }
   
   if ((newWord == "NO") ||
       (newWord == "FALSE") ||
       (newWord == "OFF") ||
       (newWord.toInt() == 0)) {
      return 0;
   }
   
   return -1;
}


/* baseXStr - Convert a number to another base (output a string) up to base 85
 * Original 17/01/2001 pickle
 * 06/04/2001 pickle - Updated the baseChrs string to produce base-85 output
 * Note: The output is NOT mime/base64-encoding compatible!!!
 */
#define MAXBASE 85
const String Utils::baseXStr(unsigned long number, const unsigned char base)
{
   static const char baseChrs[MAXBASE + 1] =
     "0123456789"				// 10 +
     "ABCDEFGHIJKLMNOPQRSTUVWXYZ"		// 26 +
     "abcdefghijklmnopqrstuvwxyz"		// 26 +
     "!?$#%&*+-/:<=>@:[]^{|}~";			// 23 = 85 chars

   // Make sure the base is within the limits..
   assert((base > 1) && (base <= MAXBASE));
   
   long digit;
   String tempStr;
   
   while (number > 0) {
      digit = number % base;
      number = (number - digit) / base;
      tempStr = baseChrs[digit] + tempStr;
   }
   
   return tempStr;
}


