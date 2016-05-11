#include "Game.h"

Game* Game::s_pInstance = 0;

Game::Game():
m_pWindow(0),
m_pRenderer(0),
m_running(false),
m_reseting(false),
m_scrollSpeed(2)
{

}

Game::~Game()
{
    // we must clean up after ourselves to prevent memory leaks
    m_pRenderer= 0;
    m_pWindow = 0;
}


bool Game::init(const char* title, int xpos, int ypos, int width, int height)
{
    // Tamaño de la ventana

    m_parserNivel = new ParserNivel();
    m_parserNivel->parsearDocumento(XML_PATH);

    m_textureHelper = new TextureHelper();

    m_gameWidth = m_parserNivel->getVentana().ancho;
    m_gameHeight = m_parserNivel->getVentana().alto;

    //printf("Path isla: %s \n", m_parserNivel->getListaSprites()[5].path.c_str());
   // printf("ID isla: %s \n", m_parserNivel->getListaSprites()[5].id.c_str());

    printf("Se cargo el escenario con ancho %d y alto %d\n",m_gameWidth, m_gameHeight );

    inicializarServer();

    m_level = new Level();
    m_level->loadFromXML();

    //TextureManager::Instance()-> init();

    //Provisorio rompen porq blackship water island son string... pone ints (hacer mapas primero)
   //m_player = new Player();
   //m_player->load(m_gameWidth/2, m_gameHeight/2, 38, 64, "blackship", 1);
   //m_player->load(m_gameWidth/2, m_gameHeight/2, 38, 64, 1, 1);
   //listOfPlayer[m_player->getObjectId()]= *m_player;

  /* m_background = new Background();
   m_background->load(0, 0, m_gameWidth, m_gameHeight, 2);
   m_background->setLayer(BACKGROUND);
	printf("Background inicializado con objectID: %d y textureID: %d y layer : %d\n", m_background->getObjectId(), 2, m_background->getLayer());
	m_listOfGameObjects[m_background->getObjectId()] = m_background;*/


  /* m_island = new Island();
   m_island->load(0, m_gameHeight/2, 150, 150, 3, 1);
   m_island->setLayer(MIDDLEGROUND);
   m_island->setReappearanceTime(5000);   // en ms
   printf("Isla inicializada con objectID: %d y textureID: %d\n", m_island->getObjectId(), 3);
   m_listOfGameObjects[m_island->getObjectId()] = m_island;*/




    //tudo ben
    m_running = true;

    return true;
}

bool Game::createPlayer(int playerID,  const std::string& playerName)
{
	//Se fija si existe un jugador con el nombre ingresado
	if (!validatePlayerName(playerName))
		return false;

	int playerSpeed = m_parserNivel->getAvion().velDespl;
	int shootingCooldown = m_parserNivel->getAvion().cdDisp;
	int bulletsSpeed = m_parserNivel->getAvion().velDisp;

	Player* newPlayer = new Player();
	newPlayer->setObjectID(playerID);
	newPlayer->setSpeed(Vector2D(playerSpeed, playerSpeed));
	newPlayer->setShootingCooldown(shootingCooldown);
	newPlayer->setShootingSpeed(bulletsSpeed);


	m_playerNames[playerID] = playerName;

	std::stringstream ss;
	ss << "player" << (playerID + 1);
	string playerStringID = ss.str();
	int playerTextureID = m_textureHelper->stringToInt(playerStringID);

	//Workaround
	bool found = false;;
	for(int i=0; i < m_parserNivel->getListaSprites().size(); i++)
	{
	  if (playerStringID == m_parserNivel->getListaSprites()[i].id)
	  {
		  found = true;
		  break;
	  }
	}
	if (!found)
		playerTextureID = m_textureHelper->stringToInt("default");

	newPlayer->load(m_gameWidth/2, m_gameHeight/2, 38, 64, playerTextureID, 14);
	newPlayer->setConnected(true);

	m_listOfPlayer[newPlayer->getObjectId()]= newPlayer;
	printf("Player: %s inicializado con objectID: %d y textureID: %d\n",m_playerNames[playerID].c_str(), newPlayer->getObjectId(), playerID);

	return true;
}

