#include <iostream>
#include <vector>
#include <string>
#include <limits>   // for numeric_limits
#include <iomanip>  // for setw

using namespace std;

struct Student {
    int roll;
    string name;
    float marks;
};

vector<Student> students;

void pauseAndClearLine() {
    // Clear remaining input on the current line (useful after >>)
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool rollExists(int roll) {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].roll == roll) return true;
    }
    return false;
}

void addStudent() {
    Student s;
    cout << "\nEnter Roll Number: ";
    while (!(cin >> s.roll)) {
        cout << "Invalid input. Enter an integer for roll: ";
        cin.clear();
        pauseAndClearLine();
    }
    pauseAndClearLine(); // remove newline left by >>

    if (rollExists(s.roll)) {
        cout << "A student with roll " << s.roll << " already exists. Aborting add.\n";
        return;
    }

    cout << "Enter Name: ";
    getline(cin, s.name);
    if (s.name.size() == 0) {
        cout << "Name cannot be empty. Aborting add.\n";
        return;
    }

    cout << "Enter Marks (0-100): ";
    while (!(cin >> s.marks) || s.marks < 0.0f || s.marks > 100.0f) {
        cout << "Invalid marks. Enter a number between 0 and 100: ";
        cin.clear();
        pauseAndClearLine();
    }
    pauseAndClearLine();

    students.push_back(s);
    cout << "Student added successfully.\n";
}

void displayStudents() {
    if (students.empty()) {
        cout << "\nNo records to display.\n";
        return;
    }

    cout << "\n--- Student Records ---\n";
    cout << left << setw(8) << "Roll" << setw(30) << "Name" << setw(8) << "Marks" << "\n";
    cout << "-------------------------------------------------\n";
    for (size_t i = 0; i < students.size(); ++i) {
        cout << left << setw(8) << students[i].roll
             << setw(30) << students[i].name
             << setw(8) << fixed << setprecision(2) << students[i].marks << "\n";
    }
}

void searchStudent() {
    int roll;
    cout << "\nEnter Roll Number to search: ";
    while (!(cin >> roll)) {
        cout << "Invalid input. Enter an integer for roll: ";
        cin.clear();
        pauseAndClearLine();
    }
    pauseAndClearLine();

    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].roll == roll) {
            cout << "\nRecord Found:\n";
            cout << "Roll: " << students[i].roll << "\n";
            cout << "Name: " << students[i].name << "\n";
            cout << "Marks: " << fixed << setprecision(2) << students[i].marks << "\n";
            return;
        }
    }
    cout << "Student with roll " << roll << " not found.\n";
}

void updateStudent() {
    int roll;
    cout << "\nEnter Roll Number to update: ";
    while (!(cin >> roll)) {
        cout << "Invalid input. Enter an integer for roll: ";
        cin.clear();
        pauseAndClearLine();
    }
    pauseAndClearLine();

    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].roll == roll) {
            cout << "Current Name: " << students[i].name << "\n";
            cout << "Enter New Name (leave blank to keep current): ";
            string newName;
            getline(cin, newName);
            if (newName.size() != 0) students[i].name = newName;

            cout << "Current Marks: " << fixed << setprecision(2) << students[i].marks << "\n";
            cout << "Enter New Marks (or -1 to keep current): ";
            float newMarks;
            while (!(cin >> newMarks)) {
                cout << "Invalid input. Enter a number for marks or -1 to keep current: ";
                cin.clear();
                pauseAndClearLine();
            }
            pauseAndClearLine();
            if (newMarks >= 0.0f && newMarks <= 100.0f) {
                students[i].marks = newMarks;
            } else if (newMarks != -1.0f) {
                cout << "Invalid marks entered; keeping old marks.\n";
            }

            cout << "Record updated successfully.\n";
            return;
        }
    }

    cout << "Student with roll " << roll << " not found.\n";
}

void deleteStudent() {
    int roll;
    cout << "\nEnter Roll Number to delete: ";
    while (!(cin >> roll)) {
        cout << "Invalid input. Enter an integer for roll: ";
        cin.clear();
        pauseAndClearLine();
    }
    pauseAndClearLine();

    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].roll == roll) {
            // erase by shifting
            students.erase(students.begin() + i);
            cout << "Record deleted successfully.\n";
            return;
        }
    }
    cout << "Student with roll " << roll << " not found.\n";
}

int main() {
    int choice = 0;

    do {
        cout << "\n===== Student Data Management =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid choice. Please enter a number 1-6.\n";
            cin.clear();
            pauseAndClearLine();
            continue;
        }
        pauseAndClearLine();

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please select 1-6.\n";
        }
    } while (choice != 6);

    return 0;
}

