#pragma once
#include<queue>
#include<mutex>
#include<condition_variable>
#include"MysqlConn.h"
using namespace std;
class ConnectionPool
{
public:
	static ConnectionPool* getConnectPool();
	ConnectionPool(const ConnectionPool& obj) = delete;
	ConnectionPool& operator=(const ConnectionPool& obj) = delete;
	shared_ptr<MysqlConn> getConnection();
	~ConnectionPool();
private:
	ConnectionPool();
	void parseJsonFile();
	void producerConnection();
	void recycleConnection();
	void addConnection();
	string m_ip;
	string m_user;
	string m_passwd;
	string m_dbName;
	unsigned short m_port;
	int m_maxsize;
	int m_minsize;
	int m_timeout;
	int m_maxIdleTime;
	queue<MysqlConn*>m_connectionQ;
	mutex m_mutexQ;
	condition_variable m_cond;
};

