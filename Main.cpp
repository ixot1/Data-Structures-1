#include <iostream>
#include "Dynamic_Array.h"
#include "Singly_Linked_List.h"
#include "Doubly_Linked_List.h"

int main()
{	
	DynamicArray array{5};
	array.push_back(1);
	array.push_back(2);
	array.push_back(3);
	array.push_back(4);
	array.push_back(5);
	array.push_front(0);
	array.push_at(10, 3);
	array.print_array();
}
