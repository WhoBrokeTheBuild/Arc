#pragma once

#ifndef __ARC_LAYER_H__
#define __ARC_LAYER_H__

#include "Common.h"
#include "EventDispatcher.h"

#include "Unit.h"

namespace Arc
{
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

        Layer( void );
        virtual ~Layer( void ) { term(); }

        virtual void init( Scene* scene );
        virtual void term( void );

        virtual string toString( void ) const { return "Layer"; }

        virtual void update( const Event& event );
        virtual void render( const Event& event );

        virtual void layerChanged( const Event& event );

        virtual bool addUnit   ( Unit* unit );
        virtual bool removeUnit( Unit* unit );
        virtual bool hasUnit   ( Unit* unit );

        virtual unsigned int removeAllUnits( void );

        virtual Scene* getParentScene( void ) { return _pParent; }

    }; // class Layer

    struct UnitDepthComp
        : std::binary_function<Unit*, Unit*, bool>
    {
        bool operator()( const Unit* lhs, const Unit* rhs ) const
        {
            return lhs->Depth < rhs->Depth;
        }
    }; // struct UnitDepthComp

} // namespace Arc

#endif // __ARC_LAYER_H__
