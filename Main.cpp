#include <iostream>
#include "DynamicArray.h"

int main()
{	
	DynamicArray array{ 5 };
	array.push_back(1);
	array.push_back(2);
	array.push_back(3);
	array.push_back(4);
	array.push_back(5);
	array.print_array();
}

