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

/*! \file
 * \brief Rudimentary time routines
 * 
 * Basic time routines
 */ 

# include <string>
# include <ctime>
# include <sys/time.h>

namespace AIS {
   namespace Util {
      /*!
       * \brief Basic time routines
       * 
       * These basic time routines are intended to be extremely simplistic.
       * The main goal for these time routines has been for time-stamping
       * purposes.
       * 
       * Intentionally, this class doesn't offer any special date formatting
       * routines, since such routines are already provided by <em>Standard
       * C</em> and <em>POSIX 1003.1-2001</em>.
       * 
       * The class offers the ability to store time in \a seconds and 
       * \a nanoseconds, however the precision of the \a nanoseconds field is
       * based primarily on the operating system and architecture of the
       * machine you compile the library on.
       * 
       * The time routines also offer a convenient way to convert between
       * common time types, such as \c time_t, \c struct \c timespec and
       * \c struct \c timeval (if they are available).
       * 
       * The two most important factors of these routines are the arithmetic
       * functions and the boolean functions. Times can be easily added,
       * subtracted, and divided, with \a nanoseconds overflowing into
       * \a seconds appropriately. Comparisons between times are equally
       * simplified.
       * 
       * The ability to obtain the current system time has been provided
       * purely for convenience.
       */
      struct Time {
	 //! Type of the \a seconds variable
	 typedef signed long seconds_type;
	 
	 //! Type of the \a nanoseconds variable
	 typedef signed long nanoseconds_type;
	 
	 
	 /*!
	  * \brief The number of nanoseconds in a second
	  * 
	  * This represents the number of nanoseconds in a second, and is here
	  * for convenience to assist in arithmetic operations.
	  * 
	  * A nanosecond is defined as a \e billionth \e of \e a \e second.
	  */
	 static const nanoseconds_type max_nsec = 1000000000;
	 
	 /*!
	  * \brief Number of seconds
	  *
	  * This is the number of \a seconds field. If the time set from the
	  * system, this represents the number of seconds since the \e UNIX
	  * \e Epoch (1970-01-01 00:00:00.0)
	  */
	 seconds_type seconds;
	 
	 /*!
	  * \brief Number of nanoseconds
	  * 
	  * This is the number of \a nanoseconds, following the \a seconds
	  * count. It's \e loosely guaranteed to be a \e fraction of a second,
	  * and should therefore always be a value less than 
	  */
	 nanoseconds_type nanoseconds;
	 
	 
	 /*!
	  * \brief Default constructor
	  *
	  * This is a blank constructor, and will initialise the structure to
	  * zeros.
	  */
	 Time(void)
	   : seconds(0),
	     nanoseconds(0)
	   {};
      
	 /*!
	  * \brief Constructor
	  * 
	  * Create a new Time structure with the given \p _seconds and also
	  * (optionally) \p _nanoseconds values. Since the \a nanoseconds
	  * variable must represent a \e fraction of a second, it will be
	  * checked and overflowed as required to avoid misrepresentation.
	  * 
	  * \param _seconds The \a seconds initialiser
	  * \param _nanoseconds The \a nanoseconds initialiser
	  */
	 explicit Time(const seconds_type _seconds,
		       const nanoseconds_type _nanoseconds)
	   : seconds(_seconds),
	     nanoseconds(_nanoseconds)
	   {
	      // The nanoseconds field doesn't represent more than one second
	      while (nanoseconds >= max_nsec) {
		 ++seconds;
		 nanoseconds -= max_nsec;
	      }
	      while (nanoseconds <= max_nsec) {
		 --seconds;
		 nanoseconds += max_nsec;
	      }
	   };
	 
	 /*!
	  * \brief Copy constructor
	  * 
	  * Creates a brand new copy of another Time structure
	  * 
	  * \param time The Time structure to create a copy from
	  */
	 Time(const Time& time)
	   : seconds(time.seconds),
	     nanoseconds(time.nanoseconds)
	   {};
      
	 /*!
	  * \brief Current time constructor
	  * 
	  * For convenience, passing a boolean value of \c true here will
	  * cause the current system time to be set on this object when it is
	  * created. The result will be a Time structure representing the time
	  * it was created.
	  */
	 explicit Time(const bool setTimeNow)
	   : seconds(0),
	     nanoseconds(0)
	   {
	      if (setTimeNow) {
		 (void)setTime();
	      }
	   };
      
	 /*!
	  * \brief Constructor (from a '\c time_t')
	  * 
	  * Convert a time of the \c time_t type into a new Time structure.
	  * 
	  * \param time The time you wish to convert, of \c time_t type
	  */
	 Time(const time_t& time)
	   : seconds(time),
	     nanoseconds(0)
	   {};
      
	 /*!
	  * \brief Constructor (from a '\c struct \c timespec')
	  * 
	  * This will convert a \c struct \c timespec time structure into a
	  * Time structure.
	  * 
	  * \param time The \c struct \c timespec time you wish to convert
	  */
	 Time(const struct timespec& time)
	   : seconds(time.tv_sec),
	     nanoseconds(time.tv_nsec)
	   {};
      
