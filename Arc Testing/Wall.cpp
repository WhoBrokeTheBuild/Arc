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

void Wall::update( const Event& event )
{
    const FrameData* data = event.dataAs<FrameData>();
}

void Wall::render( const Event& event )
{
    const RenderData* data = event.dataAs<RenderData>();

    render(data->renderTarget(), Pos);
}

void Wall::render( const RenderTarget* renderTarget, const Vector2 pos )
{
    renderTarget->fillRect(Rect(_area.pos() + pos, _area.size()), BlendColor);
}
