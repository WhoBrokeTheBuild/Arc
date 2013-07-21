#pragma once

#ifndef __ARC_EVENT_H__
#define __ARC_EVENT_H__

#include "Common.h"
#include "GameObject.h"

#include "EventData.h"

namespace Arc
{
    typedef string EventType;

    class EventDispatcher;

    class Event :
        public GameObject
    {

        friend class EventDispatcher;

    protected:

        EventDispatcher
            *_pEventTarget;

        EventType
            _type;

        EventData
            *_pData;

    public:

        static const EventType EVENT_NULL;

        static const EventData BLANK_DATA;
        static const Event     BLANK_EVENT;

        Event( const EventType &type = EVENT_NULL, const EventData &data = BLANK_DATA );
        Event( const Event &rhs);
        virtual ~Event( void );

        virtual string toString( void ) const { return "Event"; }

        inline EventType type( void ) const { return _type; };
        inline EventDispatcher *target( void ) const { return _pEventTarget; };
        inline void setTarget( EventDispatcher* target ) { _pEventTarget = target; }

        template <typename T>
        inline T* targetAs( void ) const { return dynamic_cast<T*>(_pEventTarget); };

        inline const EventData *data( void ) const { return _pData; };

        template <typename T>
        inline const T* dataAs( void ) const { return dynamic_cast<const T*>(_pData); };

    }; // class Event

} // namespace Arc

#endif // __ARC_EVENT_H__
