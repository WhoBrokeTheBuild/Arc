#pragma once

#ifndef __ARC_UNIT_H__
#define __ARC_UNIT_H__

#include "Common.h"
#include "EventDispatcher.h"

#include "OriginLocation.h"

namespace Arc
{
    class Layer;
    class Scene;

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

        virtual void calcOriginLocation( void );

        virtual void setParentLayer( Layer* layer ) { _pParent = layer; }

    public:

        Point
            Pos;

        float
            Depth;

        bool
            Enabled,
            Visible;

        Unit( void );
        virtual ~Unit( void ) { term(); }

        virtual void init( Vector2 pos, float depth = 0.0f );
        virtual void term( void ) { }

        virtual void update( const Event& event );
        virtual void render( const Event& event );

        virtual void update( const FrameData* data )  = 0;
        virtual void render( const RenderData* data ) = 0;

        virtual Size  getSize  ( void ) { return _size; }
        virtual Point getOrigin( void ) { return _origin; }
        virtual OriginLocation getOriginLocation( void ) { return _originLocation; }

        virtual void setSize  ( Size size );
        virtual void setOrigin( Vector2 origin );
        virtual void setOriginLocation( OriginLocation originLocation );

        virtual Layer* getParentLayer( void ) { return _pParent; }
        virtual Scene* getParentScene( void );

    }; // class Unit

} // namespace Arc

#endif // __ARC_UNIT_H__