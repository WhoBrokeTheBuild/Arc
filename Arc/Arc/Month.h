#pragma once

#ifndef __ARC_MONTH_H__
#define __ARC_MONTH_H__

#include <string>

using std::string;

namespace Arc
{
	// Enum of months of the year
	enum Months
	{
		INVALID_MONTH = -1,

		MONTH_JANUARY,
		MONTH_FEBRUARY,
		MONTH_MARCH,
		MONTH_APRIL,
		MONTH_MAY,
		MONTH_JUNE,
		MONTH_JULY,
		MONTH_AUGUST,
		MONTH_SEPTEMBER,
		MONTH_OCTOBER,
		MONTH_NOVEMBER,
		MONTH_DECEMBER,

		NUM_MONTHS

	}; // enum MouseButton

	const string MONTH_NAMES[NUM_MONTHS] =
	{
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
	};

} // namespace Arc

#endif // __ARC_MONTH_H__
