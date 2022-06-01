#pragma once
#include<winsock.h>
#include<cstdio>
#pragma comment(lib,"ws2_32.lib")
#pragma error(disable:4996)
using namespace std;
class Serve {
private:
	char m_serve_name[155];//服务器主机名
	char* m_serve_localip;//服务器本地IP

	/*
	返回值：int型
			-1表示初始化套接字库失败
			0表示套接字库版本号不符
			1表示创建成功
	功能：创建套接字
	*/
	int initialization() {
		int i = -1;
		WORD w_req = MAKEWORD(2, 2);//版本号
		WSADATA wsadata;
		
		//获取主机名与服务端IP地址(本地)
		PHOSTENT hostinfo;
		WSAStartup(MAKEWORD(2, 2), &wsadata);
		gethostname(m_serve_name, sizeof(m_serve_name));
		hostinfo = gethostbyname(m_serve_name);
		m_serve_localip = inet_ntoa(*(struct in_addr*)hostinfo->h_addr_list[0]);
		
		int err;
		err = WSAStartup(w_req, &wsadata);
		if (err != 0) 
			return i; //初始化套接字库失败！
		
		else 
			++i;//初始化套接字库成功！

		//检测版本号
		if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
			WSACleanup();
			return i;//套接字库版本号不符！
		}
		else 
			++i;//套接字库版本号符合！
		return i;
		
	}
	
	SOCKET s_server;
	SOCKET s_accept;
	SOCKADDR_IN server_addr;
	SOCKADDR_IN *accept_addr;

	char m_local_ip[100];
	char *m_return_mes;
	int m_number_client = 0;
	
public:
	Serve(const int& local_port, const int& number_client):m_number_client(number_client) {
		initialization();
		accept_addr = new SOCKADDR_IN[m_number_client];
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.S_un.S_addr = inet_addr(m_serve_localip);
		server_addr.sin_port = htons(local_port);
		s_server = socket(AF_INET, SOCK_STREAM, 0);
	}
	~Serve() {
		//关闭套接字
		closesocket(s_server);
		closesocket(s_accept);

		//释放DLL资源
		WSACleanup();

		delete[]accept_addr;
	}
	bool set_status_listen() {//设置监听状态
		if (bind(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
			printf("套接字绑定失败！");
			WSACleanup();
			return false;
		}
		else {}//套接字绑定成功！
		char s[50];
		strcat(s, "1");
		if (listen(s_server, SOMAXCONN) < 0) {
			printf("设置监听状态失败！");
			WSACleanup();
			return false;
		}
		else {
			printf("服务端正在监听连接，请稍候....\n");//设置监听状态成功！
			return true;
		}
	}
	bool handshake() {
		//接受连接请求
		for (int i = 0; i < m_number_client; i++) {
			int len = sizeof(SOCKADDR);
			s_accept = accept(s_server, (SOCKADDR*)&accept_addr[i], &len);
			if (s_accept == SOCKET_ERROR) {
				printf("%d号连接失败！",i+1);
				WSACleanup();
				return false;
			}
			else {
				send_mes("Wait for other ");
				printf("%d号连接成功，IP: %s,Port: %d\n", i + 1, inet_ntoa(accept_addr[i].sin_addr), ntohs(accept_addr[i].sin_port));
			}//连接成功！
		}
		printf("所有连接建立，准备接受数据");
		return true;
	}
	//必须为char*类型
	template <typename T>
	bool accept_mes(T& recv_buf) {//接收数据
		int recv_len = recv(s_accept, recv_buf, sizeof(T) / sizeof(*recv_buf), 0);
		if (recv_len < 0) 
			return false;//接受失败！
		return true;
		
	}
	
	//必须为char*类型
	template <typename T>
	bool send_mes(T &send_buf) {
		//sendto(s_accept, send_buf, sizeof(T) / sizeof(*send_buf),);
		int send_len = send(s_accept, send_buf, sizeof(T) / sizeof(*send_buf), 0);
		if (send_len < 0) {
			printf( "发送失败！");
			return false;
		}
		return true;
	}
	const char* get_serve_name() {
		return m_serve_name;
	}
	const char* get_local_ip() {
		return m_serve_localip;
	}
};
