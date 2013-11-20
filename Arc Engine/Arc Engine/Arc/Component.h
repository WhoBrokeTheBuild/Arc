#pragma once

#ifndef __ARC_COMPONENT_H__
#define __ARC_COMPONENT_H__

#include "Common.h"
#include "EventDispatcher.h"

namespace Arc
{
	class Unit;

	typedef string ComponentType;

	class Component :
        public EventDispatcher
	{
	protected:

		ArrayList<ComponentType> _types;

		Unit* _pUnit;

	public:

		bool Enabled;
		bool Visible;

		static const ComponentType CMP_TYPE_BASE;

		inline Component( Unit* pUnit )
			: _pUnit(pUnit)
		{
			addType(CMP_TYPE_BASE);
		}

		virtual inline ~Component() 
		{ }

		virtual inline string toString( void ) const { return "Component"; }

        virtual void update( const FrameData* data ) { };
		virtual void render( const RenderData* data ) { };

		bool removeSelf( void );

		inline Unit* getUnit( void ) const { return _pUnit; }
		inline void setUnit( Unit* unit ) { _pUnit = unit; }

		virtual inline ArrayList<ComponentType> getTypes( void ) { return _types; }
		virtual inline void addType( ComponentType type ) { if ( ! _types.contains(type)) _types.add(type); }

	}; // class Component

} // namespace Arc

#endif // __ARC_COMPONENT_H__
