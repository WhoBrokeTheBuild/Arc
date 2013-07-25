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

void TestUnit::update( const Event& event )
{
    const FrameData* data = event.dataAs<FrameData>();

    if (Active)
        IPhysicsObject::update(Pos, data->deltaTime());

    if (collideTag("test", getParentScene(), Pos))
        INFO(toString(), "Colliding");
}

void TestUnit::render( const Event& event )
{
    const RenderData* data = event.dataAs<RenderData>();

    render(data->renderTarget(), Pos);
    _pCollider->render(data->renderTarget(), Pos);
}

void TestUnit::render( const RenderTarget* renderTarget, const Vector2 pos )
{
    Color 
        first  = Color::RED,
        second = Color::BLUE;

    first.A = 100;
    second.A = 100;

    renderTarget->fillTriangle(Pos, 50.0f, first, Rot, _origin);
    renderTarget->fillTriangle(Pos, 50.0f, second, Rot + (float)PI, _origin);

    bool color = false;
    for (int deg = 0; deg < 360; deg += 15)
    {
        renderTarget->fillPentagon(Pos + Vector2(100.0f, 0), 20.0f, (color ? first : second), (Rot / 2.0f) + toRad(deg), Vector2(-100.0f, 0));
        color = !color;
    }
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
