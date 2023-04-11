#include "speechManager.h"

// ����
SpeechManager::SpeechManager()
{
	// ��ʼ������
	this->initSpeech();
    // ����ѡ��
	this->createSpeaker();
	// ���������¼
	this->loadRecord();
}

// �˵�
void SpeechManager::showMenu()
{
	cout << "************************************************" << endl;
	cout << "*************** ��ӭ�μ��ݽ����� ***************" << endl;
	cout << "*************** 1.��ʼ�ݽ����� *****************" << endl;
	cout << "*************** 2.�鿴�����¼ *****************" << endl;
	cout << "*************** 3.��ձ�����¼ *****************" << endl;
	cout << "*************** 0.�˳��������� *****************" << endl;
	cout << endl;
}

// �˳�ϵͳ
void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}

// ��ʼ������
void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	this->m_Index = 1;

	this->m_Record.clear();
}

// ����ѡ��
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];

		// ��������ѡ��
		Speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		// ����ѡ�ֱ�ţ�������v1��
		this->v1.push_back(i + 10001);
		// ѡ�ֱ�źͶ�Ӧѡ�ַ���map
		this->m_Speaker.insert(make_pair(i + 10001, sp));

	}
}

// ��ʼ����
void SpeechManager::startSpeech()
{
	// ��һ�ֱ�����ʼ

	// 1.��ǩ
	this->speechDraw();
	// 2.����
	this->speechContest();
	// 3.��ʾ�������
	this->showScore();
	// �ڶ��ֱ�����ʼ
	this->m_Index++;
	// 1.��ǩ
	this->speechDraw();
	// 2.����
	this->speechContest();
	// 3.��ʾ���ս��
	this->showScore();
	// 4.����������ļ�
	this->saveRecord();

	// ���ñ���
	// ��ʼ������
	this->initSpeech();
	// ����ѡ��
	this->createSpeaker();
	// ���������¼
	this->loadRecord();

	cout << "���������ϣ�" << endl;
	system("pause");
	system("cls");
}

// ��ǩ
void SpeechManager::speechDraw()
{
	cout << "�� " << this->m_Index << " �� ����ѡ�����ڳ�ǩ" << endl;
	cout << "-------------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;

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

// ����
void SpeechManager::speechContest()
{
	cout << "-----------�� " << this->m_Index << " �ֱ�����ʽ��ʼ-----------" << endl;

	// ��ʱ����������key ������value ѡ�ֱ��
	multimap<double, int, greater<double>> groupScore;
	// ��¼��Ա����6��Ϊһ��
	int num = 0	;

	vector<int> vSrc; // ����ѡ������
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
		// ��ί���
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			// cout << score << " ";
			d.push_back(score);
		}
		
		sort(d.begin(), d.end(), greater<double>()); // ����
		d.pop_front(); // ȥ����߷�
		d.pop_back(); // ȥ����ͷ�

		double sum = accumulate(d.begin(), d.end(), 0.0);
		double avg = sum / (double)d.size();

		//cout << "���:" << *it << "������:" << this->m_Speaker[*it].m_Name << "����ȡƽ����:" << avg << endl;

		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//6 ��һ�飬����ʱ��������
		groupScore.insert(make_pair(avg, *it));

		if (num % 6 == 0)
		{
			cout << "�� " << num / 6 << " ������������£�" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "���:" << it->second << "������:" << this->m_Speaker[it->second].m_Name 
					<< "���ɼ�:" << m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}

			// ȡ��ǰ����
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
	cout << "------------- �� " << this->m_Index << " �ֱ��������� -------------------" << endl;
	system("pause");
}

// ��ʾ�÷�
void SpeechManager::showScore()
{
	cout << "------------- �� " << this->m_Index << " �ֽ���ѡ����Ϣ���£�------------" << endl;

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
		cout << "ѡ�ֱ��:" << *it << " ����:" << this->m_Speaker[*it].m_Name 
			<< " �÷�:" << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->showMenu();
}

// �������
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
	cout << "��¼������ϣ�" << endl;

	this->fileIsEmpty = false;
}

// ��ȡ�����¼
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	// �ļ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	this->fileIsEmpty = false;
	ifs.putback(ch);
	string data;
	int index = 0; //�ڼ���

	while (ifs >> data)
	{
		vector<string> v; //��ŷָ����ַ���
		int pos = -1; //�鵽 , ��λ��
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				// û���ҵ�
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

// ��ʾ�����¼
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "�ļ������ڣ���Ϊ�գ�" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "�� " << i + 1 << " �� "
				<< "�ھ����:" << this->m_Record[i][0] << " �÷�:" << this->m_Record[i][1] << " "
				<< "�Ǿ����:" << this->m_Record[i][2] << " �÷�:" << this->m_Record[i][3] << " "
				<< "�������:" << this->m_Record[i][4] << " �÷�:" << this->m_Record[i][5] << endl;
		}
	}
	
	system("pause");
	system("cls");
}

// ����ļ�
void SpeechManager::clearRecord()
{
	cout << "�Ƿ�ȷ����ռ�¼��" << endl;
	cout << "1.��" << endl;
	cout << "2.��" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		// ��ʼ������
		this->initSpeech();
		// ����ѡ��
		this->createSpeaker();
		// ���������¼
		this->loadRecord();

		cout << "��ճɹ���" << endl;
	}
	
	system("pause");
	system("cls");
}

// ����
SpeechManager::~SpeechManager()
{

}
