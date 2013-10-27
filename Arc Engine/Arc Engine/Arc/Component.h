#pragma once

#ifndef __ARC_COMPONENT_H__
#define __ARC_COMPONENT_H__

#include "Common.h"
#include "EventDispatcher.h"

typedef string ComponentType;

namespace Arc
{
	class Unit;

	class Component :
        public EventDispatcher
	{
	protected:

		ArrayList<ComponentType>
			_types;

		Unit*
			_pUnit;

	public:

		bool
			Enabled,
			Visible;

		static const EventType
			EVENT_UNIT_CHANGED;

		static const ComponentType
			CMP_TYPE_BASE;

		Component( Unit* pUnit );
		virtual ~Component();

		virtual inline string toString( void ) const { return "Component"; }

        virtual void update( const FrameData* data )  { };
		virtual void render( const RenderData* data ) { };

		bool removeSelf( void );

		inline Unit* getUnit( void ) const { return _pUnit; }
		inline void setUnit( Unit* unit ) { _pUnit = unit; }

		virtual inline ArrayList<ComponentType> getTypes( void ) { return _types; }

	}; // class Component

} // namespace Arc

#endif // __ARC_COMPONENT_H__
