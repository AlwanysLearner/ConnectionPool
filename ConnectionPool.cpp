#include "ConnectionPool.h"
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include<thread>
using namespace std;
ConnectionPool* ConnectionPool::getConnectPool()
{
    static ConnectionPool pool;
    return &pool;
}

void ConnectionPool::parseJsonFile()
{
    // 打开JSON文件
    FILE* fp = fopen("dbconf.json", "rb");
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    // 解析JSON文件
    rapidjson::Document document;
    document.ParseStream(is);

    // 输出JSON数据
    m_ip = document["ip"].GetString();
    m_port = document["port"].GetInt();
    m_user = document["userName"].GetString();
    m_passwd = document["password"].GetString();
    m_dbName = document["dbName"].GetString();
    m_minsize = document["minSize"].GetInt();
    m_maxsize = document["maxSize"].GetInt();
    m_maxIdleTime = document["maxIdleTime"].GetInt();
    m_timeout = document["timeout"].GetInt();

    // 关闭文件
    fclose(fp);
}
void ConnectionPool::producerConnection()
{
    while (true) {
        unique_lock<mutex> locker(m_mutexQ);
        while (m_connectionQ.size() >= m_maxsize) {
            m_cond.wait(locker);
        }
        addConnection();
        m_cond.notify_all();
    }
}
void ConnectionPool::recycleConnection()
{
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(500));
        lock_guard<mutex> locker(m_mutexQ);
        while (m_connectionQ.size() > m_minsize) {
            MysqlConn* conn = m_connectionQ.front();
            if (conn->getAliveTime() > m_maxIdleTime) {
                m_connectionQ.pop();
                delete conn;
            }
            else {
                break;
            }
        }
    }
}
void ConnectionPool::addConnection()
{
    MysqlConn* conn = new MysqlConn();
    conn->connect(m_user, m_passwd, m_dbName, m_ip, m_port);
    conn->refreshAliveTime();
    m_connectionQ.push(conn);
}
shared_ptr<MysqlConn> ConnectionPool::getConnection()
{
    unique_lock<mutex> locker(m_mutexQ);
    while (m_connectionQ.empty()) {
        if (cv_status::timeout==m_cond.wait_for(locker, chrono::milliseconds(m_timeout))) {
            //如果等待时间过长直接放弃用这个
            /*if(m_connectionQ.empty()){
                return nullptr;
            }*/
            //等待过后继续等待用这个
            continue;
        }
    }
    shared_ptr<MysqlConn> connptr(m_connectionQ.front(), [this](MysqlConn* conn) {
        lock_guard<mutex> locker(m_mutexQ);
        conn->refreshAliveTime();
        m_connectionQ.push(conn);
        });
    m_connectionQ.pop();
    m_cond.notify_all();
    return connptr;
}
ConnectionPool::~ConnectionPool()
{
    while (!m_connectionQ.empty()) {
        MysqlConn* conn = m_connectionQ.front();
        m_connectionQ.pop();
        delete conn;
    }
}
ConnectionPool::ConnectionPool() {
    //加载配置文件
    parseJsonFile();
    for (int i = 0; i < m_minsize; ++i) {
        addConnection();
    }
    thread producer(&ConnectionPool::producerConnection,this);
    thread recycle(&ConnectionPool::recycleConnection,this);
    producer.detach();
    recycle.detach();
}
