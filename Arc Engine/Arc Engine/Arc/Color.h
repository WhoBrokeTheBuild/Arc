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

		/* Get the Color as an SDL_Color struct
		 * 
		 * @returns: The color as an SDL_Color struct
		 */
        virtual SDL_Color getSDLColor( void ) const;

	protected:

		// The Red component of the color in 0-255 format
		uint8_t _r;

		// The Green component of the color in 0-255 format
		uint8_t _g;

		// The Blue component of the color in 0-255 format
		uint8_t _b;

		// The Alpha component of the color in 0-255 format
		uint8_t _a;

    public:

		// Predefined colors
		static const Color BLACK;
		static const Color WHITE;
		static const Color RED;
		static const Color GREEN;
		static const Color BLUE;
		static const Color CORNFLOWER_BLUE;
		static const Color STORM;
		static const Color PEACH;

		/* Creates a color with R, G, B, and A values of 0
		 */
        Color( void ) { _r = _g = _b = _a = 0; }

		/* Creates a color with the specified Red, Green, and Blue values, and an alpha value of 255
		 * 
		 * @param r: The Red component in 0.0-1.0 format
		 * @param g: The Green component in 0.0-1.0 format
		 * @param b: The Blue component in 0.0-1.0 format
		 */
        Color( float r, float g, float b );
		
		/* Creates a color with the specified Red, Green, Blue, and Alpha values
		 * 
		 * @param r: The Red component in 0.0-1.0 format
		 * @param g: The Green component in 0.0-1.0 format
		 * @param b: The Blue component in 0.0-1.0 format
		 * @param a: The Alpha component in 0.0-1.0 format
		 */
        Color( float r, float g, float b, float a );
		
		/* Creates a color with the specified Red, Green, and Blue values, and an alpha value of 255
		 * 
		 * @param r: The Red component in 0-255 format
		 * @param g: The Green component in 0-255 format
		 * @param b: The Blue component in 0-255 format
		 */
        Color( int r, int g, int b );
		
		/* Creates a color with the specified Red, Green, Blue, and Alpha values
		 * 
		 * @param r: The Red component in 0-255 format
		 * @param g: The Green component in 0-255 format
		 * @param b: The Blue component in 0-255 format
		 * @param a: The Alpha component in 0-255 format
		 */
        Color( int r, int g, int b, int a );

        virtual inline string toString( void ) const;

		/* Generates a random color between the specified RGBA values
		 * 
		 * @param minR: The minimum Red value in 0-255 format
		 *		default: 0
		 * @param maxR: The maximum Red value in 0-255 format
		 *		default: 255
		 * @param minG: The minimum Green value in 0-255 format
		 *		default: 0
		 * @param maxG: The maximum Green value in 0-255 format
		 *		default: 255
		 * @param minB: The minimum Blue value in 0-255 format
		 *		default: 0
		 * @param maxB: The maximum Blue value in 0-255 format
		 *		default: 255
		 * @param minA: The minimum Alpha value in 0-255 format
		 *		default: 0
		 * @param maxA: The maximum Alpha value in 0-255 format
		 *		default: 255
		 * @returns: The randomly generated color
		 */
		inline static Color rand( int minR = 0, int maxR = 255, int minG = 0, int maxG = 255, int minB = 0, int maxB = 255, int minA = 0, int maxA = 255 )
		{
			return Color(randInt(minR, maxR), randInt(minG, maxG), randInt(minB, maxB), randInt(minA, maxA));
		}

		/* Linearly interpolate between two colors
		 *
		 * @param start: The color values to start at
		 * @param end: The color values to move to
		 * @param fraction: The amount to interpolate, should be a value from 0.0-1.0
		 * @returns: The interpolated color
		 */
		inline static Color lerp( const Color& start, const Color& end, float fraction )
		{
			return Color(MathHelper::lerp(start.getByteR(), end.getByteR(), fraction), 
				         MathHelper::lerp(start.getByteG(), end.getByteG(), fraction), 
						 MathHelper::lerp(start.getByteB(), end.getByteB(), fraction),
						 MathHelper::lerp(start.getByteA(), end.getByteA(), fraction));
		}

		/*
		 * @returns: The Red component in 0.0-1.0 format
		 */
        inline float getFracR( void ) const { return (float)((1.0f / 255.0f) * _r); }

		/*
		 * @returns: The Green component in 0.0-1.0 format
		 */
        inline float getFracG( void ) const { return (float)((1.0f / 255.0f) * _g); }

		/*
		 * @returns: The Blue component in 0.0-1.0 format
		 */
        inline float getFracB( void ) const { return (float)((1.0f / 255.0f) * _b); }

		/*
		 * @returns: The Alpha component in 0.0-1.0 format
		 */
        inline float getFracA( void ) const { return (float)((1.0f / 255.0f) * _a); }
		
		/* 
		 * @param r: The Red component in 0.0-1.0 format
		 */
		inline void setFracR( float r ) { _r = (uint8_t)(MathHelper::clamp(r, 0.0f, 1.0f) * 255.0f); }

		/* 
		 * @param g: The Green component in 0.0-1.0 format
		 */
		inline void setFracG( float g ) { _g = (uint8_t)(MathHelper::clamp(g, 0.0f, 1.0f) * 255.0f); }

		/* 
		 * @param b: The Blue component in 0.0-1.0 format
		 */
		inline void setFracB( float b ) { _b = (uint8_t)(MathHelper::clamp(b, 0.0f, 1.0f) * 255.0f); }

		/* 
		 * @param a: The Alpha component in 0.0-1.0 format
		 */
		inline void setFracA( float a ) { _a = (uint8_t)(MathHelper::clamp(a, 0.0f, 1.0f) * 255.0f); }

		/*
		 * @returns: The Red component in 0-255 format
		 */
        inline int getByteR( void ) const { return _r; }
		
		/*
		 * @returns: The Green component in 0-255 format
		 */
        inline int getByteG( void ) const { return _g; }
		
		/*
		 * @returns: The Blue component in 0-255 format
		 */
        inline int getByteB( void ) const { return _b; }
		
		/*
		 * @returns: The Alpha component in 0-255 format
		 */
		inline int getByteA( void ) const { return _a; }

		/* 
		 * @param r: The Red component in 0-255 format
		 */
		inline void setByteR( int r ) { _r = MathHelper::clamp(r, 0, 255); }

		/* 
		 * @param g: The Green component in 0-255 format
		 */
		inline void setByteG( int g ) { _g = MathHelper::clamp(g, 0, 255); }

		/* 
		 * @param b: The Blue component in 0-255 format
		 */
		inline void setByteB( int b ) { _b = MathHelper::clamp(b, 0, 255); }

		/* 
		 * @param a: The Alpha component in 0-255 format
		 */
		inline void setByteA( int a ) { _a = MathHelper::clamp(a, 0, 255); }

		/*
		 * @param r: The Red component in 0.0-1.0 format
		 * @param g: The Green component in 0.0-1.0 format
		 * @param b: The Blue component in 0.0-1.0 format
		 */
        inline void setFracValues( float r, float g, float b );

		/*
		 * @param r: The Red component in 0.0-1.0 format
		 * @param g: The Green component in 0.0-1.0 format
		 * @param b: The Blue component in 0.0-1.0 format
		 * @param a: The Alpha component in 0.0-1.0 format
		 */
        void setFracValues( float r, float g, float b, float a );
		
		/*
		 * @param r: The Red component in 0-255 format
		 * @param g: The Green component in 0-255 format
		 * @param b: The Blue component in 0-255 format
		 */
        void setByteValues( int r, int g, int b );
		
		/*
		 * @param r: The Red component in 0-255 format
		 * @param g: The Green component in 0-255 format
		 * @param b: The Blue component in 0-255 format
		 * @param a: The Alpha component in 0-255 format
		 */
        void setByteValues( int r, int g, int b, int a );

    }; // class Color

} // namespace Arc

#endif // __ARC_COLOR_H__
