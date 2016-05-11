/*
 * FiveBulletsWeapon.cpp
 *
 *  Created on: May 9, 2016
 *      Author: gonzalo
 */

#include "FiveBulletsWeapon.h"

FiveBulletsWeapon::FiveBulletsWeapon(): Weapon()
{
	m_shootCooldown = 150;
	m_waitTime = 0;
	m_canShoot = true;
}

FiveBulletsWeapon::~FiveBulletsWeapon()
{
}

bool FiveBulletsWeapon::shoot(const Vector2D& bulletPosition)
{
	bool didShoot = false;

	if (m_canShoot)
	{
		Bullet* bullet = new BlueBullet();
		bullet->setPosition(Vector2D(bulletPosition.m_x, bulletPosition.m_y));
		bullet->setDirection(Vector2D(0,DIRECTION_UP));

		BulletsHandler::Instance()->addBullet(bullet);

		bullet = new BlueBullet();
				bullet->setPosition(Vector2D(bulletPosition.m_x, bulletPosition.m_y));
				bullet->setDirection(Vector2D(-0.213,DIRECTION_UP));

				BulletsHandler::Instance()->addBullet(bullet);

		bullet = new BlueBullet();
				bullet->setPosition(Vector2D(bulletPosition.m_x, bulletPosition.m_y));
				bullet->setDirection(Vector2D(0.213,DIRECTION_UP));
				BulletsHandler::Instance()->addBullet(bullet);

		bullet = new BlueBullet();
				bullet->setPosition(Vector2D(bulletPosition.m_x, bulletPosition.m_y));
				bullet->setDirection(Vector2D(-0.44,DIRECTION_UP));

				BulletsHandler::Instance()->addBullet(bullet);

		bullet = new BlueBullet();
				bullet->setPosition(Vector2D(bulletPosition.m_x, bulletPosition.m_y));
				bullet->setDirection(Vector2D(0.44,DIRECTION_UP));
				BulletsHandler::Instance()->addBullet(bullet);

		m_waitTime = 0;
		m_canShoot = false;
		didShoot = true;
	}

	return didShoot;

}
