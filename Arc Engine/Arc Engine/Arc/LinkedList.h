#pragma once

#ifndef __ARC_LINKED_LIST_H__
#define __ARC_LINKED_LIST_H__

#include "Common.h"

#include <list>
#include <algorithm>

using std::list;

namespace Arc
{
    template <class T>
    class ArrayList;

    template <class T>
    class Queue;
	
	/** A templated Linked List 
	  */
    template <class T>
    class LinkedList :
        public ManagedObject
    {
    protected:

		// A STL list to handle the storage
        list<T>
			_list;

		// A cached length of the collection
		size_t
			_size;

		virtual inline void updateSize( void ) { _size = _list.size(); }

    public:

        typedef typename list<T>::iterator       Iterator;
        typedef typename list<T>::const_iterator ConstIterator;

        inline LinkedList ( void )
			: _list(),
			  _size()
		{
		}

        inline LinkedList ( const LinkedList& rhs) 
			: _list(rhs._list)
			  _size(rhs._list.size())
		{
		}

		virtual inline ~LinkedList( void ) { clear(); }

        inline LinkedList& operator=( const LinkedList& rhs ) { _list = rhs._list; updateSize(); return *this; }

        virtual inline string toString( void ) const { return "Linked List"; }

        inline Iterator begin ( void ) { return _list.begin(); }
        inline Iterator end   ( void ) { return _list.end(); }
        inline Iterator rbegin( void ) { return _list.rbegin(); }
        inline Iterator rend  ( void ) { return _list.rend(); }

        inline ConstIterator cbegin ( void ) const { return _list.cbegin(); }
        inline ConstIterator cend   ( void ) const { return _list.cend(); }
        inline ConstIterator crbegin( void ) const { return _list.crbegin(); }
        inline ConstIterator crend  ( void ) const { return _list.crend(); }

        LinkedList<T>* add        ( const T& item );
        LinkedList<T>* addFront   ( const T& item );
        LinkedList<T>* addBack    ( const T& item );
        LinkedList<T>* insertAt   ( const T& item, const int& index );
        LinkedList<T>* clear      ( void );
        T              popFront   ( void );
        T              popBack    ( void );
        bool           remove     ( const T& item );
        bool           removeAll  ( const T& item );
        bool           removeAt   ( const unsigned int& index );
        bool           removeFront( void );
        bool           removeBack ( void );

        inline T& front( void ) { return _list.front(); }
        inline T& back ( void ) { return _list.back(); }

        inline const T& front( void ) const { return _list.front(); }
        inline const T& back ( void ) const { return _list.back(); }

        bool contains( const T& item ) const;
        bool hasIndex( const int& index) const;
        inline bool isEmpty( void )    const { return (_size == 0); }

		// Get the index of a value
        int indexOf( T& item ) const;

		inline size_t getSize( void ) const { return _size; }

		// Merge this collection with another collection

        unsigned int merge( ArrayList<T> list );
        unsigned int merge( LinkedList<T> list );
		unsigned int merge( Queue<T> list );

		// Convert the queue into a different storage type

        inline T*           toArray    ( void ) { unsigned int i; return toArray(i); }
        inline ArrayList<T> toArrayList( void ) { unsigned int i; return toArrayList(i); }
        inline Queue<T>     toQueue    ( void ) { unsigned int i; return toQueue(i); }

        T*           toArray    ( unsigned int& length );
        ArrayList<T> toArrayList( unsigned int& length );
        Queue<T>     toQueue    ( unsigned int& length );

    }; // class LinkedList<T>

} // namespace Arc

#include "ArrayList.h"
#include "Queue.h"

template <class T>
Arc::LinkedList<T>* Arc::LinkedList<T>::add( const T& item )
{
    addBack(item);
    return this;
}

template <class T>
Arc::LinkedList<T>* Arc::LinkedList<T>::addFront( const T& item )
{
	_list.push_front(item);
	updateSize();
    return this;
}

template <class T>
Arc::LinkedList<T>* Arc::LinkedList<T>::addBack( const T& item )
{
	_list.push_back(item);
	updateSize();
    return this;
}

template <class T>
Arc::LinkedList<T>* Arc::LinkedList<T>::insertAt( const T& item, const int& index )
{
	_list.insert(_list.begin() + index, item);
	updateSize();
    return this;
}

template <class T>
T Arc::LinkedList<T>::popFront( void )
{
    T tmp = front();
    removeFront();
    return tmp;
}

template <class T>
T Arc::LinkedList<T>::popBack( void )
{
    T tmp = back();
    removeBack();
    return tmp;
}

template <class T>
bool Arc::LinkedList<T>::remove( const T& item )
{
    Iterator it;

    for (it = begin(); it != end(); ++it)
    {
        if (it == item)
        {
            _list.erase(it);
            return true;
        }
	}
	updateSize();
    return false;
}

template <class T>
bool Arc::LinkedList<T>::removeAll( const T& item )
{
	bool removed = (_list.remove(item) > 0);
	updateSize();
	return removed;
}

template <class T>
bool Arc::LinkedList<T>::removeAt( const unsigned int& index )
{
    if ( ! hasIndex(index))
        return false;

	_list.erase(begin() + index);
	updateSize();
    return true;
}

template <class T>
bool Arc::LinkedList<T>::removeFront( void )
{
    if (isEmpty())
        return false;

	_list.pop_front();
	updateSize();
    return true;
}

template <class T>
bool Arc::LinkedList<T>::removeBack( void )
{
    if (isEmpty())
        return false;

	_list.pop_back();
	updateSize();
    return true;
}

template <class T>
Arc::LinkedList<T>* Arc::LinkedList<T>::clear( void )
{
	_list.clear();
	updateSize();
    return this;
}

template <class T>
bool Arc::LinkedList<T>::contains( const T& item ) const
{
    if (isEmpty())
        return false;

    return (find(cbegin(), cend(), item) != cend());
}

template <class T>
bool Arc::LinkedList<T>::hasIndex( const int& index ) const
{
    return (between(index, 0, (const int)getSize()));
}

template <class T>
unsigned int Arc::LinkedList<T>::merge( ArrayList<T> list )
{
    for (unsigned int i = 0; i < list.getSize(); ++i)
        add(list[i]);
    return list.getSize();
}

template <class T>
unsigned int Arc::LinkedList<T>::merge( LinkedList<T> list )
{
    LinkedList<T>::ConstIterator it;
    for (it = list.cbegin(); it != list.cend(); ++it)
        add(*it);
    return list.getSize();
}

template <class T>
unsigned int Arc::LinkedList<T>::merge( Queue<T> list )
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
T* Arc::LinkedList<T>::toArray( unsigned int& length )
{
    length = getSize();
    T* other = new T[length];

    int index = 0;
    for (Iterator it = begin(); it != end(); ++it, ++index)
        other[index] = *it;

    return other;
}

template <class T>
Arc::ArrayList<T> Arc::LinkedList<T>::toArrayList( unsigned int& length )
{
    ArrayList<T> other;

    for (Iterator it = begin(); it != end(); ++it)
        other.add(*it);

    return other;
}

template <class T>
Arc::Queue<T> Arc::LinkedList<T>::toQueue( unsigned int& length )
{
    Queue<T> other;

    for (Iterator it = begin(); it != end(); ++it)
        other.push(*it);

    return other;
}

#endif // __ARC_LINKED_LIST_H__
