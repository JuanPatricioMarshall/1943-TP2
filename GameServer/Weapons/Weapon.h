/*
 * Weapon.h
 *
 *  Created on: May 6, 2016
 *      Author: gonzalo
 */

#ifndef WEAPONS_WEAPON_H_
#define WEAPONS_WEAPON_H_

#include "Bullet.h"
#include "../Singletons/GameTimeHelper.h"
#include "../Vector2D.h"
#include <vector>

//Abstacta
class Weapon
{
public:
    virtual ~Weapon() {}

    //devuelve true si se realizo el disparo.
	virtual bool shoot(const Vector2D& bulletPosition) = 0;

	virtual void update()
	{
		if (!m_canShoot)
		{
			//actualiza el timer solo si canShoot es falso, para evitar entrar innecesariamente
			m_waitTime += GameTimeHelper::Instance()->deltaTime();
			//printf("waitTime del arma: %d \n", GameTimeHelper::Instance()->deltaTime());
			if (m_waitTime >= m_shootCooldown)
				m_canShoot = true;
		}
	}

    void setBulletSpeed(int speed) { m_bulletSpeed = speed; }
    void setShootingCooldown(int cooldown) { m_shootCooldown = cooldown; }

protected:

	Weapon(): m_shootCooldown(0.5f),
			  m_waitTime(0),
			  m_canShoot(true)
	{}

	//Cooldown de disparo en segundos
	int m_shootCooldown;
	int m_waitTime;
	bool m_canShoot;

	//Por Obligacion
	int m_bulletSpeed;

};

#endif /* WEAPONS_WEAPON_H_ */
