//#include<WINSOCK2.H>  
//#include<STDIO.H>  
//#include<iostream>  
//#include<cstring>  
//using namespace std;
//#pragma comment(lib, "ws2_32.lib")  
//
//int main()
//{
//	WORD sockVersion = MAKEWORD(2, 2);
//	WSADATA data;
//	if (WSAStartup(sockVersion, &data) != 0)
//	{
//		return 0;
//	}
//	while (true) {
//		SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//		if (sclient == INVALID_SOCKET)
//		{
//			printf("invalid socket!");
//			return 0;
//		}
//
//		sockaddr_in serAddr;
//		serAddr.sin_family = AF_INET;
//		serAddr.sin_port = htons(8888);
//		serAddr.sin_addr.S_un.S_addr = inet_addr("168.168.127.21");
//
//		if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
//		{  //连接失败   
//			printf("connect error !");
//			closesocket(sclient);
//			return 0;
//		}
//
//		string data = "客户端请求abc";
//		const char * sendData;
//		sendData = data.c_str();   //string转const char*   
//								   //char * sendData = "你好，TCP服务端，我是客户端\n";  
//		send(sclient, sendData, strlen(sendData), 0);
//		//send()用来将数据由指定的socket传给对方主机  
//		//int send(int s, const void * msg, int len, unsigned int flags)  
//		//s为已建立好连接的socket，msg指向数据内容，len则为数据长度，参数flags一般设0  
//		//成功则返回实际传送出去的字符数，失败返回-1，错误原因存于error   
//
//		char recData[255];
//		int ret = recv(sclient, recData, 255, 0);
//		if (ret>0) {
//			recData[ret] = 0x00;
//			printf(recData);
//		}
//		closesocket(sclient);
//	}
//
//
//	WSACleanup();
//	return 0;
//
//}



//-------------------------------------------------------------非阻塞模式------------------------------------------------------------------------------
//来源：http://blog.csdn.net/ithzhang/article/details/8274596

