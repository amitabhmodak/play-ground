// PlayGround.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LinkList.h"
#include "DoubleLinkList.h"
#include "BST.h"
#include<conio.h>
 
int main()
{
	{
		linklist::DriverProgram d;
		d.test();
	}
	{
		dlinklist::DriverProgram d;
		d.test();
	}
	{
		bst::DriverProgram d;
		d.test();
	}
	
	_getch();
	return 0;
}

