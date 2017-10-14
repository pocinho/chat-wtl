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

	// a estrutura wsa é utilizada para guardar a informação
	// de inicialização de Windows Sockets
	WSADATA wsa;

	// socket de servidor onde o cliente se liga e se efetua a ligação
	SOCKET server_socket;

	// sockaddr_in: utilizado por Windows Sockets para especificar um endereço
	// local ou remoto para o qual se vai ligar o socket
	// neste caso 'server' é o endereço remoto
	struct sockaddr_in server;

	// construtor
	CThreadCliente(MainDialog * md, int porta, std::string ip);

	// destrutor
	virtual ~CThreadCliente();

	// inicialização da thread
	BOOL Initialize();

	// Run() corre automaticamente
	DWORD Run();

	// estabelecer ligação ao servidor
	void Ligar();

};

#endif // !CTHREADCLIENTE_H
