#include "cliente.h"

using namespace std;

void cliente::error(const char *msg)
{
	Logger::Instance()->LOG(msg, ERROR);
	Logger::Instance()->Close();
    exit(0);
}

bool cliente::conectar()
{
	if (m_connecting)
		return true;
	m_connecting = true;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
    	Logger::Instance()->LOG("Cliente: Error en la creación del socket", ERROR);
    	m_connecting = false;
    	return false;
    }
    setTimeOut();
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
    	Logger::Instance()->LOG("Cliente: El cliente no se pudo conectar satisfactoriamente", WARN);
    	m_connecting = false;
       return false;
    }
    m_connected = true;
	leer();

	if (m_connected)
	{
		serverTimeOut->Reset();
		//sendTimeOutTimer->Reset();
		serverTimeOut->Start();
		//sendTimeOutTimer->Start();
		//createTimeoutThread();
	}
	else
	{
		cerrarSoket();
	}
	m_connecting = false;

    return m_connected;
}
void cliente::desconectar()
{
	if (!m_connected)
		return;
	Game::Instance()->disconnect();
	m_connected = false;
	serverTimeOut->Stop();
	cerrarSoket();
	printf("Has sido desconectado del servidor \n");
	Logger::Instance()->LOG("Cliente: El cliente se ha desconectado satisfactoriamente", DEBUG);
}

cliente::cliente(int argc, string ip, int port, std::string name){
	m_connected = false;
	m_connecting = false;
	m_alanTuring = new AlanTuring();

    //XInitThreads();
    pthread_mutex_init(&m_readingMutex, NULL);
    pthread_mutex_init(&m_writingMutex, NULL);
    pthread_cond_init(&m_condv, NULL);

    portno = port;
	printf("Cargo Puerto: %d \n",portno);
	cout << ip;
    /*sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    	error("Cliente: Error en la creación del socket");*/
    const char* ip1 = ip.c_str();
    server = gethostbyname(ip1);
    if (server == NULL) {
    	error("Cliente: No se pudo encontrar el servidor ingresado");
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);

    m_playerName = name;

    serverTimeOut = new Timer();
    //sendTimeOutTimer = new Timer();


}
cliente::~cliente()
{
    pthread_mutex_destroy(&m_readingMutex);
    pthread_mutex_destroy(&m_writingMutex);
    pthread_cond_destroy(&m_condv);
	delete serverTimeOut;
	//delete sendTimeOutTimer;

	delete m_alanTuring;
}

void cliente::escribir(Mensaje mensaje)
{
	sendMsg(mensaje);
}

void cliente::sendMsg(Mensaje msg)
{
	pthread_mutex_lock(&m_writingMutex);
	char bufferEscritura[MESSAGE_BUFFER_SIZE];
	int msgLength = m_alanTuring->encodeXMLMessage(msg, bufferEscritura);
	char *ptr = (char*) bufferEscritura;

    while (msgLength > 0)
    {
        int bytesEnviados = send(sockfd, ptr, msgLength, 0);
        if (bytesEnviados < 1)
        {
        	Logger::Instance()->LOG("Server: No se pudo enviar el mensaje.", WARN);
        	return;
        }
        ptr += bytesEnviados;
        msgLength -= bytesEnviados;
    }

	pthread_mutex_unlock(&m_writingMutex);
    if (msg.tipo.compare("timeoutACK") != 0)
    {
		std::stringstream ss;
		ss << "Cliente: Se ha enviado con éxito el mensaje con ID: " << msg.id.c_str() << ".";
		Logger::Instance()->LOG(ss.str(), DEBUG);
    }
}

void cliente::sendNetworkMsg(NetworkMessage netMsg)
{
	char bufferEscritura[MESSAGE_BUFFER_SIZE];
	bzero(bufferEscritura,MESSAGE_BUFFER_SIZE);

	int msgLength = m_alanTuring->encodeNetworkMessage(netMsg, bufferEscritura);

	char *ptr = (char*) bufferEscritura;

    while (msgLength > 0)
    {
        int bytesEnviados = send(sockfd, ptr, msgLength, 0);
        if (bytesEnviados < 1)
        {
        	Logger::Instance()->LOG("Server: No se pudo enviar el mensaje.", WARN);
        	return;
        }
        ptr += bytesEnviados;
        msgLength -= bytesEnviados;
    }
}


