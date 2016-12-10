#include "stdafx.h"
#include "BST.h"


using namespace bst;
void DriverProgram::test()
{

	BST<int> list;
	/* for (int i = 0; i < 10; i++) {
		 
		list.add(int(i));
	} */
	list.add(13);
	list.add(3);
	list.add(5);
	list.add(31);
	list.add(1);

	list.inorder();
	list.inorderSingleLoop();
	list.inorderRecur();

	list.preorder();
	list.preorderSingleLoop();
	list.preorderRecur();
	

	list.postorder();
	list.postorderRecur();
	
}