#include "Unit.h"
#include "Component.h"

Arc::Unit::Unit( Vector2 pos, float depth /*= 0.0f */ )
	: _pParent(nullptr),
	  _pos(pos),
	  _depth(depth),
	  _enabled(true),
	  _visible(true)
{
}

Arc::Unit::~Unit( void )
{
	while ( ! _componentsToAdd.isEmpty())
		delete _componentsToAdd.popBack();

	while ( ! _componentsToRemove.isEmpty())
		delete _componentsToRemove.popBack();

	while ( ! _components.isEmpty())
		delete _components.popBack();
}

void Arc::Unit::update( const FrameData* pData )
{
	if ( ! isEnabled())
		return;

	updateComponents(pData);
	update(pData);
}

void Arc::Unit::render( const RenderData* pData )
{
	if ( ! isVisible())
		return;

	renderComponents(pData);
	render(pData);
}

void Arc::Unit::updateComponents( const FrameData* data )
{
    while ( ! _componentsToAdd.isEmpty())
    {
        Component* cmp = _componentsToAdd.popFront();
        cmp->setUnit(this);
        _components.add(cmp);
    }

    while ( ! _componentsToRemove.isEmpty())
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

Arc::PhysicsComponent* Arc::Unit::addNewPhysicsComponent( Vector2 vel /*= Vector2::ZERO*/, 
														  Vector2 acc /*= Vector2::ZERO*/ )
{
    PhysicsComponent* cmp = New PhysicsComponent(this, vel, acc);
    addComponent(cmp);
    return cmp;
}

Arc::ImageComponent* Arc::Unit::addNewImageComponent( Texture *pTexture, 
												      Color blendColor /*= Color::WHITE*/, 
												      Origin origin /*= Origin::ZERO*/, 
												      Vector2 scale /*= Vector2::ONE*/,
												      Angle rotation /*= Angle::ZERO*/, 
												      Point offset /*= Point::ZERO */ )
{
	ImageComponent* cmp = New ImageComponent(this, pTexture, blendColor, origin, scale, rotation, offset);
	addComponent(cmp);
	return cmp;
}

Arc::ShapeComponent* Arc::Unit::addNewShapeComponent( Color blendColor /*= Color::WHITE*/,
												      Origin origin /*= Origin::ZERO*/, 
												      Vector2 scale /*= Vector2::ONE*/, 
												      Angle rotation /*= Angle::ZERO*/, 
												      Point offset /*= Point::ZERO */ )
{
	ShapeComponent* cmp = New ShapeComponent(this, blendColor, origin, scale, rotation, offset);
	addComponent(cmp);
	return cmp;
}

Arc::AnimatedComponent* Arc::Unit::addNewAnimatedComponent( Animation* pAnimation, 
															Color blendColor /*= Color::WHITE*/, 
															Origin origin /*= Origin::ZERO*/, 
															Vector2 scale /*= Vector2::ONE*/,
															Angle rotation /*= Angle::ZERO*/,
															Point offset /*= Point::ZERO */ )
{
	AnimatedComponent* cmp = New AnimatedComponent(this, pAnimation, blendColor, origin, scale, rotation, offset);
	addComponent(cmp);
	return cmp;
}

Arc::TextComponent* Arc::Unit::addNewTextComponent( Font *pFont, 
													string text,
													Color blendColor /*= Color::WHITE*/, 
													Origin origin /*= Origin::ZERO*/,
													Vector2 scale /*= Vector2::ONE*/, 
													Angle rotation /*= Angle::ZERO*/,
													Point offset /*= Point::ZERO*/ )
{
	TextComponent* cmp = New TextComponent(this, pFont, text, blendColor, origin, scale, rotation, offset);
	addComponent(cmp);
	return cmp;
}

bool Arc::Unit::hasComponentOfType( ComponentType type )
{
	Component* cmp;
	auto end = _components.end();
	for (auto it = _components.begin(); it != end; ++it)
	{
		cmp = (*it);
		if (cmp->getTypes().contains(type))
			return true;
	}

	return false;
}

Arc::Component* Arc::Unit::getFirstComponentOfType( ComponentType type )
{
	Component* cmp;
	auto end = _components.end();
	for (auto it = _components.begin(); it != end; ++it)
	{
		cmp = (*it);
		if (cmp->getTypes().contains(type))
			return cmp;
	}

	return nullptr;
}
