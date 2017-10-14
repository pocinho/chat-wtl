#include "stdafx.h"
#include "CThreadCliente.h"
#include "MainDialog.h"
#include "Utils.h"

CThreadCliente::CThreadCliente(MainDialog * md, int porta, std::string ip) : dlg(md), m_porta(porta), m_ip(ip)
{
}

CThreadCliente::~CThreadCliente()
{
}

BOOL CThreadCliente::Initialize()
{
	return TRUE;
}

DWORD CThreadCliente::Run()
{
	Ligar();
	return 0;
}

void CThreadCliente::Ligar()
{

	char server_reply[2000];
	int resultado;

	// inicializar winsocket
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// inicializar um socket para ligar ao servidor
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	// inicializar a ligação para escutar respostas do servidor no ip especificado
	inet_pton(AF_INET, m_ip.c_str(), &server.sin_addr.s_addr);
	server.sin_family = AF_INET; // ligações tcp e udp
	server.sin_port = htons(m_porta); // definir porta do servidor

	// Conectar ao servidor
	connect(server_socket, (struct sockaddr *)&server, sizeof(server));

	do
	{
		resultado = recv(server_socket, server_reply, 2000, 0);

		if (resultado == 0 || resultado == -1) // servidor a desligar
		{
			dlg->TerminarLigacao();
			break;
		}
		else
		{
			server_reply[resultado] = '\0';

			// Converter para wchar_t*
			size_t origsize = strlen(server_reply) + 1;
			const size_t newsize = 2000;
			size_t convertedChars = 0;
			wchar_t wcstring[newsize];
			mbstowcs_s(&convertedChars, wcstring, origsize, server_reply, _TRUNCATE);

			std::wstring msg(wcstring);

			// emojis
			SubstituirEmWString(msg, L":)", L"\u263A");
			SubstituirEmWString(msg, L":(", L"\u2639");
			SubstituirEmWString(msg, L"<3", L"\uE006");
			SubstituirEmWString(msg, L":yingyang:", L"\u262F");
			SubstituirEmWString(msg, L":caveira:", L"\u2620");
			SubstituirEmWString(msg, L":radioactive:", L"\u2622");
			SubstituirEmWString(msg, L":star:", L"\uE202");
			SubstituirEmWString(msg, L":up:", L"\uE203");
			SubstituirEmWString(msg, L":snowman:", L"\u26C4");
			SubstituirEmWString(msg, L":check:", L"\u2714");

			dlg->EscreverMsg(msg);
		}
	} while (!IsAborted() && resultado > 0);

	// limpar ligação

	shutdown(server_socket, SD_SEND);
	closesocket(server_socket);
}
