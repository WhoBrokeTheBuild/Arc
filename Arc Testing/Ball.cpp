#include "Ball.h"

Ball::Ball(void)
{
}

void Ball::init( Vector2 pos, float depth /*= 0.0f */ )
{
    _radius  = 25.0f;
    _gravity = 0.08f;
    _speed   = 5.0f;
    _damping = 0.90f;

    Unit::init(pos, depth);
    ICollidable::init(CircleCollider(0, 0, _radius));
    IPhysicsObject::init(Vector2::ZERO, Vector2(0.0f, _gravity));
    IDrawable::init(Color::RED);

    setOrigin(OriginLocation::ORIGIN_LOCATION_CENTER);
}

void Ball::term( void )
{
}

void Ball::update( const Event& event )
{
    const FrameData* data = event.dataAs<FrameData>();

    if (collideTag("wall-vert", getParentScene(), Pos))
    {
        Vel.Y *= -_damping;
        do 
        {
            Pos.Y += Vel.Y;
        } 
        while (collideTag("wall-vert", getParentScene(), Pos));
    }
    else if (collideTag("wall-horiz", getParentScene(), Pos))
    {
        Vel.X *= -_damping;
        do 
        {
            Pos.X += Vel.X;
        } 
        while (collideTag("wall-horiz", getParentScene(), Pos));
    }

    IPhysicsObject::update(Pos, data->deltaTime());
}

void Ball::render( const Event& event )
{
    const RenderData* data = event.dataAs<RenderData>();

    render(data->renderTarget(), Pos);
}

void Ball::render( const RenderTarget* renderTarget, const Vector2 pos )
{
    renderTarget->fillCircle(Circle(Pos, _radius), BlendColor, 0.0f, _origin);
}

void Ball::setTarget( Point target )
{
    _speed = Pos.distanceTo(target) / 20.0f;

    float angle = Pos.angleToRad(target);

    Vel = Vector2(cos(angle) * _speed, sin(angle) * _speed);
}
