#pragma once
#include<Winsock2.h>//socketͷ�ļ�
#pragma comment(lib,"ws2_32.lib")   //socket��
#include<cstring>
#include<string.h>
#include"cocos2d.h"
#include "ui/CocosGUI.h"
#include"ChineseWord.h"
//#define MAX_LINK_NUM  3//��������������,��������
extern ChineseWord Words;
extern cocos2d::SpriteFrameCache* spritecache;
class OnlineChat :public cocos2d::Scene {
private:
	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();

	
	cocos2d::ui::Button* button_back;
	cocos2d::ui::Button* button_join_room= cocos2d::ui::Button::create();
	cocos2d::ui::Button* button_create_room= cocos2d::ui::Button::create();
	cocos2d::ui::Button* button_send= cocos2d::ui::Button::create();
	cocos2d::Label* label_show_myip= cocos2d::Label::create();
	cocos2d::Label* label_show_myport= cocos2d::Label::create();
	
	//cocos2d::Label* label_show_myport;
	DrawNode* _line_0;
	
	void update(float delta);
	inline void _set_button_back();
public:
	//�༭��
	cocos2d::ui::TextField* outputmes = ui::TextField::create();
	cocos2d::ui::TextField* inputmes = ui::TextField::create();
	
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(OnlineChat);
	~OnlineChat();
	
};

inline void GetLocalIpAddress();//��ȡ����IP
DWORD WINAPI servEventThread(LPVOID IpParameter);//����˴����߳�
DWORD WINAPI socketSeverMainThread(LPVOID IpParameter);//����˴����߳�

DWORD WINAPI recvMsgThread(LPVOID IpParameter);//�ͻ��˽����߳�
DWORD WINAPI socketClientMainThread(LPVOID IpParameter);//�ͻ��˴����߳