/*
 * Level.h
 *
 *  Created on: May 9, 2016
 *      Author: gonzalo
 */

#ifndef BACKGROUND_LEVEL_H_
#define BACKGROUND_LEVEL_H_

#include "../Game.h"
#include "../GameObject.h"
#include "../Background/Island.h"
#include "Background.h"
#include "Island.h"
#include "../Utils/Parser/ParserNivel.h"
#include "../Utils/TextureHelper.h"
#include "../Utils/GameObjectFactory.h"
#include <vector>
#include <sstream>

class Level
{
public:
	Level();
	~Level();

	void loadFromXML();
	void initialize(int backgroundTextureID, int levelWidth, int levelHeigth, float scrollSpeed);
	void addObject(GameObject* gameObject, int x, int y);
	//void paintBackground();
	void update();
	void clean();

private:

	void resetPositions();

	int m_virtualPosition; // Posicion en Y virtual, tiene el cero en la esquina de abajo e incrementa hacia arriba

	int m_backgroundTextureID;
	int m_levelWidth;
	int m_levelHeight;
	int m_scrollSpeed;
	std::vector<GameObject*> m_levelObjects;

	ParserNivel* m_parserNivel;
	TextureHelper* m_textureHelper;
};



#endif /* BACKGROUND_LEVEL_H_ */
