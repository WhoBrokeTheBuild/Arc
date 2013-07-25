#include "Color.h"
#include "RenderTarget.h"
#include "CachedText.h"

Arc::Color Arc::Color::BLACK             = Color(0,   0,   0);
Arc::Color Arc::Color::WHITE             = Color(255, 255, 255);
Arc::Color Arc::Color::RED               = Color(255, 0,   0);
Arc::Color Arc::Color::GREEN             = Color(0,   255, 0);
Arc::Color Arc::Color::BLUE              = Color(0,   0,   255);
Arc::Color Arc::Color::CORNFLOWER_BLUE   = Color(100, 149, 237);
Arc::Color Arc::Color::STORM             = Color(0,   170, 170);
Arc::Color Arc::Color::PEACH             = Color(0,   170, 170);

Arc::Color::Color( float r, float g, float b )
{
    setFrac(r, g, b);
}

Arc::Color::Color( float r, float g, float b, float a )
{
    setFrac(r, g, b, a);
}

Arc::Color::Color( int r, int g, int b )
{
    setByte(r, g, b);
}

Arc::Color::Color( int r, int g, int b, int a )
{
    setByte(r, g, b, a);
}

string Arc::Color::toString( void ) const
{
    stringstream ss;
    ss << "Color [" << byteR() << ", " << byteG() << ", " << byteB() << ", " << byteA() << "]" << endl;
    return ss.str();
}

void Arc::Color::setFrac( float r, float g, float b )
{
    R = (uint8_t)(clamp(r, 0.0f, 1.0f) * 255.0f);
    G = (uint8_t)(clamp(g, 0.0f, 1.0f) * 255.0f);
    B = (uint8_t)(clamp(b, 0.0f, 1.0f) * 255.0f);
    A = 255;
}

void Arc::Color::setFrac( float r, float g, float b, float a )
{
    R = (uint8_t)(clamp(r, 0.0f, 1.0f) * 255.0f);
    G = (uint8_t)(clamp(g, 0.0f, 1.0f) * 255.0f);
    B = (uint8_t)(clamp(b, 0.0f, 1.0f) * 255.0f);
    A = (uint8_t)(clamp(a, 0.0f, 1.0f) * 255.0f);
}

void Arc::Color::setByte( int r, int g, int b )
{
    R = clamp(r, 0, 255);
    G = clamp(g, 0, 255);
    B = clamp(b, 0, 255);
    A = 255;
}

void Arc::Color::setByte( int r, int g, int b, int a )
{
    R = clamp(r, 0, 255);
    G = clamp(g, 0, 255);
    B = clamp(b, 0, 255);
    A = clamp(a, 0, 255);
}

SDL_Color Arc::Color::SDLColor( void )
{
    SDL_Color color = { R, G, B, A };
    return color;
}
