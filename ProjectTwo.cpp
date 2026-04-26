#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <limits>

using namespace std;

struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

vector<Course> courses;

string toUpperCase(string text) {
    for (size_t i = 0; i < text.length(); i++) {
        text[i] = toupper(text[i]);
    }
    return text;
}

void loadCourses(string fileName) {
    ifstream file(fileName);
    string line;

    if (!file.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    courses.clear();

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string token;
        Course course;

        getline(ss, token, ',');
        course.courseNumber = toUpperCase(token);

        getline(ss, token, ',');
        course.courseName = token;

        while (getline(ss, token, ',')) {
            course.prerequisites.push_back(toUpperCase(token));
        }

        courses.push_back(course);
    }

    file.close();
    cout << "Data loaded successfully." << endl;
}

bool compareCourses(const Course& a, const Course& b) {
    return a.courseNumber < b.courseNumber;
}

void printCourseList() {
    if (courses.empty()) {
        cout << "No course data loaded." << endl;
        return;
    }

    vector<Course> sortedCourses = courses;
    sort(sortedCourses.begin(), sortedCourses.end(), compareCourses);

    cout << "Here is a sample schedule:" << endl;
    for (size_t i = 0; i < sortedCourses.size(); i++) {
        cout << sortedCourses[i].courseNumber << ", " << sortedCourses[i].courseName << endl;
    }
}

void printCourse(string courseNumber) {
    if (courses.empty()) {
        cout << "No course data loaded." << endl;
        return;
    }

    courseNumber = toUpperCase(courseNumber);

    for (size_t i = 0; i < courses.size(); i++) {
        if (courses[i].courseNumber == courseNumber) {
            cout << courses[i].courseNumber << ", " << courses[i].courseName << endl;

            cout << "Prerequisites: ";
            if (courses[i].prerequisites.empty()) {
                cout << "None";
            } else {
                for (size_t j = 0; j < courses[i].prerequisites.size(); j++) {
                    cout << courses[i].prerequisites[j];
                    if (j < courses[i].prerequisites.size() - 1) {
                        cout << ", ";
                    }
                }
            }
            cout << endl;
            return;
        }
    }

    cout << "Course not found." << endl;
}

void printMenu() {
    cout << endl;
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
    cout << "What would you like to do? ";
}

int main() {
    int choice = 0;
    string fileName;
    string courseNumber;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        printMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Enter file name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, fileName);
                loadCourses(fileName);
                break;

            case 2:
                printCourseList();
                break;

            case 3:
                cout << "What course do you want to know about? ";
                cin >> courseNumber;
                printCourse(courseNumber);
                break;

            case 9:
                cout << "Thank you for using the course planner!" << endl;
                break;

            default:
                cout << choice << " is not a valid option." << endl;
                break;
        }
    }

    return 0;
}
