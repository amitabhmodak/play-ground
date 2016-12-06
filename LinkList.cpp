#include "stdafx.h"
#include "LinkList.h"
#include "PayLoad.h"
namespace linklist {


	void DriverProgram::test()
	{

	LinkList<PayLoad> list;
	for (int i = 0; i < 10; i++) {
		if (i == 5)
			continue;
		list.add(PayLoad(i));
	}
		

	list.show();

	for (int i = 0; i <= 5; i++)
		list.removeByValue(i);
	list.show();
	list.removeAllUsingStack();
	list.removeAll();
	list.show();

	list.removeAllUsingStack();

	for (int i = 0; i < 10; i++)
	list.insert(i,i);
	list.show();
 
	}

}