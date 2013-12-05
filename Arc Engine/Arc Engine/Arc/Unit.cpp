#include "Unit.h"
#include "UnitComponent.h"

const Arc::EventType Arc::Unit::EVENT_ENABLED_CHANGED  = "unit.enabledChanged";
const Arc::EventType Arc::Unit::EVENT_VISIBLE_CHANGED  = "unit.visibleChanged";
const Arc::EventType Arc::Unit::EVENT_DEPTH_CHANGED	   = "unit.depthChanged";
const Arc::EventType Arc::Unit::EVENT_POSITION_CHANGED = "unit.positionChanged";

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
	updateComponents(pData);
}

void Arc::Unit::render( const RenderTarget* pTarget )
{
	renderComponents(pTarget);
}

void Arc::Unit::updateComponents( const FrameData* pData )
{
    while ( ! _componentsToAdd.isEmpty())
    {
        UnitComponent* cmp = _componentsToAdd.popFront();
        cmp->setUnit(this);
        _components.add(cmp);
    }

    while ( ! _componentsToRemove.isEmpty())
	{
		UnitComponent* cmp = _componentsToRemove.popFront();
        _components.remove(cmp);
		delete cmp;
	}

	auto end = _components.end();
    for (auto it = _components.begin(); it != end; ++it)
        (*it)->update(pData);
}

void Arc::Unit::renderComponents( const RenderTarget* pTarget )
{
	auto end = _components.end();
    for (auto it = _components.begin(); it != end; ++it)
        (*it)->render(pTarget);
}

bool Arc::Unit::addComponent( UnitComponent* component )
{
    if (_components.contains(component))
        return false;

    if (_componentsToAdd.contains(component))
        return false;

	_componentsToAdd.add(component);
    return true;
}

bool Arc::Unit::removeComponent( UnitComponent* component )
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

Arc::ImageComponent* Arc::Unit::addNewImageComponent( Sprite *pSprite, Color blendColor /*= Color::WHITE*/, Origin origin /*= Origin::ZERO*/, Vector2 scale /*= Vector2::ONE*/, Angle rotation /*= Angle::ZERO*/, Point offset /*= Point::ZERO */ )
{
	ImageComponent* cmp = New ImageComponent(this, pSprite, blendColor, origin, scale, rotation, offset);
	addComponent(cmp);
	return cmp;
}


Arc::ShapeComponent* Arc::Unit::addNewShapeComponent( bool filled /*= false*/,
													  Color blendColor /*= Color::WHITE*/,
												      Origin origin /*= Origin::ZERO*/, 
												      Vector2 scale /*= Vector2::ONE*/, 
												      Angle rotation /*= Angle::ZERO*/, 
												      Point offset /*= Point::ZERO */ )
{
	ShapeComponent* cmp = New ShapeComponent(this, filled, blendColor, origin, scale, rotation, offset);
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

bool Arc::Unit::hasComponentOfType( const UnitComponentType& type )
{
	UnitComponent* cmp;
	auto end = _components.end();
	for (auto it = _components.begin(); it != end; ++it)
	{
		cmp = (*it);
		if (cmp->getTypes().contains(type))
			return true;
	}

	return false;
}
