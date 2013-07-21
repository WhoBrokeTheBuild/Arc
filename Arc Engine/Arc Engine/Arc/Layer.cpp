#include "Layer.h"
#include "Program.h"
#include "Scene.h"

const Arc::EventType Arc::Layer::EVENT_LAYER_CHANGED = "layerChanged";

Arc::Layer::Layer( void )
{
    _units   = ArrayList<Unit*>();
    _pParent = nullptr;
    Visible  = false;
    Enabled  = false;
}

void Arc::Layer::init( void )
{
    _units  = ArrayList<Unit*>();
    Visible = true;
    Enabled = true;

    addEventListener(EVENT_LAYER_CHANGED, this, &Layer::layerChanged);
}

void Arc::Layer::term( void )
{
    removeEventListener(EVENT_LAYER_CHANGED, this, &Layer::layerChanged);

    removeAllUnits();
}

void Arc::Layer::update( const Event& event )
{
    if (Enabled)
    {
        for (unsigned int i = 0; i < _units.size(); ++i)
        {
            _units[i]->update(event);
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
    sortByDepth();
}

bool Arc::Layer::addUnit( Unit* unit )
{
    if (!_units.contains(unit))
    {
        _units.add(unit);

        addEventListener(Program::EVENT_UPDATE, unit, &Unit::update);
        addEventListener(Program::EVENT_RENDER, unit, &Unit::render);

        dispatchEvent(Event(EVENT_LAYER_CHANGED));

        return true;
    }

    return false;
}

bool Arc::Layer::removeUnit( Unit* unit )
{
    return _units.remove(unit);
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
        removeEventListener(Program::EVENT_RENDER, _units[i], &Unit::render);
        removeEventListener(Program::EVENT_UPDATE, _units[i], &Unit::update);

        delete _units[i];
    }
    _units.clear();

    return size;
}
