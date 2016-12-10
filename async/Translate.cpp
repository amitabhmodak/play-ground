// Translate.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RestClient.h"
#include <conio.h>

int main()
{
	RestClient client;
	client.translate(L"Hello world", L"nl")
		.then([](std::wstring str) {
		std::wcout << str << "\n";
	})
	.wait();

	_getch();
    return 0;
}

