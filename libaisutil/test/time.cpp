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

extern "C" {
#include <unistd.h>
};
#include <aisutil/time.h>
#include <ctime>

#include "tests.h"


int main(int argc, char **argv)
{
   TEST_STATUS("Creating a new Time:: object (blank)");
   AISutil::Time timeA;
   TEST_FAIL_IF((timeA.seconds != 0) ||
		(timeA.nanoseconds != 0));

   TEST_STATUS("Setting the time");
   TEST_FAIL_IF(!timeA.setTime() ||
		(timeA.seconds == 0));

   TEST_STATUS("Sleeping for a bit");
   TEST_FAIL_IF(sleep(3) != 0); // <=- we need to sleep for the next test..

   TEST_STATUS("Creating a new Time:: object (of the current time)");
   const AISutil::Time timeB(true);
   TEST_FAIL_IF(timeB.seconds == 0);


   TEST_STATUS("Checking that times see themselves as being identical");
   TEST_FAIL_IF((timeA != timeA) ||
		!(timeA == timeA) ||
		(timeB != timeB) ||
		!(timeB == timeB));

   TEST_STATUS("Checking that the first and second times are not identical");
   TEST_FAIL_IF((timeA == timeB) ||
		(timeB == timeA) ||
		!(timeA != timeB) ||
		!(timeB != timeA));

   TEST_STATUS("Checking less than/greater than");
   TEST_FAIL_IF((timeA < timeA) ||
		(timeA > timeA) ||
		(timeB < timeB) ||
		(timeB > timeB));

   TEST_STATUS("Checking that the first time is older");
   TEST_FAIL_IF((timeA > timeB) ||
		(timeB < timeA));

   TEST_STATUS("Checking less than or equal to/greater than or equal to");
   TEST_FAIL_IF(!(timeA >= timeA) ||
		!(timeA <= timeA) ||
		!(timeB >= timeB) ||
		!(timeB <= timeB));


   TEST_STATUS("Creating a new Time:: object (copy of first)");
   AISutil::Time timeC(timeA);
   TEST_FAIL_IF(timeC != timeA);

   TEST_STATUS("Assigning the second time to the third time");
   timeC = timeB;
   TEST_FAIL_IF((timeC != timeB) &&
		(timeC == timeA));


   TEST_STATUS("Creating a new Time:: object (from a time_t)");
   static const time_t time_t_timeA = (time_t)0xAABBCCDD;
   AISutil::Time time_t_time(time_t_timeA);
   TEST_FAIL_IF((time_t_time.seconds !=
		 (AISutil::Time::seconds_type)time_t_timeA) ||
		(time_t_time.nanoseconds != 0));

   TEST_STATUS("Reassigning this time (from a time_t)");
   static const time_t time_t_timeB = (time_t)0xDDCCBBAA;
   time_t_time = time_t_timeB;
   TEST_FAIL_IF((time_t_time.seconds !=
		 (AISutil::Time::seconds_type)time_t_timeB) ||
		(time_t_time.nanoseconds != 0));

   TEST_STATUS("Typecasting this time (to a time_t)");
   const time_t time_t_timeC =
     static_cast<time_t>(time_t_time);
   TEST_FAIL_IF(((AISutil::Time::seconds_type)time_t_timeC !=
		 time_t_time.seconds) ||
		(time_t_timeC != time_t_timeB));

   
   TEST_STATUS("Creating a new Time:: object (from a timespec)");
   struct timespec timespec_timeA;
   timespec_timeA.tv_sec = 0x12345678;
   timespec_timeA.tv_nsec = 0x0000EEFF;
   AISutil::Time timespec_time(timespec_timeA);
   TEST_FAIL_IF((timespec_time.seconds !=
		 (AISutil::Time::seconds_type)timespec_timeA.tv_sec) ||
		(timespec_time.nanoseconds !=
		 (AISutil::Time::nanoseconds_type)timespec_timeA.tv_nsec));

   TEST_STATUS("Reassigning this time (from a timespec)");
   struct timespec timespec_timeB;
   timespec_timeB.tv_sec = 0xAABBAABB;
   timespec_timeB.tv_nsec = 0x00012345;
   timespec_time = timespec_timeB;
   TEST_FAIL_IF((timespec_time.seconds !=
		 (AISutil::Time::seconds_type)timespec_timeB.tv_sec) ||
		(timespec_time.nanoseconds != 
		 (AISutil::Time::nanoseconds_type)timespec_timeB.tv_nsec));

   TEST_STATUS("Typecasting this time (to a timespec)");
   struct timespec timespec_timeC =
     static_cast<struct timespec>(timespec_time);
   TEST_FAIL_IF((((AISutil::Time::seconds_type)timespec_timeC.tv_sec !=
		  timespec_time.seconds) ||
		 ((AISutil::Time::seconds_type)timespec_timeC.tv_nsec !=
		  timespec_time.nanoseconds)) ||
		((timespec_timeC.tv_sec != timespec_timeB.tv_sec) ||
		 (timespec_timeC.tv_nsec != timespec_timeB.tv_nsec)));
   

   TEST_STATUS("Creating a new Time:: object (from a timeval)");
   struct timeval timeval_timeA;
   timeval_timeA.tv_sec = 0x22334455;
   timeval_timeA.tv_usec = 0x000000AB;
   AISutil::Time timeval_time(timeval_timeA);
   TEST_FAIL_IF((timeval_time.seconds !=
		 (AISutil::Time::seconds_type)timeval_timeA.tv_sec) ||
		(timeval_time.nanoseconds !=
		 (AISutil::Time::nanoseconds_type)
		 (timeval_timeA.tv_usec * 1000)));

   TEST_STATUS("Reassigning this time (from a timeval)");
   struct timeval timeval_timeB;
   timeval_timeB.tv_sec = 0x99887766;
   timeval_timeB.tv_usec = 0x00000123;
   timeval_time = timeval_timeB;
   TEST_FAIL_IF((timeval_time.seconds !=
		 (AISutil::Time::seconds_type)timeval_timeB.tv_sec) ||
		(timeval_time.nanoseconds != 
		 (AISutil::Time::nanoseconds_type)
		 (timeval_timeB.tv_usec * 1000)));

   TEST_STATUS("Typecasting this time (to a timespec)");
   struct timeval timeval_timeC =
     static_cast<struct timeval>(timeval_time);
   TEST_FAIL_IF((((AISutil::Time::seconds_type)timeval_timeC.tv_sec !=
		  timeval_time.seconds) ||
		 ((AISutil::Time::seconds_type)
		  (timeval_timeC.tv_usec * 1000) !=
		  timeval_time.nanoseconds)) ||
		((timeval_timeC.tv_sec != timeval_timeB.tv_sec) ||
		 (timeval_timeC.tv_usec != timeval_timeB.tv_usec)));
   

   TEST_STATUS("All tests were successful");
   return TEST_RETURN_PASS;
}
