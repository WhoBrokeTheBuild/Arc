#pragma once

#ifndef __ARC_ARRAY_FUNC_H__
#define __ARC_ARRAY_FUNC_H__

namespace Arc
{
	template <typename Value>
	inline bool arrayContains(unsigned int size, const Value list[], const Value& element)
	{
		for (unsigned int i = 0; i < size; ++i)
		{
			if (list[i] == element)
				return true;
		}

		return false;
	}

	template <typename Value>
	inline int arrayIndexOf(unsigned int size, const Value list[], const Value& element)
	{
		for (unsigned int i = 0; i < size; ++i)
		{
			if (list[i] == element)
				return i;
		}

		return -1;
	}

} // namespace Arc

#endif // __ARC_ARRAY_FUNC_H__