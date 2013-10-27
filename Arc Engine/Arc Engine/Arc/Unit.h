#pragma once

#ifndef __ARC_UNIT_H__
#define __ARC_UNIT_H__

#include "Common.h"
#include "EventDispatcher.h"

#include "OriginLocation.h"
#include "Layer.h"
#include "Scene.h"
#include "Origin.h"

#include "PhysicsComponent.h"
#include "ImageComponent.h"
#include "ShapeComponent.h"
#include "AnimatedComponent.h"
#include "TextComponent.h"

namespace Arc
{
	class Component;

    class Unit :
        public EventDispatcher
    {

        friend class Layer;

    protected:

        Layer
            *_pParent;

        Point
            _pos;

        float
            _depth;

        bool
            _enabled,
            _visible;

		ArrayList<Component*>
			_components;

        LinkedList<Component*>
			_componentsToAdd,
			_componentsToRemove;

        virtual void setParentLayer( Layer* layer ) { _pParent = layer; }

		virtual void updateComponents( const FrameData* data );
		virtual void renderComponents( const RenderData* data );

    public:

        Unit( Vector2 pos, float depth = 0.0f );
        virtual ~Unit( void );

        virtual void update( const FrameData* pData );;
        virtual void render( const RenderData* pData );;
		
		virtual inline bool isEnabled( void ) const { return _enabled; }
		virtual inline bool isVisible( void ) const { return _visible; }
		virtual inline void setEnabled( bool enabled ) { _enabled = enabled; }
		virtual inline void setVisible( bool visible ) { _visible = visible; }
		virtual inline void toggleEnabled( void ) { _enabled = !_enabled; }
		virtual inline void toggleVisible( void ) { _visible = !_visible; }

		virtual inline Point getPos    ( void ) const { return _pos; }
		virtual inline void  setPos    ( Point pos )   { _pos = pos; }
		virtual inline void  addToPos  ( Point val ) { setPos(_pos + val); }
		virtual inline void  subFromPos( Point val ) { setPos(_pos - val); }

		virtual inline float getDepth( void ) const { return _depth; };
		virtual inline void  setDepth( float depth ) { _depth = depth; };

        inline Layer* getParentLayer( void ) { return _pParent; }
		inline Scene* getParentScene( void ) { return _pParent->getParentScene(); }

		virtual bool addComponent   ( Component* component );
		virtual bool removeComponent( Component* component );

		virtual inline bool hasComponent( Component* component ) { return _components.contains(component); }

		virtual PhysicsComponent*  addNewPhysicsComponent ( Vector2 vel = Vector2::ZERO,  
															Vector2 acc = Vector2::ZERO );

		virtual ImageComponent*    addNewImageComponent   ( Texture *pTexture,
															Color blendColor = Color::WHITE,
			                                                Origin origin = Origin::ZERO,
			                                                Vector2 scale = Vector2::ONE, 
			                                                Angle rotation = Angle::ZERO,
															Point offset = Point::ZERO );

		virtual ShapeComponent*    addNewShapeComponent   ( Color blendColor = Color::WHITE,
			                                                Origin origin = Origin::ZERO,
			                                                Vector2 scale = Vector2::ONE, 
			                                                Angle rotation = Angle::ZERO,
															Point offset = Point::ZERO );

		virtual AnimatedComponent* addNewAnimatedComponent( Animation* pAnimation,
														    Color blendColor = Color::WHITE,
			                                                Origin origin = Origin::ZERO,
			                                                Vector2 scale = Vector2::ONE, 
			                                                Angle rotation = Angle::ZERO,
															Point offset = Point::ZERO );

		virtual TextComponent*     addNewTextComponent    ( Font *pFont,
															string text,
															Color blendColor = Color::WHITE,
															Origin origin = Origin::ZERO,
															Vector2 scale = Vector2::ONE,
															Angle rotation = Angle::ZERO,
															Point offset = Point::ZERO);

		virtual bool hasComponentOfType( ComponentType type );
		virtual Component* getFirstComponentOfType( ComponentType type );

		template <typename T>
		ArrayList<T*> getComponentsOfType( ComponentType type )
		{
			ArrayList<T*> cmpList = ArrayList<T*>();

			auto end = _components.end();
			for (auto it = _components.begin(); it != end; ++it)
			{
				Component* cmp = (*it);
				if (cmp->getTypes().contains(type))
					cmpList.add((T*)cmp);
			}

			return cmpList;
		}

		virtual Component*         getFirstComponent        ( void ) { return ( _components.isEmpty() ? nullptr : _components[0] ); }
		virtual PhysicsComponent*  getFirstPhysicsComponent ( void ) { return (PhysicsComponent*) getFirstComponentOfType(PhysicsComponent::CMP_TYPE_PHYSICS); }
		virtual ImageComponent*    getFirstImageComponent   ( void ) { return (ImageComponent*)   getFirstComponentOfType(ImageComponent::CMP_TYPE_IMAGE); }
		virtual ShapeComponent*    getFirstShapeComponent   ( void ) { return (ShapeComponent*)   getFirstComponentOfType(ShapeComponent::CMP_TYPE_SHAPE); }
		virtual AnimatedComponent* getFirstAnimatedComponent( void ) { return (AnimatedComponent*)getFirstComponentOfType(AnimatedComponent::CMP_TYPE_ANIMATED); }
		virtual TextComponent*     getFirstTextComponent    ( void ) { return (TextComponent*)    getFirstComponentOfType(TextComponent::CMP_TYPE_TEXT); }

		virtual ArrayList<Component*>         getComponents        ( void ) { return _components; }
		virtual ArrayList<PhysicsComponent*>  getPhysicsComponents ( void ) { return getComponentsOfType<PhysicsComponent>(PhysicsComponent::CMP_TYPE_PHYSICS); }
		virtual ArrayList<ImageComponent*>    getImageComponents   ( void ) { return getComponentsOfType<ImageComponent>(ImageComponent::CMP_TYPE_IMAGE); }
		virtual ArrayList<ShapeComponent*>    getShapeComponents   ( void ) { return getComponentsOfType<ShapeComponent>(ShapeComponent::CMP_TYPE_SHAPE); }
		virtual ArrayList<AnimatedComponent*> getAnimatedComponents( void ) { return getComponentsOfType<AnimatedComponent>(AnimatedComponent::CMP_TYPE_ANIMATED); }
		virtual ArrayList<TextComponent*>     getTextComponents    ( void ) { return getComponentsOfType<TextComponent>(TextComponent::CMP_TYPE_TEXT); }

    }; // class Unit

    struct UnitDepthComp
        : std::binary_function<Unit*, Unit*, bool>
    {
        inline bool operator()( const Unit* lhs, const Unit* rhs ) const
        {
			return lhs->getDepth() < rhs->getDepth();
        }
    }; // struct UnitDepthComp

} // namespace Arc

#endif // __ARC_UNIT_H__
