// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RestServer.h"
#include <conio.h>
int main()
{
	RestServer server;
	server.start(8080);
	_getch();
    return 0;
}

