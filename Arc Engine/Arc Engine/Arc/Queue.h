#pragma once

#ifndef __ARC_QUEUE_H__
#define __ARC_QUEUE_H__

#include "Common.h"
#include "GameObject.h"

#include <queue>

using std::queue;

namespace Arc
{
    template <class T>
    class ArrayList;

    template <class T>
    class LinkedList;

    template <class T>
    class Queue :
        public GameObject
    {
    protected:

        queue<T>
            _queue;

    public:

        Queue ( void ) { _queue = queue<T>(); }
        virtual ~Queue( void ) { clear(); }

        virtual string toString( void ) const { return "Queue"; }

        Queue<T>* push ( const T& item );
        T         peek ( void );
        T         pop  ( void );
        Queue<T>* clear( void );

        T& front( void ) { return _queue.front(); }
        T& back ( void ) { return _queue.back(); }

        const T& front( void ) const { return _queue.front(); }
        const T& back ( void ) const { return _queue.back(); }

        bool empty( void ) const { return _queue.empty(); }

        size_t size( void ) const { return _queue.size(); }

        T*            toArray     ( void ) { unsigned int i; return toArray(i); }
        ArrayList<T>  toArrayList ( void ) { unsigned int i; return toArrayList(i); }
        LinkedList<T> toLinkedList( void ) { unsigned int i; return toLinkedList(i); }

        T*            toArray     ( unsigned int& length );
        ArrayList<T>  toArrayList ( unsigned int& length );
        LinkedList<T> toLinkedList( unsigned int& length );

    }; // class Queue<T>

} // namespace Arc

#include "ArrayList.h"
#include "LinkedList.h"

template <class T>
Arc::Queue<T>* Arc::Queue<T>::push( const T& item )
{
    _queue.push(item);
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
    return value;
}

template <class T>
Arc::Queue<T>* Arc::Queue<T>::clear( void )
{
    while (!empty())
        _queue.pop();
    return this;
}

template <class T>
T*  Arc::Queue<T>::toArray( unsigned int& length )
{
    queue<T> tmp = _queue;
    length = size();
    T* other = new T[length];

    for (unsigned int i = 0; i < length; ++i)
        other[i] = tmp.pop();

    return other;
}

template <class T>
Arc::ArrayList<T> Arc::Queue<T>::toArrayList( unsigned int& length )
{
    queue<T> tmp = _queue;
    length = size();
    ArrayList<T> other;

    for (unsigned int i = 0; i < length; ++i)
        other.add(tmp.pop());

    return other;
}

template <class T>
Arc::LinkedList<T> Arc::Queue<T>::toLinkedList( unsigned int& length )
{
    queue<T> tmp = _queue;
    length = size();
    LinkedList<T> other;

    for (unsigned int i = 0; i < length; ++i)
        other.add(tmp.pop());

    return other;
}

#endif // __ARC_QUEUE_H__
