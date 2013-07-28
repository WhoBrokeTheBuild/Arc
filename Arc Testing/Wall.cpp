#include "Wall.h"

Wall::Wall(void)
    : _area()
{
}

void Wall::init( Vector2 pos, Rect area, float depth /*= 0.0f */ )
{
    _area = area;

    Unit::init(pos, depth);
    ICollidable::init(RectCollider(_area));
    IDrawable::init(Color::BLACK);
}

void Wall::term( void )
{
}

void Wall::update( const FrameData* data )
{
}

void Wall::render( const RenderData* data )
{
    const RenderTarget* target = data->renderTarget();

    target->fillRect(Rect(_area.pos() + Pos, _area.size()), BlendColor, 0.0f, getOrigin());
    _pCollider->render(target, Pos, getOrigin());
}