bool Game::validatePlayerName(const std::string& playerName)
{
	for (std::map<int, std::string>::iterator it = m_playerNames.begin(); it != m_playerNames.end(); ++it )
	{
	    if (it->second.compare(playerName.c_str()) == 0)
	        return false;
	}
	//Nombre disponible
	return true;
}

void Game::disconnectPlayer(int playerID)
{
	PlayerDisconnection playerDiscMsg;
	std::size_t length = m_playerNames[playerID].copy(playerDiscMsg.name, MAX_NAME_LENGTH, 0);
	playerDiscMsg.name[length]='\0';
	playerDiscMsg.objectID = m_listOfPlayer[playerID]->getObjectId();
	playerDiscMsg.layer = m_listOfPlayer[playerID]->getLayer();
	m_server->informPlayerDisconnection(playerDiscMsg, playerID);

	m_listOfPlayer[playerID]->setConnected(false);
	m_playerNames.erase(playerID);
	//listOfPlayer.erase(id);
	//mostrar en gris
}

void Game::render()
{
    //SDL_RenderClear(m_pRenderer);


    //Dibujar lo que haya que dibujar
 /*   m_background->draw(); //Provisorio
    m_island->draw(); //Provisorio
    m_player->draw();//Provisorio
*/
    //SDL_RenderPresent(m_pRenderer);
}


void Game::update()
{
	BulletsHandler::Instance()->updateBullets();

	m_level->update();

	for (std::map<int,Player*>::iterator it=m_listOfPlayer.begin(); it != m_listOfPlayer.end(); ++it)
	{
		//printf("objectID = %d \n", it->second.getObjectId());
	     it->second->update();
	}
	for (std::map<int,GameObject*>::iterator it=m_listOfGameObjects.begin(); it != m_listOfGameObjects.end(); ++it)
	{
		//printf("objectID = %d \n", it->second.getObjectId());
	     it->second->update();
	}

}

void Game::handleEvents()
{
}
void Game::inicializarServer()
{

	std::string fileName = "Utils/Default/servidor.xml";

	ParserServidor* servidorParser = new ParserServidor();
	servidorParser->parsearDocumento(fileName);

	LoggerInfo loggerInfo = servidorParser->getLoggerInfo();
	Logger::Instance()->setLoglevel(loggerInfo.debugAvailable, loggerInfo.warningAvailable, loggerInfo.errorAvailable);

	int porto = servidorParser->getServidorInfo().puerto ;
	int maxClientes = m_parserNivel->getEscenario().cantidadJugadores;
	//printf("Creando enlazamiento\n");
	m_server = new server(porto, maxClientes);

    m_drawMessagePacker = new DrawMessagesPacker(m_server);

	//printf("Se pone a escuchar\n");
	m_server->escuchar();

	int auxi = 0;
	while(m_server->getNumClientes() < m_server->getMaxClientes())
	{
		auxi++;
		m_server->aceptar();
	}

	//Informa a los clientes que el juego comenzará
	m_server->informGameBeginning();

}


void Game::sendToAllClients(DrawMessage mensaje)
{
	m_server->sendDrawMsgToAll(mensaje);
}

void Game::addToPackage(DrawMessage drawMsg)
{
	m_drawMessagePacker->addDrawMessage(drawMsg);
}
void Game::sendPackages()
{
	m_drawMessagePacker->sendPackedMessages();
}



void* Game::koreaMethod(void)
{

	std::cout << "Empece a ciclar bitches!\n";
	while (Game::Instance()->isRunning()) {

			/*if (!m_server->leer())
				break;*/
	        }
	 pthread_exit(NULL);
}
void *Game::thread_method(void *context)
{
	return ((Game *)context)->koreaMethod();
}
void Game::readFromKorea()
{
	pthread_create(&listenThread, NULL, &Game::thread_method, (void*)this);

}

