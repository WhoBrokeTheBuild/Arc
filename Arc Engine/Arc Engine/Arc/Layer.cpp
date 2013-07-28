#include "Layer.h"
#include "Program.h"
#include "Scene.h"

const Arc::EventType Arc::Layer::EVENT_LAYER_CHANGED = "layerChanged";

Arc::Layer::Layer( void )
    : _units(),
      _pParent(),
      Visible(),
      Enabled()
{
}

void Arc::Layer::init( Scene* scene )
{
    _pParent = scene;
    Visible  = true;
    Enabled  = true;

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
        unit->setParentLayer(this);

        dispatchEvent(Event(EVENT_LAYER_CHANGED));

        return true;
    }

    return false;
}

bool Arc::Layer::removeUnit( Unit* unit )
{
    if (!hasUnit(unit))
        return false;

    unit->setParentLayer(nullptr);

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
        delete _units[i];
    }
    _units.clear();

    return size;
}
