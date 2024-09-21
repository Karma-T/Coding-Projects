
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

// Function to read data from CSV file
void readCSV(const string& fileName, vector<pair<string, double>>& data) {
    ifstream fin(fileName);
    if (fin.fail()) {
        cerr << "Failed to open the file: " << fileName << endl;
        exit(1);
    }

    string line, leftPart;
    double rightPart;
    while (getline(fin, line)) {
        size_t pos = line.find(',');
        leftPart = line.substr(0, pos);
        rightPart = stod(line.substr(pos + 1));
        data.push_back({leftPart, rightPart});
    }

    fin.close();
}

// Function to check if two doubles are approximately equal
bool approxEquals(double a, double b) {
    return abs(a - b) < 0.001;
}

int main() {
    // Initialize correctAnswers to count the number of correct responses
    int correctAnswers = 0;

    // Declare variables for storing questions and answers
    vector<pair<string, double>> data;

    // Read data from CSV file
    readCSV("problems.csv", data);

    // Generate a random seed based on system time for random question selection
    srand(time(nullptr));

    // Determine the total number of questions initially available
    int totalQuestions = data.size();

    // Loop until there are no more questions in data
    while (!data.empty()) {
        // Select a random question from data
        int randIndex = rand() % data.size();

        // Prompt the user with the selected question and read their input
        cout << "What is " << data[randIndex].first << "? ";
        double userInput;
        cin >> userInput;

        // Check if the user's input is approximately equal to the correct answer
        if (approxEquals(userInput, data[randIndex].second)) {
            cout << "True" << endl;
            correctAnswers++;
        } else {
            cout << "False" << endl;
        }

        // Remove the answered question from consideration
        swap(data[randIndex], data.back());
        data.pop_back();

        // Check if at least 60% of the answers are correct; if so, stop the quiz
        if (static_cast<double>(correctAnswers) / totalQuestions >= 0.6) {
            cout << "At least 60% is correct. Stop." << endl;
            break;
        }
    }

    // Calculate and output the percentage of correct answers
    double percentageCorrect = (static_cast<double>(correctAnswers) / totalQuestions) * 100;
    cout << "Percentage correct: " << percentageCorrect << "%" << endl;

    return 0;
}