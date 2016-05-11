/*
 * TextureHelper.cpp
 *
 *  Created on: May 10, 2016
 *      Author: gonzalo
 */

#include "TextureHelper.h"


TextureHelper::TextureHelper()
{
	initialize();
}

TextureHelper::~TextureHelper()
{
	m_textureIDMap.clear();
}

void TextureHelper::initialize()
{
	m_textureIDMap["default"] = 999;

	//Escenario
	m_textureIDMap["agua"] = 10;

	//Jugadores
	m_textureIDMap["avion"] = 0;
	m_textureIDMap["player1"] = 0;
	m_textureIDMap["player2"] = 1;
	m_textureIDMap["player3"] = 2;
	m_textureIDMap["player4"] = 3;

	//ELEMENTOS DE BACKGROUND
	m_textureIDMap["isla"] = 20;
	m_textureIDMap["piedra"] = 21;

	//Disparos
	m_textureIDMap["disparo"] = 50;


}

int TextureHelper::stringToInt(const std::string& stringID)
{
	if (m_textureIDMap.find(stringID) == m_textureIDMap.end())
		return 9999;

	return m_textureIDMap[stringID];
}
