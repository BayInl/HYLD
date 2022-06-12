#include"OnlineChat.h"
//==============================����Socket�ı���===================================
WSAData wsaData;
SOCKET servSock;
std::string m_serve_localip;//�ҵķ���������IP
std::string m_serve_name;//�ҵķ�����������
std::string serve_localip;//Ҫ����ķ���������IP
int defaultport = atoi(Words.getWord("9984").c_str());//�����ҵķ������˿ں�
int serve_port = atoi(Words.getWord("9984").c_str());//Ҫ����ķ������Ķ˿ں�
//==============================ȫ�ֱ�����===================================
const int BUFFER_SIZE = 1024;//��������С
int RECV_TIMEOUT = 10;//������Ϣ��ʱ
int SEND_TIMEOUT = 10;//������Ϣ��ʱ
const int WAIT_TIME = 10;//ÿ���ͻ��˵ȴ��¼���ʱ�䣬��λ����
int MAX_LINK_NUM = atoi(Words.getWord("MaxConncetNum").c_str());//��������������

SOCKET *cliSock;//�ͻ����׽��� 0��Ϊ�����
SOCKADDR_IN *cliAddr;//�ͻ��˵�ַ
WSAEVENT *cliEvent;//�ͻ����¼� 0��Ϊ�����,�������ó����һ���ֵȴ�������һ���ֵ��źš����磬�����ݴ��׽��ֱ�Ϊ����ʱ��winsock ��Ὣ�¼�����Ϊ�ź�״̬
int total = 0;//��ǰ�Ѿ����ӵĿͷ��˷�����
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
	
	//spritecache->addSpriteFramesWithFile("plist_setting.plist", "plist_setting.png");//��һ������Ҫ��
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

	
	outputmes->setFontName("����");
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
	_line_0->drawLine(Vec2(visibleSize.width/2, visibleSize.height),Vec2(visibleSize.width / 2,0),Color4F(14, 24, 14, 1));//����
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


	inputmes->setFontName("����");
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
		//����ַ�����15��
		if (type == ui::TextField::EventType::INSERT_TEXT){
			auto input = dynamic_cast<cocos2d::ui::TextField*>(ref);
			if (inputmes->getString().length() > 15)
			{
				inputmes->setString(inputmes->getString().substr(0, 15));
			}
			std::string content = input->getString();
			for (char c : content)
			{
				if (c > 127 || c <= 0)//�������������ģ�������ݣ�����ʾ����Ӣ�ĺ�����
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
//��ȡ������������IP��ַ(����)
void GetLocalIpAddress() {
	WORD w_req = MAKEWORD(2, 2);//�汾��
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
DWORD WINAPI servEventThread(LPVOID IpParameter) //���������߳�
{
	//���̸߳��������˺͸����ͻ��˷������¼�
	//������Ĳ�����ʼ��
	SOCKET servSock = *(SOCKET*)IpParameter;//LPVOIDΪ��ָ�����ͣ���Ҫ��ת��SOCKET���������ã�����ʹ�ô����SOCKET
	while (1) //��ִͣ��
	{
		for (int i = 0; i < total + 1; i++)//i�����������ڼ����¼����ն�
		{
			//����һ���ͻ������ӣ�total==1��ѭ�����Σ������ͻ��˺ͷ����
			//��ÿһ���նˣ��ͻ��˺ͷ���ˣ����鿴�Ƿ����¼����ȴ�WAIT_TIME����
			int index = WSAWaitForMultipleEvents(1, &cliEvent[i], false, WAIT_TIME, 0);

			index -= WSA_WAIT_EVENT_0;//��ʱindexΪ�����¼����ն��±�

			if (index == WSA_WAIT_TIMEOUT || index == WSA_WAIT_FAILED)
				continue;//���������߳�ʱ�����������ն�

			else if (index == 0)
			{
				WSANETWORKEVENTS networkEvents;
				WSAEnumNetworkEvents(cliSock[i], cliEvent[i], &networkEvents);//�鿴��ʲô�¼�

				//�¼�ѡ��
				if (networkEvents.lNetworkEvents & FD_ACCEPT)//������accept�¼����˴���λ�������룩
				{
					if (networkEvents.iErrorCode[FD_ACCEPT_BIT] != 0)
					{
						message.mes = "An error occurred while connecting. Error code:" + std::to_string(networkEvents.iErrorCode[FD_ACCEPT_BIT]);
						message.is_need_update = true;
						log("An error occurred while connecting. Error code:%d", networkEvents.iErrorCode[FD_ACCEPT_BIT]);
						continue;
					}
					//��������
					if (total + 1 < MAX_LINK_NUM)//������һ���ͻ�����ȻС�����������������ܸ�����
					{
						//totalΪ�����ӿͻ�������
						int nextIndex = total + 1;//������¿ͻ��˵��±�
						int addrLen = sizeof(SOCKADDR);
						SOCKET newSock = accept(servSock, (SOCKADDR*)&cliAddr[nextIndex], &addrLen);
						if (newSock != INVALID_SOCKET)
						{
							//���÷��ͺͽ���ʱ��
							/*setsockopt(newSock, SOL_SOCKET, SO_SNDTIMEO, (const char*) & SEND_TIMEOUT, sizeof(SEND_TIMEOUT));
							setsockopt(newSock, SOL_SOCKET, SO_SNDTIMEO, (const char*) &RECV_TIMEOUT, sizeof(RECV_TIMEOUT));*/
							//���¿ͻ��˷���socket
							cliSock[nextIndex] = newSock;
							//�¿ͻ��˵ĵ�ַ�Ѿ�����cliAddr[nextIndex]����
							//Ϊ�¿ͻ��˰��¼�����,ͬʱ���ü�����close��read��write
							WSAEVENT newEvent = WSACreateEvent();
							WSAEventSelect(cliSock[nextIndex], newEvent, FD_CLOSE | FD_READ | FD_WRITE);
							cliEvent[nextIndex] = newEvent;
							total++;//�ͻ�������������
							log("#%dPlayer(ip:%s) went the chat room, current connections: %d", nextIndex, inet_ntoa(cliAddr[nextIndex].sin_addr),total);
							
							//�����пͻ��˷��ͻ�ӭ��Ϣ
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
				else if (networkEvents.lNetworkEvents & FD_CLOSE)//�ͻ��˱��رգ����Ͽ�����
				{

					//i��ʾ�ѹرյĿͻ����±�
					total--;
					log("#%dPlayer(ip:%s) left the chat room, current connections: %d", i, inet_ntoa(cliAddr[i].sin_addr), total);
					//�ͷ�����ͻ��˵���Դ
					closesocket(cliSock[i]);
					WSACloseEvent(cliEvent[i]);

					//�������,��˳���ɾ��Ԫ��
					for (int j = i; j < total; j++)
					{
						cliSock[j] = cliSock[j + 1];
						cliEvent[j] = cliEvent[j + 1];
						cliAddr[j] = cliAddr[j + 1];
					}
					//�����пͻ��˷����˳������ҵ���Ϣ
					char buf[BUFFER_SIZE] = "Player��IP��";
					strcat(buf, inet_ntoa(cliAddr[i].sin_addr));
					strcat(buf, ")left the chat room");
					message.mes = buf;
					for (int j = 1; j <= total; j++)
					{
						send(cliSock[j], buf, sizeof(buf), 0);
					}
					message.is_need_update = true;
				}
				else if (networkEvents.lNetworkEvents & FD_READ)//���յ���Ϣ
				{
					char buffer[BUFFER_SIZE] = { 0 };//�ַ������������ڽ��պͷ�����Ϣ
					char buffer2[BUFFER_SIZE] = { 0 };

					for (int j = 1; j <= total; j++)
					{
						int nrecv = recv(cliSock[j], buffer, sizeof(buffer), 0);//nrecv�ǽ��յ����ֽ���
						if (nrecv > 0)//������յ����ַ�������0
						{
							sprintf(buffer2, "[#%d]%s", j, buffer);
							//�ڷ������ʾ
							message.mes = buffer2;
							//�������ͻ�����ʾ���㲥�������ͻ��ˣ�
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
} // ����˴����߳�

DWORD WINAPI socketSeverMainThread(LPVOID IpParameter) {//����˴����߳�
	
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	servSock = socket(AF_INET, SOCK_STREAM, 0);//������·����ʽ�׽���

	SOCKADDR_IN servAddr; //sockaddr_in ��internet�������׽��ֵĵ�ַ��ʽ
	servAddr.sin_family = AF_INET;//�ͷ�������socketһ����sin_family��ʾЭ��أ�һ����AF_INET��ʾTCP/IPЭ�顣
	servAddr.sin_addr.S_un.S_addr = inet_addr(m_serve_localip.c_str());//����˵�ַ����Ϊ���ػػ���ַ
	servAddr.sin_port = htons(defaultport);//host to net short �˿ں�����Ϊ8888

	//4���󶨷���˵�socket�ʹ���õĵ�ַ
	bind(servSock, (SOCKADDR*)&servAddr, sizeof(servAddr));
	//4.5�������sokect��һ���¼������������տͻ������ӵ��¼�
	WSAEVENT servEvent = WSACreateEvent();//����һ���˹�����Ϊ���ŵ��¼�����
	WSAEventSelect(servSock, servEvent, FD_ALL_EVENTS);//���¼����󣬲��Ҽ��������¼�

	cliSock[0] = servSock;
	cliEvent[0] = servEvent;
	//5����������
	listen(servSock, 10);//�������г���Ϊ10

	//6�������������ӵ��߳�
	//����Ҫ�������ֱ�ӹر�

	CloseHandle(CreateThread(NULL, 0, servEventThread, (LPVOID)&servSock, 0, 0));
	//��Ҫ�����߳�һֱ������ȥ
	//������Ϣ��ȫ���ͻ���
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
	//1����ʼ��socket��
	WSADATA wsaData;//��ȡ�汾��Ϣ��˵��Ҫʹ�õİ汾
	WSAStartup(MAKEWORD(2, 2), &wsaData);//MAKEWORD(���汾��, ���汾��)

	//2������socket
	SOCKET cliSock = socket(AF_INET, SOCK_STREAM, 0);//������·����ʽ�׽���,���������������Զ�ѡ��Э��

	//3�������ַ
	//�ͻ���
	SOCKADDR_IN cliAddr = { 0 };
	cliAddr.sin_family = AF_INET;
	cliAddr.sin_addr.s_addr = inet_addr("127.101.101.1");//IP��ַm_serve_localip.c_str()
	cliAddr.sin_port = htons(defaultport);//�˿ں�
	//�����
	SOCKADDR_IN servAddr = { 0 };
	servAddr.sin_family = AF_INET;//�ͷ�������socketһ����sin_family��ʾЭ��أ�һ����AF_INET��ʾTCP/IPЭ�顣
	servAddr.sin_addr.S_un.S_addr = inet_addr(serve_localip.c_str());//����˵�ַ����Ϊ���ػػ���ַ
	servAddr.sin_port = htons(serve_port);
	if (connect(cliSock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
		log("error,the error code is%d", WSAGetLastError());

	//����������Ϣ�߳�
	CloseHandle(CreateThread(NULL, 0, recvMsgThread, (LPVOID)&cliSock, 0, 0));
	while (1)
	{
		if (mymessage.is_need_update) {
			mymessage.is_need_update = false;
			if (mymessage.mes == "quit")//�����롰quit�������˳�������
				break;
			send(cliSock, mymessage.mes.c_str(), sizeof(mymessage.mes.c_str()), 0);
		}
		
	}
	closesocket(cliSock);
	WSACleanup();
	return 0;
}

DWORD WINAPI recvMsgThread(LPVOID IpParameter)//������Ϣ���߳�
{
	SOCKET cliSock = *(SOCKET*)IpParameter;//��ȡ�ͻ��˵�SOCKET����
	while (1)
	{
		char buffer[BUFFER_SIZE] = { 0 };//�ַ������������ڽ��պͷ�����Ϣ
		int nrecv = recv(cliSock, buffer, sizeof(buffer), 0);//nrecv�ǽ��յ����ֽ���
		log("%d", nrecv);
		if (nrecv > 0)//������յ����ַ�������0
		{
			message.is_need_update = true;
			message.mes = buffer;
		}
		else if (nrecv < 0)//������յ����ַ���С��0��˵���Ͽ�����
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