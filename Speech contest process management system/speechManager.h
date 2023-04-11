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

// �ݽ�����������
class SpeechManager
{
public:
	// ����
	SpeechManager();
	// �˵�
	void showMenu();
	// �˳�ϵͳ
	void exitSystem();
	// ��ʼ������
	void initSpeech();
	// ����ѡ��
	void createSpeaker();
	// ��ʼ����
	void startSpeech();
	// ��ǩ
	void speechDraw();
	// ����
	void speechContest();
	// ��ʾ�÷�
	void showScore();
	// �������
	void saveRecord();
	// ��ȡ�����¼
	void loadRecord();
	// ��ʾ�����¼
	void showRecord();
	// ����ļ�
	void clearRecord();

	// ����
	~SpeechManager();


	// ��Ա����
	vector<int> v1; //��һ��ѡ�ֱ��
	vector<int> v2; //�ڶ���ѡ�ֱ��
	vector<int> vVictory; //ʤ��ѡ��
	map<int, Speaker> m_Speaker; //���--ѡ��
	int m_Index; //��������
	bool fileIsEmpty; //�ж��ļ��Ƿ�Ϊ��
	map<int, vector<string>> m_Record; //��������¼
};
