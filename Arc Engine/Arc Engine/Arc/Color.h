#pragma once

#ifndef __ARC_COLOR_H__
#define __ARC_COLOR_H__

#include "Common.h"
#include "ManagedObject.h"

#include <SDL/SDL.h>

namespace Arc
{
	/** A class to represent a RGBA Color with functions to convert between the 0.0-1.0 and 0-255 formats.
	  */
    class Color
        : public ManagedObject
    {

		// Friend classes to allow access to getSDLColor()
        friend class RenderTarget;
        friend class RenderedText;

    private:

		// A function to get the Color as an SDL_Color struct
        virtual SDL_Color getSDLColor( void );

    public:

		// The four values of the color in 0-255 format
        uint8_t
            R,
            G,
            B,
            A;

		// A handy predefined list of colors
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

		// Constructors for 0.0-1.0 format
        Color( float r, float g, float b );
        Color( float r, float g, float b, float a );

		// Constructors for 0-255 format
        Color( int r, int g, int b );
        Color( int r, int g, int b, int a );

        virtual inline string toString( void ) const;

		// Generate a random color between the specified RGBA values
		inline static Color rand( int minR = 0, int maxR = 255, int minG = 0, int maxG = 255, int minB = 0, int maxB = 255, int minA = 0, int maxA = 255 )
		{
			return Color(randInt(minR, maxR), randInt(minG, maxG), randInt(minB, maxB), randInt(minA, maxA));
		}

		// Linearly interpolate between two colors
		inline static Color lerp( const Color& start, const Color& end, float fraction )
		{
			return Color(lerpNumber(start.byteR(), end.byteR(), fraction), 
				         lerpNumber(start.byteG(), end.byteG(), fraction), 
						 lerpNumber(start.byteB(), end.byteB(), fraction),
						 lerpNumber(start.byteA(), end.byteA(), fraction));
		}

		// Get the RGBA values in 0.0-1.0 format
        float fracR( void ) const { return (float)((1.0f / 255.0f) * R); }
        float fracG( void ) const { return (float)((1.0f / 255.0f) * G); }
        float fracB( void ) const { return (float)((1.0f / 255.0f) * B); }
        float fracA( void ) const { return (float)((1.0f / 255.0f) * A); }

		// Get the RGBA values in 0-255 format
        int byteR( void ) const { return R; }
        int byteG( void ) const { return G; }
        int byteB( void ) const { return B; }
        int byteA( void ) const { return A; }

		// Set the RGBA values in 0.0-1.0 format
        void setFrac( float r, float g, float b );
        void setFrac( float r, float g, float b, float a );

		// Set the RGBA values in 0-255 format
        void setByte( int r, int g, int b );
        void setByte( int r, int g, int b, int a );

    }; // class Color

} // namespace Arc

#endif // __ARC_COLOR_H__
