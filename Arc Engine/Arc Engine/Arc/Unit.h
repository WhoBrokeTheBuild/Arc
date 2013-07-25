#pragma once

#ifndef __ARC_UNIT_H__
#define __ARC_UNIT_H__

#include "Common.h"
#include "EventDispatcher.h"

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

        virtual void setParentLayer( Layer* layer ) { _pParent = layer; }

    public:

        Point
            Pos;

        float
            Depth;

        Unit( void );
        virtual ~Unit( void ) { term(); }

        virtual void init( Vector2 pos, float depth = 0.0f );
        virtual void term( void ) { }

        virtual void update( const Event& event ) { }
        virtual void render( const Event& event ) { }

        virtual Layer* getParentLayer( void ) { return _pParent; }
        virtual Scene* getParentScene( void );

    }; // class Unit

} // namespace Arc

#endif // __ARC_UNIT_H__