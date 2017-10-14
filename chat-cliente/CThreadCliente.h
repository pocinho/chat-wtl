#pragma once
#ifndef CTHREADCLIENTE_H
#define CTHREADCLIENTE_H

#include "stdafx.h"

class MainDialog;

class CThreadCliente : public CThreadImpl<CThreadCliente>
{
public:
	std::string m_ip;
	int m_porta;
	MainDialog * dlg;

	// a estrutura wsa � utilizada para guardar a informa��o
	// de inicializa��o de Windows Sockets
	WSADATA wsa;

	// socket de servidor onde o cliente se liga e se efetua a liga��o
	SOCKET server_socket;

	// sockaddr_in: utilizado por Windows Sockets para especificar um endere�o
	// local ou remoto para o qual se vai ligar o socket
	// neste caso 'server' � o endere�o remoto
	struct sockaddr_in server;

	// construtor
	CThreadCliente(MainDialog * md, int porta, std::string ip);

	// destrutor
	virtual ~CThreadCliente();

	// inicializa��o da thread
	BOOL Initialize();

	// Run() corre automaticamente
	DWORD Run();

	// estabelecer liga��o ao servidor
	void Ligar();

};

#endif // !CTHREADCLIENTE_H
