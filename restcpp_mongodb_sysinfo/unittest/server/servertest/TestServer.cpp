#include "TestServer.h"
#include <qtest.h>
#include "Storagetest.h"
 

TestServer::~TestServer()
{
}
int TestServer::runTests() {
	Storagetest sotrageTest;
	int result = QTest::qExec(&sotrageTest);
	 
	return result;
}