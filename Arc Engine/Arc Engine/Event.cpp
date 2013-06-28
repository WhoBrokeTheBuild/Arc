#include "Event.h"
#include "EventDispatcher.h"

const EventType Event::EVENT_NULL = "null";

const EventData Event::BLANK_DATA  = EventData();
const Event     Event::BLANK_EVENT = Event(EVENT_NULL, BLANK_DATA);

Event::Event( const EventType &type /*= EVENT_NULL*/, const EventData &data /*= BLANK_DATA*/ )
{
    _type = type;
    _pData = data.clone();
}

Event::Event( const Event &rhs )
{
    _type = rhs._type;
    _pData = (rhs._pData != nullptr ? rhs._pData->clone() : nullptr);
}

Event::~Event( void )
{
    if (_pData != nullptr)
        delete _pData;
}

std::string Event::toString( void ) const
{
    return "Event";
}
