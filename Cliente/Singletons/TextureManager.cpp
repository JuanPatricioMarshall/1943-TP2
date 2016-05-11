#include "TextureManager.h"

TextureManager* TextureManager::s_pInstance = 0;

bool TextureManager::load(std::string fileName, int id, SDL_Renderer* renderer)
{


    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

    if(pTempSurface == 0)
    {
		std::cout << IMG_GetError();
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(renderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);

    if(pTexture != 0)
    {
        m_textureMap[id] = pTexture;
        return true;
    }

    return false;
}
TextureInfo TextureManager::getTextureInfo(int textureId){
	return m_textureMapInfo[textureId];
}
void TextureManager::init(SDL_Renderer* pRenderer){

	TextureInfo hola;

	//PLAYERS


	hola.width =60;
	hola.height = 66;
	hola.numFrames = 14;
	hola.path =	"Assets/Sprites/player4.png";
	m_textureMapInfo[0]=hola;
	load(hola.path, 0, pRenderer);

	hola.width =60;
	hola.height = 66;
	hola.numFrames = 14;
	hola.path =	"Assets/Sprites/player2v2.png";
	m_textureMapInfo[1]=hola;
	load(hola.path, 1, pRenderer);

	hola.width =60;
	hola.height = 66;
	hola.numFrames = 14;
	hola.path =	"Assets/Sprites/player3.png";
	m_textureMapInfo[1]=hola;
	load(hola.path, 1, pRenderer);

	hola.width =60;
	hola.height = 66;
	hola.numFrames = 14;
	hola.path =	"Assets/Sprites/player1.png";
	m_textureMapInfo[1]=hola;
	load(hola.path, 1, pRenderer);

	//BACKGROUND
	hola.width = 64;
	hola.height = 64;
	hola.numFrames = 1;
	hola.path =	"Assets/Sprites/Water.jpg";
	m_textureMapInfo[10]=hola;
	load(hola.path, 10, pRenderer);


	hola.height = 128;
	hola.numFrames = 1;
	hola.path =	"Assets/Sprites/island.png";
	hola.width = 128;
	m_textureMapInfo[20]=hola;
	load(hola.path, 20, pRenderer);

	hola.height = 128;
	hola.numFrames = 1;
	hola.path =	"Assets/Sprites/Piedra.jpg";
	hola.width = 128;
	m_textureMapInfo[21]=hola;
	load(hola.path, 21, pRenderer);

	//BALAS
	hola.width = 9;
	hola.height = 54;
	hola.numFrames = 1;
	hola.path =	"Assets/Sprites/laserBlue01.png";
	m_textureMapInfo[11]=hola;
	//load(hola.path, 11, Game::Instance()->getRenderer());

	hola.width = 32;
	hola.height = 32;
	hola.numFrames = 1;
	hola.path =	"Assets/Sprites/bullet.png";
	m_textureMapInfo[50]=hola;
	load(hola.path, 50, pRenderer);


	//DEFAULT
	hola.width = 32;
	hola.height = 32;
	hola.numFrames = 1;
	hola.path =	"Assets/Sprites/missing.jpg";
	m_textureMapInfo[999]=hola;
	load(hola.path, 999, pRenderer);



}
void TextureManager::draw(int id, int x, int y, int width, int height, double angle, SDL_Renderer* renderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(renderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::drawFrame(int id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer, double angle, int alpha, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = width * currentFrame;
    srcRect.y = height * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::changeTextureColor(int textureID, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(m_textureMap[textureID], r, g, b);
}

void TextureManager::clearTextureMap()
{
    m_textureMap.clear();
}

void TextureManager::clearFromTextureMap(int id)
{
    m_textureMap.erase(id);
}