//#include<iostream>  
//#include"windows.h"  
//#pragma  comment (lib,"wsock32.lib")  
//SOCKET clientSocket;
//HANDLE hRecvThread;
//HANDLE hSendThread;
//bool IsConnected;
//char sendBuff[1024];
//char recvBuff[1024];
//HANDLE hEvent;
//HANDLE hSendEvent;
//bool InitMember();
//bool InitSocket();
//bool startConnect();
//DWORD WINAPI recvThread(void*param);
//DWORD WINAPI sendThread(void*param);
//
//
//int main(int argc, char**argv)
//{
//	InitMember();
//	InitSocket();
//	startConnect();
//	char buff[256];
//	while (IsConnected)
//	{
//		memset(buff, 0, 256);
//		std::cout << "请输入表达式：";
//		std::cin >> sendBuff;
//		if (!strcmp(buff, "exit"))
//		{
//			std::cout << "即将推出！" << std::endl;
//			IsConnected = false;
//			HANDLE hHandleArray[2];
//			hHandleArray[0] = hRecvThread;
//			hHandleArray[1] = hSendThread;
//			SetEvent(hEvent);
//			WaitForMultipleObjects(2, hHandleArray, true, INFINITE);
//			getchar();
//			return 0;
//		}
//		else
//		{
//			SetEvent(hEvent);
//		}
//	}
//
//
//	return 0;
//}
////初始化套接字。  
//bool InitSocket()
//{
//	WSAData wsadata;
//	WSAStartup(MAKEWORD(2, 2), &wsadata);
//	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
//	if (clientSocket == INVALID_SOCKET)
//	{
//		return false;
//	}
//	unsigned long ul = 1;
//	ioctlsocket(clientSocket, FIONBIO, &ul);
//
//	sockaddr_in addr;
//	addr.sin_family = AF_INET;
//	addr.sin_port = htons(8888);
//	addr.sin_addr.S_un.S_addr = inet_addr("168.168.127.21");
//
//	while (true)
//	{
//		int ret = connect(clientSocket, (sockaddr*)&addr, sizeof(addr));
//		if (ret == SOCKET_ERROR)
//		{
//			int r = WSAGetLastError();
//			if (r == WSAEWOULDBLOCK || r == WSAEINVAL)
//			{
//				Sleep(20);
//				continue;
//			}
//			else if (r == WSAEISCONN)//套接字原来已经连接！！  
//			{
//				break;
//			}
//			else
//			{
//				std::cout << "发生错误" << std::endl;
//				return false;
//			}
//		}
//		if (ret == 0)
//		{
//			break;
//		}
//	}
//	IsConnected = true;
//	return true;
//}
//
//bool InitMember()
//{
//	hSendThread = NULL;
//	hRecvThread = NULL;
//	hEvent = CreateEvent(NULL, true, false, NULL);
//	hSendEvent = CreateEvent(NULL, true, false, NULL);
//	IsConnected = false;
//	memset(recvBuff, 0, 1024);
//	memset(sendBuff, 0, 1024);
//	return true;
//}
////创建接收和发送数据线程。  
//bool startConnect()
//{
//	hRecvThread = CreateThread(NULL, 0, recvThread, NULL, 0, NULL);
//	if (hRecvThread == NULL)
//	{
//		return false;
//	}
//	hSendThread = CreateThread(NULL, 0, sendThread, NULL, 0, NULL);
//	if (hSendThread == NULL)
//	{
//		return false;
//	}
//	return 0;
//}
////接收数据线程入口函数。  
//DWORD WINAPI recvThread(void*param)
//{
//	std::cout << "数据接收线程已开始运行！" << std::endl;
//	while (IsConnected)
//	{
//		WaitForSingleObject(hSendEvent, INFINITE);
//		//ResetEvent(hSendEvent);  
//		int ret = recv(clientSocket, recvBuff, 1024, 0);
//		if (ret == SOCKET_ERROR)
//		{
//			int r = WSAGetLastError();
//			if (r == WSAEWOULDBLOCK)
//			{
//				//std::cout<<"没有收到服务器返回的数据！！"<<std::endl;  
//				Sleep(10);
//				continue;
//			}
//			else if (r == WSAENETDOWN)
//			{
//				std::cout << "数据发送失败！" << std::endl;
//				return false;
//			}
//		}
//		else
//		{
//			std::cout << "接收成功！" << std::endl;
//
//			std::cout << recvBuff << std::endl;
//		}
//	}
//	return true;
//}
////发送数据线程入口函数。  
//DWORD WINAPI sendThread(void*param)
//{
//	std::cout << "数据发送线程已开始运行！！" << std::endl;
//
//	while (IsConnected)//是否与服务器连接  
//	{
//		WaitForSingleObject(hEvent, INFINITE);//等待接收数据线程通知。  
//		ResetEvent(hEvent);
//		int ret = send(clientSocket, sendBuff, 256, 0);
//		if (ret == SOCKET_ERROR)
//		{
//			int r = WSAGetLastError();
//			if (r == WSAEWOULDBLOCK)
//			{
//				std::cout << "数据发送失败！" << std::endl;
//				Sleep(20);
//				continue;
//			}
//			else
//			{
//				std::cout << "数据发送失败！" << std::endl;
//				break;
//			}
//		}
//		else
//		{
//			std::cout << "发送成功！！" << std::endl;
//			SetEvent(hSendEvent);
//		}
//	}
//	return true;
//}


//-------------------------------------------------------------非阻塞模式2单线程------------------------------------------------------------------------------
#include<iostream>  
#include "WinSocketClient.h"
#include"windows.h"  

WinSocketClient socketClient;

int main(int argc, char**argv)
{
	bool result = socketClient.Connect("192.168.1.103",8888);

	if (!result)
		return 1;

	int id = 0;
	while (true)
	{
		std::string msg = "消息" + std::to_string(id++);

		socketClient.Send(msg);

		socketClient.TryReceiveData();

		Sleep(1000);
	}


	return 0;
}