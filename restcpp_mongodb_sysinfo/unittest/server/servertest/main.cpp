#include <QtCore/QCoreApplication>
#include <QtTest/QtTest>
#include "TestServer.h"
#include "AlertHandler.h"
#include <iostream>
#include<conio.h>
 

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	 TestServer test;
	 _getch();
	test.runTests(); 
	 
	return a.exec();
}
