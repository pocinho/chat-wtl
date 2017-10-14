#include "stdafx.h"
#include "CThreadServidor.h"
#include "CThreadConexao.h"
#include "MainDialog.h"

CThreadServidor::CThreadServidor(MainDialog * md, int porta) : dlg(md), m_porta(porta)
{
}

CThreadServidor::~CThreadServidor()
{
}

BOOL CThreadServidor::Initialize()
{
	return TRUE; // não inicializamos nada aqui
}

DWORD CThreadServidor::Run()
{
	Escutar(m_porta);
	return 0;
}

void CThreadServidor::Escutar(int porta)
{
	// inicializar winsocket
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// inicializar o socket do servidor
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	// escutar em TCP e UDP
	server.sin_family = AF_INET;
	// escutar em qualquer ip atribuído à máquina (ver configurações de placa de rede)
	server.sin_addr.s_addr = INADDR_ANY;
	// escutar na porta especificada
	server.sin_port = htons(porta);

	// associar um endereço local com a socket servidor
	bind(server_socket, (struct sockaddr *)&server, sizeof(server));

	// inicializar escuta com máximo de conexões predefinido
	listen(server_socket, SOMAXCONN);

	int tamanho = sizeof(struct sockaddr_in);

	dlg->EscreverMsg(L"Ligado");

	// aceitar ligações para uma socket ligada ao cliente
	while (!IsAborted() && (listen_socket = accept(server_socket, (struct sockaddr *)&client, &tamanho)) != INVALID_SOCKET)
	{
		// preparar estruturas para multicast de ipv6
		socklen_t len;
		struct sockaddr_storage addr;
		char ipstr[INET6_ADDRSTRLEN];
		int port;
		len = sizeof(addr);

		getpeername(listen_socket, (struct sockaddr*)&addr, &len);

		// multicast de ipv4
		if (addr.ss_family == AF_INET) // AF_INET define escutar para TCP e UDP
		{
			struct sockaddr_in *s = (struct sockaddr_in *)&addr;
			port = ntohs(s->sin_port);
			inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
		}

		// criar uma ligação e conectar ao cliente através de uma thread na socket respectiva
		dlg->ligacoes.push_back(new Ligacao(new CThreadConexao(dlg, listen_socket), listen_socket));

		dlg->EscreverMsg(L"Cliente conectado.");
	}
}

// a limpeza tem de ser chamada manualmente pois quando a thread termina a execução pára
void CThreadServidor::Limpar()
{
	shutdown(server_socket, SD_SEND);
	closesocket(server_socket);

	shutdown(listen_socket, SD_SEND);
	closesocket(listen_socket);
}
