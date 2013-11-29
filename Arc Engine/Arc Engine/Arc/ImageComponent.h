#pragma once

#ifndef __ARC_IMAGE_COMPONENT_H__
#define __ARC_IMAGE_COMPONENT_H__

#include "Common.h"
#include "DrawableComponent.h"

#include "Texture.h"
#include "Sprite.h"

namespace Arc
{
	class ImageComponent :
		public DrawableComponent
	{
	protected:

		Texture* _pTexture;

		Rect _sourceRect;

	public:

		static const UnitComponentType UNIT_CMP_TYPE_IMAGE;

#pragma region Event Types

		static const EventType EVENT_TEXTURE_CHANGED;

#pragma endregion

		inline ImageComponent( Unit* pUnit,
						       Texture* pTexture,
			                   Color blendColor = Color::WHITE,
			                   Origin origin = Origin::ZERO,
			                   Vector2 scale = Vector2::ONE, 
			                   Angle rotation = Angle::ZERO,
			                   Point offset = Point::ZERO )
			: DrawableComponent(pUnit, blendColor, origin, scale, rotation, offset),
			  _pTexture(pTexture),
			  _sourceRect()
		{
			_sourceRect = Rect(Point::ZERO, _pTexture->getSize());
			addType(UNIT_CMP_TYPE_IMAGE);
		}
		
		inline ImageComponent( Unit* pUnit,
						       Sprite* pSprite,
			                   Color blendColor = Color::WHITE,
			                   Origin origin = Origin::ZERO,
			                   Vector2 scale = Vector2::ONE, 
			                   Angle rotation = Angle::ZERO,
			                   Point offset = Point::ZERO )
			: DrawableComponent(pUnit, blendColor, origin, scale, rotation, offset),
			_pTexture(nullptr),
			_sourceRect()
		{
			_pTexture = pSprite->getTexture();
			_sourceRect = pSprite->getSourceRect();
			addType(UNIT_CMP_TYPE_IMAGE);
		}

		virtual inline ~ImageComponent( void ) { }

		virtual inline string toString( void ) const { return "Image Component"; }

		virtual void render( const RenderData* data );

		virtual inline Texture* getTexture( void ) const { return _pTexture; }

		virtual inline void setTexture( Texture* pTexture )
		{ 
			_pTexture = pTexture;
			setOriginSize(getSize());
			dispatchEvent(Event(EVENT_TEXTURE_CHANGED));
		}

		virtual inline Vector2 getSize( void ) const { return (_pTexture == nullptr ? Size::ZERO : _pTexture->getSize()); }

	}; // class ImageComponent

} // namespace Arc

#endif // __ARC_IMAGE_COMPONENT_H__
