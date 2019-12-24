#include <WinSock2.h>
#include <iostream>
#include <fstream>
#include "CBlockingSocket.h"

using namespace std;

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		cout << "eorror: Client.exe 192.168.0.194 8888" << endl;
		return -1;
	}

	CBlockingSocket BlockingSocket = CBlockingSocket();
	if (BlockingSocket.Open(argv[1], argv[2]))
	{
		cout << "Connection established to remote Server at " << argv[1] << ":" << argv[2] << endl;
		cout << "Input requested file path: ";
		BYTE filename[100];
		cin >> filename;
		if (BlockingSocket.Send(filename, 100))
		{
			cout << "  Requesting file on the server: " << filename << endl;
			cout << "  1.save the file to disk" << endl;
			cout << "  2.print out on the console" << endl;
			cout << "  Input your choise:";
			int choose;
			cin >> choose;
			cout << "     =========================================" << endl;
			if (choose == 1)
			{
				char filename2[100] = { 0 };
				cout << "  Input save path: ";
				cin >> filename2;
				cout << "  Receiving file " << filename << endl;
				fstream fs;
				char recvBuf[201] = { 0 };
				fs.open(filename2, ios::out | ios::binary);
				int filerecvd = 0;
				int txtlen = 0;
				while (filerecvd != -1)
				{
					filerecvd = BlockingSocket.Recv(recvBuf, sizeof(recvBuf));
					if (filerecvd != -1)
					{
						cout << "  Received " << filerecvd << " bytes." << endl;
						fs.write(recvBuf, filerecvd);
						txtlen = txtlen + filerecvd;
					}
				}
				cout << " Totally Received " << txtlen << " bytes." << endl;
			}
			else if (choose == 2) {

				int recvLen = 0;
				BYTE recvBuf[201] = { 0 };
				int len = 0;
				while ((len = BlockingSocket.Read(recvBuf, 200)) != -1 && len != 0)
				{
					recvLen += len;
					cout << recvBuf;
				}
				cout << endl << "     =========================================" << endl;
				cout << "  Received " << recvLen << " bytes" << endl;
			}
		}
	}

	return 0;
}