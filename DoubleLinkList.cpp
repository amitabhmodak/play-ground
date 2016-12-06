#include "stdafx.h"
#include "DoubleLinkList.h"
#include "PayLoad.h"
#include<iostream>
using namespace std; 


namespace dlinklist {
	void DriverProgram::test()
	{

		DoubleLinkList<PayLoad> list;
		for (int i = 0; i < 7; i++) {
			list.add(PayLoad(i));
		}


		list.show();
		list.showReverse();
		list.showMiddle();
		list.showPairSum(PayLoad(7));

	}
}