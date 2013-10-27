#include "Scene.h"
#include "Unit.h"
#include "Program.h"

Arc::Scene::Scene( void )
	: _layers(),
	  _tags(),
	  Enabled(true),
	  Visible(true)
{
}

Arc::Scene::~Scene( void )
{
	auto end = _layers.end();
    for (auto it = _layers.begin(); it != end; ++it)
        delete it->second;

    _layers.clear();
    _tags.clear();
}

void Arc::Scene::update( const FrameData* pData )
{
    if ( ! Enabled)
		return;

	auto end = _layers.end();
    for (auto it = _layers.begin(); it != end; ++it)
        it->second->update(pData);
}

void Arc::Scene::render( const RenderData* pData )
{
    if ( ! Visible)
		return;

	auto end = _layers.end();
    for (auto it = _layers.begin(); it != end; ++it)
        it->second->render(pData);
}

bool Arc::Scene::addLayer( int index )
{
    if ( ! hasLayer(index))
    {
        _layers.add(index, New Layer(this));

        return true;
    }

    return false;
}

Arc::Layer* Arc::Scene::getLayer( int index )
{
    if ( ! hasLayer(index))
        addLayer(index);

    return _layers[index];
}

bool Arc::Scene::hasLayer( int index )
{
    return _layers.containsKey(index);
}

void Arc::Scene::swapLayers( int index, int newIndex )
{
    if ( ! hasLayer(index))
        addLayer(index);

    if ( ! hasLayer(newIndex))
        addLayer(newIndex);

    std::swap(_layers[index], _layers[newIndex]);
}

unsigned int Arc::Scene::emptyLayer( int index )
{
    if ( ! hasLayer(index))
        addLayer(index);

    return _layers[index]->removeAllUnits();
}

void Arc::Scene::showLayer( int index )
{
    setLayerVisible(index, true);
}

void Arc::Scene::hideLayer( int index )
{
    setLayerVisible(index, false);
}

void Arc::Scene::setLayerVisible( int index, bool visible )
{
    if ( ! hasLayer(index))
        addLayer(index);

    _layers[index]->Visible = visible;
}

void Arc::Scene::toggleLayerVisible( int index )
{
    setLayerVisible(index, !isLayerVisible(index));
}

bool Arc::Scene::isLayerVisible( int index )
{
    if ( ! hasLayer(index))
        addLayer(index);

    return _layers[index]->Visible;
}

void Arc::Scene::enableLayer( int index )
{
    setLayerEnabled(index, true);
}

void Arc::Scene::disableLayer( int index )
{
    setLayerEnabled(index, false);
}

void Arc::Scene::setLayerEnabled( int index, bool enabled )
{
    if ( ! hasLayer(index))
        addLayer(index);

    _layers[index]->Enabled = enabled;
}

void Arc::Scene::toggleLayerEnabled( int index )
{
    setLayerEnabled(index, !isLayerEnabled(index));
}

bool Arc::Scene::isLayerEnabled( int index )
{
    if ( ! hasLayer(index))
        addLayer(index);

    return _layers[index]->Enabled;
}

bool Arc::Scene::addUnit( Unit* unit, int layer )
{
    return getLayer(layer)->addUnit(unit);
}

void Arc::Scene::moveUnit( Unit* unit, int newLayer )
{
    removeUnit(unit);
    getLayer(newLayer)->addUnit(unit);
}

bool Arc::Scene::removeUnit( Unit* unit )
{
    auto end = _layers.end();
    for (auto it = _layers.begin(); it != end; ++it)
    {
        if (it->second->removeUnit(unit))
            return true;
    }

    return false;
}

bool Arc::Scene::hasUnit( Unit* unit )
{
    bool flag = false;

    auto end = _layers.end();
    for (auto it = _layers.begin(); it != end; ++it)
    {
        if (it->second->hasUnit(unit))
        {
            flag = true;
            break;
        }
    }

    return flag;
}

Arc::Layer* Arc::Scene::getUnitLayer( Unit* unit )
{
    Layer* tmp = nullptr;

    auto end = _layers.end();
    for (auto it = _layers.begin(); it != end; ++it)
    {
        if (it->second->hasUnit(unit))
        {
            tmp = it->second;
            break;
        }
    }

    return tmp;
}

int Arc::Scene::getUnitLayerIndex( Unit* unit )
{
    int index = -1;

    auto end = _layers.end();
    for (auto it = _layers.begin(); it != end; ++it)
    {
        if (it->second->hasUnit(unit))
        {
            index = it->first;
            break;
        }
    }

    return index;
}

bool Arc::Scene::addUnitTag( Unit* unit, string tag )
{
    if (hasUnitTag(unit, tag))
        return false;

    if ( ! _tags.containsKey(tag))
        _tags.add(tag, ArrayList<Unit*>());

    _tags[tag].add(unit);

    return true;
}

bool Arc::Scene::removeUnitTag( Unit* unit, string tag )
{
    if ( ! hasUnitTag(unit, tag))
        return false;

    return _tags[tag].remove(unit);
}

bool Arc::Scene::hasUnitTag( Unit* unit, string tag )
{
    if ( ! _tags.containsKey(tag))
        return false;

    return _tags[tag].contains(unit);
}

Arc::ArrayList<string> Arc::Scene::getAllTags( string tag )
{
    return _tags.keyArrayList();
}

Arc::ArrayList<Arc::Unit*> Arc::Scene::getUnitsByTag( string tag )
{
    if ( ! _tags.containsKey(tag))
        return ArrayList<Unit*>();

    return _tags[tag];
}
