#include "TestUnit.h"

TestUnit::TestUnit(void)
    : UnitSize()
{
    Active   = false;
    UnitSize = Size::ZERO;
}

void TestUnit::init( Vector2 pos, Collider* collider, float depth /*= 0.0f*/, bool active /*= true*/ )
{
    Unit::init(pos, depth);
    IDrawable::init(Color::RED);
    IPhysicsObject::init();
    ICollidable::init(collider);
    IKeyboardListener::init();
    setOrigin(OriginLocation::ORIGIN_LOCATION_CENTER);

    Active = active;
    UnitSize = Size(50);
}

void TestUnit::term( void )
{
}

void TestUnit::update( const FrameData* data )
{
    if (Active)
        IPhysicsObject::update(Pos, data->deltaTime());
}

void TestUnit::render( const RenderData* data )
{
    const RenderTarget* target = data->renderTarget();

    Color 
        first  = Color::RED,
        second = Color::BLUE;

    first.A = 100;
    second.A = 100;

    target->fillTriangle(Pos, 50.0f, first, Rot, _origin);
    target->fillTriangle(Pos, 50.0f, second, Rot + (float)PI, _origin);

    bool color = false;
    for (int deg = 0; deg < 360; deg += 15)
    {
        target->fillPentagon(Pos + Vector2(100.0f, 0), 20.0f, (color ? first : second), (Rot / 2.0f) + toRad(deg), Vector2(-100.0f, 0));
        color = !color;
    }

    _pCollider->render(target, Pos, _origin);
}

void TestUnit::keyHeld( const Event& event )
{
    const KeyData* data = event.dataAs<KeyData>();

    switch (data->Key)
    {
    case KEY_LEFT:

        Vel.X = -5.0f;

        break;
    case KEY_RIGHT:

        Vel.X = 5.0f;

        break;
    case KEY_UP:

        Vel.Y = -5.0f;

        break;
    case KEY_DOWN:

        Vel.Y = 5.0f;

        break;
    case KEY_A:

        Rot += Arc::toRad(5.0f);

        break;
    case KEY_S:

        Rot -= Arc::toRad(5.0f);

        break;
    }
}

void TestUnit::keyReleased( const Event& event )
{
    const KeyData* data = event.dataAs<KeyData>();

    switch (data->Key)
    {
    case KEY_LEFT:
    case KEY_RIGHT:

        Vel.X = 0.0f;

        break;
    case KEY_UP:
    case KEY_DOWN:

        Vel.Y = 0.0f;

        break;
    }
}
