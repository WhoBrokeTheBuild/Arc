#pragma once

#ifndef __ARC_MAP_H__
#define __ARC_MAP_H__

#include "Common.h"
#include "ManagedObject.h"

#include <map>

using std::less;
using std::map;
using std::pair;

namespace Arc
{

    template <class T>
    class LinkedList;

    template <class T>
    class ArrayList;

    template <class K, class T, typename Sort = less<K>>
    class Map :
        public ManagedObject
    {
    protected:

        map<K, T, Sort>
            _map;

    public:

        typedef typename map<K, T, Sort>::iterator       Iterator;
        typedef typename map<K, T, Sort>::const_iterator ConstIterator;

        typedef pair<K, T> Pair;

        inline Map( void ) { _map = map<K, T, Sort>(); }
        inline Map( const Map& rhs) : _map(rhs._map) { }
        virtual inline ~Map( void ) { clear(); }

        inline Map& operator= ( const Map& rhs )     { _map = rhs._map; return *this; }
        inline T&   operator[]( const K& key )       { return at(key); }
        inline T&   operator[]( const K& key ) const { return at(key); }

        virtual inline string toString( void ) const { return "Map"; }

        inline Iterator begin ( void ) { return _map.begin(); }
        inline Iterator end   ( void ) { return _map.end(); }
        inline Iterator rbegin( void ) { return _map.rbegin(); }
        inline Iterator rend  ( void ) { return _map.rend(); }
		
        inline ConstIterator cbegin ( void ) const { return _map.cbegin(); }
        inline ConstIterator cend   ( void ) const { return _map.cend(); }
        inline ConstIterator crbegin( void ) const { return _map.crbegin(); }
        inline ConstIterator crend  ( void ) const { return _map.crend(); }
		
        inline Iterator      find( K& key )       { return _map.find(key); }
        inline ConstIterator find (K& key ) const { return _map.find(key); }

        Map<K, T, Sort>* add            ( const K& key, const T& item );
        Map<K, T, Sort>* clear          ( void );
        bool             remove         ( const K& key );
        bool             removeKey      ( const K& key );
        bool             removeValue    ( const T& value );
        bool             removeAllValues( const T& value );

        inline T& at( const K& key ) { return _map[key]; }
        inline T& at( const K& key ) const { return _map[key]; }

        bool contains     ( const K& key );
        bool containsKey  ( const K& key );
        bool containsValue( const T& value );

        inline bool empty( void ) const { return _map.empty(); }

        K& indexOf( T& item );

        inline size_t size( void ) const { return _map.size(); }

        inline K*            keyArray     ( void ) { unsigned int i; return keyArray(i); }
        inline LinkedList<K> keyLinkedList( void ) { unsigned int i; return keyLinkedList(i); }
        inline ArrayList<K>  keyArrayList ( void ) { unsigned int i; return keyArrayList(i); }

        inline T*            valueArray     ( void ) { unsigned int i; return valueArray(i); }
        inline LinkedList<T> valueLinkedList( void ) { unsigned int i; return valueLinkedList(i); }
        inline ArrayList<T>  valueArrayList ( void ) { unsigned int i; return valueArrayList(i); }

        K*            keyArray     ( unsigned int& length );
        LinkedList<K> keyLinkedList( unsigned int& length );
        ArrayList<K>  keyArrayList ( unsigned int& length );

        T*            valueArray     ( unsigned int& length );
        LinkedList<T> valueLinkedList( unsigned int& length );
        ArrayList<T>  valueArrayList ( unsigned int& length );

    }; // class Map<T, K, Sort>

} // namespace Arc

#include "LinkedList.h"
#include "ArrayList.h"

template <class K, class T, typename Sort>
Arc::Map<K, T, Sort>* Arc::Map<K, T, Sort>::add( const K& key, const T& item )
{
    _map.insert(Pair(key, item));
    return this;
}

template <class K, class T, typename Sort>
bool Arc::Map<K, T, Sort>::remove( const K& key )
{
    return removeKey(key);
}

template <class K, class T, typename Sort>
bool Arc::Map<K, T, Sort>::removeKey( const K& key )
{
    return (_map.erase(key) == 1);
}
template <class K, class T, typename Sort>
bool Arc::Map<K, T, Sort>::removeValue( const T& value )
{
    Iterator it;

    for (it = begin(); it != end(); ++it)
    {
        if (it->second == value)
        {
            _map.erase(it);
            return true;
        }
    }
    return false;
}

template <class K, class T, typename Sort>
bool Arc::Map<K, T, Sort>::removeAllValues( const T& value )
{
    Iterator it;

    bool found = false;
    for (it = begin(); it != end(); ++it)
    {
        if (it->second == value)
        {
            _map.erase(it);
            found = true;
        }
    }
    return true;
}

template <class K, class T, typename Sort>
Arc::Map<K, T, Sort>* Arc::Map<K, T, Sort>::clear( void )
{
    _map.clear();
    return this;
}

template <class K, class T, typename Sort>
bool Arc::Map<K, T, Sort>::contains( const K& key )
{
    return containsKey(key);
}

template <class K, class T, typename Sort>
bool Arc::Map<K, T, Sort>::containsKey( const K& key )
{
    ConstIterator it = _map.find(key);

    return (it != cend());
}

template <class K, class T, typename Sort>
bool Arc::Map<K, T, Sort>::containsValue( const T& value )
{
    ConstIterator it;

    for (it = cbegin(); it != cend(); ++it)
    {
        if (it->second == value)
            return true;
    }

    return false;
}

template <class K, class T, typename Sort>
K& Arc::Map<K, T, Sort>::indexOf( T& item )
{
    ConstIterator it;

    for (it = cbegin(); it != cend(); ++it)
    {
        if (it->second == item)
            return it->first;
    }

    return K();
}
template <class K, class T, typename Sort>
K* Arc::Map<K, T, Sort>::keyArray( unsigned int& length )
{
    length = size();
    K* other = new T[length];

    int index = 0;
    for (Iterator it = begin(); it != end(); ++it, ++index)
        other[index] = it->first;

    return other;
}

template <class K, class T, typename Sort>
Arc::LinkedList<K> Arc::Map<K, T, Sort>::keyLinkedList( unsigned int& length )
{
    length = size();
    LinkedList<K> other;

    for (Iterator it = begin(); it != end(); ++it)
        other.add(it->first);

    return other;
}

template <class K, class T, typename Sort>
Arc::ArrayList<K> Arc::Map<K, T, Sort>::keyArrayList( unsigned int& length )
{
    length = size();
    ArrayList<K> other;

    for (Iterator it = begin(); it != end(); ++it)
        other.add(it->first);

    return other;
}

template <class K, class T, typename Sort>
T* Arc::Map<K, T, Sort>::valueArray( unsigned int& length )
{
    length = size();
    T* other = new T[length];

    int index = 0;
    for (Iterator it = begin(); it != end(); ++it, ++index)
        other[index] = it->second;

    return other;
}

template <class K, class T, typename Sort>
Arc::LinkedList<T> Arc::Map<K, T, Sort>::valueLinkedList( unsigned int& length )
{
    length = size();
    LinkedList<T> other;

    for (Iterator it = begin(); it != end(); ++it)
        other.add(it->second);

    return other;
}

template <class K, class T, typename Sort>
Arc::ArrayList<T> Arc::Map<K, T, Sort>::valueArrayList( unsigned int& length )
{
    length = size();
    ArrayList<T> other;

    for (Iterator it = begin(); it != end(); ++it)
        other.add(it->second);

    return other;
}

#endif // __ARC_MAP_H__
