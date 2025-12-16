#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <sstream>

using namespace std;
using namespace chrono;


void readNumbersFromFile(const string& fileName, vector<int>& data) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error: Unable to open file." << endl;
        exit(1);
    }

    string line, token;
    while (getline(file, line)) {
        stringstream ss(line);
        while (getline(ss, token, ',')) {
            if (!token.empty())
                data.push_back(stoi(token));
        }
    }

    file.close();
}

void optimizedSort(vector<int>& data) {
    sort(data.begin(), data.end());
}


void writeSortedDataToFile(const string& fileName, const vector<int>& data) {
    ofstream file(fileName);
    for (int num : data)
        file << num << "\n";
    file.close();
}

int main() {
    vector<int> numbers;

    cout << "Reading numbers from file..." << endl;
    readNumbersFromFile("numbers.txt", numbers);

    cout << "Total numbers read: " << numbers.size() << endl;

    cout << "Starting optimized sorting..." << endl;

    auto start = high_resolution_clock::now();

    optimizedSort(numbers);

    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Sorting completed successfully." << endl;
    cout << "Runtime (milliseconds): " << duration.count() << " ms" << endl;

    writeSortedDataToFile("sorted_numbers.txt", numbers);

    cout << "Sorted output saved to sorted_numbers.txt" << endl;

    return 0;
}
