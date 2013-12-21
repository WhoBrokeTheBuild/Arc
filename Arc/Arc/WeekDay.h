#pragma once

#ifndef __ARC_WEEKDAY_H__
#define __ARC_WEEKDAY_H__

#include <string>

using std::string;

namespace Arc
{
	// Enum of days of the week
	enum WeekDays
	{
		INVALID_WEEK_DAY = -1,

		WEEK_SUNDAY,
		WEEK_MONDAY,
		WEEK_TUESDAY,
		WEEK_WEDNESDAY,
		WEEK_THURSDAY,
		WEEK_FRIDAY,
		WEEK_SATURDAY,

		NUM_WEEK_DAY

	}; // enum MouseButton

	const string WEEK_DAY_NAMES[NUM_WEEK_DAY] =
	{
		"Sunday",
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Saturday"
	};

} // namespace Arc

#endif // __ARC_WEEKDAY_H__
