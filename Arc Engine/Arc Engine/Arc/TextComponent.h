#pragma once

#ifndef __ARC_TEXT_COMPONENT_H__
#define __ARC_TEXT_COMPONENT_H__

#include "Common.h"
#include "DrawableComponent.h"

#include "RenderedText.h"

namespace Arc
{
	class TextComponent :
		public DrawableComponent
	{
	protected:

		RenderedText
			*_pRenderedText;

	public:
		
		TextComponent( Unit *pUnit,
			           Font *pFont, 
			           string text = "",
			           Point offset = Point::ZERO,
			           Point origin = Point::ZERO,
			           Vector2 scale = Vector2::ONE,
			           Angle rotation = Angle::ZERO,
			           Color blendColor = Color::WHITE );
		TextComponent( Unit *pUnit,
					   Font *pFont,
					   string text = "", 
					   Point offset = Point::ZERO,
					   OriginLocation originLocation = OriginLocation::ORIGIN_LOCATION_TOP_LEFT,
					   Vector2 scale = Vector2::ONE,
					   Angle rotation = Angle::ZERO,
					   Color blendColor = Color::WHITE );
		virtual ~TextComponent( void );

		virtual inline string toString( void ) const { return "Drawable Component"; }

		virtual inline string getText( void ) const { return _pRenderedText->getText(); }
		virtual inline void   setText( string text ) { _pRenderedText->setText(text); }
		
		virtual inline Font* getFont( void ) const { return _pRenderedText->getFont(); }
		virtual inline void  setFont( Font* pFont ) { _pRenderedText->setFont(pFont); }

		virtual void render( const RenderData* data );

		virtual inline Vector2 getSize( void ) const { return (_pRenderedText == nullptr ? Vector2::ZERO : _pRenderedText->getSize()); }

	}; // class TextComponent

} // namespace Arc

#endif // __ARC_TEXT_COMPONENT_H__