void cliente::sendInputMsg(InputMessage msg)
{
	pthread_mutex_lock(&m_writingMutex);
	char bufferEscritura[MESSAGE_BUFFER_SIZE];
	int msgLength = m_alanTuring->encodeInputMessage(msg, bufferEscritura);
	char *ptr = (char*) bufferEscritura;

    while (msgLength > 0)
    {
        int bytesEnviados = send(sockfd, ptr, msgLength, 0);
        if (bytesEnviados < 1)
        {
        	Logger::Instance()->LOG("Server: No se pudo enviar el mensaje.", WARN);
        	return;
        }
        ptr += bytesEnviados;
        msgLength -= bytesEnviados;
    }
	pthread_mutex_unlock(&m_writingMutex);
    //printf("Mensaje input enviado \n");
}

void cliente::sendConnectionInfoMsg(ConnectionInfo msg)
{
	pthread_mutex_lock(&m_writingMutex);
	char bufferEscritura[MESSAGE_BUFFER_SIZE];
	int msgLength = m_alanTuring->encodeConnectionInfoMessage(msg, bufferEscritura);
	char *ptr = (char*) bufferEscritura;

    while (msgLength > 0)
    {
        int bytesEnviados = send(sockfd, ptr, msgLength, 0);
        if (bytesEnviados < 1)
        {
        	Logger::Instance()->LOG("Server: No se pudo enviar el mensaje.", WARN);
        	return;
        }
        ptr += bytesEnviados;
        msgLength -= bytesEnviados;
    }
	pthread_mutex_unlock(&m_writingMutex);
    //printf("Mensaje input enviado \n");
}

//Envia mensaje de timeOut cada x tiempo
bool cliente::sendTimeOutMsg()
{
	//pthread_mutex_lock(&m_writingMutex);
	//if (!checkServerConnection())
		//return false;

	/*if ((float)sendTimeOutTimer->GetTicks()/CLOCKS_PER_SEC >= 2.5f)
	{
		Mensaje timeOutMsg = MessageFactory::Instance()->createMessage("", "",msgTimeOutACK);
		sendMsg(timeOutMsg);

		sendTimeOutTimer->Reset();
		//espera procesamiento del server
		if (!leer())
			return false;
	}
	pthread_mutex_unlock(&m_writingMutex);*/
	return true;

}

bool cliente::checkServerConnection()
{
	//printf("Timer del server = %f\n", (float)serverTimeOut->GetTicks()/CLOCKS_PER_SEC);
	if (((float)serverTimeOut->GetTicks()/CLOCKS_PER_SEC >= TIMEOUT_SECONDS) || (m_connected == false))
	{
		printf("Se perdio conexión con el servidor.\n");

		Game::Instance()->disconnect();
		desconectar();
		return false;
	}
	return true;
}


bool cliente::leer()
{
	pthread_mutex_lock(&m_readingMutex);
	//char buffer[256];
	bzero(buffer,256);
	int messageLength = 0;
	char *p = (char*)buffer;
	int readLimit = (DRAW_MESSAGE_PACK_SIZE * sizeof(DrawMessage)) + MESSAGE_CODE_BYTES + MESSAGE_LENGTH_BYTES + MESSAGE_LENGTH_BYTES;

	int n = recv(sockfd, buffer, MESSAGE_LENGTH_BYTES, 0);

   if (!lecturaExitosa(n))
   {
	   //Se perdio la conexion con el server
	   return false;
   }
   int acum = n;
   while (acum < MESSAGE_LENGTH_BYTES)
   {
	   printf("Leyo menos de 4\n");
	   p += n;
	   n = recv(sockfd, p, MESSAGE_LENGTH_BYTES - acum, 0);
	   if (!lecturaExitosa(n))
		   return false;
	   acum += n;
   }

   messageLength = m_alanTuring->decodeLength(buffer);

   p += n;
   messageLength -= acum;
   //loopea hasta haber leido la totalidad de los bytes necarios
   while (messageLength > 0)
   {
	  //printf("Leyó %d. Faltan leer %d \n", acum, messageLength);
	  n = recv(sockfd, p, messageLength, 0);
	 if(messageLength >readLimit)
		 {
			 return true;
		 }
       if (!lecturaExitosa(n))
       {
    	   //se perdio la conexion con el server
    	  return false;
       }
       p += n;
       messageLength -= n;
   }
   pthread_cond_signal(&m_condv);
   pthread_mutex_unlock(&m_readingMutex);
   //llego el mensaje bien
   serverTimeOut->Reset();

   NetworkMessage netMsgRecibido = m_alanTuring->decode(buffer);

   procesarMensaje(netMsgRecibido);

   return true;

}
bool cliente::isConnected(){
	return m_connected;
}
bool cliente::isConnecting(){
	return m_connecting;
}
void cliente::cerrarSoket()
{
    close(sockfd);
}

