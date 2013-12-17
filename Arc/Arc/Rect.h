#pragma once

#ifndef __ARC_RECT_H__
#define __ARC_RECT_H__

#include "ManagedObject.h"
#include "ISerializable.h"
#include "Functions.h"

#include "Vector2.h"

#include <cmath>

namespace Arc
{
    class Circle;

	/** A rectangle storing an X, Y, Width, and Height 
	 */
    class Rect :
        public ManagedObject,
        public ISerializable
    {
    private:

    public:

        static Rect ZERO;

		static Rect ONE;

        float X;
        float Y;
        float Width;
        float Height;

		// Initialize an empty rectangle
        inline Rect( void ) 
			: X(0.0f),
			  Y(0.0f),
			  Width(0.0f),
			  Height(0.0f)
		{ }

		// Initialize a rectangle with a x, y, width and height
        inline Rect( float x, float y, float width, float height )
			: X(x),
			  Y(y),
			  Width(width),
			  Height(height)
		{ }

		// Initialize a rectangle with a position and a size
        inline Rect( Vector2 pos, Size size )
			: X(pos.X),
			  Y(pos.Y),
			  Width(size.getWidth()),
			  Height(size.getHeight())
		{ }

        virtual inline ~Rect( void ) { }

        virtual inline string toString( void ) const
        {
            stringstream ss;
            ss << "Rect [X: " << X << ", Y: " << Y << ", W: " << Width << ", H: " << Height << "]";
            return ss.str();
        }

		// Generate a random Rect based on the min and max values
		inline static Rect rand( float minX, float maxX,
			                     float minY, float maxY,
								 float minWidth,  float maxWidth,
								 float minHeight, float maxHeight )
		{
			return Rect(randFloat(minX, maxX),
				        randFloat(minY, maxY), 
						randFloat(minWidth, maxWidth), 
						randFloat(minHeight, maxHeight));
		}
		
		// Lerp between the start and end rectangles by the fraction amount
		inline static Rect lerp( const Rect& start, const Rect& end, float fraction )
		{
			return Rect(MathHelper::lerp(start.X, end.X, fraction),
				        MathHelper::lerp(start.Y, end.Y, fraction), 
				        MathHelper::lerp(start.Width,  end.Width,  fraction),
						MathHelper::lerp(start.Height, end.Height, fraction));
		}

		virtual int serialize( ostream& stream );
		virtual int deserialize( istream& stream );

		virtual int serialize( Buffer& buffer );
		virtual int deserialize( Buffer& buffer );

        virtual void setPos( Point pos );
		virtual void setSize( Size size );

		virtual inline Point getPos ( void ) const { return Point( X, Y ); }
		virtual inline Size  getSize( void ) const { return Size( Width, Height ); }

        inline float getHalfWidth ( void ) const { return Width * 0.5f; }
        inline float getHalfHeight( void ) const { return Height * 0.5f; }

		// Get the center point of the rectangle
        inline Point getCenter( void ) const { return Point( X + getHalfWidth(), Y + getHalfHeight() ); }

		// Get the top Y location of the rectangle
        inline float getTop   ( void ) const { return Y; }
		// Get the bottom Y location of the rectangle
        inline float getBottom( void ) const { return Y + Height; }
		// Get the left X location of the rectangle
        inline float getLeft  ( void ) const { return X; }
		// Get the right X location of the rectangle
        inline float getRight ( void ) const { return X + Width; }

        inline Point getTopLeftPoint    ( void ) const { return Point(getTop(),    getLeft());  }
        inline Point getTopRightPoint   ( void ) const { return Point(getTop(),    getRight()); }
        inline Point getBottomLeftPoint ( void ) const { return Point(getBottom(), getLeft());  }
        inline Point getBottomRightPoint( void ) const { return Point(getBottom(), getRight()); }

        virtual bool intersectsRect  ( Rect   other ) const;
        virtual bool intersectsCircle( Circle other ) const;
        virtual bool containsPoint( Point point ) const;

		// Return the rectangle with no negative values
		Rect getPositiveRect( void ) const;

		// Get the rectangle that intersects this and another rectangle, if it exists
        Rect getIntersect( Rect other ) const;

        const Rect operator+( const Rect &rhs ) const;
        const Rect operator-( const Rect &rhs ) const;

        Rect& operator+=( const Rect &rhs );
        Rect& operator-=( const Rect &rhs );

        bool operator==( const Rect &rhs ) const;
        bool operator!=( const Rect &rhs ) const;

    }; // class Rect

    struct CompRect
        : public std::binary_function<Rect, Rect, bool>
    {
        inline bool operator()(const Rect& lhs, const Rect& rhs) const
        {
            return lhs.X < rhs.X; // Simple Sorting
        }
    }; // struct CompRect

} // namespace Arc

#endif // __ARC_RECT_H__
