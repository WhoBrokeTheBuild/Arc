#pragma once

#ifndef __ARC_ICOLLIDABLE_H__
#define __ARC_ICOLLIDABLE_H__

#include "Common.h"
#include "Collider.h"
#include "RectCollider.h"
#include "CircleCollider.h"

#include "ArrayList.h"
#include "Scene.h"

namespace Arc
{
    class ICollidable
    {
    protected:

        Collider
            *_pCollider;

    public:

        bool 
            Collidable;

        ICollidable( void )
        {
            _pCollider = nullptr;
        }

        ~ICollidable( void ) { term(); }

        virtual void init( Collider* collider )
        {
            _pCollider = collider;
        }

        virtual void init( RectCollider collider )
        {
            _pCollider = New RectCollider(collider.RectMask);
        }

        virtual void init( CircleCollider collider )
        {
            _pCollider = New CircleCollider(collider.CircleMask);
        }

        virtual void term( void )
        {
            delete _pCollider;
        }

        virtual Collider* getCollider( void )
        {
            return _pCollider;
        }

        virtual bool collideUnit( Unit* unit, Point pos )
        {
            if (getCollider() == nullptr)
                return false;

            ICollidable* unitColl = dynamic_cast<ICollidable*>(unit);

            if (unitColl == nullptr)
                return false;

            if (unitColl == this)
                return false;

            return getCollider()->check(pos, unitColl->getCollider(), unit->Pos);
        }

        virtual bool collideList( ArrayList<Unit*> list, Point pos )
        {
            for (unsigned int i = 0; i < list.size(); ++i)
            {
                if (collideUnit(list[i], pos))
                    return true;
            }

            return false;
        }

        virtual Unit* collideListFirst( ArrayList<Unit*> list, Point pos )
        {
            for (unsigned int i = 0; i < list.size(); ++i)
            {
                if (collideUnit(list[i], pos))
                    return list[i];
            }

            return false;
        }

        virtual ArrayList<Unit*> collideListAll( ArrayList<Unit*> list, Point pos )
        {
            ArrayList<Unit*> returnList = ArrayList<Unit*>();

            for (unsigned int i = 0; i < list.size(); ++i)
            {
                if (collideUnit(list[i], pos))
                    returnList.add(list[i]);
            }

            return returnList;
        }

        virtual bool collideTag( string tag, Scene* scene, Point pos )
        {
            return collideList(scene->getUnitsByTag(tag), pos);
        }

        // collideTag - pass in scene
        // collideTags - pass in scene
// collideUnit
// collideList
// collideListFirst
// collideListAll
        // collideRect
        // collideCircle
        // collidePoint

        virtual void collided( void ) { }

    }; // class ICollidable

} // namespace Arc

#endif // __ARC_ICOLLIDABLE_H__
