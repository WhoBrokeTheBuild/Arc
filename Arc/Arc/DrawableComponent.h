#pragma once

#ifndef __ARC_DRAWABLE_COMPONENT_H__
#define __ARC_DRAWABLE_COMPONENT_H__

#include "Common.h"
#include "UnitComponent.h"

#include "OriginLocation.h"
#include "Origin.h"

namespace Arc
{
	class DrawableComponent :
		public UnitComponent
	{
	protected:

		Point _offset;

		Origin _origin;

		Vector2 _scale;

		Angle _rotation;

		Color _blendColor;

		virtual inline void setOriginSize( Size size ) { _origin.setSize(size); }

	public:

		static const UnitComponentType UNIT_CMP_TYPE_DRAWABLE;

#pragma region Event Types

		static const EventType EVENT_OFFSET_CHANGED;
		static const EventType EVENT_SCALE_CHANGED;
		static const EventType EVENT_ROTATION_CHANGED;
		static const EventType EVENT_BLEND_COLOR_CHANGED;
		static const EventType EVENT_ORIGIN_CHANGED;

#pragma endregion

		inline DrawableComponent( Unit* pUnit,
			               Color blendColor = Color::WHITE,
			               Origin origin = Origin::ZERO,
			               Vector2 scale = Vector2::ONE, 
			               Angle rotation = Angle::ZERO,
			               Point offset = Point::ZERO )
			: UnitComponent(pUnit),
			  _blendColor(blendColor),
			  _origin(origin),
			  _scale(scale),
			  _rotation(rotation),
			  _offset(offset)
		{
			addType(UNIT_CMP_TYPE_DRAWABLE);
		}

		virtual inline ~DrawableComponent( void ) { }

		virtual inline string toString( void ) const { return "Drawable Component"; }

		virtual inline Point getOffset( void ) const { return _offset; }

		virtual inline Vector2 getScale( void ) const { return _scale; }

		virtual inline Angle getRotation( void ) const { return _rotation; }

		virtual inline Color getBlendColor( void ) const { return _blendColor; }

		virtual inline Origin getOrigin( void ) const { return _origin; }
		
		virtual inline void setOffset( Point offset ) { _offset = offset; dispatchEvent(Event(EVENT_OFFSET_CHANGED)); }

		virtual inline void setScale( Vector2 scale ) { _scale = scale; dispatchEvent(Event(EVENT_SCALE_CHANGED)); }

		virtual inline void setRotation( Angle rotation ) { _rotation = rotation; dispatchEvent(Event(EVENT_ROTATION_CHANGED)); }

		virtual inline void setBlendColor( Color blendColor ) { _blendColor = blendColor; dispatchEvent(Event(EVENT_BLEND_COLOR_CHANGED)); }

		virtual inline void setOrigin( Origin origin ) 
		{
			_origin = origin;
			setOriginSize(getSize()); 
			dispatchEvent(Event(EVENT_ORIGIN_CHANGED));
		}

		virtual Vector2 getSize( void ) const = 0;


	}; // class DrawableComponent

} // namespace Arc

#endif // __ARC_DRAWABLE_COMPONENT_H__