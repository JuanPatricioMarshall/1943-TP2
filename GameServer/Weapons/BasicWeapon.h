/*
 * BasicWapon.h
 *
 *  Created on: May 6, 2016
 *      Author: gonzalo
 */

#ifndef WEAPONS_BASICWEAPON_H_
#define WEAPONS_BASICWEAPON_H_

#include "Bullet.h"
#include "Weapon.h"
#include "../Vector2D.h"
#include "../Singletons/GameTimeHelper.h"

class BasicWeapon : public Weapon
{
public:
	BasicWeapon();
	virtual ~BasicWeapon();

	virtual bool shoot(const Vector2D& bulletPosition);

};

#endif /* WEAPONS_BASICWEAPON_H_ */
