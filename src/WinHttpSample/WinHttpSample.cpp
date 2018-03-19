#include <iostream>
#include <stdarg.h>
#include <Windows.h>
#include <winhttp.h>
#include<string.h>
#include<codecvt>

#include "HttpClientSyn.h"
#include "HttpTransByGet.h"
#include "HttpTransByPost.h"
#include<random>
#include <sstream>  

#include "json.h"

using namespace std;

inline int getRandom()
{
	static random_device rd;
	static default_random_engine e(rd());
	static uniform_real_distribution<float> u(0, 1000000000);
	return u(e);
}

int WStringReplace(std::wstring& strContent, std::wstring& strReplace, std::wstring & strDest)
{

	while (true)
	{
		size_t pos = strContent.find(strReplace);
		if (pos != std::wstring::npos)
		{
			WCHAR pBuf[1] = {  L'\0'};
			strContent.replace(pos, strReplace.length(), pBuf, 0);
			strContent.insert(pos, strDest);
		}
		else
		{
			break;
		}
	}

	return 0;
}

int main()
{	

	//std::string hostname_u8;
	//hostname = convert.from_bytes(hostname_u8);
	//filename = convert.from_bytes(filename_u8 + 1);

	//wstring url = L"http://www.evil3d.cn/demos/engine/index.html?user=jack&pwd=k89";

	//CHttpTransByGet httpClient;

	//httpClient.TransmiteData(url,EType::eGet,2000);

	//LPBYTE lpBuffer = new BYTE[1024*1024];
	//DWORD dwBufferSize;

	//httpClient.ReceiveData(lpBuffer, dwBufferSize);


	std::string u8s = u8"abc中国";
	const char *u8sC = u8s.c_str();

	int len = u8s.length();
	for (int i = 0; i < len; i++)
	{
		//61,62,63,e4,b8,ad,e5,9b,bd
		std::cout << hex << (short)((unsigned char)(u8sC[i])) << ",";
	}

	std::wstring ws = L"abc中国";
	len = ws.length();
	
	Json::Value jsonRoot; //定义根节点
	jsonRoot["openID"] = u8s;

	Json::FastWriter fastWsriter;
	fastWsriter.omitEndingLineFeed();
	string ms = fastWsriter.write(jsonRoot);

	std::cout << std::endl;

	len = ms.length();
	for (int i = 0; i < len; i++)
	{
		//61,62,63,e4,b8,ad,e5,9b,bd
		std::cout << hex << (short)((unsigned char)(ms[i])) << ",";
		//std::cout << ms[i] << ",";
	}

	int ranin = getRandom();

	wostringstream oss;
	oss << ranin;

	wstring raninStr = oss.str();
	wcout << raninStr << endl;


	wstring url = L"http://123.207.255.250:8087/zgame/?m=snake&a=snake_require";
	CHttpTransByPost httpClient;

	VecStParam vsp;
	StParam st;
	st.wstrKey = L"msg_id";
	st.wstrValue = L"30001";
	vsp.push_back(st);

	

	StParam st2;
	st2.wstrKey = L"msg";
	wstring msgValue = L"{\"openID\":\"337778176\",\"openKey\":\"\",\"pfID\":0,\"version\":\"3.5.0\",\"lastLoginTimeStamp\":0,\"sign\":\"\",\"bundleIdentifier\":\"unity.MOF.蛇蛇争霸\"}";
	wstring openID = L"337778176";

	msgValue.c_str();
	WStringReplace(msgValue, openID, raninStr);

	st2.wstrValue = msgValue;
	vsp.push_back(st2);

	httpClient.TransDataToServer(url,2000, vsp);

	LPBYTE lpBuffer = new BYTE[1024 * 1024];
	DWORD dwBufferSize;
	httpClient.ReceiveData(lpBuffer, dwBufferSize);


	/*int ranin = getRandom();

	wostringstream oss;
	oss << ranin;

	wstring raninStr = oss.str();
	wcout << raninStr << endl;


	wstring url = L"http://123.207.255.250:8087/zgame/?m=snake&a=snake_require";
	CHttpTransByGet httpClient;

	VecStParam vsp;
	StParam st;
	st.wstrKey = L"msg_id";
	st.wstrValue = L"30001";
	vsp.push_back(st);

	StParam st2;
	st2.wstrKey = L"msg";
	wstring msgValue = L"{\"openID\":\"337778176\",\"openKey\":\"\",\"pfID\":0,\"version\":\"3.5.0\",\"lastLoginTimeStamp\":0,\"sign\":\"\",\"bundleIdentifier\":\"unity.MOF.蛇蛇争霸\"}";
	wstring openID = L"337778176";

	msgValue.c_str();
	WStringReplace(msgValue, openID, raninStr);

	st2.wstrValue = msgValue;
	vsp.push_back(st2);

	url += L"&msg_id=30001";
	url += L"&msg=";
	url += msgValue;

	VecStParam vsp2;
	httpClient.TransDataToServer(url,2000, vsp2);

	LPBYTE lpBuffer = new BYTE[1024 * 1024];
	DWORD dwBufferSize;
	httpClient.ReceiveData(lpBuffer, dwBufferSize);*/

	//int ranin = getRandom();
	//string raninStr = to_string(ranin);

	//string url = u8"http://123.207.255.250:8087/zgame/?m=snake&a=snake_require&msg_id=30001";
	//CHttpTransByGet httpClient;

	//string msgValue = u8"{\"openID\":\"337778176\",\"openKey\":\"\",\"pfID\":0,\"version\":\"3.5.0\",\"lastLoginTimeStamp\":0,\"sign\":\"\",\"bundleIdentifier\":\"unity.MOF.蛇蛇争霸\"}";
	//string openID = u8"337778176";

	//msgValue = msgValue.replace(msgValue.find(openID), 1, raninStr); //从第一个@位置替换第一个@为空  

	//url += u8"&msg=";
	//url += msgValue;

	//std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
	//wstring wurl = convert.from_bytes(url);

	//VecStParam vsp2;
	//httpClient.TransDataToServer(wurl, 2000, vsp2);

	//LPBYTE lpBuffer = new BYTE[1024 * 1024];
	//DWORD dwBufferSize = 1024 * 1024;
	//httpClient.ReceiveData(lpBuffer, dwBufferSize);

	//std::string strJson((char*)lpBuffer);
	//Json::Reader reader;
	//Json::Value value;

	//if (reader.parse(strJson, value))
	//{
	//	string authKey = value["authKey"].asString();
	//	std::cout << authKey << std::endl;
	//}

	std::cin.get();
	std::cin.get();
	return 0;
}