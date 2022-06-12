#ifndef __GLOBALVARS_H__
#define __GLOBALVARS_H__
#include"ChineseWord.h"
extern int number_npc_;//npc数量 
extern int player_ranking_;//玩家排名 
extern int trophy_;//玩家奖杯
extern int number_win_;//玩家吃鸡次数
extern bool switch_music_;//音量开关 
extern bool switch_sound_;//音效开关 
extern int volume_;//音量（浮点数，和基础音量为相乘关系）
extern char user_name_[11];//用户名
extern ChineseWord Words;
extern int heroflag;//玩家角色代号
#endif