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
    struct CollisionData
        : public GameObject
    {
    public:

        bool
            Collided;

        Unit
            *pOther;

        Point
            Pos;

        float
            Angle;

        CollisionData( void )
            : Collided(false),
              pOther(nullptr),
              Pos(),
              Angle()
        {
        }

        CollisionData( Unit* other, Point pos, float angle )
        {
            Collided = true;
            pOther   = other;
            Pos      = pos;
            Angle    = angle;
        }

        virtual string toString( void ) const { return "Collision Data"; }

        Direction getSide( void ) { return angleRadToDirFour(Angle); }
        Direction getSideEightWay( void ) { return angleRadToDirEight(Angle); }

    };

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
            delete _pCollider;
            _pCollider = collider;
        }

        virtual void init( RectCollider collider )
        {
            delete _pCollider;
            _pCollider = New RectCollider(collider.RectMask);
        }

        virtual void init( CircleCollider collider )
        {
            delete _pCollider;
            _pCollider = New CircleCollider(collider.CircleMask);
        }

        virtual void term( void )
        {
            delete _pCollider;
        }

        virtual Collider* getCollider( void ) { return _pCollider; }

        virtual bool checkUnit( Unit* other, Point pos, Point origin = Point::ZERO, Vector2 offset = Vector2::ZERO )
        {
            if (getCollider() == nullptr)
                return false;

            Point otherPos;

            pos = (pos - origin) + offset;
            otherPos = other->Pos - other->getOrigin();

            ICollidable* unitColl = dynamic_cast<ICollidable*>(other);

            if (unitColl == nullptr)
                return false;

            if (unitColl == this)
                return false;

            return getCollider()->check(pos, unitColl->getCollider(), otherPos);
        }

        virtual bool checkList( ArrayList<Unit*> otherList, Point pos, Point origin = Point::ZERO, Vector2 offset = Vector2::ZERO )
        {
            for (unsigned int i = 0; i < otherList.size(); ++i)
            {
                if (checkUnit(otherList[i], pos, origin, offset))
                    return true;
            }

            return false;
        }

        virtual bool checkTag( string tag, Scene* scene, Point pos, Point origin = Point::ZERO, Vector2 offset = Vector2::ZERO )
        {
            return checkList(scene->getUnitsByTag(tag), pos, origin, offset);
        }

        virtual bool checkTagList( ArrayList<string> tagList, Scene* scene, Point pos, Point origin, Vector2 offset = Vector2::ZERO )
        {
            for (unsigned int i = 0; i < tagList.size(); ++i)
            {
                if (checkList(scene->getUnitsByTag(tagList[i]), pos, origin, offset))
                    return true;
            }

            return false;
        }
        
        //virtual bool checkPoint( Point point, Point pos, Point origin = Point::ZERO, Vector2 offset = Vector2::ZERO );
        //virtual bool checkRect( Rect rect, Point pos, Point origin = Point::ZERO, Vector2 offset = Vector2::ZERO );
        //virtual bool checkCircle( Circle circle, Point pos, Point origin = Point::ZERO, Vector2 offset = Vector2::ZERO );

        virtual CollisionData collideUnit( Unit* other, Point pos, Point origin = Point::ZERO, Vector2 offset = Vector2::ZERO )
        {
            CollisionData data;
            data.pOther = other;
            data.Collided = false;

            Point otherPos;
            Point centerPos;

            pos = (pos - origin) + offset;
            otherPos = other->Pos - other->getOrigin();

            centerPos = pos + getCollider()->center();

            if (getCollider() == nullptr)
                return data;

            ICollidable* unitColl = dynamic_cast<ICollidable*>(other);

            if (unitColl == nullptr || unitColl == this)
                return data;

            data.Collided = getCollider()->check(pos, unitColl->getCollider(), otherPos);

            if (data.Collided)
            {
                data.Pos = getCollider()->getCollisionPoint(pos, unitColl->getCollider(), otherPos);
                data.Angle = centerPos.angleToRad(data.Pos);
            }

            return data;
        }

        virtual ArrayList<CollisionData> collideList( ArrayList<Unit*> otherList, Point pos, Point origin = Point::ZERO, Vector2 offset = Vector2::ZERO )
        {
            ArrayList<CollisionData> dataList;

            CollisionData data;
            for (unsigned int i = 0; i < otherList.size(); ++i)
            {
                data = collideUnit(otherList[i], pos, origin, offset);
                if (data.Collided)
                    dataList.add(data);
            }

            return dataList;
        }

        virtual CollisionData collideListFirst( ArrayList<Unit*> otherList, Point pos, Point origin = Point::ZERO, Vector2 offset = Vector2::ZERO )
        {
            CollisionData data;
            for (unsigned int i = 0; i < otherList.size(); ++i)
            {
                data = collideUnit(otherList[i], pos, origin, offset);
                if (data.Collided)
                    return data;
            }
            data = CollisionData();
            data.Collided = false;
            return data;
        }

        virtual ArrayList<CollisionData> collideTag( string tag, Scene* scene, Point pos, Point origin = Point::ZERO, Vector2 offset = Vector2::ZERO )
        {
            return collideList(scene->getUnitsByTag(tag), pos, origin, offset);
        }

        virtual ArrayList<CollisionData> collideTagList( ArrayList<string> tagList, Scene* scene, Point pos, Point origin = Point::ZERO, Vector2 offset = Vector2::ZERO )
        {
            ArrayList<CollisionData> dataList;

            for (unsigned int i = 0; i < tagList.size(); ++i)
                dataList.merge(collideTag(tagList[i], scene, pos, origin, offset));

            return dataList;
        }

        virtual CollisionData collideTagFirst( string tag, Scene* scene, Point pos, Point origin = Point::ZERO, Vector2 offset = Vector2::ZERO )
        {
            return collideListFirst(scene->getUnitsByTag(tag), pos, origin, offset);
        }

        virtual CollisionData collideTagListFirst( ArrayList<string> tagList, Scene* scene, Point pos, Point origin = Point::ZERO, Vector2 offset = Vector2::ZERO )
        {
            CollisionData data;
            for (unsigned int i = 0; i < tagList.size(); ++i)
            {
                data = collideTagFirst(tagList[i], scene, pos, origin, offset);
                if (data.Collided)
                    return data;
            }

            return data;
        }

        //virtual CollisionData collidePoint( Point point, Point pos, Point origin = Point::ZERO, Vector2 offset = Vector2::ZERO );
        //virtual CollisionData collideRect( Rect rect, Point pos, Point origin = Point::ZERO, Vector2 offset = Vector2::ZERO );
        //virtual CollisionData collideCircle( Circle circle, Point pos, Point origin = Point::ZERO, Vector2 offset = Vector2::ZERO );


    }; // class ICollidable

} // namespace Arc

#endif // __ARC_ICOLLIDABLE_H__
