/*
 * BasicWeapon.cpp
 *
 *  Created on: May 6, 2016
 *      Author: gonzalo
 */

#include "BasicWeapon.h"

BasicWeapon::BasicWeapon(): Weapon()
{
	m_shootCooldown = 150;
	m_waitTime = 0;
	m_canShoot = true;
	m_bulletSpeed = 10;
}

BasicWeapon::~BasicWeapon()
{
}

bool BasicWeapon::shoot(const Vector2D& bulletPosition)
{
	bool didShoot = false;

	if (m_canShoot)
	{
		Bullet* bullet = new Bullet();
		bullet->setPosition(Vector2D(bulletPosition.m_x, bulletPosition.m_y));
		bullet->setDirection(Vector2D(0,DIRECTION_UP));
		bullet->setSpeed(Vector2D(m_bulletSpeed, m_bulletSpeed));

		BulletsHandler::Instance()->addBullet(bullet);
		m_waitTime = 0;
		m_canShoot = false;
		didShoot = true;
	}

	return didShoot;

}

