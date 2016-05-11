/*
 * Bullet.h
 *
 *  Created on: May 6, 2016
 *      Author: gonzalo
 */

#ifndef WEAPONS_BULLET_H_
#define WEAPONS_BULLET_H_

#include "../MoveableObject.h"
#include "../Game.h"
#include "../Singletons/GameTimeHelper.h"
#include <iostream>

class Bullet : public MoveableObject
{
public:
	Bullet();
    virtual ~Bullet();

    virtual void update();
    virtual void clean();

    bool isDead();

    void sendDrawMessage(bool isAlive);

protected:
    bool m_dead;
    //tiempo de vida en ms para autodestruirse
    int m_dyingTime;

};




#endif /* WEAPONS_BULLET_H_ */
