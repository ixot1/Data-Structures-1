#include "Benchmark_Menu.h"
#include "Benchmark.h"
#include <iostream>

//clearing the buffer in case of a wrong input
static void clearInput() {
	std::cin.clear();
	std::cin.ignore(100, '\n');
}
//get and return a choice from the user 
static int getUserChoice() {
	int choice;
	while (!(std::cin >> choice)) {
		clearInput();
		std::cout << "Incorrect choice, please try again. \n";
	}
	return choice;
}

static void methodMenu(int structureType) {
	while (true) {
		std::cout << "\n--- Choose the method for benchmarking. ---\n";
		std::cout << "1. push_back (add to the back)\n";
		std::cout << "2. push_front (add to the front)\n";
		std::cout << "3. push_at (add at index)\n";
		std::cout << "4. pop_back (remove from the back)\n";
		std::cout << "5. pop_front (remove from the front)\n";
		std::cout << "6. pop_at (remove at index)\n";
		std::cout << "7. search (search for value)\n";
		std::cout << "8. RUN ALL TESTS FOR THIS STRUCTURE\n";
		std::cout << "0. GO BACK\n";

		int methodChoice = getUserChoice();

		if (methodChoice == 0) break;

		std::cout << "\n Executing the benchmark... \n";

		switch (structureType) {
		case 1: //DynamicArray
			switch (methodChoice) {
			case 1:	Benchmark::testArrayPushBack();
				break;
			case 2: Benchmark::testArrayPushFront();
				break;
			case 3: Benchmark::testArrayPushAt();
				break;
			case 4: Benchmark::testArrayPopBack();
				break;
			case 5: Benchmark::testArrayPopFront();
				break;
			case 6: Benchmark::testArrayPopAt();
				break;
			case 7: Benchmark::testArraySearch();
				break;
			case 8:
				Benchmark::testArrayPushBack();
				Benchmark::testArrayPushFront();
				Benchmark::testArrayPushAt();
				Benchmark::testArrayPopBack();
				Benchmark::testArrayPopFront();
				Benchmark::testArrayPopAt();
				Benchmark::testArraySearch();
				break;
			default: std::cout << "Incorrect choice, please try again \n"; break;
			}
			break;
		case 2: //SinglyLinkedList
			switch (methodChoice) {
			case 1: Benchmark::testSLLPushBack();
				break;
			case 2: Benchmark::testSLLPushFront();
				break;
			case 3: Benchmark::testSLLPushAt();
				break;
			case 4: Benchmark::testSLLPopBack();
				break;
			case 5: Benchmark::testSLLPopFront();
				break;
			case 6: Benchmark::testSLLPopAt();
				break;
			case 7: Benchmark::testSLLSearch();
				break;
			case 8: 
				Benchmark::testSLLPushBack();
				Benchmark::testSLLPushFront();
				Benchmark::testSLLPushAt();
				Benchmark::testSLLPopBack();
				Benchmark::testSLLPopFront();
				Benchmark::testSLLPopAt();
				Benchmark::testSLLSearch();
				break;
			default: std::cout << "Incorrect choice, please try again \n"; break;
			}
			break;
		case 3: //DoublyLinkedList
			switch (methodChoice) {
			case 1: Benchmark::testDLLPushBack();
				break;
			case 2: Benchmark::testDLLPushFront();
				break;
			case 3: Benchmark::testDLLPushAt();
				break;
			case 4: Benchmark::testDLLPopBack();
				break;
			case 5: Benchmark::testDLLPopFront();
				break;
			case 6: Benchmark::testDLLPopAt();
				break;
			case 7: Benchmark::testDLLSearch();
				break;
			case 8:
				Benchmark::testDLLPushBack();
				Benchmark::testDLLPushFront();
				Benchmark::testDLLPushAt();
				Benchmark::testDLLPopBack();
				Benchmark::testDLLPopFront();
				Benchmark::testDLLPopAt();
				Benchmark::testDLLSearch();
				break;
			}
		}
	}
}

void runMainMenu() {
	while (true) {
		std::cout << "\n====== Choose the structure for benchmarking ======\n";
		std::cout << "1. Dynamic Array (DA)\n";
		std::cout << "2. Singly Linked List (SLL)\n";
		std::cout << "3. Doubly Linked List (DLL)\n";
		std::cout << "0. EXIT\n";

		int structureChoice = getUserChoice();

		if (structureChoice == 0) {
			std::cout << "Closing program...\n";
			break;
		}

		if (structureChoice >= 1 && structureChoice <= 3) {
			methodMenu(structureChoice);
		}
		else {
			std::cout << "Invalid structure choice. Try 1, 2 or 3.\n";
		}
	}
}