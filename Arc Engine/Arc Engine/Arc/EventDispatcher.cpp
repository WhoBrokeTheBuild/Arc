#include "EventDispatcher.h"
#include "Event.h"

Arc::EventDispatcher* gpEventDispatcher = nullptr;

Arc::ArrayList<Arc::EventDispatcher*> Arc::EventDispatcher::_sDispatchers = Arc::ArrayList<Arc::EventDispatcher*>();

Arc::EventDispatcher::EventDispatcher( void )
{
    _eventMap = EventMap();
    _changed  = false;

    _sDispatchers.add(this);
}

Arc::EventDispatcher::~EventDispatcher( void )
{
    _sDispatchers.remove(this);
    removeAllListeners();
}

void Arc::EventDispatcher::addEventListener( const EventType& eventType, const EventDelegate& functionDelegate )
{
    if (!_eventMap.contains(eventType))
        _eventMap[eventType] = EventListenerList();

    int length = _eventMap[eventType].size();

    for(int i = 0; i < length; ++i)
    {
        if (_eventMap[eventType][i] == nullptr)
            continue;
        if (*(_eventMap[eventType][i]) == functionDelegate)
            return;
    }

    _eventMap[eventType].add(New EventDelegate(functionDelegate));
}

void Arc::EventDispatcher::removeEventListener( const EventType& eventType, const EventDelegate& functionDelegate )
{
    if (!_eventMap.contains(eventType))
        return;

    int length = _eventMap[eventType].size();

    for(int i = 0; i < length; ++i)
    {
        if (_eventMap[eventType][i] == nullptr)
            continue;
        if (*(_eventMap[eventType][i]) == functionDelegate)
        {
            delete _eventMap[eventType][i];
            _eventMap[eventType][i] = nullptr;
            _changed = true;
            return;
        }
    }
}

void Arc::EventDispatcher::removeEventListener( const EventType& eventType, void (*function)(const Event&) )
{
    removeEventListener(eventType, EventDelegate(function));
}

void Arc::EventDispatcher::addEventListener( const EventType& eventType, void (*function)(const Event&) )
{
    addEventListener(eventType, EventDelegate(function));
}

void Arc::EventDispatcher::removeAllListeners( void )
{
    EventMap::Iterator          mapIt;
    EventListenerList::Iterator listIt;

    int length;
    for (mapIt = _eventMap.begin(); mapIt != _eventMap.end(); ++mapIt)
    {
        length = mapIt->second.size();
        for (int i = 0; i < length; ++i)
        {
            if (mapIt->second[i] != nullptr)
            {
                delete mapIt->second[i];
                mapIt->second[i] = nullptr;
            }
        }
    }

    _eventMap.clear();
}

void Arc::EventDispatcher::removeAllListeners( const EventType& eventType )
{
    if (!_eventMap.contains(eventType))
        return;

    int length = _eventMap[eventType].size();
    for(int i = 0; i < length; ++i)
    {
        if ( _eventMap[eventType][i] != nullptr )
        {
            delete _eventMap[eventType][i];
            _eventMap[eventType][i] = nullptr;
        }
    }

    _eventMap.remove(eventType);

    _changed = true;
}

void Arc::EventDispatcher::dispatchEvent( const Event& event )
{
    EventType type = event.type();

    if (!_eventMap.contains(type))
        return;

    Event tmp = Event(event);

    tmp.setTarget(this);

    unsigned int length = _eventMap[type].size();
    for(unsigned int i = 0; i < length; ++i)
    {
        if (_eventMap[type][i] != nullptr)
            _eventMap[type][i]->invoke(event);
    }
}

void Arc::EventDispatcher::cleanMap( void )
{
    if (!_changed)
        return;

    bool needRepeat = true;
    EventMap::Iterator mapIt;
    EventListenerList* list;

    while (needRepeat)
    {
        needRepeat = false;
        for (mapIt = _eventMap.begin(); !needRepeat && mapIt != _eventMap.end(); ++mapIt)
        {
            list = &mapIt->second;
            for (unsigned int i = 0; !needRepeat && i < list->size(); ++i)
            {
                if (list->at(i) == nullptr)
                {
                    list->removeAt(i);
                    needRepeat = true;
                    break;
                }
            }
        }
    }

    _changed = false;
}
