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
#include "ArrayList.h"

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

namespace Arc
{
    class GraphicsSystem;

    class RenderTarget :
        public ManagedObject
    {
    private:

		// A pointer to the base graphics system
		GraphicsSystem* _pGraphicsSystem;

		/* Draws the outline of a shape centered at x,y with the specified number of sides
		 *
		 * @param x: The X coordinate to draw at
		 * @param y: The Y coordinate to draw at
		 * @param radius: The radius of the shape to draw
		 * @param sides: The number of sides on the shape, should be at least 3
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
        virtual void drawShape(
			const float x,
			const float y,
			const float radius,
			const float sides,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO 
			) const;
		
		/* Draws a shape centered at x,y with the specified number of sides
		 *
		 * @param x: The X coordinate to draw at
		 * @param y: The Y coordinate to draw at
		 * @param radius: The radius of the shape to draw
		 * @param sides: The number of sides on the shape, should be at least 3
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
        virtual void fillShape( 
			const float x, 
			const float y,
            const float radius,
            const float sides,
            const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
            const Origin origin = Origin::ZERO 
			) const;

    public:

		/* Creates a render target with a reference to the base graphics system
		 * 
		 * @param pGraphicsSystem: A pointer to the base graphics system
		 */
        RenderTarget( GraphicsSystem *pGraphicsSystem );

        virtual inline ~RenderTarget( void ) { }

        virtual inline string toString( void ) const { return "Render Target"; }

		/* Starts a new draw phase and clears the buffer to the clear color stored in the graphics system
		 */
        virtual void beginDraw( void ) const;
		
		/* Finishes the current draw phase and swaps the buffers
		 */
		virtual inline void endDraw  ( void ) const { SDL_GL_SwapBuffers(); }
		
		/* Renders the text using the font specified and then draws it at the given location
		 *
		 * @warning: This function creates and re-renders a new rendered text each time it is called,
		 * it will cause performance issues if overused
		 *
		 * @param pos: The position to draw at
		 * @param text: The text to render and draw
		 * @param pFont: A pointer to the font to use to render the text
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Renders the text using the font specified and then draws it at the given location
		 *
		 * @warning: This function creates and re-renders a new rendered text each time it is called,
		 * it will cause performance issues if overused
		 *
		 * @param x: The X coordinate to draw at
		 * @param y: The Y coordinate to draw at
		 * @param text: The text to render and draw
		 * @param pFont: A pointer to the font to use to render the text
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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

		/* Draws text at the given position with a pre-rendered text
		 *
		 * @param pos: The position to draw at
		 * @param pRenderedText: A pointer to the rendereded text to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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

		/* Draws text at the given position with a pre-rendered text
		 *
		 * @param x: The X coordinate to draw at
		 * @param y: The Y coordinate to draw at
		 * @param pRenderedText: A pointer to the rendereded text to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
        virtual void drawText(
			const float x, 
			const float y,
			const RenderedText* pRenderedText,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const;

		/* Draws a texture at the given point
		 *
		 * @param pos: The position to draw at
		 * @param pTexture: A pointer to the texture to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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

		/* Draws a texture at the given point
		 *
		 * @param x: The X coordinate to draw at
		 * @param y: The Y coordinate to draw at
		 * @param pTexture: A pointer to the texture to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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

		/* Draws a section of a texture at the given point
		 *
		 * @param pos: The position to draw at
		 * @param pTexture: A pointer to the texture to draw
		 * @param sourceRect: The area from the texture to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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

		/* Draws a section of a texture at the given point
		 *
		 * @param x: The X coordinate to draw at
		 * @param y: The Y coordinate to draw at
		 * @param pTexture: A pointer to the texture to draw
		 * @param sourceRect: The area from the texture to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Draws a line between the given points
		 *
		 * @param start: The first point
		 * @param end: The second point
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param thickness: The thickness in pixels of the line to draw
		 *		default: 1.0f
		 */
        virtual inline void drawLine(
			const Vector2 start,
            const Vector2 end,
            const Color color = Color::WHITE,
            const float thickness = 1.0f
			) const
		{
			drawLine(start.X, start.Y, end.X, end.Y, color, thickness);
		}
		
		/* Draws a line between the given points
		 *
		 * @param x1: The X coordinate of the first point
		 * @param y1: The Y coordinate of the first point
		 * @param x2: The X coordinate of the second point
		 * @param y2: The Y coordinate of the second point
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param thickness: The thickness in pixels of the line to draw
		 *		default: 1.0f
		 */
        virtual void drawLine( 
			const float x1, 
			const float y1,
            const float x2,
			const float y2,
            const Color color = Color::WHITE,
            const float thickness = 1.0f
			) const;
		
		/* Draws the outline of a rectangle with the given size at the given point
		 *
		 * @param x: The X coordinate to draw at
		 * @param y: The Y coordinate to draw at
		 * @param width: The width of the rectangle to draw
		 * @param height: The height of the rectangle to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Draws the outline of a rectangle with the given size at the given point
		 *
		 * @param pos: The position to draw at
		 * @param size: The size of the rectangle to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Draws the outline of a rectangle using the x, y, width, and height from the specified rectangle
		 *
		 * @param rect: The rectangle to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
        virtual void drawRect(
			const Rect rect,
			const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
			const Origin origin = Origin::ZERO
			) const;
		
		/* Draws a filled rectangle with the given size at the given point
		 *
		 * @param x: The X coordinate to draw at
		 * @param y: The Y coordinate to draw at
		 * @param width: The width of the rectangle to draw
		 * @param height: The height of the rectangle to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Draws a filled rectangle with the given size at the given point
		 *
		 * @param pos: The position to draw at
		 * @param size: The size of the rectangle to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Draws a filled rectangle using the x, y, width, and height from the specified rectangle
		 *
		 * @param rect: The rectangle to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
        virtual void fillRect(
			const Rect rect,
            const Color color = Color::WHITE,
			const Angle rotation = Angle::ZERO,
			const Vector2 scale = Vector2::ONE,
            const Origin origin = Origin::ZERO
			) const;
		
		/* Draws the outline of a circle centered at the given point
		 *
		 * @param x: The X coordinate to draw at
		 * @param y: The Y coordinate to draw at
		 * @param float radius: the radius of the circle to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Draws the outline of a circle centered at the given point
		 *
		 * @param pos: The position to draw at
		 * @param float radius: the radius of the circle to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Draws the outline circle using the position and radius of the circle specified
		 *
		 * @param circle: The circle to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Draws a filled a circle centered at the given point
		 *
		 * @param x: The X coordinate to draw at
		 * @param y: The Y coordinate to draw at
		 * @param float radius: the radius of the circle to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Draws a filled a circle centered at the given point
		 *
		 * @param pos: The position to draw at
		 * @param float radius: the radius of the circle to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Draws a filled circle using the position and radius of the circle specified
		 *
		 * @param circle: The circle to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Draws the outline of a triangle centered at the given point
		 *
		 * @param pos: The position to draw at
		 * @param float radius: the radius of the triangle to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Draws a filled a triangle centered at the given point
		 *
		 * @param pos: The position to draw at
		 * @param float radius: the radius of the triangle to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Draws the outline of a triangle centered at the given point
		 *
		 * @param x: The X coordinate to draw at
		 * @param y: The Y coordinate to draw at
		 * @param float radius: the radius of the triangle to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Draws a filled a triangle centered at the given point
		 *
		 * @param x: The X coordinate to draw at
		 * @param y: The Y coordinate to draw at
		 * @param float radius: the radius of the triangle to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Draws the outline of a triangle with the given points
		 *
		 * @param pointA: The first point in the triangle
		 * @param pointB: The second point in the triangle
		 * @param pointC: The third point in the triangle
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 */
		virtual void drawTriangle(
			const Vector2 pointA,
			const Vector2 pointB,
			const Vector2 pointC,
			const Color color = Color::WHITE
			) const;
		
		/* Draws a filled a triangle with the given points
		 *
		 * @param pointA: The first point in the triangle
		 * @param pointB: The second point in the triangle
		 * @param pointC: The third point in the triangle
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 */
		virtual void fillTriangle(
			const Vector2 pointA,
			const Vector2 pointB,
			const Vector2 pointC,
			const Color color = Color::WHITE
			) const;
		
		/* Draws the outline of a pentagon centered at the given point
		 *
		 * @param pos: The position to draw at
		 * @param float radius: the radius of the pentagon to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Draws a filled a pentagon centered at the given point
		 *
		 * @param pos: The position to draw at
		 * @param float radius: the radius of the pentagon to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Draws the outline of a pentagon centered at the given point
		 *
		 * @param x: The X coordinate to draw at
		 * @param y: The Y coordinate to draw at
		 * @param float radius: the radius of the pentagon to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Draws a filled a pentagon centered at the given point
		 *
		 * @param x: The X coordinate to draw at
		 * @param y: The Y coordinate to draw at
		 * @param float radius: the radius of the pentagon to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Draws the outline of a hexagon centered at the given point
		 *
		 * @param pos: The position to draw at
		 * @param float radius: the radius of the hexagon to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Draws a hexagon centered at the given point
		 *
		 * @param pos: The position to draw at
		 * @param float radius: the radius of the hexagon to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Draws the outline of a hexagon centered at the given point
		 *
		 * @param x: The X coordinate to draw at
		 * @param y: The Y coordinate to draw at
		 * @param float radius: the radius of the hexagon to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Draws a filled a hexagon centered at the given point
		 *
		 * @param x: The X coordinate to draw at
		 * @param y: The Y coordinate to draw at
		 * @param float radius: the radius of the hexagon to draw
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 * @param rotation: The angle of rotation to draw at
		 *		default: Angle::ZERO
		 * @param scale: The X and Y scaling factors
		 *		default: Vector2::ONE
		 * @param origin: The origin, relative to the x and y to draw at
		 *		default: Origin::ZERO
		 */
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
		
		/* Draws the outline of a shape defined by the list of points
		 *
		 * @param points: The list of points that define the polygon
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 */
		virtual void drawPolygon( const ArrayList<Point> &points, const Color color = Color::WHITE ) const;

		/* Draws a filled a shape defined by the list of points
		 *
		 * @param points: The list of points that define the polygon
		 * @param color: The color to draw with
		 *		default: Color::WHITE
		 */
		virtual void fillPolygon( const ArrayList<Point> &points, const Color color = Color::WHITE ) const;

    }; // class RenderTarget

} // namespace Arc

#endif // __ARC_RENDER_TARGET_H__
