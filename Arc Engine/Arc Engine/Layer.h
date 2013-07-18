#pragma once

namespace Arc
{

#ifndef __ARC_LAYER_H__
#define __ARC_LAYER_H__

#include "Common.h"
#include "EventDispatcher.h"

#include "Unit.h"

class Scene;

class Layer :
    public EventDispatcher
{
protected:

    ArrayList<Unit*>
        _units;

    Scene
        *_pParent;

    virtual void sortByDepth( void );

public:

    bool
        Enabled,
        Visible;

    static const EventType
        EVENT_LAYER_CHANGED;

    Layer( void ) { }
    virtual ~Layer( void ) { term(); }

    virtual void init( void );
    virtual void term( void );

    virtual void update( const Event& event );
    virtual void render( const Event& event );

    virtual void layerChanged( const Event& event );

    virtual bool addUnit   ( Unit* unit );
    virtual bool removeUnit( Unit* unit );
    virtual bool hasUnit   ( Unit* unit );

    virtual unsigned int removeAllUnits( void );

};

struct UnitDepthComp
    : binary_function<Unit*, Unit*, bool>
{
    bool operator()( const Unit* lhs, const Unit* rhs ) const
    {
        return lhs->Depth < rhs->Depth;
    }
};

#endif

}
