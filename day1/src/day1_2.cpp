#include <tuple>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <set>

typedef std::tuple<std::vector<int>*, std::vector<int>*> TuplesOfVec;

int calcSimilarityScore(std::vector<int> &first, std::vector<int> &second);
TuplesOfVec readLists(std::string fileLocation);

int main() {
    TuplesOfVec lists = readLists("day1/data/input.txt");
    std::vector<int> first = *std::get<0>(lists);
    std::vector<int> second = *std::get<1>(lists);
    int similarityScore = calcSimilarityScore(first, second);
    std::cout << "Similarity Score: " << similarityScore << std::endl;
    return 0;
}

int calcSimilarityScore(std::vector<int> &first, std::vector<int> &second) {
    std::set<int> checkSet(first.begin(), first.end());
    int total = 0;
    for (int currentSetItem : checkSet) {
        int currentValTotal = 0;
        for (int secondItem : second) {
            if (secondItem == currentSetItem) {
                currentValTotal++;
            }
        }

        total += (currentValTotal * currentSetItem);
        currentValTotal = 0;
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