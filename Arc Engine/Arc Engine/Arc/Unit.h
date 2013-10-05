#pragma once

#ifndef __ARC_UNIT_H__
#define __ARC_UNIT_H__

#include "Common.h"
#include "EventDispatcher.h"

#include "OriginLocation.h"
#include "Layer.h"
#include "Scene.h"

namespace Arc
{
	class Component;
	class PhysicsComponent;
	class ImageComponent;
	class ShapeComponent;
	class AnimatedComponent;
	class TextComponent;

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

        virtual void update( const Event& event );
        virtual void render( const Event& event );

        virtual void update( const FrameData* data )  { };
        virtual void render( const RenderData* data ) { };
		
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

		virtual PhysicsComponent*  addNewPhysicsComponent ( Vector2 vel = Vector2::ZERO, Vector2 acc = Vector2::ZERO );

		virtual ImageComponent*    addNewImageComponent   ( Texture *pTexture,
															Point offset = Point::ZERO,
															Point origin = Point::ZERO, 
															Vector2 scale = Vector2::ZERO,
															Angle rotation = Angle::ZERO,
															Color blendColor = Color::WHITE );

		virtual ImageComponent*    addNewImageComponent   ( Texture *pTexture, 
															Point offset = Point::ZERO,
															OriginLocation originLocation = OriginLocation::ORIGIN_LOCATION_TOP_LEFT, 
															Vector2 scale = Vector2::ZERO,
															Angle rotation = Angle::ZERO,
															Color blendColor = Color::WHITE );

		virtual ShapeComponent*    addNewShapeComponent   ( Point offset = Point::ZERO,
															Point origin = Point::ZERO,
															Vector2 scale = Vector2::ZERO, 
															Angle rotation = Angle::ZERO,
															Color blendColor = Color::WHITE );

		virtual ShapeComponent*    addNewShapeComponent   ( Point offset = Point::ZERO,
															OriginLocation originLocation = OriginLocation::ORIGIN_LOCATION_TOP_LEFT, 
															Vector2 scale = Vector2::ZERO,
															Angle rotation = Angle::ZERO, 
															Color blendColor = Color::WHITE );

		virtual AnimatedComponent* addNewAnimatedComponent( void );

		virtual TextComponent*     addNewTextComponent    ( Font *pFont,
															string text, 
															Point offset = Point::ZERO,
															Point origin = Point::ZERO,
															Vector2 scale = Vector2::ZERO, 
															Angle rotation = Angle::ZERO, 
															Color blendColor = Color::WHITE );

		virtual TextComponent*     addNewTextComponent    ( Font *pFont,
															string text,
															Point offset = Point::ZERO,
															OriginLocation originLocation = OriginLocation::ORIGIN_LOCATION_TOP_LEFT,
															Vector2 scale = Vector2::ZERO, 
															Angle rotation = Angle::ZERO,
															Color blendColor = Color::WHITE );

		virtual Component*         getFirstComponent        ( void ) { return ( _components.empty() ? nullptr : _components[0] ); }
		virtual PhysicsComponent*  getFirstPhysicsComponent ( void );
		virtual ImageComponent*    getFirstImageComponent   ( void );
		virtual ShapeComponent*    getFirstShapeComponent   ( void );
		virtual AnimatedComponent* getFirstAnimatedComponent( void );
		virtual TextComponent*     getFirstTextComponent    ( void );

		template <class T>
		ArrayList<T*> getComponentListAs( void )
		{
			ArrayList<T*> list = ArrayList<T*>();

			for (auto it = _components.begin(); it != _components.end(); ++it)
			{
				Component* cmp = (*it);
				T* newCmp = dynamic_cast<T*>(cmp);
				if (newCmp != nullptr)
					list.add(newCmp);
			}

			return list;
		}

		template <class T>
		T* getFirstComponenAs( void )
		{
			for (auto it = _components.begin(); it != _components.end(); ++it)
			{
				Component* cmp = (*it);
				T* newCmp = dynamic_cast<T*>(cmp);
				if (newCmp != nullptr)
					return newCmp;
			}
			return nullptr;
		}

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
