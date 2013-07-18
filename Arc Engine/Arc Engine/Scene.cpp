#include "Scene.h"
#include "Program.h"

void Scene::init( void )
{
    IFrameListener::init();

    _layers = Map<unsigned int, Layer*>();
    Visible = true;
    Enabled = true;
}

void Scene::term( void )
{
    Map<unsigned int, Layer*>::Iterator it;
    for (it = _layers.begin(); it != _layers.end(); ++it)
    {
        removeEventListener(Program::EVENT_RENDER, it->second, &Layer::render);
        removeEventListener(Program::EVENT_UPDATE, it->second, &Layer::update);

        delete it->second;
    }
    _layers.clear();
}

void Scene::update( const Event& event )
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

void Scene::render( const Event& event )
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

bool Scene::addLayer( int index )
{
    if (!hasLayer(index))
    {
        _layers.add(index, New Layer());
        _layers[index]->init();

        addEventListener(Program::EVENT_UPDATE, _layers[index], &Layer::update);
        addEventListener(Program::EVENT_RENDER, _layers[index], &Layer::render);

        return true;
    }

    return false;
}

Layer* Scene::getLayer( int index )
{
    if (!hasLayer(index))
        addLayer(index);

    return _layers[index];
}

bool Scene::hasLayer( int index )
{
    return _layers.containsKey(index);
}

void Scene::swapLayers( int index, int newIndex )
{
    if (!hasLayer(index))
        addLayer(index);

    if (!hasLayer(newIndex))
        addLayer(newIndex);

    swap(_layers[index], _layers[newIndex]);
}

unsigned int Scene::emptyLayer( int index )
{
    if (!hasLayer(index))
        addLayer(index);

    return _layers[index]->removeAllUnits();
}

void Scene::showLayer( int index )
{
    setLayerVisible(index, true);
}

void Scene::hideLayer( int index )
{
    setLayerVisible(index, false);
}

void Scene::setLayerVisible( int index, bool visible )
{
    if (!hasLayer(index))
        addLayer(index);

    _layers[index]->Visible = visible;
}

void Scene::toggleLayerVisible( int index )
{
    setLayerVisible(index, !isLayerVisible(index));
}

bool Scene::isLayerVisible( int index )
{
    if (!hasLayer(index))
        addLayer(index);

    return _layers[index]->Visible;
}

void Scene::enableLayer( int index )
{
    setLayerEnabled(index, true);
}

void Scene::disableLayer( int index )
{
    setLayerEnabled(index, false);
}

void Scene::setLayerEnabled( int index, bool enabled )
{
    if (!hasLayer(index))
        addLayer(index);

    _layers[index]->Enabled = enabled;
}

void Scene::toggleLayerEnabled( int index )
{
    setLayerEnabled(index, !isLayerEnabled(index));
}

bool Scene::isLayerEnabled( int index )
{
    if (!hasLayer(index))
        addLayer(index);

    return _layers[index]->Enabled;
}

bool Scene::addUnit( Unit* unit, int layer )
{
    return getLayer(layer)->addUnit(unit);
}

void Scene::moveUnit( Unit* unit, int newLayer )
{
    removeUnit(unit);
    getLayer(newLayer)->addUnit(unit);
}

bool Scene::removeUnit( Unit* unit )
{
    Map<unsigned int, Layer*>::Iterator it;
    for (it = _layers.begin(); it != _layers.end(); ++it)
    {
        if (it->second->removeUnit(unit))
            return true;
    }

    return false;
}

bool Scene::hasUnit( Unit* unit )
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

Layer* Scene::getUnitLayer( Unit* unit )
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

int Scene::getUnitLayerIndex( Unit* unit )
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