void cliente::setTimeOut()
{
    struct timeval timeout;
    timeout.tv_sec = TIMEOUT_SECONDS * 6;
    timeout.tv_usec = TIMEOUT_MICROSECONDS;

    if (setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
    {
    	Logger::Instance()->LOG("Cliente: No se pudo setear un timeout en la conexion con el servidor.", WARN);
    }

    if (setsockopt (sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
    {
    	Logger::Instance()->LOG("Cliente: No se pudo setear un timeout en la conexion con el servidor.", WARN);
    }
}

void cliente::procesarMensaje(NetworkMessage networkMessage)
{
	//Timeout
	if ((networkMessage.msg_Code[0] == 't') && (networkMessage.msg_Code[1] == 'm') && (networkMessage.msg_Code[2] == 'o'))
	{
		//TimeOut ACK, lo dej opor si en el futuro queremos hacer algo extra
		serverTimeOut->Reset();
		return;
	}

	//Mensaje de coneccion con el servidor
	if ((networkMessage.msg_Code[0] == 'c') && (networkMessage.msg_Code[1] == 'n') && (networkMessage.msg_Code[2] == 't'))
	{
		printf("Conectando\n");
		ConnectedMessage connectedMessage = m_alanTuring->decodeConnectedMessage(networkMessage);
		if (connectedMessage.requestData && !connectedMessage.connected)
		{
			//El SERVER ESTA SOLICITANDO INFORMACION DE CONECCION
			//ENVIAR CONNECTION INFO
			ConnectionInfo connectionInfo;
			std::size_t length = m_playerName.copy(connectionInfo.name, MAX_NAME_LENGTH, 0);
			connectionInfo.name[length]='\0';

			sendConnectionInfoMsg(connectionInfo);
			printf("Envio el nombre: %s \n", connectionInfo.name);
			if (!leer())
			{
				printf("No se pudo terminar el proceso de conexion\n");
				desconectar();
				m_connected = false;
			}
		}

		if (connectedMessage.connected && !connectedMessage.requestData)
		{
			printf("Conectado con id: %d \n", connectedMessage.objectID);
			Timer* initializingTimer = new Timer();
			initializingTimer->Start();
			while (Game::Instance()->isInitializingSDL())
			{
				continue;
				printf("Esperando que termina la inicializacion de SDL\n");
				if ((long double)initializingTimer->GetTicks()/CLOCKS_PER_SEC >= 5.0)
				{
					initializingTimer->Stop();
					break;
				}
				else
				{
					continue;
				}
			}
			delete initializingTimer;
			Game::Instance()->createPlayer(connectedMessage.objectID, connectedMessage.textureID);
			Game::Instance()->setWindowSize(static_cast<int>(connectedMessage.windowWidth), static_cast<int>(connectedMessage.windowHeight));
			//El cliente se conecto con exito.
			printf("Conección con el server exitosa. \n");
			Logger::Instance()->LOG("Cliente: Conección al servidor exitosa.\n", DEBUG);
		}

		if (!connectedMessage.connected && !connectedMessage.requestData)
		{
			printf("El nombre ya existe\n");
			desconectar();
			m_connected = false;
		}

		return;
	}
	if ((networkMessage.msg_Code[0] == 'e') && (networkMessage.msg_Code[1] == 'x') && (networkMessage.msg_Code[2] == 't'))
	{
		printf("Exit\n");
		//El cliente fue pateado
		desconectar();
		printf("El cliente ha sido desconectado del server.\n");
		Logger::Instance()->LOG("Cliente: El cliente ha sido desconectado del server.", DEBUG);

		return;
	}
	//Servidor Lleno
	if ((networkMessage.msg_Code[0] == 'f') && (networkMessage.msg_Code[1] == 'u') && (networkMessage.msg_Code[2] == 'l'))
	{
		//El server esta lleno. Patear
		desconectar();
		m_connected = false;

		printf("El servidor está lleno.\n");
		Logger::Instance()->LOG("Cliente: No se pudo conectar al servidor. El servidor está lleno.", DEBUG);
		return;
	}


	//Draw Message
	if ((networkMessage.msg_Code[0] == 'd') && (networkMessage.msg_Code[1] == 'm') && (networkMessage.msg_Code[2] == 's'))
	{
		while (Game::Instance()->isInitializingSDL())
		{
			continue;
			printf("Esperando que termina la inicializacion de SDL\n");

		}
		//printf("Leyendo DrawMessage\n");
		DrawMessage drwMsg = m_alanTuring->decodeDrawMessage(networkMessage);
		Game::Instance()->interpretarDrawMsg(drwMsg);
			//Logger::Instance()->LOG("Se envio drwMsg a interpretar\n", DEBUG);
		//printf("Fin Leyendo DrawMessage\n");
		return;
	}
	//Draw Message Package
	if ((networkMessage.msg_Code[0] == 'd') && (networkMessage.msg_Code[1] == 'm') && (networkMessage.msg_Code[2] == 'p'))
	{
		//printf("Leyendo DrawMessagePackage\n");
		DrawMessagePack drwMsgPackage = m_alanTuring->decodeDrawMessagePackage(networkMessage);
		procesarDrawPackage(drwMsgPackage);
			//Logger::Instance()->LOG("Se envio drwMsg a interpretar\n", DEBUG);
		//printf("Fin Leyendo DrawMessagePackage\n");
		return;
	}

	//Reinicio de Juego
	if ((networkMessage.msg_Code[0] == 'r') && (networkMessage.msg_Code[1] == 's') && (networkMessage.msg_Code[2] == 't'))
	{
		ResetInfo resetInfo = m_alanTuring->decodeResetInfo(networkMessage);
		Game::Instance()->setWindowSize(static_cast<int>(resetInfo.windowWidth), static_cast<int>(resetInfo.windowHeight));
		Game::Instance()->resetGame();
		Logger::Instance()->LOG("Juego: El juego ha sido reiniciado.", DEBUG);

		return;
	}

	//Desconeccion de un jugador
	if ((networkMessage.msg_Code[0] == 'p') && (networkMessage.msg_Code[1] == 'd') && (networkMessage.msg_Code[2] == 'c'))
	{
		PlayerDisconnection playerDiscMsg = m_alanTuring->decodePlayerDisconnectionMessage(networkMessage);
		Game::Instance()->disconnectObject(playerDiscMsg.objectID, playerDiscMsg.layer);

		printf ("El jugador %s se ha desconectado. \n", playerDiscMsg.name);
		std::stringstream ss;
		ss <<"Cliente: El jguador " << playerDiscMsg.name << " se ha desconectado.";
		Logger::Instance()->LOG(ss.str(), DEBUG);

		return;
	}


	//Game Beginning
	if ((networkMessage.msg_Code[0] == 'g') && (networkMessage.msg_Code[1] == 'b') && (networkMessage.msg_Code[2] == 'g'))
	{
		Game::Instance()->setGameStarted(true);
		return;
	}

}

bool cliente::validarMensaje(DataMessage dataMsg)
{
	bool mensajeValido = true;
	string messageID(dataMsg.msg_ID);
	std::stringstream ss;
	if ((dataMsg.msg_status == '-') || (dataMsg.msg_status == 'I'))
	{
		mensajeValido = false;
		ss.clear();
		ss << "El Mensaje con ID: " << messageID.c_str() << " fue rechazado.";
		Logger::Instance()->LOG(ss.str(), DEBUG);
		ss << "\n";
		printf("%s", ss.str().c_str());

	}
	if (dataMsg.msg_status == 'V')
	{
		mensajeValido = true;
		ss.clear();
		ss << "El Mensaje con ID: " << messageID.c_str() << " fue procesado correctamente.";
		Logger::Instance()->LOG(ss.str(), DEBUG);
		ss << "\n";
		printf("%s", ss.str().c_str());
	}
	return mensajeValido;
}
void *cliente::sendTimeOuts(void)
{

    while(true)
    {
    	if (!sendTimeOutMsg())
    		break;
	}
    pthread_exit(NULL);

}
void *cliente::timeOut_method(void *context)
{
	return ((cliente *)context)->sendTimeOuts();
}
void cliente::createTimeoutThread(){

	pthread_create(&timeOutThread, NULL, &cliente::timeOut_method, (void*)this);
}

bool cliente::lecturaExitosa(int bytesLeidos)
{
    if (bytesLeidos < 0)
    {
    	//Se perdio la coneccion con el server
    	printf("Leyó menos de 0\n");
    	desconectar();
    	return false;
    }
	if (bytesLeidos == 0){
		//Se perdio la coneccion con el server
    	printf("Leyó 0\n");
		desconectar();
		return false;
    }
	return true;
}

void cliente::procesarDrawPackage(DrawMessagePack drawMsgPackage)
{
	int drawMessagesAmount = (drawMsgPackage.totalSize - sizeof(int)) / sizeof(DrawMessage);
	for (int i = 0; i < drawMessagesAmount; i++)
	{
		DrawMessage drawMessage = drawMsgPackage.drawMessages[i];
		Game::Instance()->interpretarDrawMsg(drawMessage);
	}
}
