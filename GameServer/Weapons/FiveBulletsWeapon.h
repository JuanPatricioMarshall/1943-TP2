/*
 * FiveBulletsWeapon.h
 *
 *  Created on: May 9, 2016
 *      Author: gonzalo
 */

#ifndef WEAPONS_FIVEBULLETSWEAPON_H_
#define WEAPONS_FIVEBULLETSWEAPON_H_

#include "Bullet.h"
#include "BlueBullet.h"
#include "Weapon.h"
#include "../Vector2D.h"

class FiveBulletsWeapon : public Weapon
{
public:
	FiveBulletsWeapon();
	virtual ~FiveBulletsWeapon();

	virtual bool shoot(const Vector2D& bulletPosition);

};



#endif /* WEAPONS_FIVEBULLETSWEAPON_H_ */
