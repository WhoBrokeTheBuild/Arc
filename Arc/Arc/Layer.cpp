#include "Layer.h"
#include "Program.h"
#include "Scene.h"
#include "Unit.h"

const Arc::EventType Arc::Layer::EVENT_LAYER_CHANGED = "layer.layerChanged";

Arc::Layer::Layer( Scene* scene )
    : _units(),
      _pParent(scene),
      Enabled(true),
      Visible(true)
{
    addEventListener(EVENT_LAYER_CHANGED, this, &Layer::layerChanged);
}

Arc::Layer::~Layer( void )
{
	removeEventListener(EVENT_LAYER_CHANGED, this, &Layer::layerChanged);

	while ( ! _units.isEmpty())
		delete _units.popBack();
}

void Arc::Layer::update( const FrameTime* pTime )
{
    if ( ! Enabled )
		return;

	auto end = _units.end();
	for (auto it = _units.begin(); it != end; ++it)
		if ((*it)->isEnabled())
			(*it)->update(pTime);
}

void Arc::Layer::render( const RenderTarget* pTarget )
{
    if ( ! Visible)
		return;

	auto end = _units.end();
    for (auto it = _units.begin(); it != end; ++it)
		if ((*it)->isVisible())
			(*it)->render(pTarget);
}

void Arc::Layer::layerChanged( const Event& event )
{
    sortByDepth();
}

bool Arc::Layer::addUnit( Unit* unit )
{
    if ( ! _units.contains(unit) )
    {
        _units.add(unit);
        unit->setParentLayer(this);

        dispatchEvent(Event(EVENT_LAYER_CHANGED));

        return true;
    }

    return false;
}

bool Arc::Layer::removeUnit( Unit* unit, bool del /*= false*/ )
{
    if ( ! hasUnit(unit) )
        return false;

    unit->setParentLayer(nullptr);

	bool success = _units.remove(unit);
	delete unit;

    return success;
}

bool Arc::Layer::removeUnitAt( unsigned int index, bool del /*= false */ )
{
	if ( ! _units.hasIndex(index))
		return false;

	return removeUnit(_units[index], del);
}

Arc::Unit* Arc::Layer::getUnit( unsigned int index )
{
	if ( ! _units.hasIndex(index))
		return nullptr;

	return _units[index];
}


bool Arc::Layer::hasUnit( Unit* unit )
{
    return _units.contains(unit);
}

void Arc::Layer::sortByDepth( void )
{
    std::sort(_units.begin(), _units.end(), UnitDepthComp());
}

unsigned int Arc::Layer::removeAllUnits( void )
{
    unsigned int size = _units.getSize();

	while ( ! _units.isEmpty())
		delete _units.popBack();

    return size;
}