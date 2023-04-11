#include <iostream>
using namespace std;
#include <ctime>

#include "speechManager.h"

int main()
{
	// 随机数种子
	srand((unsigned int)time(NULL));

	SpeechManager sm;
	int choice = 0;

	while (true)
	{
		sm.showMenu();
		cout << "请输入您的选择：" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1: // 开始比赛
			sm.startSpeech();
			break;
		case 2: // 查看往届记录
			sm.showRecord();
			break;
		case 3: // 清空比赛记录
			sm.clearRecord();
			break;
		case 0: // 退出系统
			sm.exitSystem();
			break;
		default:
			system("cls"); // 清屏
			break;
		}
	}

	system("pause");
	return 0;
}