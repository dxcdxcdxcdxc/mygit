//winsock 2.2
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

class CBlockingSocket
{
private:
	SOCKET m_socket;
	struct addrinfo *m_result;
public:
	CBlockingSocket(void);  // create socket
	CBlockingSocket(SOCKET socket);
	virtual		~CBlockingSocket(void);
	BOOL		Open();  // connect socket
	BOOL		Close();  // close socket
	BOOL		Bind();  // connect socket
	BOOL		Listen(const char *port);  // listen socket
	BOOL        Connect();
	CBlockingSocket Accept(struct sockaddr &their_addr);// accept the client socket
	BOOL		Send(BYTE *s, UINT count);  // send package
	INT			Read(BYTE *s, UINT count);  // receive package
	int HintsAndResult(const char *ip, const char *port);
	static int Initialize();
	static void Cleanup();
};


