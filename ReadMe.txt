=====================================================================
Data: 7/10/2017
Turma: TPSI-CS-0117
Formando: Paulo Pocinho
Formador: Dário Quental

=====================================================================
PROJECTO

/bin-x64 -> executáveis 64 bits
/bin-x86 -> executáveis 32 bits
/chat-cliente -> código do projecto cliente
/chat-wtl -> código do projecto servidor
/wtl -> bibliotecas wtl
chat-wtl.sln -> solução de visual studio 2017
ReadMe.txt -> este ficheiro

=====================================================================
UTILIZAÇÃO

Feito em Visual Studio 2017 com as bibliotecas ATL instaladas.

As bibliotecas WTL vem incluidas no projecto (pasta wtl).
São uma extensão às bibliotecas ATL da Microsoft. 

=====================================================================
FUNCIONAMENTO

Correr o executável 'chat-servidor.exe' e clicar em ligar.
Correr clientes com o executável 'chat-cliente.exe'.

O servidor escuta e serve nas ligações de rede disponíveis.
(Ver configurações de placa de rede do computador.)

Para cada cliente, preencher nome, IP de rede onde o servidor se
encontra (IP atribuido a placa de rede ou então 127.0.0.1)
e clicar em ligar.

Se a ligação for feita com sucesso vemos o 'message of the day'.

Para sair da aplicação clicar no botão 'Fechar'.

=====================================================================
BUGS / CAVEATS

Por motivos didáticos, as mensagens têm um limite de 2000 caracteres.


