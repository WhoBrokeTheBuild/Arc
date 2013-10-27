#pragma once

#ifndef __ARC_RENDER_TARGET_H__
#define __ARC_RENDER_TARGET_H__

#include "Common.h"
#include "ManagedObject.h"

#include "Color.h"
#include "Font.h"
#include "RenderedText.h"
#include "Texture.h"
#include "Origin.h"

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

namespace Arc
{
    class GraphicsSystem;

    class RenderTarget :
        public ManagedObject
    {
    private:

        GraphicsSystem
            *_pGraphicsSystem;

        virtual void drawShape(
			const float x,
			const float y,
			const float radius,
			const float shapeValue,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO 
			) const;

        virtual void fillShape( 
			const float x, 
			const float y,
            const float radius,
            const float shapeValue,
            const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
            const Origin origin = Origin::ZERO 
			) const;

    public:

        RenderTarget( GraphicsSystem *pGraphicsSystem );
        virtual inline ~RenderTarget( void ) { }

        virtual inline string toString( void ) const { return "Render Target"; }

		// Clear the screen and reset OpenGL
        virtual void beginDraw( void ) const;
		virtual inline void endDraw  ( void ) const { SDL_GL_SwapBuffers(); }

        virtual inline void drawText( 
			const Vector2 pos,
			const string text,
			Font* pFont,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO 
			) const
		{
			drawText(pos.X, pos.Y, text, pFont, color, rotation, scale, origin);
		}

        virtual inline void drawText(
			const float x, 
			const float y,
			const string text,
			Font* pFont,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const
		{
			RenderedText renderedText(text, pFont);
			drawText(x, y, &renderedText, color, rotation, scale, origin.getPoint());
		}

        virtual inline void drawText( 
			const Vector2 pos,
            const RenderedText* pRenderedText,
            const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
            const Origin origin = Origin::ZERO
			) const
		{
			drawText(pos.X, pos.Y, pRenderedText, color, rotation, scale, origin.getPoint());
		}

        virtual void drawText(
			const float x, 
			const float y,
			const RenderedText* pRenderedText,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const;

        virtual inline void draw(
			const Vector2 pos,
			const Texture *pTexture,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const
		{
			draw(pos.X, pos.Y, pTexture, color, rotation, scale, origin.getPoint());
		}

        virtual inline void draw( 
			const float x, 
			const float y,
			const Texture *pTexture,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const
		{
			draw(x, y, pTexture, Rect(Vector2::ZERO, pTexture->getSize()), color, rotation, scale, origin.getPoint());
		}

        virtual inline void draw( 
			const Vector2 pos,
			const Texture *pTexture,
			const Rect sourceRect,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const
		{
			draw(pos.X, pos.Y, pTexture, sourceRect, color, rotation, scale, origin);
		}

        virtual void draw( 
			const float x,
			const float y,
            const Texture *pTexture,
            const Rect sourceRect,
            const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
            const Origin origin = Origin::ZERO
			) const;

        virtual inline void drawLine(
			const Vector2 start,
            const Vector2 end,
            const Color color = Color::WHITE,
            const float thickness = 1.0f
			) const
		{
			drawLine(start.X, start.Y, end.X, end.Y, color, thickness);
		}

        virtual void drawLine( 
			const float x1, 
			const float y1,
            const float x2,
			const float y2,
            const Color color = Color::WHITE,
            const float thickness = 1.0f
			) const;

        virtual inline void drawRect(
			const float x,
			const float y,
			const float width,
			const float height,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const
		{
			Rect rect = Rect(x, y, width, height);
			drawRect(rect, color, rotation, scale, origin.getPoint());
		}

		virtual inline void drawRect( 
			const Point pos,
			const Size size,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const
		{
			Rect rect = Rect(pos, size);
			drawRect(rect, color, rotation, scale, origin.getPoint());
		}

        virtual void drawRect(
			const Rect rect,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const;

        virtual inline void fillRect( 
			const float x,
			const float y,
            const float width,
            const float height,
            const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const
		{
			Rect rect = Rect(x, y, width, height);
			fillRect(rect, color, rotation, scale, origin.getPoint());
		}

		virtual inline void fillRect(
			const Point pos,
			const Size size,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const
		{
			Rect rect = Rect(pos, size);
			fillRect(rect, color, rotation, scale, origin.getPoint());
		}

        virtual void fillRect(
			const Rect rect,
            const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
            const Origin origin = Origin::ZERO
			) const;

        virtual inline void drawCircle(
			const float x,
			const float y,
			const float radius,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const
		{
			Circle circle = Circle(x, y, radius);
			drawCircle(circle, color, rotation, scale, origin.getPoint());
		}

		virtual inline void drawCircle(
			const Point pos,
			const float radius,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const
		{
			Circle circle = Circle(pos, radius);
			drawCircle(circle, color, rotation, scale, origin.getPoint());
		}

        virtual inline void drawCircle( 
			const Circle circle,
            const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
            const Origin origin = Origin::ZERO
			) const
		{
			drawShape(circle.X, circle.Y, circle.Radius, 24, color, rotation, scale, origin.getPoint());
		}

        virtual inline void fillCircle( 
			const float x, 
			const float y,
            const float radius,
            const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const
		{
			Circle circle = Circle(x, y, radius);
			fillCircle(circle, color, rotation, scale, origin.getPoint());
		}

		virtual inline void fillCircle( 
			const Point pos,
			const float radius,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const
		{
			Circle circle = Circle(pos, radius);
			fillCircle(circle, color, rotation, scale, origin.getPoint());
		}

        virtual inline void fillCircle( 
			const Circle circle,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const
		{
			fillShape(circle.X, circle.Y, circle.Radius, 24, color, rotation, scale, origin.getPoint());
		}

        virtual inline void drawTriangle(
			const Vector2 pos,
            const float radius,
            const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
            const Origin origin = Origin::ZERO
			) const
		{
			drawTriangle(pos.X, pos.Y, radius, color, rotation, scale, origin.getPoint());
		}

        virtual inline void fillTriangle(
			const Vector2 pos,
			const float radius,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const
		{
			fillTriangle(pos.X, pos.Y, radius, color, rotation, scale, origin.getPoint());
		}

        virtual inline void drawTriangle( 
			const float x,
			const float y,
			const float radius,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const
		{
			drawShape(x, y, radius, 1.5, color, rotation, scale, origin.getPoint());
		}

        virtual inline void fillTriangle( 
			const float x,
			const float y,
            const float radius,
            const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
            const Origin origin = Origin::ZERO
			) const
		{
			fillShape(x, y, radius, 1.5, color, rotation, scale, origin.getPoint());
		}

		virtual void drawTriangle(
			const Vector2 pointA,
			const Vector2 pointB,
			const Vector2 pointC,
			const Color color = Color::WHITE
			) const;

		virtual void fillTriangle(
			const Vector2 pointA,
			const Vector2 pointB,
			const Vector2 pointC,
			const Color color = Color::WHITE
			) const;

        virtual inline void drawPentagon( 
			const Vector2 pos,
			const float radius,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const
		{
			drawPentagon(pos.X, pos.Y, radius, color, rotation, scale, origin.getPoint());
		}

        virtual inline void fillPentagon( 
			const Vector2 pos,
			const float radius,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const
		{
			fillPentagon(pos.X, pos.Y, radius, color, rotation, scale, origin.getPoint());
		}

        virtual inline void drawPentagon( 
			const float x, 
			const float y,
            const float radius,
            const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
            const Origin origin = Origin::ZERO
			) const
		{
			drawShape(x, y, radius, 2.5, color, rotation, scale, origin.getPoint());
		}

        virtual inline void fillPentagon( 
			const float x,
			const float y,
            const float radius,
            const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
            const Origin origin = Origin::ZERO
			) const
		{
			fillShape(x, y, radius, 2.5, color, rotation, scale, origin.getPoint());
		}

        virtual inline void drawHexagon(
			const Vector2 pos,
            const float radius,
            const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
            const Origin origin = Origin::ZERO
			) const
		{
			drawShape(pos.X, pos.Y, radius, 3, color, rotation, scale, origin.getPoint());
		}

        virtual inline void fillHexagon( 
			const Vector2 pos,
			const float radius,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const
		{
			fillShape(pos.X, pos.Y, radius, 3, color, rotation, scale, origin.getPoint());
		}

        virtual inline void drawHexagon(
			const float x,
			const float y,
			const float radius,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const
		{
			drawShape(x, y, radius, 3, color, rotation, scale, origin.getPoint());
		}

        virtual inline void fillHexagon( 
			const float x, 
			const float y,
			const float radius,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const
		{
			fillShape(x, y, radius, 3, color, rotation, scale, origin.getPoint());
		}

		virtual void drawPolygon( const ArrayList<Point> &points, const Color color = Color::WHITE ) const;
		virtual void fillPolygon( const ArrayList<Point> &points, const Color color = Color::WHITE ) const;

    }; // class RenderTarget

} // namespace Arc

#endif // __ARC_RENDER_TARGET_H__
