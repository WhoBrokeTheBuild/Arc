#pragma once

#ifndef __ARC_UNIT_H__
#define __ARC_UNIT_H__

#include "Common.h"
#include "EventDispatcher.h"

#include "OriginLocation.h"
#include "Layer.h"
#include "Scene.h"

namespace Arc
{
	class Component;

    class Unit :
        public EventDispatcher
    {

        friend class Layer;

    protected:

        Layer
            *_pParent;

        OriginLocation
            _originLocation;

        Point
            _origin;

        Size
            _size;

		ArrayList<Component*>
			_components;

        LinkedList<Component*>
			_componentsToAdd,
			_componentsToRemove;

        virtual void calcOriginLocation( void );

        virtual void setParentLayer( Layer* layer ) { _pParent = layer; }

		virtual void updateComponents( const FrameData* data );
		virtual void renderComponents( const RenderData* data );

    public:

        Point
            Pos;

        float
            Depth;

        bool
            Enabled,
            Visible;

        Unit( Vector2 pos, float depth = 0.0f );
        virtual ~Unit( void );

        virtual void update( const Event& event );
        virtual void render( const Event& event );

        virtual void update( const FrameData* data )  { };
        virtual void render( const RenderData* data ) { };

        virtual Size  getSize  ( void ) { return _size; }
        virtual Point getOrigin( void ) { return _origin; }
        virtual inline OriginLocation getOriginLocation( void ) { return _originLocation; }

        virtual void setSize  ( Size size );
        virtual void setOrigin( Vector2 origin );
        virtual void setOriginLocation( OriginLocation originLocation );

        inline Layer* getParentLayer( void ) { return _pParent; }
		inline Scene* getParentScene( void ) { return _pParent->getParentScene(); }

		virtual bool addComponent   ( Component* component );
		virtual bool removeComponent( Component* component );
		virtual inline bool hasComponent( Component* component ) { return _components.contains(component); }

    }; // class Unit

    struct UnitDepthComp
        : std::binary_function<Unit*, Unit*, bool>
    {
        bool operator()( const Unit* lhs, const Unit* rhs ) const
        {
            return lhs->Depth < rhs->Depth;
        }
    }; // struct UnitDepthComp

} // namespace Arc

#endif // __ARC_UNIT_H__
