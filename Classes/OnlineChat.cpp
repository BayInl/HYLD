#include"OnlineChat.h"
//==============================负责Socket的变量===================================
WSAData wsaData;
SOCKET servSock;
std::string m_serve_localip;//我的服务器本地IP
std::string m_serve_name;//我的服务器主机名
std::string serve_localip;//要加入的服务器本地IP
int defaultport = atoi(Words.getWord("9984").c_str());//设置我的服务器端口号
int serve_port = atoi(Words.getWord("9984").c_str());//要加入的服务器的端口号
//==============================全局变量区===================================
const int BUFFER_SIZE = 1024;//缓冲区大小
int RECV_TIMEOUT = 10;//接收消息超时
int SEND_TIMEOUT = 10;//发送消息超时
const int WAIT_TIME = 10;//每个客户端等待事件的时间，单位毫秒
int MAX_LINK_NUM = atoi(Words.getWord("MaxConncetNum").c_str());//服务端最大链接数

SOCKET *cliSock;//客户端套接字 0号为服务端
SOCKADDR_IN *cliAddr;//客户端地址
WSAEVENT *cliEvent;//客户端事件 0号为服务端,它用于让程序的一部分等待来自另一部分的信号。例如，当数据从套接字变为可用时，winsock 库会将事件设置为信号状态
int total = 0;//当前已经链接的客服端服务数
struct inf {
	std::string mes;
	bool is_need_update = false;
}message;
inf mymessage;
void OnlineChat::_set_button_back()
{
	button_back = ui::Button::create("back.png", "back.png", "back.png", ui::Widget::TextureResType::PLIST);
	button_back->setAnchorPoint(Vec2(0, 0));
	button_back->setPosition(Vec2(0, 0));
	button_back->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::ENDED:
			//Director::getInstance()->popScene();
			break;
		default:
			break;
		}
		});
	this->addChild(button_back, 1);
}
cocos2d::Scene* OnlineChat::createScene()
{
	return OnlineChat::create();
}

