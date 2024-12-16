#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <chrono>

typedef std::tuple<std::vector<int>*, std::vector<int>*> TuplesOfVec;

TuplesOfVec readLists(std::string fileLocation);
int getTotalDistance(std::vector<int> &first, std::vector<int> &second);
void timeIt(int (*func)(), int timesToRun); // This can be replaced with the c++ 11 function
int readListsAndGetTotalDistance();

int main() {
    timeIt(readListsAndGetTotalDistance, 25);
}

int readListsAndGetTotalDistance() {
    TuplesOfVec lists = readLists("day1/data/input.txt");
    std::vector<int> firstList = *std::get<0>(lists);
    std::vector<int> secondList = *std::get<1>(lists);
    std::sort(firstList.begin(), firstList.end());
    std::sort(secondList.begin(), secondList.end());
    return getTotalDistance(firstList, secondList);
}

void timeIt(int (*func)(), int timesToRun) {
    int sum = 0;
    for (int i = 0; i < timesToRun; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = end - start;
        sum += duration.count();
    }
    std::cout << "Average Runtime: " << (double)sum / timesToRun << std::endl;
}

int getTotalDistance(std::vector<int> &first, std::vector<int> &second) {
    int total = 0;
    for (int i = 0; i < first.size(); i++) {
        int distance = first[i] - second[i];
        if (distance < 0) {
            distance *= -1;
        }
        total += distance;
    }
    return total;
}

TuplesOfVec readLists(std::string fileLocation) {
    std::vector<int> *firstList = new std::vector<int>();
    std::vector<int> *secondList = new std::vector<int>();
    std::ifstream file(fileLocation);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t start = line.find("   ");
            size_t end = start + 3;
            std::string first = line.substr(0, start);
            std::string second = line.substr(end);
            firstList -> push_back(std::stoi(first));
            secondList -> push_back(std::stoi(second));
        }
        file.close();
    } else {
        std::cerr << "Error opening file!" << std::endl;
    }

    return std::make_tuple(firstList, secondList);
}