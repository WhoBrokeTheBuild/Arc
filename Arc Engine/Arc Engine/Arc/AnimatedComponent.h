#pragma once

#ifndef __ARC_ANIMATED_COMPONENT_H__
#define __ARC_ANIMATED_COMPONENT_H__

#include "Common.h"
#include "DrawableComponent.h"

#include "Animation.h"

namespace Arc
{
	class AnimatedComponent :
		public DrawableComponent
	{
	protected:

		Animation
			*_pAnimation;

		int 
			_frame;

		double
			_timeout;

	public:

		static const ComponentType CMP_TYPE_ANIMATED;

		static const EventType EVENT_ANIMATION_COMPLETE;

		AnimatedComponent( Unit* pUnit, 
						   Animation *pAnimation,
			               Color blendColor = Color::WHITE,
			               Origin origin = Origin::ZERO,
			               Vector2 scale = Vector2::ONE, 
			               Angle rotation = Angle::ZERO,
			               Point offset = Point::ZERO )
			: DrawableComponent(pUnit, blendColor, origin, scale, rotation, offset),
			  _pAnimation(pAnimation),
			  _frame(),
			  _timeout()
		{
			addType(CMP_TYPE_ANIMATED);

			if (_pAnimation != nullptr)
				_timeout = _pAnimation->getSpeed();
		}

		virtual inline ~AnimatedComponent( void ) { }

		virtual inline string toString( void ) const { return "Animated Component"; }

		virtual inline Size getSize( void ) const { return (_pAnimation == nullptr || ! _pAnimation->hasFrame(_frame) ? Size::ZERO : _pAnimation->getFrameSize(_frame)); }

		virtual void update( const FrameData* data );
		virtual void render( const RenderData* data );

	}; // class AnimatedComponent

} // namespace Arc

#endif // __ARC_ANIMATED_COMPONENT_H__