bool OnlineChat::init()
{
	if(!Scene::init())
		return false;
	cliSock = new SOCKET[MAX_LINK_NUM];
	cliAddr = new SOCKADDR_IN[MAX_LINK_NUM];
	cliEvent = new WSAEVENT[MAX_LINK_NUM];
	
	//spritecache->addSpriteFramesWithFile("plist_setting.plist", "plist_setting.png");//第一次载入要加
	GetLocalIpAddress();
	_set_button_back();
	this->scheduleUpdate();	
	button_create_room->setTitleText(Words.getWord("9980"));
	button_create_room->setTitleFontSize(30);
	button_create_room->setTitleColor(Color3B::WHITE);
	button_create_room->setPosition(Vec2(310, 650));
	button_create_room->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			button_join_room->setVisible(false);
			button_create_room->setVisible(false);
			label_show_myip->setVisible(false);
			label_show_myport->setVisible(false);
			outputmes->setVisible(true);
			inputmes->setVisible(true);
			button_send->setVisible(true);
			_line_0->setVisible(true);
			CloseHandle(CreateThread(NULL, 0, socketSeverMainThread, (LPVOID)&servSock, 0, 0));
			break;
		default:
			break;
		}
		});
	this->addChild(button_create_room);


	label_show_myip->setString(Words.getWord("9982") + m_serve_localip);
	label_show_myip->setSystemFontSize(30);
	label_show_myip->setColor(Color3B::WHITE);
	label_show_myip->setPosition(Vec2(400, 700));
	this->addChild(label_show_myip);

	label_show_myport->setString(Words.getWord("9983") + std::to_string(defaultport));
	label_show_myport->setSystemFontSize(30);
	label_show_myport->setColor(Color3B::WHITE);
	label_show_myport->setPosition(Vec2(345, 730));
	this->addChild(label_show_myport);

	
	outputmes->setFontName("楷体");
	outputmes->setPlaceHolder("No new message");
	outputmes->setFontSize(20);
	outputmes->setColor(Color3B::WHITE);
	outputmes->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	outputmes->setPosition(Vec2(240,350));
	outputmes->ignoreContentAdaptWithSize(false);
	outputmes->setTextAreaSize(Size(300, 400));
	outputmes->setVisible(false);
	this->addChild(outputmes); 


	button_join_room->setTitleText(Words.getWord("9981"));
	button_join_room->setTitleFontSize(30);
	button_join_room->setTitleColor(Color3B::WHITE);
	button_join_room->setPosition(Vec2(500, 650));
	button_join_room->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			button_join_room->setVisible(false);
			button_create_room->setVisible(false);
			label_show_myip->setVisible(false);
			label_show_myport->setVisible(false);
			outputmes->setVisible(true);
			inputmes->setVisible(true);
			button_send->setVisible(true);
			_line_0->setVisible(true);
			serve_localip = m_serve_localip;
			CloseHandle(CreateThread(NULL, 0, socketClientMainThread, (LPVOID)&servSock, 0, 0));
		default:
			break;
		}
		});
	this->addChild(button_join_room);


	_line_0 = DrawNode::create();
	_line_0->setLineWidth(5);
	_line_0->drawLine(Vec2(visibleSize.width/2, visibleSize.height),Vec2(visibleSize.width / 2,0),Color4F(14, 24, 14, 1));//竖线
	_line_0->setVisible(false);
	this->addChild(_line_0, 2);
	
	button_send->setTitleText(Words.getWord("9985"));
	button_send->setTitleFontSize(30);
	button_send->setTitleColor(Color3B::WHITE);
	button_send->setPosition(Vec2(900, 28));
	button_send->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:	
			mymessage.is_need_update = true;
			mymessage.mes=Words.getWord("Username")+": " + inputmes->getString();
			if (outputmes->getString().size() > 100)
			{
				outputmes->setString("");
			}
			outputmes->setString(outputmes->getString() + "\n" + mymessage.mes);
			log("%s", mymessage.mes.c_str());
		default:
			break;
		}
		});
	button_send->setVisible(false);
	this->addChild(button_send);


	inputmes->setFontName("楷体");
	inputmes->setPlaceHolder(Words.getWord("9986"));
	inputmes->setFontSize(20);
	inputmes->setColor(Color3B::WHITE);
	inputmes->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	inputmes->setPosition(Vec2(800, 350));
	inputmes->setMaxLengthEnabled(true);
	inputmes->setMaxLength(100);
	inputmes->addClickEventListener([&](Ref* ref)
		{
			dynamic_cast<cocos2d::ui::TextField*>(ref)->setPlaceHolder("");
			dynamic_cast<cocos2d::ui::TextField*>(ref)->setString("");
		});
	inputmes->addEventListener([&](Ref* ref, ui::TextField::EventType type){
		//如果字符超过15个
		if (type == ui::TextField::EventType::INSERT_TEXT){
			auto input = dynamic_cast<cocos2d::ui::TextField*>(ref);
			if (inputmes->getString().length() > 15)
			{
				inputmes->setString(inputmes->getString().substr(0, 15));
			}
			std::string content = input->getString();
			for (char c : content)
			{
				if (c > 127 || c <= 0)//如果输入的是中文，清空内容，并提示输入英文和数字
				{
					input->setString("");
					log("Please input letters and numbers");
					break;
				}
			}
		}
	});
	inputmes->setVisible(false);
	this->addChild(inputmes);
	
	return true;
}
OnlineChat::~OnlineChat()
{
	delete []cliSock ;
	delete []cliAddr ;
	delete []cliEvent ;
}
//获取主机名与服务端IP地址(本地)
void GetLocalIpAddress() {
	WORD w_req = MAKEWORD(2, 2);//版本号
	WSADATA wsadata;

	
	PHOSTENT hostinfo;
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	char temp_serve_name[155] = { 0 };
	gethostname(temp_serve_name, sizeof(temp_serve_name));
	m_serve_name = temp_serve_name;
	hostinfo = gethostbyname(m_serve_name.c_str());
	m_serve_localip = inet_ntoa(*(struct in_addr*)hostinfo->h_addr_list[0]);
	Words.setWord(Words.getWord("9987"), m_serve_localip);
	Words.Store();
	WSACleanup();
}
DWORD WINAPI servEventThread(LPVOID IpParameter) //服务器端线程
{
	//该线程负责处理服务端和各个客户端发生的事件
	//将传入的参数初始化
	SOCKET servSock = *(SOCKET*)IpParameter;//LPVOID为空指针类型，需要先转成SOCKET类型再引用，即可使用传入的SOCKET
	while (1) //不停执行
	{
		for (int i = 0; i < total + 1; i++)//i代表现在正在监听事件的终端
		{
			//若有一个客户端链接，total==1，循环两次，包含客户端和服务端
			//对每一个终端（客户端和服务端），查看是否发生事件，等待WAIT_TIME毫秒
			int index = WSAWaitForMultipleEvents(1, &cliEvent[i], false, WAIT_TIME, 0);

			index -= WSA_WAIT_EVENT_0;//此时index为发生事件的终端下标

			if (index == WSA_WAIT_TIMEOUT || index == WSA_WAIT_FAILED)
				continue;//如果出错或者超时，即跳过此终端

			else if (index == 0)
			{
				WSANETWORKEVENTS networkEvents;
				WSAEnumNetworkEvents(cliSock[i], cliEvent[i], &networkEvents);//查看是什么事件

				//事件选择
				if (networkEvents.lNetworkEvents & FD_ACCEPT)//若产生accept事件（此处与位掩码相与）
				{
					if (networkEvents.iErrorCode[FD_ACCEPT_BIT] != 0)
					{
						message.mes = "An error occurred while connecting. Error code:" + std::to_string(networkEvents.iErrorCode[FD_ACCEPT_BIT]);
						message.is_need_update = true;
						log("An error occurred while connecting. Error code:%d", networkEvents.iErrorCode[FD_ACCEPT_BIT]);
						continue;
					}
					//接受链接
					if (total + 1 < MAX_LINK_NUM)//若增加一个客户端仍然小于最大连接数，则接受该链接
					{
						//total为已连接客户端数量
						int nextIndex = total + 1;//分配给新客户端的下标
						int addrLen = sizeof(SOCKADDR);
						SOCKET newSock = accept(servSock, (SOCKADDR*)&cliAddr[nextIndex], &addrLen);
						if (newSock != INVALID_SOCKET)
						{
							//设置发送和接收时限
							/*setsockopt(newSock, SOL_SOCKET, SO_SNDTIMEO, (const char*) & SEND_TIMEOUT, sizeof(SEND_TIMEOUT));
							setsockopt(newSock, SOL_SOCKET, SO_SNDTIMEO, (const char*) &RECV_TIMEOUT, sizeof(RECV_TIMEOUT));*/
							//给新客户端分配socket
							cliSock[nextIndex] = newSock;
							//新客户端的地址已经存在cliAddr[nextIndex]中了
							//为新客户端绑定事件对象,同时设置监听，close，read，write
							WSAEVENT newEvent = WSACreateEvent();
							WSAEventSelect(cliSock[nextIndex], newEvent, FD_CLOSE | FD_READ | FD_WRITE);
							cliEvent[nextIndex] = newEvent;
							total++;//客户端连接数增加
							log("#%dPlayer(ip:%s) went the chat room, current connections: %d", nextIndex, inet_ntoa(cliAddr[nextIndex].sin_addr),total);
							
							//给所有客户端发送欢迎消息
							char buf[BUFFER_SIZE] = "Players (ip:";
							strcat(buf, inet_ntoa(cliAddr[nextIndex].sin_addr));
							strcat(buf, ")into the chat room");
							message.mes = buf;
							for (int j = i; j <= total; j++)
							{
								send(cliSock[j], buf, sizeof(buf), 0);
							}
							message.is_need_update = true;
						}
					}

				}
				else if (networkEvents.lNetworkEvents & FD_CLOSE)//客户端被关闭，即断开连接
				{

					//i表示已关闭的客户端下标
					total--;
					log("#%dPlayer(ip:%s) left the chat room, current connections: %d", i, inet_ntoa(cliAddr[i].sin_addr), total);
					//释放这个客户端的资源
					closesocket(cliSock[i]);
					WSACloseEvent(cliEvent[i]);

					//数组调整,用顺序表删除元素
					for (int j = i; j < total; j++)
					{
						cliSock[j] = cliSock[j + 1];
						cliEvent[j] = cliEvent[j + 1];
						cliAddr[j] = cliAddr[j + 1];
					}
					//给所有客户端发送退出聊天室的消息
					char buf[BUFFER_SIZE] = "Player（IP：";
					strcat(buf, inet_ntoa(cliAddr[i].sin_addr));
					strcat(buf, ")left the chat room");
					message.mes = buf;
					for (int j = 1; j <= total; j++)
					{
						send(cliSock[j], buf, sizeof(buf), 0);
					}
					message.is_need_update = true;
				}
				else if (networkEvents.lNetworkEvents & FD_READ)//接收到消息
				{
					char buffer[BUFFER_SIZE] = { 0 };//字符缓冲区，用于接收和发送消息
					char buffer2[BUFFER_SIZE] = { 0 };

					for (int j = 1; j <= total; j++)
					{
						int nrecv = recv(cliSock[j], buffer, sizeof(buffer), 0);//nrecv是接收到的字节数
						if (nrecv > 0)//如果接收到的字符数大于0
						{
							sprintf(buffer2, "[#%d]%s", j, buffer);
							//在服务端显示
							message.mes = buffer2;
							//在其他客户端显示（广播给其他客户端）
							for (int k = 1; k <= total; k++)
							{
								if (k == j)
									continue;
								send(cliSock[k], buffer2, sizeof(buffer), 0);
							}
							message.is_need_update = true;
						}
					}
				}
			}
		}
	}
	return 0;
} // 服务端处理线程

