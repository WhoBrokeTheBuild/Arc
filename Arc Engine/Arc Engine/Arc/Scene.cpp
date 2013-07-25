#include "Scene.h"
#include "Program.h"

Arc::Scene::Scene( void )
{
    _layers = Map<unsigned int, Layer*>();
    _tags   = Map<string, ArrayList<Unit*>>();
    Visible = false;
    Enabled = false;
}

void Arc::Scene::init( void )
{
    IFrameListener::init();

    _layers = Map<unsigned int, Layer*>();
    _tags   = Map<string, ArrayList<Unit*>>();
    Visible = true;
    Enabled = true;
}

void Arc::Scene::term( void )
{
    Map<unsigned int, Layer*>::Iterator it;
    for (it = _layers.begin(); it != _layers.end(); ++it)
    {
        removeEventListener(Program::EVENT_RENDER, it->second, &Layer::render);
        removeEventListener(Program::EVENT_UPDATE, it->second, &Layer::update);

        delete it->second;
    }
    _layers.clear();
    _tags.clear();
}

void Arc::Scene::update( const Event& event )
{
    if (Enabled)
    {
        Map<unsigned int, Layer*>::Iterator it;
        for (it = _layers.begin(); it != _layers.end(); ++it)
        {
            it->second->update(event);
        }
    }
}

void Arc::Scene::render( const Event& event )
{
    if (Visible)
    {
        Map<unsigned int, Layer*>::Iterator it;
        for (it = _layers.begin(); it != _layers.end(); ++it)
        {
            it->second->render(event);
        }
    }
}

bool Arc::Scene::addLayer( int index )
{
    if (!hasLayer(index))
    {
        _layers.add(index, New Layer());
        _layers[index]->init(this);

        addEventListener(Program::EVENT_UPDATE, _layers[index], &Layer::update);
        addEventListener(Program::EVENT_RENDER, _layers[index], &Layer::render);

        return true;
    }

    return false;
}

Arc::Layer* Arc::Scene::getLayer( int index )
{
    if (!hasLayer(index))
        addLayer(index);

    return _layers[index];
}

bool Arc::Scene::hasLayer( int index )
{
    return _layers.containsKey(index);
}

void Arc::Scene::swapLayers( int index, int newIndex )
{
    if (!hasLayer(index))
        addLayer(index);

    if (!hasLayer(newIndex))
        addLayer(newIndex);

    std::swap(_layers[index], _layers[newIndex]);
}

unsigned int Arc::Scene::emptyLayer( int index )
{
    if (!hasLayer(index))
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
    if (!hasLayer(index))
        addLayer(index);

    _layers[index]->Visible = visible;
}

void Arc::Scene::toggleLayerVisible( int index )
{
    setLayerVisible(index, !isLayerVisible(index));
}

bool Arc::Scene::isLayerVisible( int index )
{
    if (!hasLayer(index))
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
    if (!hasLayer(index))
        addLayer(index);

    _layers[index]->Enabled = enabled;
}

void Arc::Scene::toggleLayerEnabled( int index )
{
    setLayerEnabled(index, !isLayerEnabled(index));
}

bool Arc::Scene::isLayerEnabled( int index )
{
    if (!hasLayer(index))
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
    Map<unsigned int, Layer*>::Iterator it;
    for (it = _layers.begin(); it != _layers.end(); ++it)
    {
        if (it->second->removeUnit(unit))
            return true;
    }

    return false;
}

bool Arc::Scene::hasUnit( Unit* unit )
{
    bool flag = false;

    Map<unsigned int, Layer*>::Iterator it;
    for (it = _layers.begin(); it != _layers.end(); ++it)
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

    Map<unsigned int, Layer*>::Iterator it;
    for (it = _layers.begin(); it != _layers.end(); ++it)
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

    Map<unsigned int, Layer*>::Iterator it;
    for (it = _layers.begin(); it != _layers.end(); ++it)
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

    if (!_tags.containsKey(tag))
        _tags.add(tag, ArrayList<Unit*>());

    _tags[tag].add(unit);

    return true;
}

bool Arc::Scene::removeUnitTag( Unit* unit, string tag )
{
    if (!hasUnitTag(unit, tag))
        return false;

    return _tags[tag].remove(unit);
}

bool Arc::Scene::hasUnitTag( Unit* unit, string tag )
{
    if (!_tags.containsKey(tag))
        return false;

    return _tags[tag].contains(unit);
}

Arc::ArrayList<string> Arc::Scene::getAllTags( string tag )
{
    return _tags.keyArrayList();
}

Arc::ArrayList<Arc::Unit*> Arc::Scene::getUnitsByTag( string tag )
{
    if (!_tags.containsKey(tag))
        return ArrayList<Unit*>();

    return _tags[tag];
}
