#pragma once
#include "stdafx.h"

class MainDialog;

class CThreadServidor : public CThreadImpl<CThreadServidor>
{
public:	

	int m_porta;
	MainDialog * dlg;

	// a estrutura wsa é utilizada para guardar a informação
	// de inicialização de Windows Sockets
	WSADATA wsa;

	// socket de servidor e socket de escuta onde o cliente se liga e se efetua a ligação
	SOCKET server_socket, listen_socket;

	// sockaddr_in: utilizado por Windows Sockets para especificar um endereço
	// local ou remoto para o qual se vai ligar o socket
	// neste caso 'server' é o endereço local e 'client' o endereço remoto
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
