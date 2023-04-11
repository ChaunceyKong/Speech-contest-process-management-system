#include "speechManager.h"

// 构造
SpeechManager::SpeechManager()
{
	// 初始化属性
	this->initSpeech();
    // 创建选手
	this->createSpeaker();
	// 加载往届记录
	this->loadRecord();
}

// 菜单
void SpeechManager::showMenu()
{
	cout << "************************************************" << endl;
	cout << "*************** 欢迎参加演讲比赛 ***************" << endl;
	cout << "*************** 1.开始演讲比赛 *****************" << endl;
	cout << "*************** 2.查看往届记录 *****************" << endl;
	cout << "*************** 3.清空比赛记录 *****************" << endl;
	cout << "*************** 0.退出比赛程序 *****************" << endl;
	cout << endl;
}

// 退出系统
void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

// 初始化属性
void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	this->m_Index = 1;

	this->m_Record.clear();
}

// 创建选手
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];

		// 创建具体选手
		Speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		// 创建选手编号，并放入v1中
		this->v1.push_back(i + 10001);
		// 选手编号和对应选手放入map
		this->m_Speaker.insert(make_pair(i + 10001, sp));

	}
}

// 开始比赛
void SpeechManager::startSpeech()
{
	// 第一轮比赛开始

	// 1.抽签
	this->speechDraw();
	// 2.比赛
	this->speechContest();
	// 3.显示晋级结果
	this->showScore();
	// 第二轮比赛开始
	this->m_Index++;
	// 1.抽签
	this->speechDraw();
	// 2.比赛
	this->speechContest();
	// 3.显示最终结果
	this->showScore();
	// 4.保存分数到文件
	this->saveRecord();

	// 重置比赛
	// 初始化属性
	this->initSpeech();
	// 创建选手
	this->createSpeaker();
	// 加载往届记录
	this->loadRecord();

	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");
}

// 抽签
void SpeechManager::speechDraw()
{
	cout << "第 " << this->m_Index << " 轮 比赛选手正在抽签" << endl;
	cout << "-------------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;

	if (this->m_Index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "-------------------------------" << endl;
	system("pause");
	cout << endl;
}

// 比赛
void SpeechManager::speechContest()
{
	cout << "-----------第 " << this->m_Index << " 轮比赛正式开始-----------" << endl;

	// 临时容器，保存key 分数，value 选手编号
	multimap<double, int, greater<double>> groupScore;
	// 记录人员数，6个为一组
	int num = 0	;

	vector<int> vSrc; // 比赛选手容器
	if (this->m_Index == 1)
	{
		vSrc = v1;
	}
	else
	{
		vSrc = v2;
	}

	for (vector<int>::iterator it = vSrc.begin(); it != vSrc.end(); it++)
	{
		num++;
		// 评委打分
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			// cout << score << " ";
			d.push_back(score);
		}
		
		sort(d.begin(), d.end(), greater<double>()); // 排序
		d.pop_front(); // 去掉最高分
		d.pop_back(); // 去掉最低分

		double sum = accumulate(d.begin(), d.end(), 0.0);
		double avg = sum / (double)d.size();

		//cout << "编号:" << *it << "，姓名:" << this->m_Speaker[*it].m_Name << "，获取平均分:" << avg << endl;

		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//6 人一组，用临时容器保存
		groupScore.insert(make_pair(avg, *it));

		if (num % 6 == 0)
		{
			cout << "第 " << num / 6 << " 组比赛名次如下：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号:" << it->second << "，姓名:" << this->m_Speaker[it->second].m_Name 
					<< "，成绩:" << m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}

			// 取走前三名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "------------- 第 " << this->m_Index << " 轮比赛结束！ -------------------" << endl;
	system("pause");
}

// 显示得分
void SpeechManager::showScore()
{
	cout << "------------- 第 " << this->m_Index << " 轮晋级选手信息如下：------------" << endl;

	vector<int> v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号:" << *it << " 姓名:" << this->m_Speaker[*it].m_Name 
			<< " 得分:" << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->showMenu();
}

// 保存分数
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	ofs.close();
	cout << "记录保存完毕！" << endl;

	this->fileIsEmpty = false;
}

// 读取往届记录
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	// 文件为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	this->fileIsEmpty = false;
	ifs.putback(ch);
	string data;
	int index = 0; //第几届

	while (ifs >> data)
	{
		vector<string> v; //存放分割后的字符串
		int pos = -1; //查到 , 的位置
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				// 没有找到
				break;
			}
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);

			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}

	ifs.close();

}

// 显示往届记录
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件不存在，或为空！" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "第 " << i + 1 << " 届 "
				<< "冠军编号:" << this->m_Record[i][0] << " 得分:" << this->m_Record[i][1] << " "
				<< "亚军编号:" << this->m_Record[i][2] << " 得分:" << this->m_Record[i][3] << " "
				<< "季军编号:" << this->m_Record[i][4] << " 得分:" << this->m_Record[i][5] << endl;
		}
	}
	
	system("pause");
	system("cls");
}

// 清空文件
void SpeechManager::clearRecord()
{
	cout << "是否确认清空记录：" << endl;
	cout << "1.是" << endl;
	cout << "2.否" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		// 初始化属性
		this->initSpeech();
		// 创建选手
		this->createSpeaker();
		// 加载往届记录
		this->loadRecord();

		cout << "清空成功！" << endl;
	}
	
	system("pause");
	system("cls");
}

// 析构
SpeechManager::~SpeechManager()
{

}
