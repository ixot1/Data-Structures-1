#include "Benchmark.h"
#include "Dynamic_Array.h"
#include "Singly_Linked_List.h"
#include "Doubly_Linked_List.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <string>
#include <functional>
#include <vector>

const int Benchmark::REPETITIONS = 10;
const int Benchmark::SEED = 12345;
const std::vector<int> Benchmark::SIZES = { 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000 };

//helper class encapsulating the rng engine and distribution
class RandomGenerator {
private:
    std::mt19937 generator;
    std::uniform_int_distribution<> distribution;
public:
    RandomGenerator(int seed, int min, int max) : generator(seed), distribution(min, max) {}
    int getNext() { return distribution(generator); }
};

template <typename StructureType>
static void runBenchmark(const std::string& testName, const std::string& fileName, int numCopies,
    std::function<void(StructureType&, RandomGenerator&, int)> operation)
{
    std::cout << "\n[ Beginning benchmark: " << testName << " ]\n";
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Couldn't open save file.\n";
        return;
    }

    file << "Size_N;Avg_Time_ns\n";

    for (int n : Benchmark::SIZES) {
        double totalTimeNs = 0.0;

        for (int r = 0; r < Benchmark::REPETITIONS; ++r) {

            //preparation phase
            //we create multiple instances to prevent low-resolution clock errors for fast O(1) operations
            std::vector<StructureType> copies(numCopies);

            //deterministic filling of structures based on the current repetition
            RandomGenerator prepRng(Benchmark::SEED + r, 1, 1000000);
            for (int i = 0; i < numCopies; ++i) {
                for (int j = 0; j < n; ++j) {
                    copies[i].push_back(prepRng.getNext());
                }
            }

            RandomGenerator testRng(Benchmark::SEED + 999 + r, 1, 1000000);

            //measurement phase
            //start stopwatch - isolating the actual operation from data generation
            auto start = std::chrono::high_resolution_clock::now();

            for (int i = 0; i < numCopies; ++i) {
                //execute the passed lambda function (e.g. pop_back)
                operation(copies[i], testRng, n);
            }

            auto end = std::chrono::high_resolution_clock::now();

            //calculations
            //calculate total nanoseconds for all copies, then divide by numCopies for an average single-op time
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            totalTimeNs += (static_cast<double>(duration) / numCopies);
        }

        //final average across all repetitions to smooth out OS-level interruptions
        double avgTimeNs = totalTimeNs / Benchmark::REPETITIONS;

        file << n << ";" << avgTimeNs << "\n";
        std::cout << "   N = " << n << " \tfinished. Avg: " << avgTimeNs << " ns\n";
    }
    file.close();
}

template <typename StructureType>
static void runSearchBenchmark(const std::string& testName, const std::string& fileName, int numCopies,
    std::function<void(StructureType&, int)> operation)
{
    std::cout << "\n[ Beginning benchmark: " << testName << " ]\n";
    std::ofstream file(fileName);
    if (!file.is_open()) return;
    file << "Size_N;Avg_Time_ns\n";

    for (int n : Benchmark::SIZES) {
        double totalTimeNs = 0.0;

        for (int r = 0; r < Benchmark::REPETITIONS; ++r) {
            std::vector<StructureType> copies(numCopies);

            //preparation phase
            for (int i = 0; i < numCopies; ++i) {
                RandomGenerator prepRng(Benchmark::SEED + r, 1, 1000000);
                for (int j = 0; j < n; ++j) {
                    copies[i].push_back(prepRng.getNext());
                }
            }

            //fair drawing of the element outside the stopwatch
            int targetValue = 0;
            if (n > 0) {
                //we use a different rng offset so we don't disrupt the deterministic sequence of prepRng
                RandomGenerator idxRng(Benchmark::SEED + r + 123, 0, n - 1);
                int randomIndex = idxRng.getNext() % n;

                //extract a guaranteed-to-exist value from the first copy before the timer starts
                targetValue = copies[0].get_component(randomIndex);
            }

            //measurement phase
            //timer strictly wraps the search execution
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < numCopies; ++i) {
                operation(copies[i], targetValue);
            }
            auto end = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            totalTimeNs += (static_cast<double>(duration) / numCopies);
        }

        double avgTimeNs = totalTimeNs / Benchmark::REPETITIONS;
        file << n << ";" << avgTimeNs << "\n";
        std::cout << "   N = " << n << " \tfinished. Avg: " << avgTimeNs << " ns\n";
    }
    file.close();
}

// ============================================================================
// dynamic array tests
// ============================================================================

void Benchmark::testArrayPushBack() {
    runBenchmark<DynamicArray>("DA::push_back", "DA_push_back.csv", 50,
        [](DynamicArray& ds, RandomGenerator& rng, int n) { ds.push_back(rng.getNext()); });
}

void Benchmark::testArrayPushFront() {
    runBenchmark<DynamicArray>("DA::push_front", "DA_push_front.csv", 50,
        [](DynamicArray& ds, RandomGenerator& rng, int n) { ds.push_front(rng.getNext()); });
}

