#pragma once

#ifndef __ARC_QUEUE_H__
#define __ARC_QUEUE_H__

#include "Common.h"
#include "ManagedObject.h"

#include <queue>

using std::queue;

namespace Arc
{
    template <class T>
    class ArrayList;

    template <class T>
    class LinkedList;

	/** A templated Queue 
	  */
    template <class T>
    class Queue :
        public ManagedObject
    {
    protected:

		// A STL queue to handle the storage
        queue<T>
			_queue;

		// A cached length of the collection
		size_t
			_size;

		virtual inline void updateSize( void ) { _size = _queue.size(); }

    public:

		inline Queue ( void )
			: _queue(),
			  _size()
		{
		}

		inline Queue ( const Queue& rhs) 
			: _queue(rhs._queue),
			  _size(rhs._queue.size())
		{
		}

		virtual inline ~Queue( void ) { clear(); }

		inline Queue& operator=( const Queue& rhs ) { _queue = rhs._queue; updateSize(); return *this; }

        virtual inline string toString( void ) const { return "Queue"; }

        Queue<T>* push ( const T& item );
        T         peek ( void );
        T         pop  ( void );
        Queue<T>* clear( void );

        inline T& getFront( void ) { return _queue.front(); }
        inline T& getBack ( void ) { return _queue.back(); }

        inline const T& getFront( void ) const { return _queue.front(); }
        inline const T& getBack ( void ) const { return _queue.back(); }

        inline bool isEmpty( void ) const { return (_size == 0); }

		inline size_t getSize( void ) const { return _size; }

		// Convert the queue into a different storage type

		T*            toArray     ( unsigned int& length );
		ArrayList<T>  toArrayList ( unsigned int& length );
		LinkedList<T> toLinkedList( unsigned int& length );

        inline T*            toArray     ( void ) { unsigned int i; return toArray(i); }
        inline ArrayList<T>  toArrayList ( void ) { unsigned int i; return toArrayList(i); }
        inline LinkedList<T> toLinkedList( void ) { unsigned int i; return toLinkedList(i); }

    }; // class Queue<T>

} // namespace Arc

#include "ArrayList.h"
#include "LinkedList.h"

template <class T>
Arc::Queue<T>* Arc::Queue<T>::push( const T& item )
{
	_queue.push(item);
	updateSize();
    return this;
}

template <class T>
T Arc::Queue<T>::peek( void )
{
    return _queue.front();
}

template <class T>
T Arc::Queue<T>::pop ( void )
{
    T value = peek();
	_queue.pop();
	updateSize();
    return value;
}

template <class T>
Arc::Queue<T>* Arc::Queue<T>::clear( void )
{
    while ( ! isEmpty())
		_queue.pop();
	updateSize();
    return this;
}

template <class T>
T*  Arc::Queue<T>::toArray( unsigned int& length )
{
    queue<T> tmp = _queue;
    length = getSize();
    T* other = new T[length];

    for (unsigned int i = 0; i < length; ++i)
        other[i] = tmp.pop();

    return other;
}

template <class T>
Arc::ArrayList<T> Arc::Queue<T>::toArrayList( unsigned int& length )
{
    queue<T> tmp = _queue;
    length = getSize();
    ArrayList<T> other;

    for (unsigned int i = 0; i < length; ++i)
        other.add(tmp.pop());

    return other;
}

template <class T>
Arc::LinkedList<T> Arc::Queue<T>::toLinkedList( unsigned int& length )
{
    queue<T> tmp = _queue;
    length = getSize();
    LinkedList<T> other;

    for (unsigned int i = 0; i < length; ++i)
        other.add(tmp.pop());

    return other;
}

#endif // __ARC_QUEUE_H__
