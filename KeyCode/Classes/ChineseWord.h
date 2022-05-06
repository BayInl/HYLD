#pragma once
#include"cocos2d.h"
#include<map>
#include<string>
USING_NS_CC;
class ChineseWord  {
public:
	ChineseWord(std::string path= "ChineseContent.xml") {
		auto configData = FileUtils::getInstance()->getValueMapFromFile(path);

		//解析数据
		for (auto& valPair : configData) {
			//获取单词
			int key = atoi(valPair.first.c_str());
			Value value = valPair.second;
			CCLOG("key=%d,value=%s", key, value);
			//auto word = valPair.second.asValueMap();

			prt_cnWords.insert(std::pair<int, Value>(key, value));
		}
	}
	//记录中文字集 key:文字编号   value:中文字
	std::map<int, Value> prt_cnWords;
};
