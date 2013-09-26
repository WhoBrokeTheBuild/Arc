#include "Layer.h"
#include "Program.h"
#include "Scene.h"
#include "Unit.h"

const Arc::EventType Arc::Layer::EVENT_LAYER_CHANGED = "layerChanged";

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
    removeAllUnits();
}

void Arc::Layer::update( const Event& event )
{
    if ( ! Enabled )
		return;

    for (unsigned int i = 0; i < _units.size(); ++i)
    {
        _units[i]->update(event);
    }
}

void Arc::Layer::render( const Event& event )
{
    if ( ! Visible)
		return;

    for (unsigned int i = 0; i < _units.size(); ++i)
    {
        _units[i]->render(event);
    }
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
    unsigned int size = _units.size();

    for (unsigned int i = 0; i < size; ++i)
    {
        delete _units[i];
    }
    _units.clear();

    return size;
}