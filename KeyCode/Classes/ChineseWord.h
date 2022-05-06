#pragma once
#include"cocos2d.h"
#include<map>
#include<string>
USING_NS_CC;
class ChineseWord  {
public:
	ChineseWord(std::string path= "ChineseContent.xml") {
		auto configData = FileUtils::getInstance()->getValueMapFromFile(path);

		//��������
		for (auto& valPair : configData) {
			//��ȡ����
			int key = atoi(valPair.first.c_str());
			Value value = valPair.second;
			CCLOG("key=%d,value=%s", key, value);
			//auto word = valPair.second.asValueMap();

			prt_cnWords.insert(std::pair<int, Value>(key, value));
		}
	}
	//��¼�����ּ� key:���ֱ��   value:������
	std::map<int, Value> prt_cnWords;
};
