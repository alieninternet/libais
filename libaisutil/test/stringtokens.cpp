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

#include <aisutil/string/tokens.h>

#include "tests.h"

using namespace AIS::Util;


struct {
   const char* const string;
   const std::string::size_type stringLength;
   const char delimiter;			// <=- 0377 = none specified
   const unsigned int expectedTokenCount;
   const char* const expectedTokens[12];
} static const testData[] = {
     { 
	"This is four tokens.",
	  20,
	  ' ',
	  4,
	  {
	     "This",
	     "is",
	     "four",
	     "tokens.",
	     0
	  }
     },
     {
	"This is\tthree tokens.",
	  21,
	  ' ',
	  3,
	  {
	     "This",
	     "is\tthree",
	     "tokens.",
	     0
	  }
     },
     {
	"..But\tthis is\tfive tokens.",
	  26,
	  '\377',
	  5,
	  {
	     "..But",
	     "this",
	     "is",
	     "five",
	     "tokens.",
	     0
	  }
     },
     {
	"This:is to:only be:five:tokens",
	  30,
	  ':',
	  5,
	  {
	     "This",
	     "is to",
	     "only be",
	     "five",
	     "tokens",
	     0
	  }
     },
     {
	"But::this::should::be::eleven::tokens",
	  37,
	  ':',
	  11,
	  {
	     "But",
	     "",
	     "this",
	     "",
	     "should",
	     "",
	     "be",
	     "",
	     "eleven",
	     "",
	     "tokens",
	     0
	  }
     },
     {
	"This\0weird\0one\0should\0be\0seven\0tokens",
	  37,
	  '\0',
	  7,
	  {
	     "This",
	     "weird",
	     "one",
	     "should",
	     "be",
	     "seven",
	     "tokens",
	     0
	  }
     },
     { 0, 0, 0, 0, { 0 } }
};


int main(int argc, char **argv)
{
   for (unsigned int i = 0; testData[i].string != 0; ++i) {
      TEST_STATUS("Tokenising '" << testData[i].string << '\'');
      StringTokens st = std::string(testData[i].string,
				    testData[i].stringLength);
      TEST_FAIL_IF(st.empty());
      
      TEST_STATUS("\tChecking token count");
      TEST_ASSERT(((testData[i].delimiter == '\377') ?
		   st.countTokens() : st.countTokens(testData[i].delimiter)) ==
		  testData[i].expectedTokenCount);
      
      TEST_STATUS("\tChecking rest() is complete (with the position at 0)");
      TEST_ASSERT(st.rest() == st);
      
      TEST_STATUS("\tChecking tokens");
      for (unsigned int j = 0; j < testData[i].expectedTokenCount; ++j) {
	 if (j != testData[i].expectedTokenCount) {
	    TEST_STATUS("\t\tMaking sure there are more token(s) to read");
	    TEST_ASSERT(st.hasMoreTokens());
	 }

	 TEST_STATUS("\t\tReading the next token (" << (j + 1) <<
		     ")\n\t\t  Want: '" << testData[i].expectedTokens[j] <<
		     '\'');
	 const std::string token = 
	   ((testData[i].delimiter == '\377') ?
	    st.nextToken() : st.nextToken(testData[i].delimiter));
	 TEST_STATUS("\t\t   Got: '" << token << '\'');
	 TEST_ASSERT(token == testData[i].expectedTokens[j]);
	 
      }
   }

   TEST_STATUS("All tests were successful");
   return TEST_RETURN_PASS;
}
