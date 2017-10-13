#pragma once
#include "stdafx.h"

class MainDialog;

class CThreadServidor : public CThreadImpl<CThreadServidor>
{
public:	

	int m_porta;
	MainDialog * dlg;

	// a estrutura wsa � utilizada para guardar a informa��o
	// de inicializa��o de Windows Sockets
	WSADATA wsa;

	// socket de servidor e socket de escuta onde o cliente se liga e se efetua a liga��o
	SOCKET server_socket, listen_socket;

	// sockaddr_in: utilizado por Windows Sockets para especificar um endere�o
	// local ou remoto para o qual se vai ligar o socket
	// neste caso 'server' � o endere�o local e 'client' o endere�o remoto
	struct sockaddr_in server, client;

	// construtor
	CThreadServidor(MainDialog * md, int porta);

	// destrutor
	virtual ~CThreadServidor();

	BOOL Initialize();

	// Run() corre automaticamente.
	DWORD Run();

	void Escutar(int porta);
	void Limpar();
};
