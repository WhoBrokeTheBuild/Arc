#include "Color.h"
#include "RenderTarget.h"
#include "RenderedText.h"

const Arc::Color Arc::Color::BLACK             = Color(0,   0,   0);
const Arc::Color Arc::Color::WHITE             = Color(255, 255, 255);
const Arc::Color Arc::Color::RED               = Color(255, 0,   0);
const Arc::Color Arc::Color::GREEN             = Color(0,   255, 0);
const Arc::Color Arc::Color::BLUE              = Color(0,   0,   255);
const Arc::Color Arc::Color::CORNFLOWER_BLUE   = Color(100, 149, 237);
const Arc::Color Arc::Color::STORM             = Color(0,   170, 170);
const Arc::Color Arc::Color::PEACH             = Color(0,   170, 170);

Arc::Color::Color( float r, float g, float b )
{
    setFracValues(r, g, b, 1.0f);
}

Arc::Color::Color( float r, float g, float b, float a )
{
    setFracValues(r, g, b, a);
}

Arc::Color::Color( int r, int g, int b )
{
	setByteValues(r, g, b, 255);
}

Arc::Color::Color( int r, int g, int b, int a )
{
    setByteValues(r, g, b, a);
}

string Arc::Color::toString( void ) const
{
    stringstream ss;
    ss << "Color [" << getByteR() << ", " << getByteG() << ", " << getByteB() << ", " << getByteA() << "]" << endl;
    return ss.str();
}

void Arc::Color::setFracValues( float r, float g, float b )
{
	setFracR(r);
	setFracG(g);
	setFracB(b);
}

void Arc::Color::setFracValues( float r, float g, float b, float a )
{
	setFracR(r);
	setFracG(g);
	setFracB(b);
	setFracA(a);
}

void Arc::Color::setByteValues( int r, int g, int b )
{
	setByteR(r);
	setByteG(g);
	setByteB(b);
}

void Arc::Color::setByteValues( int r, int g, int b, int a )
{
	setByteR(r);
	setByteG(g);
	setByteB(b);
	setByteA(a);
}

SDL_Color Arc::Color::getSDLColor( void ) const
{
    SDL_Color color = { _r, _g, _b, _a };
    return color;
}
