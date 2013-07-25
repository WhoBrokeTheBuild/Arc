#pragma once

#ifndef __ARC_COLOR_H__
#define __ARC_COLOR_H__

#include "Common.h"
#include "GameObject.h"

#include <SDL/SDL.h>

namespace Arc
{
    class Color
        : public GameObject
    {

        friend class RenderTarget;
        friend class CachedText;

    private:

        virtual SDL_Color SDLColor( void );

    public:

        uint8_t
            R,
            G,
            B,
            A;

        static Color
            BLACK,
            WHITE,
            RED,
            GREEN,
            BLUE,
            CORNFLOWER_BLUE,
            STORM,
            PEACH;

        Color( void ) { setByte(0, 0, 0, 0); }

        Color( float r, float g, float b );
        Color( float r, float g, float b, float a );

        Color( int r, int g, int b );
        Color( int r, int g, int b, int a );

        virtual ~Color( void ) { }

        virtual string toString( void ) const;

        float fracR( void ) const { return (float)((1.0f / 255.0f) * R); }
        float fracG( void ) const { return (float)((1.0f / 255.0f) * G); }
        float fracB( void ) const { return (float)((1.0f / 255.0f) * B); }
        float fracA( void ) const { return (float)((1.0f / 255.0f) * A); }

        int byteR( void ) const { return R; }
        int byteG( void ) const { return G; }
        int byteB( void ) const { return B; }
        int byteA( void ) const { return A; }

        void setFrac( float r, float g, float b );
        void setFrac( float r, float g, float b, float a );

        void setByte( int r, int g, int b );
        void setByte( int r, int g, int b, int a );

    }; // class Color

} // namespace Arc

#endif // __ARC_COLOR_H__
