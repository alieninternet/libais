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

#include <aisutil/sha1.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

#include "tests.h"

using namespace AIS::Util;


// Number of bases to check digest_type::toStr() for
static const unsigned int baseCheckCount = 2;


// digestToStr() base/padding pairs
struct {
   const unsigned char base;
   const std::string::size_type pad;
} static const digestToStrBaseTable[baseCheckCount] = {
     { 2,	32 },	// binary
     { 16,	8 },	// hexadecimal (sexadecimal)
};


// Test data (known results)
struct {
   const char* const string;
   const std::string::size_type stringLength;
   const unsigned char expectedDigest[20];
   const char* const expectedDigestStrings[baseCheckCount];
} static const testData[] = {
   // Null test
     {
	"\0null\0null",
	  10,
	  {
	     0xC0, 0xE9, 0xFC, 0x92,
	     0x26, 0x68, 0x23, 0xFD,
	     0xB5, 0x14, 0xDA, 0x5A,
	     0x85, 0xBB, 0x1A, 0x81,
	     0x1E, 0x31, 0xDA, 0x4E
	  },
	  {
	     "11000000111010011111110010010010"
	     "00100110011010000010001111111101"
	     "10110101000101001101101001011010"
	     "10000101101110110001101010000001"
	     "00011110001100011101101001001110",
	     "C0E9FC92"
	     "266823FD"
	     "B514DA5A"
	     "85BB1A81"
	     "1E31DA4E"
	  }
     },
   // Control char test
     {
	"\000\001\002\003\004\005\006\007\010\011\012\013\014\015\016\017"
	"\020\021\022\023\024\025\026\027\030\031\032\033\034\035\036\037",
	  32,
	  {
	     0xAE, 0x5B, 0xD8, 0xEF,
	     0xEA, 0x53, 0x22, 0xC4,
	     0xD9, 0x98, 0x6D, 0x06,
	     0x68, 0x0A, 0x78, 0x13,
	     0x92, 0xF9, 0xA6, 0x42
	  },
	  {
	     "10101110010110111101100011101111"
	     "11101010010100110010001011000100"
	     "11011001100110000110110100000110"
	     "01101000000010100111100000010011"
	     "10010010111110011010011001000010",
	     "AE5BD8EF"
	     "EA5322C4"
	     "D9986D06"
	     "680A7813"
	     "92F9A642"
	  }
     },
   // This test data is from RFC3174 (lonesome char and exact multiple of 512)
     { 
	"a",
	  1,
	  {
	     0x86, 0xF7, 0xE4, 0x37,
	     0xFA, 0xA5, 0xA7, 0xFC,
	     0xE1, 0x5D, 0x1D, 0xDC,
	     0xB9, 0xEA, 0xEA, 0xEA,
	     0x37, 0x76, 0x67, 0xB8
	  },
	  {
	     "10000110111101111110010000110111"
	     "11111010101001011010011111111100"
	     "11100001010111010001110111011100"
	     "10111001111010101110101011101010"
	     "00110111011101100110011110111000",
	     "86F7E437"
	     "FAA5A7FC"
	     "E15D1DDC"
	     "B9EAEAEA"
	     "377667B8"
	  }
     },
     { 
	"01234567012345670123456701234567"
	"01234567012345670123456701234567",
	  64,
	  {
	     0xE0, 0xC0, 0x94, 0xE8,
	     0x67, 0xEF, 0x46, 0xC3,
	     0x50, 0xEF, 0x54, 0xA7,
	     0xF5, 0x9D, 0xD6, 0x0B,
	     0xED, 0x92, 0xAE, 0x83
	  },
	  {
	     "11100000110000001001010011101000"
	     "01100111111011110100011011000011"
	     "01010000111011110101010010100111"
	     "11110101100111011101011000001011"
	     "11101101100100101010111010000011",
	     "E0C094E8"
	     "67EF46C3"
	     "50EF54A7"
	     "F59DD60B"
	     "ED92AE83"
	  }
     },
     { 0, 0, { 0 }, { 0 } }
};