void Benchmark::testArrayPushAt() {
    runBenchmark<DynamicArray>("DA::push_at", "DA_push_at.csv", 50,
        [](DynamicArray& ds, RandomGenerator& rng, int n) { ds.push_at(rng.getNext() % (n + 1), rng.getNext()); });
}

void Benchmark::testArrayPopBack() {
    runBenchmark<DynamicArray>("DA::pop_back", "DA_pop_back.csv", 50,
        [](DynamicArray& ds, RandomGenerator& rng, int n) { ds.pop_back(); });
}

void Benchmark::testArrayPopFront() {
    runBenchmark<DynamicArray>("DA::pop_front", "DA_pop_front.csv", 50,
        [](DynamicArray& ds, RandomGenerator& rng, int n) { ds.pop_front(); });
}

void Benchmark::testArrayPopAt() {
    runBenchmark<DynamicArray>("DA::pop_at", "DA_pop_at.csv", 50,
        [](DynamicArray& ds, RandomGenerator& rng, int n) { ds.pop_at(rng.getNext() % n); });
}

void Benchmark::testArraySearch() {
    runSearchBenchmark<DynamicArray>("DA::search", "DA_search.csv", 50,
        [](DynamicArray& ds, int target) { ds.search(target); });
}

// ============================================================================
// singly linked list tests
// ============================================================================

void Benchmark::testSLLPushBack() {
    runBenchmark<SinglyLinkedList>("SLL::push_back", "SLL_push_back.csv", 50,
        [](SinglyLinkedList& ds, RandomGenerator& rng, int n) { ds.push_back(rng.getNext()); });
}

void Benchmark::testSLLPushFront() {
    runBenchmark<SinglyLinkedList>("SLL::push_front", "SLL_push_front.csv", 50,
        [](SinglyLinkedList& ds, RandomGenerator& rng, int n) { ds.push_front(rng.getNext()); });
}

void Benchmark::testSLLPushAt() {
    runBenchmark<SinglyLinkedList>("SLL::push_at", "SLL_push_at.csv", 50,
        [](SinglyLinkedList& ds, RandomGenerator& rng, int n) { ds.push_at(rng.getNext() % (n + 1), rng.getNext()); });
}

void Benchmark::testSLLPopBack() {
    runBenchmark<SinglyLinkedList>("SLL::pop_back", "SLL_pop_back.csv", 50,
        [](SinglyLinkedList& ds, RandomGenerator& rng, int n) { ds.pop_back(); });
}

void Benchmark::testSLLPopFront() {
    runBenchmark<SinglyLinkedList>("SLL::pop_front", "SLL_pop_front.csv", 50,
        [](SinglyLinkedList& ds, RandomGenerator& rng, int n) { ds.pop_front(); });
}

void Benchmark::testSLLPopAt() {
    runBenchmark<SinglyLinkedList>("SLL::pop_at", "SLL_pop_at.csv", 50,
        [](SinglyLinkedList& ds, RandomGenerator& rng, int n) { ds.pop_at(rng.getNext() % n); });
}

void Benchmark::testSLLSearch() {
    runSearchBenchmark<SinglyLinkedList>("SLL::search", "SLL_search.csv", 50,
        [](SinglyLinkedList& ds, int target) { ds.search(target); });
}

// ============================================================================
// doubly linked list tests
// ============================================================================

void Benchmark::testDLLPushBack() {
    runBenchmark<DoublyLinkedList>("DLL::push_back", "DLL_push_back.csv", 50,
        [](DoublyLinkedList& ds, RandomGenerator& rng, int n) { ds.push_back(rng.getNext()); });
}

void Benchmark::testDLLPushFront() {
    runBenchmark<DoublyLinkedList>("DLL::push_front", "DLL_push_front.csv", 50,
        [](DoublyLinkedList& ds, RandomGenerator& rng, int n) { ds.push_front(rng.getNext()); });
}

void Benchmark::testDLLPushAt() {
    runBenchmark<DoublyLinkedList>("DLL::push_at", "DLL_push_at.csv", 50,
        [](DoublyLinkedList& ds, RandomGenerator& rng, int n) { ds.push_at(rng.getNext() % (n + 1), rng.getNext()); });
}

void Benchmark::testDLLPopBack() {
    runBenchmark<DoublyLinkedList>("DLL::pop_back", "DLL_pop_back.csv", 50,
        [](DoublyLinkedList& ds, RandomGenerator& rng, int n) { ds.pop_back(); });
}

void Benchmark::testDLLPopFront() {
    runBenchmark<DoublyLinkedList>("DLL::pop_front", "DLL_pop_front.csv", 50,
        [](DoublyLinkedList& ds, RandomGenerator& rng, int n) { ds.pop_front(); });
}

void Benchmark::testDLLPopAt() {
    runBenchmark<DoublyLinkedList>("DLL::pop_at", "DLL_pop_at.csv", 50,
        [](DoublyLinkedList& ds, RandomGenerator& rng, int n) { ds.pop_at(rng.getNext() % n); });
}

void Benchmark::testDLLSearch() {
    runSearchBenchmark<DoublyLinkedList>("DLL::search", "DLL_search.csv", 50,
        [](DoublyLinkedList& ds, int target) { ds.search(target); });
}