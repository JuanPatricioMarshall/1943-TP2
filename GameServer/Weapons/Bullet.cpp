/*
 * Bullet.cpp
 *
 *  Created on: May 6, 2016
 *      Author: gonzalo
 */

#include "Bullet.h"

Bullet::Bullet(): MoveableObject(),
			m_dead(false)
{
	m_tag = "Bullet";
	m_layer = MIDDLEGROUND;
	m_textureID = 50;

	m_dyingTime = 3000;
	m_speed = Vector2D(20,20);
}

Bullet::~Bullet() {}


void Bullet::update()
{
	if(!m_dead)
	{
		MoveableObject::update();
		m_dyingTime -= GameTimeHelper::Instance()->deltaTime();
		if (m_dyingTime <= 0)
		{
			printf("murio una bala");
			m_dead = true;
		}
	}
	else
	{
		m_direction.setX(0);
		m_direction.setY(0);
	}

	if (m_dirty)
	{
		sendDrawMessage(true);
		m_dirty = false;
	}

}

bool Bullet::isDead()
{
	return m_dead;
}

void Bullet::clean()
{
	MoveableObject::clean();
	sendDrawMessage(false);
}

void Bullet::sendDrawMessage(bool isAlive)
{
	DrawMessage drawMsg;
	drawMsg.unused1 = false;
	drawMsg.connectionStatus = true;
	drawMsg.alive = isAlive;
	drawMsg.hasSound = false;

	drawMsg.objectID = m_objectId;
	drawMsg.layer = m_layer;
	drawMsg.soundID = 0;
	drawMsg.column = m_currentFrame;
	drawMsg.row = m_currentRow;
	drawMsg.posX = m_position.getX();
	drawMsg.posY = m_position.getY();
	drawMsg.textureID = m_textureID;

	if (USE_DRAWMESSAGE_PACKAGING)
	{
		Game::Instance()->addToPackage(drawMsg);
	}
	else
	{
		Game::Instance()->sendToAllClients(drawMsg);
	}
}
