#include"ChineseWord.h"

Scene* ChineseWord::createScene()
{
	return ChineseWord::create();//ChineseWord�̳���Scene���˴����õ�ʵ����Scene
	
}

bool ChineseWord::init()
{
	if (!Scene::init())return false;
	
	//��ȡxml����
	auto configData = FileUtils::getInstance()->getValueMapFromFile("ChineseContent.xml");

	//��������
	for (auto& valPair : configData) {
		//��ȡ����
		int key = atoi(valPair.first.c_str());
		Value value = valPair.second;
		CCLOG("key=%d,value=%s",key,value);
		//auto word = valPair.second.asValueMap();

		prt_cnWords.insert(std::pair<int, Value>(key,value));
	}

	return false;
}