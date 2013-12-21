#pragma once

#ifndef __ARC_TIME_H__
#define __ARC_TIME_H__

#include "Common.h"
#include "ManagedObject.h"
#include <ctime>

namespace Arc
{

	class Time :
		public ManagedObject
	{
	private:

		unsigned int _hours;
		unsigned int _minutes;
		unsigned int _seconds;
		double _milliseconds;

		bool _dst;

	public:

		inline Time( unsigned int hours = 0, unsigned int minutes = 0, unsigned int seconds = 0, double milliseconds = 0.0, bool dst = false )
			: _hours(hours),
			_minutes(minutes),
			_seconds(seconds),
			_milliseconds(milliseconds),
			_dst(dst) { }

		inline Time( const Time& rhs )
			: _hours(rhs._hours),
			_minutes(rhs._minutes),
			_seconds(rhs._seconds),
			_milliseconds(rhs._milliseconds),
			_dst(rhs._dst) { }

		inline virtual ~Time( void ) { }

		inline virtual string toString( void ) const { return "Time"; }

		static inline Time now( void )
		{
			time_t rawtime;
			struct tm * timeinfo;

			time (&rawtime);
			timeinfo = localtime (&rawtime);
			
			// TODO Implement millisecond grab for Now
			return Time(timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, 0.0, timeinfo->tm_isdst);
		}

		inline unsigned int getHours( void ) const { return _hours; }
		inline void setHours( unsigned int val ) { _hours = val; }

		inline unsigned int getMinutes( void ) const { return _minutes; }
		inline void setMinutes( unsigned int val ) { _minutes = val; }

		inline unsigned int getSeconds( void ) const { return _seconds; }
		inline void setSeconds( unsigned int val ) { _seconds = val; }

		inline double getMilliseconds( void ) const { return _milliseconds; }
		inline void setMilliseconds( double val ) { _milliseconds = val; }

		inline bool isDST( void ) const { return _dst; }
		inline void setDST( bool val ) { _dst = val; }

	}; // class Time

} // namespace Arc

#endif __ARC_TIME_H__