void Game::actualizarEstado(int id, InputMessage inputMsg){
	/*printf("Actualizar player %d\n",inputMsg.objectID);
	printf("button right: %d \n",inputMsg.buttonRight);
	printf("button left: %d \n",inputMsg.buttonLeft);
	printf("button up: %d \n",inputMsg.buttonUp);
	printf("button down: %d \n",inputMsg.buttonDown);*/

	m_listOfPlayer[inputMsg.objectID]->handleInput(inputMsg);
}

void Game::clean()
{
    cout << "cleaning game\n";
    BulletsHandler::Instance()->clearBullets();

	for (std::map<int,Player*>::iterator it=m_listOfPlayer.begin(); it != m_listOfPlayer.end(); ++it)
	{
		//printf("objectID = %d \n", it->second.getObjectId());
	     it->second->clean();
	     delete  it->second;
	}
	for (std::map<int,GameObject*>::iterator it=m_listOfGameObjects.begin(); it != m_listOfGameObjects.end(); ++it)
	{
		//printf("objectID = %d \n", it->second.getObjectId());
	     it->second->clean();
	     delete  it->second;
	}
    m_listOfPlayer.clear();
    m_listOfGameObjects.clear();
    m_playerNames.clear();

    m_drawMessagePacker->clean();
    delete m_drawMessagePacker;

    m_parserNivel->clean();
    delete m_parserNivel;

    m_level->clean();
    delete m_level;
    delete m_textureHelper;

    InputHandler::Instance()->clean();
    TextureManager::Instance()->clearTextureMap();


    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

void Game::resetGame()
{
	 BulletsHandler::Instance()->clearBullets();
	 InputHandler::Instance()->clean();
	 //delete m_background;
	 //delete m_island;
	 //m_listOfGameObjects.clear();
	 m_level->clean();
	 delete m_level;
	 m_parserNivel->clean();

	 printf("Se terminó de borrar bien\n");

	 //CARGAR XML
	 m_parserNivel = new ParserNivel();
	 m_parserNivel->parsearDocumento(XML_PATH);
	 m_gameWidth = m_parserNivel->getVentana().ancho;
	 m_gameHeight = m_parserNivel->getVentana().alto;

	 m_level = new Level();
	 m_level->loadFromXML();

	int newPlayerSpeed = m_parserNivel->getAvion().velDespl;
	int newShootingCooldown = m_parserNivel->getAvion().cdDisp;
	int newBulletsSpeed = m_parserNivel->getAvion().velDisp;
	for (std::map<int,Player*>::iterator it=m_listOfPlayer.begin(); it != m_listOfPlayer.end(); ++it)
	{
		 it->second->setSpeed(Vector2D(newPlayerSpeed, newPlayerSpeed));
		 it->second->setShootingCooldown(newShootingCooldown);
		 it->second->setShootingSpeed(newBulletsSpeed);
	}

	 //tudo ben
	 m_running = true;
}
/*	 m_background = new Background();
	 m_background->load(0, 0, m_gameWidth, m_gameHeight, 2);
	 m_background->setLayer(BACKGROUND);
	 printf("Background inicializado con objectID: %d y textureID: %d y layer : %d\n", m_background->getObjectId(), 2, m_background->getLayer());
	 m_listOfGameObjects[m_background->getObjectId()] = m_background;

	 printf("Se creó bien el background");

	 m_island = new Island();
	 m_island->load(0, m_gameHeight/2, 150, 150, 3, 1);
	 m_island->setLayer(MIDDLEGROUND);
	 m_island->setReappearanceTime(5000);   // en ms
	 printf("Isla inicializada con objectID: %d y textureID: %d\n", m_island->getObjectId(), 3);
	 m_listOfGameObjects[m_island->getObjectId()] = m_island;

	 printf("Se creó bien la isla");
*/
	 //tudo ben
	 //m_running = true;
