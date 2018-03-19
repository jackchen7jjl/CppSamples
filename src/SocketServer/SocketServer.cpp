
//----------------------------------------------------------------- 阻塞模式--------------------------------------------------------------------------
//#include <stdio.h>    
//#include <winsock2.h>    
//
//#pragma comment(lib,"ws2_32.lib")    
//
//int main(int argc, char* argv[])
//{
//	初始化WSA    
//	WORD sockVersion = MAKEWORD(2, 2);
//	WSADATA wsaData;
//	if (WSAStartup(sockVersion, &wsaData) != 0)
//	{
//		return 0;
//	}
//
//	创建套接字    
//	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (slisten == INVALID_SOCKET)
//	{
//		printf("socket error !");
//		return 0;
//	}
//
//	绑定IP和端口    
//	sockaddr_in sin;
//	sin.sin_family = AF_INET;
//	sin.sin_port = htons(8888);
//	sin.sin_addr.S_un.S_addr = inet_addr("168.168.127.21");// INADDR_ANY;
//	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
//	{
//		printf("bind error !");
//	}
//
//	开始监听    
//	if (listen(slisten, 5) == SOCKET_ERROR)
//	{
//		printf("listen error !");
//		return 0;
//	}
//
//	循环接收数据    
//	SOCKET sClient;
//	sockaddr_in remoteAddr;
//	int nAddrlen = sizeof(remoteAddr);
//	char revData[255];
//	while (true)
//	{
//		printf("等待连接...\n");
//		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
//		if (sClient == INVALID_SOCKET)
//		{
//			printf("accept error !");
//			continue;
//		}
//		printf("接受到一个连接：%s \r\n", inet_ntoa(remoteAddr.sin_addr));
//
//		接收数据    
//		int ret = recv(sClient, revData, 255, 0);
//		if (ret > 0)
//		{
//			revData[ret] = 0x00;
//			printf(revData);
//		}
//
//		发送数据    
//		const char * sendData = "你好，TCP客户端！\n";
//		send(sClient, sendData, strlen(sendData), 0);
//		closesocket(sClient);
//	}
//
//	closesocket(slisten);
//	WSACleanup();
//	return 0;
//}



//-------------------------------------------------------------非阻塞模式------------------------------------------------------------------------------
//来源：http://blog.csdn.net/ithzhang/article/details/8274596

#include"windows.h"  
#include<iostream>  
#include<list>  
#include"CClient.h"  
#pragma comment(lib,"wsock32.lib")  

HANDLE hAcceptHandle;
HANDLE hCleanHandle;
HANDLE hEvent;
SOCKET servSocket;
CRITICAL_SECTION cs;
bool IsServerRunning;
std::list<CClient*> clientlist;//该链表中存储与服务器建立的各连接。清理线程将执行对此链表进行删除操作。  

bool InitMemember();//初始化成员变量。  
bool InitSocket();//初始化套接字，设置为非阻塞模式。绑定并监听。  
bool StartService();//开始运行接收客户端请求线程。</span><span style="font-size:18px;">  
bool StopService();//终止服务器运行。  
DWORD WINAPI CleanThread(void*param);//资源清理线程。  
DWORD WINAPI AcceptThread(void*param);//接受客户端请求线程。  


int main(int argc, char**argv)
{
	InitMemember();
	InitSocket();
	do
	{
		char c;
		std::cout << "请选择操作：" << std::endl;

		std::cin >> c;
		if (c == 'e')
		{
			std::cout << "即将退出服务器程序。" << std::endl;
			StopService();
		}
		else if (c == 'y')
		{
			if (IsServerRunning)
			{
				std::cout << "服务器已经开启，请不要重复开启！！" << std::endl;

			}
			else
			{
				StartService();
			}


		}
		else if (c == 'n')
		{
			if (!IsServerRunning)
			{
				std::cout << "服务器未开启，无法关闭！！" << std::endl;

			}
			else
			{
				StopService();

			}
		}
		else
		{

		}
		getchar();
	} while (IsServerRunning);

	Sleep(3000);
	WaitForSingleObject(CleanThread, INFINITE);


	return 0;
}

bool InitMemember()
{
	std::cout << "初始化变量。" << std::endl;

	IsServerRunning = false;
	hEvent = NULL;
	hCleanHandle = NULL;
	hAcceptHandle = NULL;
	InitializeCriticalSection(&cs);
	servSocket = INVALID_SOCKET;
	return 0;
}

bool InitSocket()
{
	std::cout << "初始化套接字。" << std::endl;

	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	servSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (servSocket == INVALID_SOCKET)
	{
		return false;
	}
	unsigned long ul = 1;
	int r = ioctlsocket(servSocket, FIONBIO, &ul);
	if (r == SOCKET_ERROR)
	{
		return false;
	}
	sockaddr_in addr;
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.S_un.S_addr = inet_addr("168.168.127.21");// INADDR_ANY;

	r = bind(servSocket, (sockaddr*)&addr, sizeof(addr));
	if (r == SOCKET_ERROR)
	{
		return false;
	}
	int ret = listen(servSocket, 10);
	if (ret == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}

bool StartService()
{
	std::cout << "开启服务器。" << std::endl;

	IsServerRunning = true;

	hAcceptHandle = CreateThread(NULL, 0, AcceptThread, NULL, 0, NULL);
	if (hAcceptHandle == NULL)
	{
		return false;
	}
	CloseHandle(hCleanHandle);
	CloseHandle(hAcceptHandle);
}

bool StopService()
{
	std::cout << "关闭服务器。" << std::endl;
	hCleanHandle = CreateThread(NULL, 0, CleanThread, NULL, 0, NULL);
	if (hCleanHandle == NULL)
	{
		std::cout << "清理线程创建失败！" << std::endl;
		return false;
	}
	IsServerRunning = false;
	return 0;
}

DWORD WINAPI CleanThread(void*param)
{
	std::cout << "资源清理线程已运行" << std::endl;
	//中断所有连接。退出所有接收和发送线程循环。各线程将会退出。  
	for (std::list<CClient*>::iterator iter = clientlist.begin(); iter != clientlist.end(); iter++)
	{
		(*iter)->DisConnect();
	}
	Sleep(100);
	for (std::list<CClient*>::iterator iter = clientlist.begin(); iter != clientlist.end(); iter++)
	{
		delete *iter;
	}
	clientlist.clear();
	SetEvent(hEvent);
	std::cout << "资源清理完毕，资源清理线程退出！！" << std::endl;
	return 0;
}

DWORD WINAPI AcceptThread(void*param)
{
	std::cout << "接受客户端连接线程开始运行。" << std::endl;

	while (IsServerRunning)
	{
		sockaddr_in addr;
		SOCKET s;
		int len = sizeof(addr);
		s = accept(servSocket, (sockaddr*)&addr, &len);
		if (s == SOCKET_ERROR)
		{
			int r = WSAGetLastError();
			if (r == WSAEWOULDBLOCK)
			{
				//std::cout<<"未收到客户端的连接请求。"<<std::endl;  

				Sleep(1000);
				continue;
			}
			else
			{
				std::cout << "未知错误，接受客户端连接线程退出。" << std::endl;
				getchar();
				return false;
			}
		}
		else//收到客户端请求。  
		{
			std::cout << "收到客户端的连接请求。" << std::endl;

			CClient*pClient = new CClient(s, addr);
			pClient->startRunning();//该链接接受和发送线程开始执行。  
			clientlist.push_back(pClient);
		}
	}
	std::cout << "接受客户端连接线程退出。" << std::endl;

	return 0;
}