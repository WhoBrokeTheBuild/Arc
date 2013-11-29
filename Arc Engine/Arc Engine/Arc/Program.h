#pragma once

#ifndef __ARC_PROGRAM_H__
#define __ARC_PROGRAM_H__

#include "Common.h"
#include "EventDispatcher.h"

#include "ScriptingSystem.h"
#include "NetworkSystem.h"

namespace Arc
{
	/* The control class for the entire program. Stores the scripting and
	 * network systems
	 */
    class Program :
        public EventDispatcher
    {
	private:

		static Program* _pInstance;

    protected:

		ArrayList<SystemComponent*> _systems;

    public:

		Program( void );
		virtual ~Program( void );

        virtual inline string toString( void ) const { return "Program"; }

		static Program* getInstance( void ) { return _pInstance; }

		template <class T>
		inline T* getSystemOfType( const SystemComponentType& type )
		{
			SystemComponent* pCmp;

			auto end = _systems.end();
			for (auto it = _systems.begin(); it != end; ++it)
			{
				pCmp = (*it);

				if (pCmp->hasType(type))
					return (T*)pCmp;
			}

			return nullptr;
		}

		/* Initialize the scripting system
		 */
        void initScriptingSystem( void );
		
		/* Initialize the networking system
		 */
        void initNetworkSystem( void );
		
		/* Terminate the scripting system
		 */
        void termScriptingSystem( void );
		
		/* Terminate the networking system
		 */
        void termNetworkSystem( void );

		bool isScriptingSystemActive( void ) const { return (Program::getScriptingSystem() != nullptr); }
		bool isNetworkSystemActive( void ) const { return (Program::getNetworkSystem() != nullptr); }

		/* Access the scripting system
		 * 
		 * @returns: A pointer to the scripting system
		 */
		static inline ScriptingSystem* getScriptingSystem( void )
		{
			return Program::getInstance()->getSystemOfType<ScriptingSystem>(ScriptingSystem::SYS_CMP_TYPE_SCRIPTING); 
		}
		
		/* Access the network system
		 * 
		 * @returns: A pointer to the network system
		 */
        static inline NetworkSystem* getNetworkSystem( void ) 
		{
			return Program::getInstance()->getSystemOfType<NetworkSystem>(NetworkSystem::SYS_CMP_TYPE_NETWORK); 
		}

    }; // class Program

} // namespace Arc

#endif // __ARC_PROGRAM_H__
