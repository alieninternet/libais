/* $Id$
 * 
 * Copyright (c) 2004 Alien Internet Services
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

#include <aisutil/config/config.h>
#include <iostream>

#include "tests.h"

using namespace AIS::Util;


// Table of configuration definitions
static Config::defTable_type definitionTable = {
     { 0, 0, 0, 0, 0, 0 }
};


/* Error reporting mechanism.
 * Due to the very nature of the configuration parser, this is how the tests
 * are actually monitored. The error responces are synchronised with the
 * test configuration file and are checked based on correct error responces.
 */
class TestReporter : public Config::ErrorReporter {
 private:
   const bool silent;
   
 public:
   TestReporter(const bool _silent)
     : silent(_silent)
     {};
   
   
   ~TestReporter(void)
     {};
};


// Configuration class itself
class TestConfig : public Config::Config {
 private:
   // Test variables
   bool testBool;

   signed int testSignedInt;
   unsigned int testUnsignedInt;

   signed char testSignedChar;
   unsigned char testUnsignedChar;

   signed short testSignedShort;
   unsigned short testUnsighedShort;
   
   signed long testSignedLong;
   unsigned long testUnsignedLong;
   
   
 public:   
   TestConfig(void)
     : Config::Config(definitionTable)
     {};
   
   ~TestConfig(void) 
     {};
};


int main(int argc, char **argv)
{
   TEST_STATUS("Creating local error reporting/tracking mechanism");
   TestReporter reporter(TEST_VERBOSE);
   
   TEST_STATUS("Creating configuration class");
   TestConfig configuration;
   

   TEST_END;
}
