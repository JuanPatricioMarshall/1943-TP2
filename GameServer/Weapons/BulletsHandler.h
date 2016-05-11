/*
 * BulletsHandler.h
 *
 *  Created on: May 6, 2016
 *      Author: gonzalo
 */

#ifndef WEAPONS_BULLETSHANDLER_H_
#define WEAPONS_BULLETSHANDLER_H_

#include "Bullet.h"
#include <vector>
class Bullet;

class BulletsHandler
{
public:

    static BulletsHandler* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new BulletsHandler();
            return s_pInstance;
        }
        return s_pInstance;
    }

    void addBullet(Bullet* bullet);

    void updateBullets();

    void clearBullets();

    const std::vector<Bullet*> getPlayerBullets() { return m_bullets; }

private:

    BulletsHandler();
    ~BulletsHandler();

    BulletsHandler(const BulletsHandler&);
    BulletsHandler& operator=(const BulletsHandler&);

    static BulletsHandler* s_pInstance;

    // in play bullets
	std::vector<Bullet*> m_bullets;
};



#endif /* WEAPONS_BULLETSHANDLER_H_ */
