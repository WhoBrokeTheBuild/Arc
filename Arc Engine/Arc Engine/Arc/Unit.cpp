#include "Unit.h"
#include "Layer.h"
#include "Scene.h"

Arc::Unit::Unit( void )
    : _pParent(),
      _origin(),
      _originLocation(INVALID_ORIGIN_LOCATION),
      Pos(),
      Depth(),
      Enabled(),
      Visible()
{
}

void Arc::Unit::init( Vector2 pos, float depth /*= 0.0f */ )
{
    Pos     = pos;
    Depth   = depth;
    Enabled = true;
    Visible = true;
}

void Arc::Unit::update( const Event& event )
{
    if (!Enabled) 
        return;

    const FrameData* data = event.dataAs<FrameData>();

    update(data);
}

void Arc::Unit::render( const Event& event )
{
    if (!Visible)
        return;

    const RenderData* data = event.dataAs<RenderData>();

    render(data);
}

Arc::Scene* Arc::Unit::getParentScene( void )
{
    return _pParent->getParentScene();
}

void Arc::Unit::calcOriginLocation( void )
{
    switch (_originLocation)
    {
    case ORIGIN_LOCATION_TOP_LEFT:

        _origin = Vector2::ZERO;

        break;
    case ORIGIN_LOCATION_TOP_RIGHT:

        _origin = Vector2(_size.width(), 0);

        break;
    case ORIGIN_LOCATION_BOTTOM_LEFT:

        _origin = Vector2(0, _size.height());

        break;
    case ORIGIN_LOCATION_BOTTOM_RIGHT:

        _origin = Vector2(_size.width(), _size.height());

        break;
    case ORIGIN_LOCATION_CENTER:

        _origin = Vector2(_size.halfWidth(), _size.halfHeight());

        break;
    case ORIGIN_LOCATION_TOP_CENTER:

        _origin = Vector2(_size.halfWidth(), 0);

        break;
    case ORIGIN_LOCATION_BOTTOM_CENTER:

        _origin = Vector2(_size.halfWidth(), _size.height());

        break;
    case ORIGIN_LOCATION_LEFT_CENTER:

        _origin = Vector2(0, _size.halfHeight());

        break;
    case ORIGIN_LOCATION_RIGHT_CENTER:

        _origin = Vector2(_size.width(), _size.halfHeight());

        break;
    default:
        break;
    }
}

void Arc::Unit::setSize( Size size )
{
    _size = size;
    calcOriginLocation();
}

void Arc::Unit::setOrigin( Vector2 origin )
{
    _origin = origin;
    _originLocation = ORIGIN_LOCATION_MANUAL;
}

void Arc::Unit::setOriginLocation( OriginLocation originLocation )
{
    _originLocation = originLocation;
    calcOriginLocation();
}
