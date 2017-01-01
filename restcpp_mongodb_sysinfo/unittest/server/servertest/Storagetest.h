#pragma once
#include <QObject>
class Storagetest : public QObject
{
	Q_OBJECT
	QString m_mailid = "amitabh.modak@gmail.com";
	QString m_key = "0123456789";

	QString m_mailid2 = "amitabh.modak@hotmail.com";
	QString m_key2 = "0123456";
	QString m_key3 = "120123456";

	
	QString m_invalidToken = "012";
	QString m_validToken;
public:
	Storagetest(QObject *parent = 0) {};
	~Storagetest();
	void getValidToken();
	private slots:
	void initTestCase();
	void cleanupTestCase();
	void testinsertCpuUsage_data();
	void testinsertCpuUsage();
	void testinsertMemoryUsage_data();
	void testinsertMemoryUsage();
	void testinsertProcess_data();
	void testinsertProcess();
	void testRegisterDevice_data();
	void testRegisterDevice();
	void testToken_data();
	void testToken();
 
};

