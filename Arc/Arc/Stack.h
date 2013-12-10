#pragma once

#ifndef __ARC_STACK_H__
#define __ARC_STACK_H__

#include "Common.h"
#include "ManagedObject.h"

#include <stack>

using std::stack;

namespace Arc
{
    template <class T>
    class ArrayList;

    template <class T>
    class LinkedList;

	/** A templated Stack 
	  */
    template <class T>
    class Stack :
        public ManagedObject
    {
    protected:

		// A STL stack to handle the storage
        stack<T>
			_stack;

		// A cached length of the collection
		size_t
			_size;

		virtual inline void updateSize( void ) { _size = _stack.size(); }

    public:

		inline Stack ( void )
			: _stack(),
			  _size()
		{
		}

		inline Stack ( const Stack& rhs) 
			: _stack(rhs._stack),
			  _size(rhs._stack.size())
		{
		}

		virtual inline ~Stack( void ) { clear(); }

		inline Stack& operator=( const Stack& rhs ) { _stack = rhs._stack; updateSize(); return *this; }

        virtual inline string toString( void ) const { return "Stack"; }

        Stack<T>* push( const T& item );

		T pop( void );

		inline T& top( void ) { return _stack.top(); }

		inline const T& top( void ) const { return _stack.top(); }

        Stack<T>* clear( void );


        inline bool isEmpty( void ) const { return (_size == 0); }

		inline size_t getSize( void ) const { return _size; }

		// Convert the Stack into a different storage type

		T*            toArray     ( unsigned int& length );
		ArrayList<T>  toArrayList ( unsigned int& length );
		LinkedList<T> toLinkedList( unsigned int& length );

        inline T*            toArray     ( void ) { unsigned int i; return toArray(i); }
        inline ArrayList<T>  toArrayList ( void ) { unsigned int i; return toArrayList(i); }
        inline LinkedList<T> toLinkedList( void ) { unsigned int i; return toLinkedList(i); }

    }; // class Stack<T>

} // namespace Arc

#include "ArrayList.h"
#include "LinkedList.h"

template <class T>
Arc::Stack<T>* Arc::Stack<T>::push( const T& item )
{
	_stack.push(item);
	updateSize();
    return this;
}

template <class T>
T Arc::Stack<T>::pop ( void )
{
    T value = peek();
	_stack.pop();
	updateSize();
    return value;
}

template <class T>
Arc::Stack<T>* Arc::Stack<T>::clear( void )
{
    while ( ! isEmpty())
		_stack.pop();
	updateSize();
    return this;
}

template <class T>
T*  Arc::Stack<T>::toArray( unsigned int& length )
{
    Stack<T> tmp = _stack;
    length = getSize();
    T* other = new T[length];

    for (unsigned int i = 0; i < length; ++i)
        other[i] = tmp.pop();

    return other;
}

template <class T>
Arc::ArrayList<T> Arc::Stack<T>::toArrayList( unsigned int& length )
{
    Stack<T> tmp = _stack;
    length = getSize();
    ArrayList<T> other;

    for (unsigned int i = 0; i < length; ++i)
        other.add(tmp.pop());

    return other;
}

template <class T>
Arc::LinkedList<T> Arc::Stack<T>::toLinkedList( unsigned int& length )
{
    Stack<T> tmp = _stack;
    length = getSize();
    LinkedList<T> other;

    for (unsigned int i = 0; i < length; ++i)
        other.add(tmp.pop());

    return other;
}

#endif // __ARC_STACK_H__
