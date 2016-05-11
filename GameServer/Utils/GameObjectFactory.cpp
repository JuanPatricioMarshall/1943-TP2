/*
 * GameObjectFactory.cpp
 *
 *  Created on: May 10, 2016
 *      Author: gonzalo
 */

#include "GameObjectFactory.h"

GameObject* GameObjectFactory::createGameObject(const std::string& gameObjectID)
{
	GameObject* go;
	if (gameObjectID.compare("isla") == 0)
	{
		go = new Island();
		return go;
	}

	delete go;

}
