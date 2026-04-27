#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Course structure
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Display menu
void displayMenu() {
    cout << "\n1. Load Data Structure\n";
    cout << "2. Print Course List\n";
    cout << "3. Print Course Information\n";
    cout << "9. Exit\n";
    cout << "Enter choice: ";
}

// Load file
void loadCourses(map<string, Course>& courses, string fileName) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error opening file.\n";
        return;
    }

    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;

        Course course;

        getline(ss, course.courseNumber, ',');
        getline(ss, course.courseTitle, ',');

        while (getline(ss, token, ',')) {
            course.prerequisites.push_back(token);
        }

        courses[course.courseNumber] = course;
    }

    file.close();
    cout << "Data loaded.\n";
}

// Print all courses
void printCourseList(map<string, Course>& courses) {
    if (courses.empty()) {
        cout << "No data loaded.\n";
        return;
    }

    for (auto it = courses.begin(); it != courses.end(); ++it) {
        cout << it->second.courseNumber << ", "
             << it->second.courseTitle << endl;
    }
}

// Print one course
void printCourseInfo(map<string, Course>& courses) {
    string courseNumber;
    cout << "Enter course number: ";
    cin >> courseNumber;

    transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);

    if (courses.find(courseNumber) == courses.end()) {
        cout << "Course not found.\n";
        return;
    }

    Course course = courses[courseNumber];

    cout << course.courseNumber << ", " << course.courseTitle << endl;

    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None\n";
    } else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); i++) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

int main() {
    map<string, Course> courses;
    int choice = 0;
    string fileName;

    while (choice != 9) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter file name: ";
                cin >> fileName;
                loadCourses(courses, fileName);
                break;

            case 2:
                printCourseList(courses);
                break;

            case 3:
                printCourseInfo(courses);
                break;

            case 9:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}
