#pragma once
#include <QObject>
class TestServer : public QObject
{
	Q_OBJECT
public:
	TestServer(QObject *parent = 0) {};
	~TestServer();
	int runTests();

	void testinsertCpuUsage();
};



 