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

#include <aisutil/peakcount.h>

#include "tests.h"

using namespace AIS::Util;


int main(int argc, char **argv)
{
   TEST_STATUS("Creating a new PeakCount<int>:: object (zeroed)");
   PeakCount < int > pcA;
   TEST_FAIL_IF((pcA.getValue() != 0) ||
		(pcA.getPeak() != 0) ||
		(pcA != 0));

   TEST_STATUS("operator+");
   TEST_FAIL_IF(((pcA + 123).getValue() != 123) ||
		(pcA.getValue() != 0) ||
		(pcA.getPeak() != 0));

   TEST_STATUS("operator+=");
   TEST_FAIL_IF(((pcA += 456).getValue() != 456) ||
		(pcA.getValue() != 456) ||
		(pcA.getPeak() != 456));

   TEST_STATUS("operator-");
   TEST_FAIL_IF(((pcA - 123).getValue() != 333) ||
		(pcA.getValue() != 456) ||
		(pcA.getPeak() != 456));
   
   TEST_STATUS("operator-=");
   TEST_FAIL_IF(((pcA -= 321).getValue() != 135) ||
		(pcA.getValue() != 135) ||
		(pcA.getPeak() != 456));
   
   TEST_STATUS("operator++ prefix");
   TEST_FAIL_IF(((++pcA).getValue() != 136) ||
		(pcA.getValue() != 136) ||
		(pcA.getPeak() != 456));
   
   TEST_STATUS("operator++ postfix");
   TEST_FAIL_IF(((pcA++).getValue() != 136) ||
		(pcA.getValue() != 137) ||
		(pcA.getPeak() != 456));
   
   TEST_STATUS("operator-- prefix");
   TEST_FAIL_IF(((--pcA).getValue() != 136) ||
		(pcA.getValue() != 136) ||
		(pcA.getPeak() != 456));
   
   TEST_STATUS("operator-- postfix");
   TEST_FAIL_IF(((pcA--).getValue() != 136) ||
		(pcA.getValue() != 135) ||
		(pcA.getPeak() != 456));
   
   TEST_STATUS("Creating a new PeakCount<int>:: object (initialised)");
   PeakCount < int > pcB(654, 321); // peak is lower than value intentionally
   TEST_FAIL_IF((pcB.getValue() != 654) ||
		(pcB.getPeak() != 654) ||
		(pcB != 654));

   TEST_STATUS("Adding PeakCount's together");
   PeakCount < int > pcC = pcA + pcB;
   TEST_FAIL_IF((pcC.getValue() != (pcA.getValue() + pcB.getValue())) ||
		(pcC.getPeak() != (pcA.getPeak() + pcB.getPeak())));
   
   TEST_END;
}