DWORD WINAPI socketSeverMainThread(LPVOID IpParameter) {//服务端处理线程
	
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	servSock = socket(AF_INET, SOCK_STREAM, 0);//面向网路的流式套接字

	SOCKADDR_IN servAddr; //sockaddr_in 是internet环境下套接字的地址形式
	servAddr.sin_family = AF_INET;//和服务器的socket一样，sin_family表示协议簇，一般用AF_INET表示TCP/IP协议。
	servAddr.sin_addr.S_un.S_addr = inet_addr(m_serve_localip.c_str());//服务端地址设置为本地回环地址
	servAddr.sin_port = htons(defaultport);//host to net short 端口号设置为8888

	//4、绑定服务端的socket和打包好的地址
	bind(servSock, (SOCKADDR*)&servAddr, sizeof(servAddr));
	//4.5给服务端sokect绑定一个事件对象，用来接收客户端链接的事件
	WSAEVENT servEvent = WSACreateEvent();//创建一个人工重设为传信的事件对象
	WSAEventSelect(servSock, servEvent, FD_ALL_EVENTS);//绑定事件对象，并且监听所有事件

	cliSock[0] = servSock;
	cliEvent[0] = servEvent;
	//5、开启监听
	listen(servSock, 10);//监听队列长度为10

	//6、创建接受链接的线程
	//不需要句柄所以直接关闭

	CloseHandle(CreateThread(NULL, 0, servEventThread, (LPVOID)&servSock, 0, 0));
	//需要让主线程一直运行下去
	//发送消息给全部客户端
	while (1)
	{
		if (mymessage.is_need_update == true) {
			mymessage.is_need_update = false;
			for (int i = 1; i <= total; i++)
			{
				send(cliSock[i], mymessage.mes.c_str(), sizeof(mymessage.mes.c_str()), 0);
			}
		}
	}
	WSACleanup();
}

