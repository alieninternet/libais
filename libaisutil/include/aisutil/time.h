/* $Id$
 * 
 * Copyright (c) 1996,2003 Alien Internet Services
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

#ifndef _INCLUDE_AISUTIL_TIME_H_
# define _INCLUDE_AISUTIL_TIME_H_ 1

# include <string>
# include <ctime>
# include <sys/time.h>

namespace AISutil {
   //! Basic time routines (supposed to be simplistic)
   struct Time {
      //! Seconds (since the UNIX Epoch; 1970-01-01 00:00)
      signed long seconds;

      //! Nanoseconds (additional to 'seconds')
      signed long nanoseconds;

      
      //! Default constructor
      Time(void)
	: seconds(0), nanoseconds(0)
	{};
      
      //! Copy constructor
      Time(const Time& time)
	: seconds(time.seconds),
          nanoseconds(time.nanoseconds)
	{};
      
      //! Constructor (from a 'time_t')
      Time(const time_t& time)
	: seconds(time),
          nanoseconds(0)
	{};
      
      //! Constructor (from a 'struct timespec')
      Time(const timespec& time)
	: seconds(time.tv_sec),
          nanoseconds(time.tv_nsec)
	{};
      
      //! Constructor (from a 'struct timeval')
      Time(const timeval& time)
	: seconds(time.tv_sec),
          nanoseconds(time.tv_usec * 1000)
	{};
      
      
      //! Destructor
      ~Time(void)
	{};
      
      
      //! Addition operator
      const Time operator+(const Time& rhs) const;

      //! Addition assignment operator
      const Time& operator+=(const Time& rhs)
	{ return ((*this) = (*this) + rhs); };
      
      //! Subtraction operator
      const Time operator-(const Time& rhs) const;

      //! Subtraction assignment operator
      const Time& operator-=(const Time& rhs)
	{ return ((*this) = (*this) - rhs); };
      
      //! Division operator
      const double operator/(const Time& rhs) const;


      //! Equality operator
      const bool operator==(const Time& rhs) const
	{
	   return ((seconds == rhs.seconds) &&
		   (nanoseconds == rhs.nanoseconds));
	};
      
      //! Not equal-to operator
      const bool operator!=(const Time& rhs) const
	{ return (!((*this) == rhs)); };
      
      //! Greater-than operator
      const bool operator>(const Time& rhs) const
	{
	   if ((seconds > rhs.seconds) ||
	       ((seconds == rhs.seconds) &&
		(nanoseconds > rhs.nanoseconds))) {
	      return true;
	   }
	   return false;
	};
      
      //! Less-than operator
      const bool operator<(const Time& rhs) const
	{
	   if ((seconds < rhs.seconds) ||
	       ((seconds == rhs.seconds) &&
		(nanoseconds < rhs.nanoseconds))) {
	      return true;
	   }
	   return false;
	};
      
      //! Greater-than or equal to operator
      const bool operator>=(const Time& rhs) const
	{ return (!((*this) < rhs)); };
      
      //! Less-than or equal to operator
      const bool operator<=(const Time& rhs) const
	{ return (!((*this) > rhs)); };

      
      //! Convert this to a 'time_t' (we hope)
      operator time_t(void) const
	{ return time_t(seconds); };

      //! Convert this to a 'struct timespec'
      operator timespec(void) const
	{
	   timespec result;
	   result.tv_sec = seconds;
	   result.tv_nsec = nanoseconds;
	   return result;
	};

      //! Convert this to a 'struct timeval'
      operator timeval(void) const
	{
	   timeval result;
	   result.tv_sec = seconds;
	   result.tv_usec = nanoseconds / 1000;
	   return result;
	};

      
      //! Assignment operator (from a 'time_t')
      const Time& operator=(const time_t& time)
	{
	   this->seconds = time;
	   this->nanoseconds = 0;
	   return (*this);
	};

      //! Assignment operator (from a 'struct timespec')
      const Time& operator=(const timespec& time)
	{
	   this->seconds = time.tv_sec;
	   this->nanoseconds = time.tv_nsec;
	   return (*this);
	};
      
      //! Assignment operator (from a 'struct timeval')
      const Time& operator=(const timeval& time)
	{
	   this->seconds = time.tv_sec;
	   this->nanoseconds = time.tv_usec * 1000;
	   return (*this);
	};

      
      //! Set the time to the time now (according to the local timezone)
      bool setTime(void);
   }; // struct Time
}; // namespace AISutil
   
#endif // _INCLUDE_AISUTIL_TIME_H_
