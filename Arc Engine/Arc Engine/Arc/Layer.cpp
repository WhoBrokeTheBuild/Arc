#include "Layer.h"
#include "Program.h"
#include "Scene.h"
#include "Unit.h"

const Arc::EventType Arc::Layer::EVENT_LAYER_CHANGED = "layerChanged";

Arc::Layer::Layer( void )
	: _units(),
	_pParent(nullptr),
	_shouldSort(),
	_unitCount(),
      Enabled(),
      Visible()
{
}

void Arc::Layer::init( Scene* scene )
{
	_pParent    = scene;
	_shouldSort = false;
	_unitCount  = 0;
	Visible     = true;
	Enabled     = true;

    addEventListener(EVENT_LAYER_CHANGED, this, &Layer::layerChanged);
}

void Arc::Layer::term( void )
{
    removeEventListener(EVENT_LAYER_CHANGED, this, &Layer::layerChanged);

    removeAllUnits();
}

void Arc::Layer::update( const Event& event )
{
    if ( Enabled )
	{
		for (unsigned int i = 0; i < _units.size(); ++i)
		{
			_units[i]->update(event);
		}

		if (_shouldSort)
		{
			sortByDepth();
			_shouldSort = false;
		}
    }
}

void Arc::Layer::render( const Event& event )
{
    if (Visible)
    {
        for (unsigned int i = 0; i < _units.size(); ++i)
        {
            _units[i]->render(event);
        }
    }
}

void Arc::Layer::layerChanged( const Event& event )
{
	_shouldSort = true;
}

bool Arc::Layer::addUnit( Unit* unit )
{
	if (hasUnit(unit))
		return false;

	_units.add(unit);
	return true;
}

bool Arc::Layer::removeUnit( Unit* unit, bool del /*= false*/ )
{
	if ( ! hasUnit(unit) )
		return false;

	unit->setParentLayer(nullptr);

	bool success = _units.remove(unit);

	if (del)
		delete unit;

	if (success)
		_unitCount--;

	return success;
}

bool Arc::Layer::removeUnitAt( unsigned int index, bool del /*= false*/ )
{
	if ( index > getUnitCount() )
		return false;

	Unit* unit = _units[index];

	return removeUnit(unit, del);
}

bool Arc::Layer::hasUnit( Unit* unit )
{
    return _units.contains(unit);
}

Arc::Unit* Arc::Layer::getUnit( unsigned int index )
{
	if (index < getUnitCount())
	{
		return _units[index];
	}

	return nullptr;
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
	_unitCount = 0;

    return size;
}
