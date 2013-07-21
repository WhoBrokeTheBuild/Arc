#include "Event.h"
#include "EventDispatcher.h"

const Arc::EventType Arc::Event::EVENT_NULL = "null";

const Arc::EventData Arc::Event::BLANK_DATA  = EventData();
const Arc::Event     Arc::Event::BLANK_EVENT = Event(EVENT_NULL, BLANK_DATA);

Arc::Event::Event( const EventType &type /*= EVENT_NULL*/, const EventData &data /*= BLANK_DATA*/ )
{
    _pEventTarget = nullptr;

    _type = type;
    _pData = data.clone();
}

Arc::Event::Event( const Event &rhs )
{
    _pEventTarget = nullptr;

    _type = rhs._type;
    _pData = (rhs._pData != nullptr ? rhs._pData->clone() : nullptr);
}

Arc::Event::~Event( void )
{
    if (_pData != nullptr)
        delete _pData;
}
