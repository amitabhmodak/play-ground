#include "Storagetest.h"
#include <iostream>
#include "Storage.h"
#include "qtest.h"
#include "qstring.h"
Q_DECLARE_METATYPE(std::vector<std::string>)
Q_DECLARE_METATYPE(std::string)

Storagetest::~Storagetest()
{
	
}
void Storagetest::initTestCase(){
	std::cout << "Storagetest::initTestCase()\n";
	Storage storage;
	storage.deleteAllData();
	getValidToken();
}
void Storagetest::getValidToken() {
	Storage storage;
	storage.registerDevice(m_mailid.toStdString(), m_key.toStdString());
	auto str = storage.getAuthToken(m_mailid.toStdString(), m_key.toStdString());
	m_validToken = QString::fromStdString(str);
 }
void Storagetest::cleanupTestCase() {
	std::cout << "Storagetest::cleanupTestCase()\n";
	Storage storage;
	storage.deleteAllData();
	 
}
void Storagetest::testinsertCpuUsage_data() {

	QTest::addColumn<QString>("clientId");
	QTest::addColumn<double>("cpuusage");
	QTest::addColumn<int>("returnvalue");
	QTest::newRow("cpu_empty_clientid") << "" << 12.0<<0;
	QTest::newRow("cpu_validtoken_invalidvalue") << m_validToken << -12.0 << 0;
	QTest::newRow("cpu_validtoken_validvalue") << m_validToken << 12.0 << 1;
}
void Storagetest::testinsertCpuUsage() {

	QFETCH(QString, clientId);
	QFETCH(double, cpuusage);
	QFETCH(int, returnvalue);

	Storage storage;
	auto output = storage.publishCpu(clientId.toStdString(), cpuusage);
 	QCOMPARE(output, returnvalue);
}

void Storagetest::testinsertMemoryUsage_data() {

	QTest::addColumn<QString>("clientId");
	QTest::addColumn<double>("memoryusage");
	QTest::addColumn<int>("returnvalue");
	QTest::newRow("memory_empty_clientid") << "" << 12.0 << 0;
	QTest::newRow("memory_validtoken_invalidvalue") << m_validToken << -12.0 << 0;
	QTest::newRow("memory_validtoken_validvalue") << m_validToken << 12.0 << 1;


}
void Storagetest::testinsertMemoryUsage() {

	QFETCH(QString, clientId);
	QFETCH(double, memoryusage);
	QFETCH(int, returnvalue);

	Storage storage;
	auto output = storage.publishMemory(clientId.toStdString(), memoryusage);
	QCOMPARE(output, returnvalue);

}
void Storagetest::testinsertProcess_data() {

	QTest::addColumn<QString>("clientId");
	QTest::addColumn<std::vector<std::string>>("process");
	QTest::addColumn<int>("returnvalue");
	std::vector<std::string> data_empty;
	std::vector<std::string> data_full;
	
	data_full.emplace_back("test1");
	data_full.emplace_back("test2");
	data_full.emplace_back("test3");

	QTest::newRow("process_empty_clientid") << "" << data_full << 0;
	QTest::newRow("process_validtoken_invalidvalue") << m_validToken << data_empty << 0;
	QTest::newRow("process_validtoken_validvalue") << m_validToken << data_full << 1;


}
void Storagetest::testinsertProcess() {

	QFETCH(QString, clientId);
	QFETCH(std::vector<std::string>, process);
	QFETCH(int, returnvalue);

	Storage storage;
	auto output = storage.publishProcessList(clientId.toStdString(), process);
	QCOMPARE(output, returnvalue);

}

void Storagetest::testRegisterDevice_data() {

	Storage storage;
	QTest::addColumn<QString>("email");
	QTest::addColumn<QString>("clientkey");
	QTest::addColumn<std::string>("returnvalue");
	QTest::newRow("register_all_empty") << QString("") << QString("") << std::string("");
	QTest::newRow("register_key_empty") << m_mailid2 << QString("") << std::string("");
	QTest::newRow("register_mail_empty") << QString("") << m_key2 << std::string("");
	QTest::newRow("register_valid") << m_mailid2 << m_key2 << storage.createClientKey(m_mailid2.toStdString(), m_key2.toStdString());
	QTest::newRow("register_duplicate_mail_unique_key") << m_mailid2 << m_key3 << storage.createClientKey(m_mailid2.toStdString(), m_key3.toStdString());

}
void Storagetest::testRegisterDevice() {

	QFETCH(QString, email);
	QFETCH(QString, clientkey);
	QFETCH(std::string, returnvalue);

	Storage storage;
	auto output = storage.registerDevice(email.toStdString(), clientkey.toStdString());
   	QCOMPARE(output, returnvalue);

}

void Storagetest::testToken_data() {
	Storage storage;
	QTest::addColumn<QString>("email");
	QTest::addColumn<QString>("clientkey");
	QTest::addColumn<std::string>("returnvalue");
	QTest::newRow("token_all_empty") << QString("") << QString("") << std::string("");
	QTest::newRow("token_key_empty") << m_mailid2 << QString("") << std::string("");
	QTest::newRow("token_mail_empty") << QString("") << m_key2 << std::string("");
	QTest::newRow("token_valid") << m_mailid2 << m_key2 << storage.createClientKey(m_mailid2.toStdString(), m_key2.toStdString());
	QTest::newRow("token_duplicate_mail_unique_key") << m_mailid2 << m_key3 << storage.createClientKey(m_mailid2.toStdString(), m_key3.toStdString());

}
void Storagetest::testToken() {
	QFETCH(QString, email);
	QFETCH(QString, clientkey);
	QFETCH(std::string, returnvalue);
 	Storage storage;
	auto output = storage.getAuthToken(email.toStdString(), clientkey.toStdString());
 	QCOMPARE(output, returnvalue);
}