	 /*!
	  * \brief Constructor (from a '\c struct \c timeval')
	  * 
	  * This will convert a \c struct \c timeval structure to a Time
	  * structure. Note that the precision of the \c timeval structure is
	  * only as small as \e microseconds.
	  * 
	  * \param time A \c struct \c timeval time to convert
	  */
	 Time(const struct timeval& time)
	   : seconds(time.tv_sec),
	     nanoseconds(time.tv_usec * 1000)
	   {};
      
      
	 //! Destructor
	 virtual ~Time(void)
	   {};

	 
	 /*!
	  * \brief Addition operator
	  * 
	  * Add the given time (\p rhs) to this time. If \a nanoseconds
	  * overflows and becomes equal to the value of one second, the value
	  * will be overflowed into the \a seconds variable to ensure an
	  * accurate addition.
	  * 
	  * \param rhs The time to add to this time
	  * \return The result of the addition
	  */
	 const Time operator+(const Time& rhs) const;
	 
	 /*!
	  * \brief Addition assignment operator
	  * 
	  * \param rhs The time to add to this time
	  * \return A reference to this time instance after the addition
	  */
	 template <class T>
	   const Time& operator+=(const T& rhs)
	   { return ((*this) = (*this) + rhs); };


	 /*!
	  * \brief Subtraction operator
	  *
	  * Subtract the given time (\p rhs) from this time. If the
	  * \a nanoseconds variable underflows by a value equal to that of
	  * one second, the \a seconds variable will be adjusted accordingly
	  * to provide an accurate representation of the time.
	  * 
	  * \param rhs The time to subtract from this time
	  * \return The resultant time after subtraction
	  */
	 const Time operator-(const Time& rhs) const;
	 
	 /*!
	  * \brief Subtraction assignment operator
	  * 
	  * \param rhs The time to subtract from this time
	  * \return A reference to this time instance after the subtraction
	  */
	 template <class T>
	   const Time& operator-=(const T& rhs)
	   { return ((*this) = (*this) - rhs); };

	 
	 /*!
	  * \brief Division operator (nanosecond fractions)
	  * 
	  * This will divide this time by the given time (\p rhs) and return
	  * the time in nanoseconds
	  * 
	  * \warning The resultant value's quantisation may vary depending on
	  *    the operating system and computer architecture.
	  * \param rhs The time slice to divide this time into
	  * \return The resulting time in nanoseconds
	  */
	 const double operator/(const Time& rhs) const;
	 
	 /*!
	  * \brief Division operator (nanosecond fractions)
	  * 
	  * This will divide this time by the given number (\p rhs) and return
	  * the time in nanoseconds.
	  * 
	  * \warning The resultant value's quantisation may vary depending on
	  *    the operating system and computer architecture.
	  * \param rhs The time slice to divide this time into
	  * \return The resulting time in nanoseconds
	  */
	 const double operator/(const unsigned int rhs) const
	   { 
	      return ((unsigned long long)
		      ((seconds * max_nsec) + nanoseconds) /
		      rhs);
	   };
	 
	 /*!
	  * \brief Division operator (Time amounts)
	  * 
	  * \param rhs The amount to divide this time by
	  * \return The divided time as a Time structure
	  */
	 template <class T>
	   const Time operator/(const T& rhs) const
	   {
	      const double result = (*this) / rhs;
	      return Time((result / max_nsec), (result % max_nsec));
	   };
	 
	 /*!
	  * \brief Division assignment operator
	  * 
	  * \param rhs The amount to divide from this time
	  * \return A reference to this time instance after the division
	  */
	 template <class T>
	   const Time& operator/=(const T& rhs)
	   { return ((*this) = (*this) / rhs); };

	 
	 /*! 
	  * \brief Equality operator
	  * 
	  * Check if two times are equal
	  * 
	  * \param rhs A time to compare with this one
	  * \return The equality of the given time (\p rhs) and this time
	  * \retval true The two times are identical
	  * \retval false The two times are not identical
	  */
	 const bool operator==(const Time& rhs) const
	   {
	      return ((seconds == rhs.seconds) &&
		      (nanoseconds == rhs.nanoseconds));
	   };
	 
	 /*! 
	  * \brief Not equal-to operator
	  * 
	  * Check if two times are not equal
	  * 
	  * \param rhs A value to compare with this time
	  * \return The negated equality of the given value and this time
	  * \retval true The given parameter (\p rhs) is not identical to this
	  *    time
	  * \retval false The given parameter is considered equal to this time
	  */
	 template <class T>
	   const bool operator!=(const T& rhs) const
	   { return (!((*this) == rhs)); };
	 
	 
	 /*! 
	  * \brief Greater-than operator
	  * 
	  * Check if the given time is greater than this time
	  * 
	  * \param rhs A Time structure to compare with this one
	  * \return A boolean representing the comparison logically
	  * \retval true The given parameter is greater than this Time
	  * \retval false The given parameter is equal or less than this Time
	  */
	 const bool operator>(const Time& rhs) const
	   {
	      if ((seconds > rhs.seconds) ||
		  ((seconds == rhs.seconds) &&
		   (nanoseconds > rhs.nanoseconds))) {
		 return true;
	      }
	      return false;
	   };
	 
