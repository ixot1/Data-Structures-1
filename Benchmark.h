#pragma once
#include <vector>

class Benchmark {

public:
	static const int REPETITIONS;
	static const int SEED;
	static const std::vector<int> SIZES;

	static void testArrayPushBack();
	static void testArrayPushFront();
	static void testArrayPushAt();
	static void testArrayPopBack();
	static void testArrayPopFront();
	static void testArrayPopAt();
	static void testArraySearch();

	static void testSLLPushBack();
	static void testSLLPushFront();
	static void testSLLPushAt();
	static void testSLLPopBack();
	static void testSLLPopFront();
	static void testSLLPopAt();
	static void testSLLSearch();

	static void testDLLPushBack();
	static void testDLLPushFront();
	static void testDLLPushAt();
	static void testDLLPopBack();
	static void testDLLPopFront();
	static void testDLLPopAt();
	static void testDLLSearch();
};

