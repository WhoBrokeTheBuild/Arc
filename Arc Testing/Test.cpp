#include "Test.h"

void Test::init( Animation *pAnimation )
{
    Unit::init(Vector2::ZERO);
    IDrawableImage::init(pAnimation, true);
    IPhysicsObject::init();
    ICollidable::init(RectCollider(Vector2::ZERO, Vector2(255)));

    IKeyboardListener::init();

    speed = 5.0f;
}

void Test::term( void )
{

}

void Test::update( const Event& event )
{
    const FrameData* data = event.dataAs<FrameData>();

    IPhysicsObject::update(Pos, data->deltaTime());
    IDrawableImage::update(data->elapsedMilliseconds());
}

void Test::render( const Event& event )
{
    const RenderData* data = event.dataAs<RenderData>();

    IDrawableImage::render(data->renderTarget(), Pos);

    RectCollider* rectCollider = dynamic_cast<RectCollider*>(_pCollider);

    if (rectCollider != nullptr)
        data->renderTarget()->drawRect(Rect(Pos, Vector2::ZERO) + rectCollider->RectMask, Color::RED);
}

void Test::keyReleased( const Event& event )
{
    const KeyData* data = event.dataAs<KeyData>();

    switch (data->Key)
    {
    case KEY_LEFT:
    case KEY_A:

        if (sign(Vel.X) == -1)
            Vel.X = 0;

        break;
    case KEY_RIGHT:
    case KEY_D:

        if (sign(Vel.X) == 1)
            Vel.X = 0;

        break;
    case KEY_UP:
    case KEY_W:

        if (sign(Vel.Y) == -1)
            Vel.Y = 0;

        break;
    case KEY_DOWN:
    case KEY_S:

        if (sign(Vel.Y) == 1)
            Vel.Y = 0;

        break;
    default:
        break;
    }
}

void Test::keyHeld( const Event& event )
{
    const KeyData* data = event.dataAs<KeyData>();

    switch (data->Key)
    {
    case KEY_LEFT:
    case KEY_A:

        Vel.X = -speed;

        break;
    case KEY_RIGHT:
    case KEY_D:

        Vel.X = speed;

        break;
    case KEY_UP:
    case KEY_W:

        Vel.Y = -speed;

        break;
    case KEY_DOWN:
    case KEY_S:

        Vel.Y = speed;

        break;
    default:
        break;
    }
}
