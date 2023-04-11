#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "speaker.h"
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <fstream>

using namespace std;

// 演讲比赛管理类
class SpeechManager
{
public:
	// 构造
	SpeechManager();
	// 菜单
	void showMenu();
	// 退出系统
	void exitSystem();
	// 初始化属性
	void initSpeech();
	// 创建选手
	void createSpeaker();
	// 开始比赛
	void startSpeech();
	// 抽签
	void speechDraw();
	// 比赛
	void speechContest();
	// 显示得分
	void showScore();
	// 保存分数
	void saveRecord();
	// 读取往届记录
	void loadRecord();
	// 显示往届记录
	void showRecord();
	// 清空文件
	void clearRecord();

	// 析构
	~SpeechManager();


	// 成员属性
	vector<int> v1; //第一轮选手编号
	vector<int> v2; //第二轮选手编号
	vector<int> vVictory; //胜出选手
	map<int, Speaker> m_Speaker; //编号--选手
	int m_Index; //比赛轮数
	bool fileIsEmpty; //判断文件是否为空
	map<int, vector<string>> m_Record; //存放往届记录
};
