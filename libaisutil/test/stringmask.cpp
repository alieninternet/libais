/* $Id$
 * 
 * Copyright (c) 2003 Alien Internet Services
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

#include <aisutil/string/mask.h>

#include "tests.h"

using namespace AIS::Util;


struct {
   const char* const string;
   const char* const mask;
   const bool expectedResult;			// Case insensitive result
   const bool expectedResultCase;		// Case sensitive result
} static const testData[] = {
     {
	"blah",
	  "blah",
	  true, true
     },
     {
	"BLAH",
	  "blah",
	  true, false
     },
     {
	"bklakfu",
	  "*",
	  true, true
     },
     {
	"Blahhhhh",
	  "b?ah*",
	  true, false
     },
     {
	"feh",
	  "???",
	  true, true
     },
     {
	"feeeeeeeh",
	  "?*?",
	  true, true
     },
     {
	"hi",
	  "?*?",
	  true, true
     },
     {
	"Heya",
	  "h?y?",
	  true, false
     },
     {
	"hrrm",
	  "****",
	  true, true
     },
     { 0, 0, false, false }
};


int main(int argc, char **argv)
{
   for (unsigned int i = 0; testData[i].string != 0; ++i) {
      TEST_STATUS("Checking '" << testData[i].mask << '\'');
      StringMask mask(testData[i].mask);
      
      TEST_STATUS("\t'" << testData[i].string <<
		  "' (case-insensitive)");
      TEST_ASSERT(mask.matches(testData[i].string) ==
		  testData[i].expectedResult);

      TEST_STATUS("\t'" << testData[i].string <<
		  "' (case-sensitive)");
      TEST_ASSERT(mask.matchesCase(testData[i].string) ==
		  testData[i].expectedResultCase);
   }
   
   TEST_STATUS("All tests were successful");
   return TEST_RETURN_PASS;
}
