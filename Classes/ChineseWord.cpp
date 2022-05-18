#include"ChineseWord.h"

Scene* ChineseWord::createScene()
{
	return ChineseWord::create();//ChineseWord继承了Scene，此处调用的实质是Scene
	
}

bool ChineseWord::init()
{
	if (!Scene::init())return false;
	
	//获取xml数据
	auto configData = FileUtils::getInstance()->getValueMapFromFile("ChineseContent.xml");

	//解析数据
	for (auto& valPair : configData) {
		//获取单词
		int key = atoi(valPair.first.c_str());
		Value value = valPair.second;
		CCLOG("key=%d,value=%s",key,value);
		//auto word = valPair.second.asValueMap();

		prt_cnWords.insert(std::pair<int, Value>(key,value));
	}

	return false;
}