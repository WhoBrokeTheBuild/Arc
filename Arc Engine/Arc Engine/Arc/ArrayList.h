#pragma once

#ifndef __ARC_ARRAY_LIST_H__
#define __ARC_ARRAY_LIST_H__

#include "Common.h"
#include "ManagedObject.h"

#include <vector>

using std::vector;

namespace Arc
{
    template <class T>
    class LinkedList;

    template <class T>
    class Queue;
	
	/** A templated Array List 
	  */
    template <class T>
    class ArrayList :
        public ManagedObject
    {
    protected:

		// A STL vector to handle the storage
        vector<T>
            _list;

		// A cached length of the collection
		size_t
			_size;

		virtual inline void updateSize( void ) { _size = _list.size(); }

    public:

        typedef typename vector<T>::iterator       Iterator;
        typedef typename vector<T>::const_iterator ConstIterator;

        inline ArrayList ( void )
			: _list(),
			  _size()
		{ }

        inline ArrayList ( const ArrayList& rhs)
			: _list(rhs._list),
		      _size(rhs._list.size())
		{ }

        virtual inline ~ArrayList( void ) { clear(); }

        inline ArrayList& operator= ( const ArrayList& rhs ) { _list = rhs._list; updateSize(); return *this; }
        inline T&         operator[]( const int index)       { return at(index); }
        inline const T    operator[]( const int index) const { return at(index); }

        virtual inline string toString( void ) const { return "Array List"; }

        inline Iterator begin ( void ) { return _list.begin(); }
        inline Iterator end   ( void ) { return _list.end(); }
        inline Iterator rbegin( void ) { return _list.rbegin(); }
        inline Iterator rend  ( void ) { return _list.rend(); }

        inline ConstIterator cbegin ( void ) const { return _list.cbegin(); }
        inline ConstIterator cend   ( void ) const { return _list.cend(); }
        inline ConstIterator crbegin( void ) const { return _list.crbegin(); }
        inline ConstIterator crend  ( void ) const { return _list.crend(); }

        ArrayList<T>* add        ( const T& item );
        ArrayList<T>* insertAt   ( const T& item, const int& index );
		ArrayList<T>* clear      ( void );
		T             popFront   ( void );
		T             popBack    ( void );
        bool          remove     ( const T& item );
        bool          removeAll  ( const T& item );
        bool          removeAt   ( const unsigned int& index );
        bool          removeFront( void );
        bool          removeBack ( void );

        inline T& at( int index ) { return _list[index]; }
        inline const T at( int index ) const { return _list[index]; }

        inline T& front( void ) { return _list.front(); }
        inline T& back ( void ) { return _list.back(); }

        inline const T& front( void ) const { return _list.front(); }
        inline const T& back ( void ) const { return _list.back(); }

        bool contains( const T& item ) const;
        bool hasIndex( const int& index ) const;
        inline bool isEmpty( void ) const { return (_size == 0); }

		// Get the index of a value
        int indexOf( T& item ) const;

        inline size_t getSize( void ) const { return _size; }

		// Merge this collection with another collection

        unsigned int merge( ArrayList<T> list );
        unsigned int merge( LinkedList<T> list );
		unsigned int merge( Queue<T> list );

		// Convert the queue into a different storage type

        inline T*            toArray     ( void ) { unsigned int i; return toArray(i); }
        inline LinkedList<T> toLinkedList( void ) { unsigned int i; return toLinkedList(i); }
        inline Queue<T>      toQueue     ( void ) { unsigned int i; return toQueue(i); }

        T*            toArray     ( unsigned int& length );
        LinkedList<T> toLinkedList( unsigned int& length );
        Queue<T>      toQueue     ( unsigned int& length );

    }; // class ArrayList<T>

} // namespace Arc

#include "LinkedList.h"
#include "Queue.h"

template <class T>
Arc::ArrayList<T>* Arc::ArrayList<T>::add( const T& item )
{
    _list.push_back(item);
	updateSize();
    return this;
}

template <class T>
Arc::ArrayList<T>* Arc::ArrayList<T>::insertAt( const T& item, const int& index )
{
	_list.insert(_list.begin() + index, item);
	updateSize();
    return this;
}

template <class T>
T Arc::ArrayList<T>::popFront( void )
{
	T tmp = front();
	removeFront();
	return tmp;
}

template <class T>
T Arc::ArrayList<T>::popBack( void )
{
	T tmp = back();
	removeBack();
	return tmp;
}

template <class T>
bool Arc::ArrayList<T>::remove( const T& item )
{
    Iterator it;

    for (it = begin(); it != end(); ++it)
    {
        if (*it == item)
        {
            _list.erase(it);
            return true;
        }
	}
	updateSize();
    return false;
}

template <class T>
bool Arc::ArrayList<T>::removeAll( const T& item )
{
    Iterator it;

    bool found = false;
    for (it = begin(); it != end(); ++it)
    {
        if (it->second == item)
        {
            _list.erase(it);
            found = true;
        }
	}
	updateSize();
    return found;
}

template <class T>
bool Arc::ArrayList<T>::removeAt( const unsigned int& index )
{
    if ( ! hasIndex(index))
        return false;

	_list.erase(begin() + index);
	updateSize();
    return true;
}

template <class T>
bool Arc::ArrayList<T>::removeFront( void )
{
    if (isEmpty())
        return false;

    removeAt(0);
    return true;
}

template <class T>
bool Arc::ArrayList<T>::removeBack( void )
{
    if (isEmpty())
        return false;

	_list.pop_back();
	updateSize();
    return true;
}

template <class T>
Arc::ArrayList<T>* Arc::ArrayList<T>::clear( void )
{
    _list.clear();
    return this;
}

template <class T>
bool Arc::ArrayList<T>::contains( const T& item ) const
{
    if (isEmpty())
        return false;

    return (find(cbegin(), cend(), item) != cend());
}

template <class T>
bool Arc::ArrayList<T>::hasIndex( const int& index ) const
{
    return (between(index, 0, (const int)getSize()));
}

template <class T>
unsigned int Arc::ArrayList<T>::merge( ArrayList<T> list )
{
    for (unsigned int i = 0; i < list.size(); ++i)
        add(list[i]);
    return list.size();
}

template <class T>
unsigned int Arc::ArrayList<T>::merge( LinkedList<T> list )
{
    typename LinkedList<T>::ConstIterator it;
    for (it = list.cbegin(); it != list.cend(); ++it)
        add(*it);
    return list.getSize();
}

template <class T>
unsigned int Arc::ArrayList<T>::merge( Queue<T> list )
{
    unsigned int count;
    while ( ! list.isEmpty())
    {
        add(list.pop());
        count++;
    }
    return count;
}

template <class T>
T* Arc::ArrayList<T>::toArray( unsigned int& length )
{
    length = getSize();
    T* other = new T[length];

    int index = 0;
    for (Iterator it = begin(); it != end(); ++it, ++index)
        other[index] = *it;

    return other;
}

template <class T>
Arc::LinkedList<T> Arc::ArrayList<T>::toLinkedList( unsigned int& length )
{
    length = getSize();
    LinkedList<T> other;

    for (Iterator it = begin(); it != end(); ++it)
        other.add(*it);

    return other;
}

template <class T>
Arc::Queue<T> Arc::ArrayList<T>::toQueue( unsigned int& length )
{
    Queue<T> other;

    for (Iterator it = begin(); it != end(); ++it)
        other.push(*it);

    return other;
}

#endif // __ARC_ARRAY_LIST_H__
