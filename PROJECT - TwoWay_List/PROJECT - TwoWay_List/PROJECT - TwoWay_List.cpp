#include <iostream>
#include"TWList.h"
int main()
{
	ms::TWList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_front(24);
	list.display();
}
