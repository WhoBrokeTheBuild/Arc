#include "Ball.h"

Ball::Ball(void)
    : _radius(),
      _gravity(),
      _maxSpeed(),
      _damping(),
      _pPing(nullptr),
      _pPong(nullptr),
      _ping()
{
}

void Ball::init( Vector2 pos, float depth /*= 0.0f */ )
{
    _radius   = 30.0f;
    _gravity  = 0.08f;
    _maxSpeed = 15.0f;
    _damping  = 1.0f;

    Unit::init(pos, depth);
    ICollidable::init(CircleCollider(0, 0, _radius));
    IPhysicsObject::init(Vector2::ZERO, Vector2(0.0f, _gravity));
    IDrawable::init(Color::RED);

    setSize(Size(_radius * 2.0f));
    setOriginLocation(OriginLocation::ORIGIN_LOCATION_CENTER);

    _pPing = New Sound();
    _pPing->init("assets/ping.wav");

    _pPong = New Sound();
    _pPong->init("assets/pong.wav");

    _ping = true;
}

void Ball::term( void )
{
    delete _pPong;
    delete _pPing;
}

void Ball::update( const FrameData* data )
{
    if (!Rect(0, 0, 600, 600).containsPoint(Pos))
        Pos = Point(300);

    CollisionData coll = collideTagListFirst(*ArrayList<string>().add("wall"), getParentScene(), Pos, getOrigin());
    if (coll.Collided)
    {
        Direction side = coll.getSide();

        if (side == DIR_NORTH || side == DIR_SOUTH)
        {
            //_pPong->play();

            Vel.Y *= -randFloat(0.7f, _damping);
        }
        else if (side == DIR_WEST || side == DIR_EAST)
        {
            //_pPing->play();

            Vel.X *= -randFloat(0.7f, _damping);
        }

        do
        {
            Angle revAng = coll.AngleTo + Angle::HALF_CIRCLE;
            Pos += Vector2(revAng.getCos() * 2.0f, revAng.getSin() * 2.0f);
        }
        while (checkTagList(*ArrayList<string>().add("wall"), getParentScene(), Pos, getOrigin()));
    }

    Vel.X = clamp(Vel.X, -_maxSpeed, _maxSpeed);
    Vel.Y = clamp(Vel.Y, -_maxSpeed, _maxSpeed);

    Rot += 0.08f;

    IPhysicsObject::update(Pos, data->deltaTime());

}

void Ball::render( const RenderData* data )
{
    const RenderTarget* target = data->renderTarget();

    //target->fillCircle(Circle(Pos, _radius), BlendColor, 0.0f, getOrigin());

    Color
        first  = Color::RED,
        second = Color::BLUE;

    first.A = 100;
    second.A = 100;

    //target->fillTriangle(Pos, 50.0f, first, Rot, _origin);
    //target->fillTriangle(Pos, 50.0f, second, Rot + (float)PI, _origin);

    bool color = false;
    for (int deg = 0; deg < 360; deg += 15)
    {
        target->fillPentagon(Pos + Vector2(-5.0f, 5.0f), 5.0f, (color ? first : second), Angle((Rot / 2.0f) + toRad(deg), ANGLE_TYPE_RAD), Vector2(-25.0f, 0));
        color = !color;
    }

    //_pCollider->render(target, Pos, getOrigin());
}

void Ball::setTarget( Point target )
{
    float speed = Pos.distanceTo(target) / 20.0f;
    Angle angle = Pos.angleTo(target);

    Vel = Vector2(angle.getCos() * speed, angle.getSin() * speed);
}
