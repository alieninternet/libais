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

#include <aisutil/utils.h>

#include "tests.h"

using namespace AIS::Util;


int main(int argc, char **argv)
{
   TEST_STATUS("toBool(): Checking boolean strings");
   struct {
      const char* const string;
      const int expectedValue;
   } static const toBoolTests[] = {
      { "YeS",		1 },
      { "No",		0 },
      { "TrUe",		1 },
      { "fAlSe",	0 },
      { "oN",		1 },
      { "oFf",		0 },
      { "1",		1 },
      { "28742342",	1 },
      { "+123",		1 },
      { "0",		0 },
      { "-123",		0 },
      { "0xABCD",	1 },
      { "0x0",		0 },
      { "012",		1 },
      { "000",		0 },
      { 0, 0 }
   };
   for (unsigned int i = 0; toBoolTests[i].string != 0; ++i) {
      TEST_STATUS(" -=> " << toBoolTests[i].string);
      TEST_FAIL_IF(Utils::toBool(toBoolTests[i].string) !=
		   toBoolTests[i].expectedValue);
   }
   
   TEST_STATUS("toBool(): Checking unknown boolean strings");
   TEST_FAIL_IF(Utils::toBool("this should break") != -1);
   
   
   TEST_STATUS("baseXStr(): Checking value to string");
   static const unsigned long number = 0x13579ACE;
   static const char* const baseXStrTestResults[] = {
      0,				// <=- there is no base-0 or base-1
      0,
      "10011010101111001101011001110",	// binary (2)
      "211121121201210101",		// ternary (3)
      "103111321223032",		// quaternary (4)
      "1131033231431",			// quinary (5)
      "52111201314",			// senary (6)
      "11020163350",			// septenary (7)
      "2325715316",			// octal (8)
      "747551711",			// nonary (9)
      "324508366",			// decimal (10)
      "1571A3A36",			// undenary (11)
      "9081623A",			// duodecimal (12)
      "522CC2B0",			// tridecimal (13)
      "311530D0",			// quattuordecimal (14)
      "1D750961",			// quindecimal (15)
      "13579ACE",			// hexadecimal (16; sexadecimal)
      "D795G57",			// septendecimal (17)
      "99D4D0A",			// octodecimal (18)
      "6H1162D",			// nonadecimal (19)
      "5183AI6",			// vigesimal (20)
      "3G9C6D7",
      "2IL5LI6",
      "249E489",
      "1GI26DM",
      "185ID9G",
      "11833P0",
      "MGGJLA",
      "INQHKE",
      "FNNF3J",
      "DAIOPG",				// trigesimal (30)
      "BABPOP",
      "9LF6ME",
      "89KUFS",
      "74SCJO",
      "668ORL",
      "5D7C9A",
      "4P5IGE",
      "43NYTW",
      "3NALcD",
      "36UHT6",				// quadragesimal (40)
      "2WYGY8",
      "2KC1RS",
      "28dLY8",
      "1gPLg6",
      "1Y6621",
      "1QLfFW",
      "1JNRdF",
      "1D6DUk",
      "17EDOZ",
      "11k3HG",				// quinquagesimal (50)
      "lnGl7",
      "iJkPQ",
      "f6bRJ",
      "c8jOA",
      "ZPPR6",
      "WtkOE",
      "UgFQD",
      "SdB1m",
      "Qk2hl",
      "P2LCk",				// sexagesimal (60)
      "NQeyH",
      "LxbRu",
      "KbnkS",
      "JLvhE",
      "IBfkQ",
      "H6mvS",
      "G6?jU",
      "FC39w",
      "ELumt",
      "Da6Du",				// septagesimal (70)
      "CslvQ",
      "C5U4k",
      "BVCw6",
      "Ayy8E",
      "AJFSG",
      "9tIE-",
      "9H!US",
      "8x?:q",
      "8QEG%",
      "7<$Yk",				// septagesimal (80)
      "7hoGA",
      "7EjH8",
      "6+iOT",
      "6hgY-",
      "6IYtf",
      0
   };
   for (unsigned int i = 2; baseXStrTestResults[i] != 0; ++i) {
      TEST_STATUS(" -=> Base " << i);
      TEST_FAIL_IF(Utils::baseXStr(number, i) != baseXStrTestResults[i]);
   }


   TEST_END;
}