int main(int argc, char **argv)
{
   TEST_STATUS("Creating two dummy digests");
   SHA1_Digest digest1;
   digest1.u_long[0] = 0x00011122;
   digest1.u_long[1] = 0x23334445;
   digest1.u_long[2] = 0x55666777;
   digest1.u_long[3] = 0x888999AA;
   digest1.u_long[4] = 0xABBBCCCD;
   SHA1_Digest digest2;
   digest2.u_long[0] = 0xDDEEEFFF;
   digest2.u_long[1] = 0xEEEDDDCC;
   digest2.u_long[2] = 0xCBBBAAA9;
   digest2.u_long[3] = 0x99888777;
   digest2.u_long[4] = 0x66655544;
   
   TEST_STATUS("Making sure the two digests are not equal");
   TEST_FAIL_IF((digest1 == digest2) ||
		(digest2 == digest1) ||
		!(digest1 != digest2) ||
		!(digest2 != digest1));
   
   TEST_STATUS("Checking that a null digest is really empty");
   SHA1_Digest nullDigest;
   TEST_ASSERT((nullDigest.u_long[0] == 0) &&
	       (nullDigest.u_long[1] == 0) &&
	       (nullDigest.u_long[2] == 0) &&
	       (nullDigest.u_long[3] == 0) &&
	       (nullDigest.u_long[4] == 0));
   
   TEST_STATUS("Checking that the null digest knows it's empty");
   TEST_ASSERT(nullDigest.isNull());
   
   TEST_STATUS("Making a third dummy digest (from the null digest)");
   SHA1_Digest digest3(nullDigest);
   TEST_ASSERT((digest3.u_long[0] == 0) &&
	       (digest3.u_long[1] == 0) &&
	       (digest3.u_long[2] == 0) &&
	       (digest3.u_long[3] == 0) &&
	       (digest3.u_long[4] == 0));
   
   TEST_STATUS("Reassigning third digest (with the first dummy)");
   digest3 = digest1;
   TEST_ASSERT((digest3 == digest1) &&
	       (digest3 != digest2));
   
   
   for (unsigned int i = 0; testData[i].string != 0; ++i) {
      TEST_STATUS("Hashing '" << testData[i].string << '\'');
      const std::string testString(testData[i].string,
				   testData[i].stringLength);
      SHA1_Digest digest(testString);
      
      TEST_STATUS("\tMaking sure the return was not null/empty");
      TEST_FAIL_IF(digest.isNull());
      
      TEST_STATUS("\tChecking hash");
      if (argc > 1) {
	 std::cout << std::setfill('0') << "\t  Want: ";
	 for (unsigned int j = 0; j < 20; ++j) {
	    std::cout << std::hex << std::setw(2) <<
	      (unsigned int)testData[i].expectedDigest[j] << 
	      (((j % 4) == 3) ? ' ' : '.');
	 }
	 std::cout << "\n\t   Got: ";
	 for (unsigned int j = 0; j < 20; ++j) {
	    std::cout << std::hex << std::setw(2) <<
	      (unsigned int)digest.u_char[j] <<
	      (((j % 4) == 3) ? ' ' : '.');
	 }
	 std::cout << std::endl;
      }
      TEST_ASSERT(::memcmp((const void*)&digest.u_char,
			   (const void*)&testData[i].expectedDigest,
			   20) == 0);
      
      TEST_STATUS("\tChecking digestToStr() output");
      for (unsigned int j = 0; j < baseCheckCount; ++j) {
	 TEST_STATUS("\t\tGenerating string for base " <<
		     (unsigned int)digestToStrBaseTable[j].base);
	 std::string digestStr = digest.toStr(digestToStrBaseTable[j].base,
					      digestToStrBaseTable[j].pad);
	 TEST_FAIL_IF(digestStr.empty() ||
		      (digestStr.size() != (digestToStrBaseTable[j].pad * 5)));

	 TEST_STATUS("\t\t  Want: " << testData[i].expectedDigestStrings[j] <<
		     "\n\t\t   Got: " << digestStr);
	 TEST_FAIL_IF(digestStr != testData[i].expectedDigestStrings[j]);
      }
   }
   

   TEST_STATUS("All tests were successful");
   return TEST_RETURN_PASS;
}