	 /*!
	  * \brief Less-than operator
	  * 
	  * Check if the given time is less than this time
	  * 
	  * \param rhs A Time structure to compare with this one
	  * \return A boolean representing the comparison logically
	  * \retval true The given parameter is less than this Time
	  * \retval false The given parameter is equal or greater than this
	  *    Time
	  */
	 const bool operator<(const Time& rhs) const
	   {
	      if ((seconds < rhs.seconds) ||
		  ((seconds == rhs.seconds) &&
		   (nanoseconds < rhs.nanoseconds))) {
		 return true;
	      }
	      return false;
	   };
	 
	 /*!
	  * /brief Greater-than or equal to operator
	  * 
	  * Check if the given value is greater than or equal to this time
	  * 
	  * \param rhs A value to compare with this Time
	  * \return A boolean representing the comparison logically
	  * \retval true The given value is greater than or equal to this Time
	  * \retval false The given value is less than this Time
	  */
	 template <class T>
	   const bool operator>=(const T& rhs) const
	   { return (!((*this) < rhs)); };
	 
	 /*!
	  * /brief Less-than or equal to operator
	  * 
	  * Check if the given value is less than or equal to this time
	  * 
	  * \param rhs A value to compare with this Time
	  * \return A boolean representing the comparison logically
	  * \retval true The given value is less than or equal to this Time
	  * \retval false The given value is greater than this Time
	  */
	 template <class T>
	   const bool operator<=(const T& rhs) const
	   { return (!((*this) > rhs)); };
	 
	 
	 /*!
	  * \brief Convert this to a '\c time_t'
	  * 
	  * \warning Be aware that due to the limitations of the \c time_t
	  *    type, \a nanoseconds will be floored from the result.
	  * \return This time represented as a \c time_t
	  */
	 operator time_t(void) const
	   { return time_t(seconds); };
	 
	 /*!
	  * \brief Convert this to a '\c struct \c timespec'
	  *
	  * \return The time represented as a \c struct \c timespec
	  */
	 operator struct timespec(void) const
	   {
	      struct timespec result;
	      result.tv_sec = seconds;
	      result.tv_nsec = nanoseconds;
	      return result;
	   };
	 
	 /*!
	  * \brief Convert this to a '\c struct \c timeval'
	  * 
	  * \warning Because the \c struct \c timeval type can only store
	  *    time down to the \e microsecond resolution, the
	  *    \a nanoseconds will be floored.
	  * \return The time represented as a \c struct \c timeval
	  */
	 operator struct timeval(void) const
	   {
	      struct timeval result;
	      result.tv_sec = seconds;
	      result.tv_usec = nanoseconds / 1000;
	      return result;
	   };
	 
	 
	 /*!
	  * \brief Assignment operator
	  * 
	  * \return A reference to this time, after the reassignment is made
	  */
	 const Time& operator=(const Time& rhs)
	   {
	      seconds = rhs.seconds;
	      nanoseconds = rhs.nanoseconds;
	      return (*this);
	   };
	 
	 /*!
	  * \brief Assignment operator (from a '\c time_t')
	  *
	  * \warning Since the \c time_t type cannot store any time of a
	  *    finer resolution than seconds, the \a nanoseconds field will
	  *    be zeroed upon assignment for accurate representation.
	  * \return A reference to this time, after the reassignment is made
	  */
	 const Time& operator=(const time_t& time)
	   {
	      seconds = time;
	      nanoseconds = 0;
	      return (*this);
	   };
	 
	 /*!
	  * \brief Assignment operator (from a '\c struct \c timespec')
	  * 
	  * \return A reference to this time, after the reassignment is made
	  */
	 const Time& operator=(const struct timespec& time)
	   {
	      seconds = time.tv_sec;
	      nanoseconds = time.tv_nsec;
	      return (*this);
	   };
	 
	 /*!
	  * \brief Assignment operator (from a '\c struct \c timeval')
	  * 
	  * \return A reference to this time, after the reassignment is made
	  */
	 const Time& operator=(const struct timeval& time)
	   {
	      seconds = time.tv_sec;
	      nanoseconds = time.tv_usec * 1000;
	      return (*this);
	   };
	 
	 
	 /*!
	  * \brief Set the time to the time now
	  * 
	  * \return A boolean representing the success of setting the time
	  * \retval true The time was obtained and this Time now represents it
	  * \retval false The time could not be obtained, and this structure
	  *    has not been modified
	  */
	 const bool setTime(void);
      }; // struct Time
   }; // namespace Util
}; // namespace AIS
   
#endif // _INCLUDE_AISUTIL_TIME_H_
