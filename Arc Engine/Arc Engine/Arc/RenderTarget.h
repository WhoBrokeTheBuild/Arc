#pragma once

#ifndef __ARC_RENDER_TARGET_H__
#define __ARC_RENDER_TARGET_H__

#include "Common.h"
#include "GameObject.h"

#include "Color.h"
#include "Font.h"
#include "CachedText.h"
#include "Texture.h"

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

namespace Arc
{
    class GraphicsSystem;

    class RenderTarget :
        public GameObject
    {
    private:

        GraphicsSystem
            *_pGraphicsSystem;

        virtual void drawShape( const float x, const float y,
                                const float radius, 
                                const float shapeValue,
                                const Color color = Color::WHITE, 
                                const float rotation = 0.0f, 
                                const Vector2 origin = Vector2::ZERO ) const;

        virtual void fillShape( const float x, const float y,
                                const float radius, 
                                const float shapeValue,
                                const Color color = Color::WHITE,
                                const float rotation = 0.0f, 
                                const Vector2 origin = Vector2::ZERO ) const;

    public:

        RenderTarget( void );
        virtual ~RenderTarget( void ) { term(); }

        virtual void init( GraphicsSystem *pGraphicsSystem );
        virtual void term( void ) { }

        virtual string toString( void ) const { return "Render Target"; }

        virtual void beginDraw( void ) const;
        virtual void endDraw  ( void ) const;

        virtual void drawText( const Vector2 pos, 
                               const string text, 
                               Font* pFont,
                               const Color color = Color::WHITE,
                               const float rotation = 0.0f,
                               const Vector2 origin = Vector2::ZERO ) const;

        virtual void drawText( const float x, const float y,
                               const string text,
                               Font* pFont, 
                               const Color color = Color::WHITE,
                               const float rotation = 0.0f,
                               const Vector2 origin = Vector2::ZERO ) const;

        virtual void drawText( const Vector2 pos,
                               const CachedText* pCachedText, 
                               const Color color = Color::WHITE, 
                               const float rotation = 0.0f,
                               const Vector2 origin = Vector2::ZERO ) const;

        virtual void drawText( const float x, const float y,
                               const CachedText* pCachedText,
                               const Color color = Color::WHITE,
                               const float rotation = 0.0f, 
                               const Vector2 origin = Vector2::ZERO ) const;

        virtual void draw( const Vector2 pos, 
                           const Texture *pTexture, 
                           const Color color = Color::WHITE, 
                           const float rotation = 0.0f,
                           const Vector2 origin = Vector2::ZERO ) const;

        virtual void draw( const float x, const float y,
                           const Texture *pTexture, 
                           const Color color = Color::WHITE, 
                           const float rotation = 0.0f,
                           const Vector2 origin = Vector2::ZERO ) const;

        virtual void draw( const Vector2 pos,
                           const Texture *pTexture,
                           const Rect sourceRect,
                           const Color color = Color::WHITE,
                           const float rotation = 0.0f,
                           const Vector2 origin = Vector2::ZERO,
                           bool flip = false ) const;

        virtual void draw( const float x, const float y,
                           const Texture *pTexture,
                           const Rect sourceRect,
                           const Color color = Color::WHITE, 
                           const float rotation = 0.0f,
                           const Vector2 origin = Vector2::ZERO,
                           bool flip = false ) const;

        virtual void drawLine( const Vector2 start,
                               const Vector2 end, 
                               const Color color = Color::WHITE, 
                               const float thickness = 1.0f ) const;

        virtual void drawLine( const float x1, const float y1,
                               const float x2, const float y2,
                               const Color color = Color::WHITE,
                               const float thickness = 1.0f ) const;

        virtual void drawRect( const float x, const float y,
                               const float width,
                               const float height,
                               const Color color = Color::WHITE,
                               const float rotation = 0.0f, 
                               const Vector2 origin = Vector2::ZERO ) const;

        virtual void drawRect( const Rect rect,
                               const Color color = Color::WHITE,
                               const float rotation = 0.0f,
                               const Vector2 origin = Vector2::ZERO ) const;

        virtual void fillRect( const float x, const float y,
                               const float width, 
                               const float height, 
                               const Color color = Color::WHITE,
                               const float rotation = 0.0f, 
                               const Vector2 origin = Vector2::ZERO ) const;

        virtual void fillRect( const Rect rect,
                               const Color color = Color::WHITE,
                               const float rotation = 0.0f,
                               const Vector2 origin = Vector2::ZERO ) const;

        virtual void drawCircle( const float x, const float y,
                                 const float radius, 
                                 const Color color = Color::WHITE,
                                 const float rotation = 0.0f,
                                 const Vector2 origin = Vector2::ZERO ) const;

        virtual void drawCircle( const Circle circle,
                                 const Color color = Color::WHITE, 
                                 const float rotation = 0.0f,
                                 const Vector2 origin = Vector2::ZERO ) const;

        virtual void fillCircle( const float x, const float y,
                                 const float radius,
                                 const Color color = Color::WHITE,
                                 const float rotation = 0.0f,
                                 const Vector2 origin = Vector2::ZERO ) const;

        virtual void fillCircle( const Circle circle,
                                 const Color color = Color::WHITE,
                                 const float rotation = 0.0f, 
                                 const Vector2 origin = Vector2::ZERO ) const;

        virtual void drawTriangle( const Vector2 pos,
                                   const float radius,
                                   const Color color = Color::WHITE,
                                   const float rotation = 0.0f,
                                   const Vector2 origin = Vector2::ZERO ) const;

        virtual void fillTriangle( const Vector2 pos,
                                   const float radius,
                                   const Color color = Color::WHITE, 
                                   const float rotation = 0.0f,
                                   const Vector2 origin = Vector2::ZERO ) const;

        virtual void drawTriangle( const float x, const float y,
                                   const float radius,
                                   const Color color = Color::WHITE,
                                   const float rotation = 0.0f, 
                                   const Vector2 origin = Vector2::ZERO ) const;

        virtual void fillTriangle( const float x, const float y, 
                                   const float radius, 
                                   const Color color = Color::WHITE,
                                   const float rotation = 0.0f, 
                                   const Vector2 origin = Vector2::ZERO ) const;

        virtual void drawPentagon( const Vector2 pos,
                                   const float radius,
                                   const Color color = Color::WHITE,
                                   const float rotation = 0.0f, 
                                   const Vector2 origin = Vector2::ZERO ) const;

        virtual void fillPentagon( const Vector2 pos,
                                   const float radius,
                                   const Color color = Color::WHITE, 
                                   const float rotation = 0.0f, 
                                   const Vector2 origin = Vector2::ZERO ) const;

        virtual void drawPentagon( const float x, const float y, 
                                   const float radius, 
                                   const Color color = Color::WHITE, 
                                   const float rotation = 0.0f,
                                   const Vector2 origin = Vector2::ZERO ) const;

        virtual void fillPentagon( const float x, const float y,
                                   const float radius,
                                   const Color color = Color::WHITE,
                                   const float rotation = 0.0f,
                                   const Vector2 origin = Vector2::ZERO ) const;

        virtual void drawHexagon( const Vector2 pos, 
                                  const float radius, 
                                  const Color color = Color::WHITE,
                                  const float rotation = 0.0f,
                                  const Vector2 origin = Vector2::ZERO ) const;

        virtual void fillHexagon( const Vector2 pos, 
                                  const float radius, 
                                  const Color color = Color::WHITE, 
                                  const float rotation = 0.0f, 
                                  const Vector2 origin = Vector2::ZERO ) const;

        virtual void drawHexagon( const float x, const float y,
                                  const float radius,
                                  const Color color = Color::WHITE,
                                  const float rotation = 0.0f,
                                  const Vector2 origin = Vector2::ZERO ) const;

        virtual void fillHexagon( const float x, const float y,
                                  const float radius,
                                  const Color color = Color::WHITE,
                                  const float rotation = 0.0f,
                                  const Vector2 origin = Vector2::ZERO ) const;

    }; // class RenderTarget

} // namespace Arc

#endif // __ARC_RENDER_TARGET_H__
