#pragma once  
#include<iostream>  
#include"windows.h"  
#include"time.h"  
class CClient
{
public:
	CClient(void);
	CClient(SOCKET s, sockaddr_in addr);
	~CClient(void);
public:
	bool IsConnected();//�ж������Ƿ��жϡ�  
	bool DisConnect();//�ж�������������ӡ�  
	bool calc();//���㵱ǰʱ�䣬�����Ƶ����ͻ������ڡ�  
	bool startRunning();//��ʼ���з��ͺͽ����̡߳�  
	static DWORD WINAPI sendThread(void*param);//�����߳���ں�����  
	static DWORD WINAPI recvThread(void*param);//�����߳���ں�����  
private:
	HANDLE m_hSendThread;//�����߳̾����  
	HANDLE m_hRecvThread;//�����߳̾����  
	HANDLE m_hEvent;//�����̺߳ͽ����߳�ͬ���¼����󡣽��տͻ��������֪ͨ�����̷߳��͵�ǰʱ�䡣  
	SOCKET m_socket;//��ͻ��������׽��֡�  
	sockaddr_in m_addr;//�ͻ��˵�ַ��  
	bool m_IsConnected;
	char *m_pRecvData;//���ջ�������  
	char *m_pSendData;//���ͻ�������  
	bool m_IsSendData;//����ֻ�н��յ��ͻ�����������Ҫ���ͣ��ñ��������Ƿ������ݡ�  
};