#pragma once

#ifndef __ARC_ARRAY_LIST_BUILDER_H__
#define __ARC_ARRAY_LIST_BUILDER_H__

#include "Common.h"
#include "ManagedObject.h"

#include "ArrayList.h"

namespace Arc
{
	template <class T>
	class ArrayListBuilder
		: ManagedObject
	{
	private:

		// The list to build
		ArrayList<T> _list;

	public:

		inline ArrayListBuilder( void )
			: _list()
		{ }

		virtual inline string toString( void ) const { return "ArrayListBuilder"; }
		
		/* Add an element to the end of the list
		 * 
		 * @param item: The element to add to the list
		 */
        inline ArrayListBuilder<T>* add( const T& item ) { _list.add(item); return this; }

		/* Returns the pre-built ArrayList
		 * 
		 * @returns: The pre-built ArrayList
		 */
		inline ArrayList<T> finish( void ) { return _list; }

	}; // class ArrayListBuilder

} // namespace Arc

#endif // __ARC_ARRAY_LIST_BUILDER_H__