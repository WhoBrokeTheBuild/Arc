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
	class UnitComponent;

    class Unit :
        public EventDispatcher
    {

        friend class Layer;

    protected:

        Layer* _pParent;

        Point _pos;

        float _depth;

        bool _enabled;
        bool _visible;

		ArrayList<UnitComponent*> _components;

        LinkedList<UnitComponent*> _componentsToAdd;
		LinkedList<UnitComponent*> _componentsToRemove;

        void setParentLayer( Layer* layer ) { _pParent = layer; }

		virtual void updateComponents( const FrameTime* pFrameTime );
		virtual void renderComponents( const RenderTarget* pTarget );

		bool hasComponentOfType( const UnitComponentType& type );

		template <class T>
		inline T* getFirstComponentOfType( const UnitComponentType& type )
		{
			UnitComponent* cmp;

			auto cmpEnd = _components.end();
			for (auto it = _components.begin(); it != cmpEnd; ++it)
			{
				cmp = (*it);
				if (cmp->hasType(type))
					return (T*)cmp;
			}

			auto cmpToAddEnd = _componentsToAdd.end();
			for (auto it = _componentsToAdd.begin(); it != cmpToAddEnd; ++it)
			{
				cmp = (*it);
				if (cmp->hasType(type))
					return (T*)cmp;
			}

			return nullptr;
		}

		template <class T>
		ArrayList<T*> inline getComponentsOfType( const UnitComponentType& type )
		{
			ArrayList<T*> cmpList = ArrayList<T*>();
			UnitComponent* pCmp;

			auto end = _components.end();
			for (auto it = _components.begin(); it != end; ++it)
			{
				pCmp = (*it);
				if (pCmp->hasType(type))
					cmpList.add((T*)pCmp);
			}

			return cmpList;
		}

	public:

#pragma region Event Types

		static const EventType EVENT_ENABLED_CHANGED;

		static const EventType EVENT_VISIBLE_CHANGED;

		static const EventType EVENT_DEPTH_CHANGED;

		static const EventType EVENT_POSITION_CHANGED;

#pragma endregion

        Unit( Point pos, float depth = 0.0f )
			: _pParent(nullptr),
			  _pos(pos),
			  _depth(depth),
			  _enabled(true),
			  _visible(true)
		{ }

        virtual ~Unit( void );

        virtual void update( const FrameTime* pFrameTime );;

		virtual void render( const RenderTarget* pTarget );;
		
#pragma region Enabled

		virtual inline bool isEnabled( void ) const { return _enabled; }

		virtual inline void setEnabled( bool enabled ) { _enabled = enabled; dispatchEvent(Event(EVENT_ENABLED_CHANGED)); }

		virtual inline void toggleEnabled( void ) { _enabled = !_enabled; dispatchEvent(Event(EVENT_ENABLED_CHANGED)); }

#pragma endregion

#pragma region Visible

		virtual inline bool isVisible( void ) const { return _visible; }

		virtual inline void setVisible( bool visible ) { _visible = visible; dispatchEvent(Event(EVENT_VISIBLE_CHANGED)); }

		virtual inline void toggleVisible( void ) { _visible = !_visible; dispatchEvent(Event(EVENT_VISIBLE_CHANGED)); }
		
#pragma endregion

#pragma region Position 

		virtual inline Point getPos( void ) const { return _pos; }

		virtual inline void setPos( Point pos ) { _pos = pos; dispatchEvent(Event(EVENT_POSITION_CHANGED)); }

#pragma endregion

#pragma region Depth

		virtual inline float getDepth( void ) const { return _depth; };

		virtual inline void setDepth( float depth ) { _depth = depth; dispatchEvent(Event(EVENT_DEPTH_CHANGED)); };

#pragma endregion

        inline Layer* getParentLayer( void ) { return _pParent; }

		inline Scene* getParentScene( void ) { return _pParent->getParentScene(); }


		virtual bool addComponent( UnitComponent* component );

		virtual bool removeComponent( UnitComponent* component );

		virtual inline bool hasComponent( UnitComponent* component ) { return _components.contains(component); }

#pragma region Add New Components

		virtual PhysicsComponent* addNewPhysicsComponent( Vector2 vel = Vector2::ZERO,  
														   Vector2 acc = Vector2::ZERO );

		virtual ImageComponent* addNewImageComponent( Texture *pTexture,
														 Color blendColor = Color::WHITE,
			                                             Origin origin = Origin::ZERO,
			                                             Vector2 scale = Vector2::ONE, 
			                                             Angle rotation = Angle::ZERO,
														 Point offset = Point::ZERO );

		virtual ImageComponent* addNewImageComponent( Sprite *pSprite,
														 Color blendColor = Color::WHITE,
			                                             Origin origin = Origin::ZERO,
			                                             Vector2 scale = Vector2::ONE, 
			                                             Angle rotation = Angle::ZERO,
														 Point offset = Point::ZERO );

		virtual ShapeComponent* addNewShapeComponent( bool filled = false,
														 Color blendColor = Color::WHITE,
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

		virtual TextComponent* addNewTextComponent( Font *pFont,
													    string text,
													    Color blendColor = Color::WHITE,
													    Origin origin = Origin::ZERO,
													    Vector2 scale = Vector2::ONE,
													    Angle rotation = Angle::ZERO,
													    Point offset = Point::ZERO);

#pragma endregion

#pragma region Get First Component Functions

		virtual inline UnitComponent* getFirstComponent( void ) { return ( _components.isEmpty() ? nullptr : _components[0] ); }

		virtual inline PhysicsComponent* getFirstPhysicsComponent( void )
		{
			return getFirstComponentOfType<PhysicsComponent>(PhysicsComponent::UNIT_CMP_TYPE_PHYSICS); 
		}

		virtual inline ImageComponent* getFirstImageComponent( void ) 
		{ 
			return getFirstComponentOfType<ImageComponent>(ImageComponent::UNIT_CMP_TYPE_IMAGE);
		}

		virtual inline ShapeComponent* getFirstShapeComponent( void ) 
		{
			return getFirstComponentOfType<ShapeComponent>(ShapeComponent::UNIT_CMP_TYPE_SHAPE);
		}

		virtual inline AnimatedComponent* getFirstAnimatedComponent( void )
		{ 
			return getFirstComponentOfType<AnimatedComponent>(AnimatedComponent::UNIT_CMP_TYPE_ANIMATED); 
		}

		virtual inline TextComponent* getFirstTextComponent( void )
		{
			return getFirstComponentOfType<TextComponent>(TextComponent::UNIT_CMP_TYPE_TEXT);
		}

#pragma endregion

#pragma region Get All Component Functions

		virtual inline ArrayList<UnitComponent*> getComponents( void ) { return _components; }

		virtual inline ArrayList<PhysicsComponent*> getPhysicsComponents ( void )
		{ 
			return getComponentsOfType<PhysicsComponent>(PhysicsComponent::UNIT_CMP_TYPE_PHYSICS);
		}

		virtual inline ArrayList<ImageComponent*> getImageComponents( void ) 
		{ 
			return getComponentsOfType<ImageComponent>(ImageComponent::UNIT_CMP_TYPE_IMAGE);
		}

		virtual inline ArrayList<ShapeComponent*> getShapeComponents( void )
		{ 
			return getComponentsOfType<ShapeComponent>(ShapeComponent::UNIT_CMP_TYPE_SHAPE);
		}

		virtual inline ArrayList<AnimatedComponent*> getAnimatedComponents( void )
		{
			return getComponentsOfType<AnimatedComponent>(AnimatedComponent::UNIT_CMP_TYPE_ANIMATED);
		}

		virtual inline ArrayList<TextComponent*> getTextComponents( void )
		{ 
			return getComponentsOfType<TextComponent>(TextComponent::UNIT_CMP_TYPE_TEXT);
		}

#pragma endregion

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
