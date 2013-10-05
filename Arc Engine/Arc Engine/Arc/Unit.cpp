#include "Unit.h"
#include "Component.h"

#include "PhysicsComponent.h"
#include "ImageComponent.h"
#include "ShapeComponent.h"
#include "AnimatedComponent.h"
#include "TextComponent.h"

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
	while ( ! _componentsToAdd.empty())
		delete _componentsToAdd.popBack();

	while ( ! _componentsToRemove.empty())
		delete _componentsToRemove.popBack();

	while ( ! _components.empty())
		delete _components.popBack();
}

void Arc::Unit::update( const Event& event )
{
    if ( ! isEnabled())
        return;

    const FrameData* data = event.dataAs<FrameData>();

    updateComponents(data);
    update(data);
}

void Arc::Unit::render( const Event& event )
{
    if ( ! isVisible())
        return;

    const RenderData* data = event.dataAs<RenderData>();

    renderComponents(data);
    render(data);
}

void Arc::Unit::updateComponents( const FrameData* data )
{
    while ( ! _componentsToAdd.empty())
    {
        Component* cmp = _componentsToAdd.popFront();
        cmp->setUnit(this);
        _components.add(cmp);
    }

    while ( ! _componentsToRemove.empty())
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

Arc::PhysicsComponent* Arc::Unit::addNewPhysicsComponent( Vector2 vel /*= Vector2::ZERO*/, Vector2 acc /*= Vector2::ZERO*/ )
{
    PhysicsComponent* cmp = New PhysicsComponent(this, vel, acc);
    addComponent(cmp);
    return cmp;
}

Arc::ImageComponent* Arc::Unit::addNewImageComponent( Texture *pTexture, Point offset /*= Point::ZERO*/, Point origin /*= Point::ZERO*/, Vector2 scale /*= Vector2::ZERO*/, Angle rotation /*= Angle::ZERO*/, Color blendColor /*= Color::WHITE*/ )
{
    ImageComponent* cmp = New ImageComponent(this, pTexture, offset, origin, scale, rotation, blendColor);
    addComponent(cmp);
    return cmp;
}

Arc::ImageComponent* Arc::Unit::addNewImageComponent( Texture *pTexture, Point offset /*= Point::ZERO*/, OriginLocation originLocation /*= OriginLocation::ORIGIN_LOCATION_TOP_LEFT*/, Vector2 scale /*= Vector2::ZERO*/, Angle rotation /*= Angle::ZERO*/, Color blendColor /*= Color::WHITE*/ )
{
	ImageComponent* cmp = New ImageComponent(this, pTexture, offset, originLocation, scale, rotation, blendColor);
	addComponent(cmp);
	return cmp;
}

Arc::ShapeComponent* Arc::Unit::addNewShapeComponent( Point offset /*= Point::ZERO*/, Point origin /*= Point::ZERO*/, Vector2 scale /*= Vector2::ZERO*/, Angle rotation /*= Angle::ZERO*/, Color blendColor /*= Color::WHITE*/ )
{
    ShapeComponent* cmp = New ShapeComponent(this, offset, origin, scale, rotation, blendColor);
    addComponent(cmp);
    return cmp;
}

Arc::ShapeComponent* Arc::Unit::addNewShapeComponent( Point offset /*= Point::ZERO*/, OriginLocation originLocation /*= OriginLocation::ORIGIN_LOCATION_TOP_LEFT*/, Vector2 scale /*= Vector2::ZERO*/, Angle rotation /*= Angle::ZERO*/, Color blendColor /*= Color::WHITE*/ )
{
	ShapeComponent* cmp = New ShapeComponent(this, offset, originLocation, scale, rotation, blendColor);
	addComponent(cmp);
	return cmp;
}

Arc::AnimatedComponent* Arc::Unit::addNewAnimatedComponent( void )
{
    AnimatedComponent* cmp = New AnimatedComponent(this);
    addComponent(cmp);
    return cmp;
}

Arc::TextComponent* Arc::Unit::addNewTextComponent( Font *pFont, string text, Point offset /*= Point::ZERO*/, Point origin /*= Point::ZERO*/, Vector2 scale /*= Vector2::ZERO*/, Angle rotation /*= Angle::ZERO*/, Color blendColor /*= Color::WHITE*/ )
{
    TextComponent* cmp = New TextComponent(this, pFont, text, offset, origin, scale, rotation, blendColor);
    addComponent(cmp);
    return cmp;
}

Arc::TextComponent* Arc::Unit::addNewTextComponent( Font *pFont, string text, Point offset /*= Point::ZERO*/, OriginLocation originLocation /*= OriginLocation::ORIGIN_LOCATION_TOP_LEFT*/, Vector2 scale /*= Vector2::ZERO*/, Angle rotation /*= Angle::ZERO*/, Color blendColor /*= Color::WHITE*/ )
{
	TextComponent* cmp = New TextComponent(this, pFont, text, offset, originLocation, scale, rotation, blendColor);
	addComponent(cmp);
	return cmp;
}

Arc::PhysicsComponent* Arc::Unit::getFirstPhysicsComponent( void )
{
	PhysicsComponent* tmp;
	{
		auto end = _components.end();
		for (auto it = _components.begin(); it != end; ++it)
		{
			tmp = dynamic_cast<PhysicsComponent*>(*it);
			if (tmp != nullptr)
				return tmp;
		}
	}
	{
		auto end = _componentsToAdd.end();
		for (auto it = _componentsToAdd.begin(); it != end; ++it)
		{
			tmp = dynamic_cast<PhysicsComponent*>(*it);
			if (tmp != nullptr)
				return tmp;
		}
	}
	return nullptr;
}

Arc::ImageComponent* Arc::Unit::getFirstImageComponent( void )
{
	ImageComponent* tmp;
	{
		auto end = _components.end();
		for (auto it = _components.begin(); it != end; ++it)
		{
			tmp = dynamic_cast<ImageComponent*>(*it);
			if (tmp != nullptr)
				return tmp;
		}
	}
	{
		auto end = _componentsToAdd.end();
		for (auto it = _componentsToAdd.begin(); it != end; ++it)
		{
			tmp = dynamic_cast<ImageComponent*>(*it);
			if (tmp != nullptr)
				return tmp;
		}
	}
	return nullptr;
}

Arc::ShapeComponent* Arc::Unit::getFirstShapeComponent( void )
{
	ShapeComponent* tmp;
	{
		auto end = _components.end();
		for (auto it = _components.begin(); it != end; ++it)
		{
			tmp = dynamic_cast<ShapeComponent*>(*it);
			if (tmp != nullptr)
				return tmp;
		}
	}
	{
		auto end = _componentsToAdd.end();
		for (auto it = _componentsToAdd.begin(); it != end; ++it)
		{
			tmp = dynamic_cast<ShapeComponent*>(*it);
			if (tmp != nullptr)
				return tmp;
		}
	}
	return nullptr;
}

Arc::AnimatedComponent* Arc::Unit::getFirstAnimatedComponent( void )
{
	AnimatedComponent* tmp;
	{
		auto end = _components.end();
		for (auto it = _components.begin(); it != end; ++it)
		{
			tmp = dynamic_cast<AnimatedComponent*>(*it);
			if (tmp != nullptr)
				return tmp;
		}
	}
	{
		auto end = _componentsToAdd.end();
		for (auto it = _componentsToAdd.begin(); it != end; ++it)
		{
			tmp = dynamic_cast<AnimatedComponent*>(*it);
			if (tmp != nullptr)
				return tmp;
		}
	}
	return nullptr;
}

Arc::TextComponent* Arc::Unit::getFirstTextComponent( void )
{
	TextComponent* tmp;
	{
		auto end = _components.end();
		for (auto it = _components.begin(); it != end; ++it)
		{
			tmp = dynamic_cast<TextComponent*>(*it);
			if (tmp != nullptr)
				return tmp;
		}
	}
	{
		auto end = _componentsToAdd.end();
		for (auto it = _componentsToAdd.begin(); it != end; ++it)
		{
			tmp = dynamic_cast<TextComponent*>(*it);
			if (tmp != nullptr)
				return tmp;
		}
	}
	return nullptr;
}

