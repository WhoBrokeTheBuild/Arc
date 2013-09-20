#include "Unit.h"
#include "Component.h"

Arc::Unit::Unit( void )
{
    _pParent = nullptr;
    _originLocation = INVALID_ORIGIN_LOCATION;
    _origin = Pos = Vector2::ZERO;
    Depth = 0.0f;
    Enabled = Visible = false;
}

void Arc::Unit::init( Vector2 pos, float depth /*= 0.0f */ )
{
    Pos     = pos;
    Depth   = depth;
    Enabled = true;
    Visible = true;
}

void Arc::Unit::term( void )
{
	while ( ! _componentsToAdd.empty())
		delete _componentsToAdd.popBack();

	while ( ! _componentsToRemove.empty())
		delete _componentsToRemove.popBack();

	while ( ! _components.empty())
		delete _components.popBack();
}

void Arc::Unit::update( const Event& event )
{
    if ( ! Enabled)
        return;

    const FrameData* data = event.dataAs<FrameData>();

    updateComponents(data);
    update(data);
}

void Arc::Unit::render( const Event& event )
{
    if ( ! Visible)
        return;

    const RenderData* data = event.dataAs<RenderData>();

    renderComponents(data);
    render(data);
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

void Arc::Unit::updateComponents( const FrameData* data )
{
    while ( ! _componentsToAdd.empty())
    {
        Component* cmp = _componentsToAdd.popFront();
        cmp->setUnit(this);
        _components.add(cmp);
    }

    while ( ! _componentsToRemove.empty())
	{
		Component* cmp = _componentsToRemove.popFront();
        _components.remove(cmp);
		delete cmp;
	}

    for (auto it = _components.begin(); it != _components.end(); ++it)
        (*it)->update(data);
}

void Arc::Unit::renderComponents( const RenderData* data )
{
    for (auto it = _components.begin(); it != _components.end(); ++it)
        (*it)->render(data);
}

bool Arc::Unit::addComponent( Component* component )
{
    if (_components.contains(component))
        return false;

    if (_componentsToAdd.contains(component))
        return false;

	_componentsToAdd.add(component);
    return true;
}

bool Arc::Unit::removeComponent( Component* component )
{
    if ( ! _components.contains(component))
        return false;

    if (_componentsToRemove.contains(component))
        return false;

	_componentsToRemove.add(component);
    return true;
}