#include <tuple>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <set>

typedef std::vector<std::vector<int> *> Vector2D;

std::vector<std::string> *split(std::string input, std::string delimiter);
Vector2D *readLists(std::string fileLocation);
int calcNumSafeReports(const Vector2D &reports);
void deleteVector2D(Vector2D *vec);

int main() {
    Vector2D *reports = readLists("day2/data/input.txt");
    int numSafeReports = calcNumSafeReports(*reports);
    std::cout << numSafeReports << std::endl;
    deleteVector2D(reports);
    return 0;
}

void deleteVector2D(Vector2D *vec) {
    Vector2D deRefVec = *vec;
    for (int i = 0; i < deRefVec.size(); i++) {
        delete(deRefVec[i]);
    }
    delete(vec); 
}

/**
 * Determing how many reports are safe out of the given reports.
 * 
 * @param reports A reference to the 2d vec of reports.
 * @return The number of safe reports.
 */
int calcNumSafeReports(const Vector2D &reports) {
    int numSafeReports = reports.size();
    for (std::vector<int> *report : reports) {
        std::vector<int> derefReport = *report;
        bool increasing = false;
        int first = derefReport[0], second = derefReport[1];
        if (first - second < 0) {
            increasing = true;
        }

        for (int startIndex = 0; startIndex < derefReport.size() - 1; startIndex++) {
            // if value is 1 or 2 bigger and inc/dec cont.
            int start = derefReport[startIndex], end = derefReport[startIndex + 1];
            int step = start - end;
            bool wasIncButChanged = increasing && step > 0;
            bool wasDecButChanged = !increasing && step < 0;
            bool jumpTooLarge = step < -3 || step > 3;
            bool noChangeInStep = step == 0;
            if (wasIncButChanged || wasDecButChanged || jumpTooLarge || noChangeInStep) {
                numSafeReports -= 1;
                break;
            }
        }
    }
    return numSafeReports;
}

/**
 * Read lines from the input file and parse into a 2d vector of ints.
 * 
 * @param fileLocation The location of the file to parse.
 * @return A pointer to a 2d vector of ints.
 */
Vector2D *readLists(std::string fileLocation) {
    Vector2D *outer = new Vector2D();
    std::ifstream file(fileLocation);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> *splitLine = split(line, " ");
            std::vector<int> *inner = new std::vector<int>();
            // Map to ints
            for (std::string value : *splitLine) {
                inner -> push_back(std::stoi(value));
            }
            // parse string to int
            delete(splitLine);
            outer -> push_back(inner);
        }
        file.close();
    } else {
        std::cerr << "Error opening file!" << std::endl;
    }

    return outer;
}

/**
 * This function is used to split a string on a variable delimiter.
 * 
 * @param input The string to split.
 * @param delimiter The value to split the string by.
 * @return A pointer to a vector of strings created by "splitting" the input on the delimiter.
 */
std::vector<std::string> *split(std::string input, std::string delimiter) {
    int delimLen = delimiter.size();
    std::vector<int> indices = {-delimLen};
    for (int charStart = 0; charStart < input.size() + 1 - delimLen; charStart++) {
        std::string currentSub = input.substr(charStart, delimLen);
        if (currentSub == delimiter) {
            indices.push_back(charStart);
        }
    }

    std::vector<std::string> *values = new std::vector<std::string>();
    for (int i = 0; i < indices.size(); i++) {
        std::string value = input.substr(indices[i] + delimLen, indices[i + 1] - indices[i]);
        values -> push_back(value);
    }

    return values;
}