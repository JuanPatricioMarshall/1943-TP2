/*
 * BulletsHandler.cpp
 *
 *  Created on: May 6, 2016
 *      Author: gonzalo
 */

#include "BulletsHandler.h"
#include "../Game.h"


BulletsHandler* BulletsHandler::s_pInstance = new BulletsHandler();

BulletsHandler::BulletsHandler()
{
}

void BulletsHandler::addBullet(Bullet* bullet)
{
    m_bullets.push_back(bullet);
}

void BulletsHandler::clearBullets()
{
	for (std::vector< Bullet* >::iterator it = m_bullets.begin() ; it != m_bullets.end(); ++it)
	{
		delete (*it);
	}
	m_bullets.clear();
}

void BulletsHandler::updateBullets()
{
    for (std::vector<Bullet*>::iterator p_it = m_bullets.begin(); p_it != m_bullets.end();)
    {
        if((*p_it)->getPosition().getX() < -20 || (*p_it)->getPosition().getX() > Game::Instance()->getGameWidth()
           || (*p_it)->getPosition().getY() < -20 || (*p_it)->getPosition().getY() > Game::Instance()->getGameHeight() || (*p_it)->isDead())
        {

        	(*p_it)->clean();
            delete * p_it;
            p_it = m_bullets.erase(p_it);
        }
        else
        {
            (*p_it)->update();
            ++p_it;
        }
    }
}

