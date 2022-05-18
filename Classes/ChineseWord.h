#pragma once
#include"cocos2d.h"
#include<map>
#include<cstring>
#include<fstream>
USING_NS_CC;
class ChineseWord  {
private:
	std::string _m_path_read;
	ValueMap configData;
public:
	ChineseWord(std::string path= "ChineseContent.xml"):_m_path_read(path) {
		configData = FileUtils::getInstance()->getValueMapFromFile(_m_path_read);
		/*
		//解析数据
		for (auto& valPair : configData) {
			//获取单词
			int key = atoi(valPair.first.c_str());
			Value value = valPair.second;
			//CCLOG("key=%d,value=%s", key, value);
			//auto word = valPair.second.asValueMap();
			prt_cnWords.insert(std::pair<int, Value>(key, value));
		}
		*/
	}
	std::string getWord(std::string key) {
		return configData.at(key).asString();
	}
	bool setWord(std::string key, std::string value) {
		if (configData.find(key)==configData.end()) 
			return false;
		configData[key] = value;
		return true;
	}
	bool removeWord(std::string key) {
		if (configData.find(key) == configData.end())
			return false;
		configData.erase(key);
		return true;
	}
	bool insertWord(std::string key, std::string value) {
		if (configData.find(key) != configData.end())
			return false;
		configData.insert(std::pair<std::string, Value>(key, Value(value)));
		return true;
	}
	bool Store(std::string path ) {
		auto _write_object=FileUtils::getInstance()->writeValueMapToFile(configData,path);
		if(_write_object==false)
			return false;
		return true;
	}
	//记录中文字集 key:文字编号   value:中文字
	//std::map<int, Value> prt_cnWords;
};
/*//写入文件
std::ofstream ofs(_m_path);
if (ofs.is_open()) {
	for (auto& valPair : prt_cnWords) {
		ofs << valPair.first << "=" << valPair.second << std::endl;
	}
	ofs.close();
}*/