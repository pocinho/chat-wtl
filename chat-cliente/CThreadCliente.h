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
	WSADATA wsa;
	SOCKET server_socket, listen_socket;
	struct sockaddr_in server, client;

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
