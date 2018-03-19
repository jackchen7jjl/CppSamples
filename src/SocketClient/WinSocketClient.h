#pragma once
#include <string>
#include <Windows.h>
#pragma  comment (lib,"wsock32.lib")  

class WinSocketClient
{
public:
	WinSocketClient() {};
	~WinSocketClient() {};

	bool Connect(std::string serverIP, WORD serverPort);
	void Send(std::string msg);
	void Send(unsigned char *data, int dataLen);

	void TryReceiveData();

private:
	SOCKET _clientSocket;
	bool _isConnected = false;
};