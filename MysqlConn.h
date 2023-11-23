#pragma once
#include<iostream>
#include<mysql.h>
#include<chrono>
using namespace std;
using namespace chrono;
class MysqlConn
{
public:
	//��ʼ�����ݿ�����
	MysqlConn();
	//�ͷ����ݿ�����
	~MysqlConn();
	//�������ݿ�
	bool connect(string user, string passwd, string dbName, string ip, unsigned short port = 3306);
	//�������ݿ�
	bool update(string sql);
	//��ѯ���ݿ�
	bool query(string sql);
	//������ѯ�õ��Ľ����
	bool next();
	//�õ�������е��ֶ�ֵ
	string value(int index);
	//�������
	bool transaction();
	//�ύ����
	bool commit();
	//����ع�
	bool rollback();
	//ˢ����ʼ����ʱ���
	void refreshAliveTime();
	//�������Ӵ����ʱ�� 
	long long getAliveTime();
private:
	void freeResult();
	MYSQL* m_conn = nullptr;
	MYSQL_RES* m_result = nullptr;
	MYSQL_ROW m_row = nullptr;
	steady_clock::time_point m_alivetime;
	
};