DWORD __stdcall socketClientMainThread(LPVOID IpParameter)
{
	//1、初始化socket库
	WSADATA wsaData;//获取版本信息，说明要使用的版本
	WSAStartup(MAKEWORD(2, 2), &wsaData);//MAKEWORD(主版本号, 副版本号)

	//2、创建socket
	SOCKET cliSock = socket(AF_INET, SOCK_STREAM, 0);//面向网路的流式套接字,第三个参数代表自动选择协议

	//3、打包地址
	//客户端
	SOCKADDR_IN cliAddr = { 0 };
	cliAddr.sin_family = AF_INET;
	cliAddr.sin_addr.s_addr = inet_addr("127.101.101.1");//IP地址m_serve_localip.c_str()
	cliAddr.sin_port = htons(defaultport);//端口号
	//服务端
	SOCKADDR_IN servAddr = { 0 };
	servAddr.sin_family = AF_INET;//和服务器的socket一样，sin_family表示协议簇，一般用AF_INET表示TCP/IP协议。
	servAddr.sin_addr.S_un.S_addr = inet_addr(serve_localip.c_str());//服务端地址设置为本地回环地址
	servAddr.sin_port = htons(serve_port);
	if (connect(cliSock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
		log("error,the error code is%d", WSAGetLastError());

	//创建接受消息线程
	CloseHandle(CreateThread(NULL, 0, recvMsgThread, (LPVOID)&cliSock, 0, 0));
	while (1)
	{
		if (mymessage.is_need_update) {
			mymessage.is_need_update = false;
			if (mymessage.mes == "quit")//若输入“quit”，则退出聊天室
				break;
			send(cliSock, mymessage.mes.c_str(), sizeof(mymessage.mes.c_str()), 0);
		}
		
	}
	closesocket(cliSock);
	WSACleanup();
	return 0;
}

DWORD WINAPI recvMsgThread(LPVOID IpParameter)//接收消息的线程
{
	SOCKET cliSock = *(SOCKET*)IpParameter;//获取客户端的SOCKET参数
	while (1)
	{
		char buffer[BUFFER_SIZE] = { 0 };//字符缓冲区，用于接收和发送消息
		int nrecv = recv(cliSock, buffer, sizeof(buffer), 0);//nrecv是接收到的字节数
		log("%d", nrecv);
		if (nrecv > 0)//如果接收到的字符数大于0
		{
			message.is_need_update = true;
			message.mes = buffer;
		}
		else if (nrecv < 0)//如果接收到的字符数小于0就说明断开连接
		{
			message.is_need_update = true;
			message.mes = "Disconnect from server";
			log("Disconnect from server");
			break;
		}
	}
	return 0;
}
void OnlineChat::update(float delta)
{
	if (message.is_need_update == true) {
		message.is_need_update = false;
		if(outputmes->getString().size()>100)
		{
			outputmes->setString("");
		}
		outputmes->setString(outputmes->getString() + "\n" + message.mes);
		log("%s",message.mes.c_str());
	}
	if (mymessage.is_need_update == true) {
		mymessage.is_need_update = false;
		if (inputmes->getString().size() > 100)
		{
			inputmes->setString("");
		}
		inputmes->setString(inputmes->getString() + "\n" + mymessage.mes);
		log("%s", mymessage.mes.c_str());
	}
}