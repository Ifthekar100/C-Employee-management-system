#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>
#include <limits>
#include <sstream>
#include <thread>
#include <chrono> // For sleep functions
#include <windows.h> // To control console output

using namespace std;

// Function to clear the screen (Windows-specific, use system("clear") for Linux/Mac)
void clearScreen() {
    system("cls");
}

// Function to print text in the center of the screen
void printCentered(const string& message) {
    const int width = 80; // Assume a fixed console width of 80 characters
    int spaces = (width - message.length()) / 2; // Calculate leading spaces for centering

    // Print leading spaces for centering
    for (int i = 0; i < spaces; ++i) {
        cout << " ";
    }

    // Print the message
    cout << message << endl;
}

// Function to animate a message and print it in the center
void animateMessage(string message, int delay) {
    const int width = 80; // Assume a fixed console width of 80 characters
    int spaces = (width - message.length()) / 2; // Calculate leading spaces for centering

    // Animate by displaying the message incrementally
    for (int i = 0; i < message.length(); ++i) {
        clearScreen(); // Clear screen to simulate animation effect
        // Print leading spaces for centering
        for (int j = 0; j < spaces; ++j) {
            cout << " ";
        }
        cout << message.substr(0, i + 1) << endl; // Show the message incrementally
        this_thread::sleep_for(chrono::milliseconds(100)); // Adjust speed of animation
    }

    this_thread::sleep_for(chrono::milliseconds(delay));  // Wait before clearing the screen completely
    clearScreen();  // Clear screen after animation
}

// Function to show the project info animation at the beginning
void startupAnimation() {
    clearScreen();
    string projectInfo =
        "================================================\n"
        "       *** EMPLOYEE MANAGEMENT SYSTEM ***      \n"   // Highlighting the project name
        "================================================\n"
        "            Galactic Workforce Navigator       \n"
        "================================================\n"
        "             Team Members:                    \n"
        "   Sadman Mehtab Ifaz      ID: C241072        \n"
        "   Jiban Mahmud            ID: C241068        \n"
        "   Ifthekar Uddin Jewel    ID: C241070        \n"
        "================================================\n";

    animateMessage(projectInfo, 3000);  // Show for 3 seconds
}

// Employee Class
class Employee {
public:
    string empID, firstName, lastName, department, email, contact, password, position, salary, contractPeriod;

    void registerEmployee() {
        string confirmPassword;

        cout << "Enter First Name: ";
        cin >> firstName;
        cout << "Enter Last Name: ";
        cin >> lastName;
        cout << "Enter Department (Engineering, Marketing, Sales, etc.): ";
        cin >> department;
        cout << "Enter Email Address: ";
        cin >> email;
        cout << "Enter Contact Number: ";
        cin >> contact;

        // Username and Password setup
        cout << "Create a Password: ";
        cin >> password;

        // Confirm Password
        cout << "Confirm Password: ";
        cin >> confirmPassword;
        while (confirmPassword != password) {
            cout << "Passwords do not match! Try again." << endl;
            cout << "Confirm Password: ";
            cin >> confirmPassword;
        }

        // Generate Unique Employee ID
        if (department == "Engineering") {
            empID = "ENG-" + to_string(rand() % 100 + 101);
        } else if (department == "Marketing") {
            empID = "MKT-" + to_string(rand() % 100 + 201);
        } else if (department == "Sales") {
            empID = "SAL-" + to_string(rand() % 100 + 301);
        } else if (department == "ProductManagement") {
            empID = "PM-" + to_string(rand() % 100 + 401);
        } else {
            empID = "CS-" + to_string(rand() % 100 + 501);
        }

        // Get Salary and Contract Period
        cout << "Enter Salary: ";
        cin >> salary;
        cout << "Enter Contract Period (in years): ";
        cin >> contractPeriod;

        // Save to file
        ofstream outFile("employees.txt", ios::app);
        outFile << email << " " << password << " " << empID << " " << firstName << " " << lastName << " " << department << " " << contact << " " << salary << " " << contractPeriod << endl;
        outFile.close();

        cout << "Employee registered successfully! Unique Employee ID: " << empID << endl;
    }

    bool login() {
        string enteredEmail, enteredPassword;
        cout << "Enter your Email: ";
        cin >> enteredEmail;
        cout << "Enter your Password: ";
        cin >> enteredPassword;

        ifstream inFile("employees.txt");
        string line;
        bool found = false;

        while (getline(inFile, line)) {
            stringstream ss(line);
            string email, password, empID, firstName, lastName, department, contact, salary, contractPeriod;

            ss >> email >> password >> empID >> firstName >> lastName >> department >> contact >> salary >> contractPeriod;

            if (enteredEmail == email && enteredPassword == password) {
                // If credentials match, store the employee information
                this->empID = empID;
                this->firstName = firstName;
                this->lastName = lastName;
                this->department = department;
                this->email = email;
                this->contact = contact;
                this->salary = salary;
                this->contractPeriod = contractPeriod;
                this->password = password;

                found = true;
                break;
            }
        }

        inFile.close();
        return found;
    }

    void viewProfile() {
        clearScreen();
        printCentered("==============================================");
        printCentered("            Employee Profile                 ");
        printCentered("==============================================");
        cout << "Employee ID: " << empID << endl;
        cout << "First Name: " << firstName << endl;
        cout << "Last Name: " << lastName << endl;
        cout << "Department: " << department << endl;
        cout << "Email: " << email << endl;
        cout << "Contact: " << contact << endl;
        cout << "Salary: " << salary << endl;
        cout << "Contract Period: " << contractPeriod << " years" << endl;
        printCentered("==============================================");
    }

    void changePassword() {
        clearScreen();
        string enteredEmail, oldPassword, newPassword;
        cout << "Enter your Email to change password: ";
        cin >> enteredEmail;

        if (enteredEmail == email) {
            cout << "Enter your current Password: ";
            cin >> oldPassword;

            if (oldPassword == password) {
                cout << "Enter new Password: ";
                cin >> newPassword;
                password = newPassword;

                // Update password in file
                ifstream inFile("employees.txt");
                ofstream tempFile("temp.txt");
                string line;

                while (getline(inFile, line)) {
                    stringstream ss(line);
                    string fileEmail, filePassword, empID, firstName, lastName, department, contact, salary, contractPeriod;

                    ss >> fileEmail >> filePassword >> empID >> firstName >> lastName >> department >> contact >> salary >> contractPeriod;

                    if (fileEmail == email) {
                        tempFile << fileEmail << " " << newPassword << " " << empID << " " << firstName << " " << lastName << " " << department << " " << contact << " " << salary << " " << contractPeriod << endl;
                    } else {
                        tempFile << line << endl;
                    }
                }

                inFile.close();
                tempFile.close();
                remove("employees.txt");
                rename("temp.txt", "employees.txt");

                cout << "Password changed successfully!" << endl;
            } else {
                cout << "Incorrect password. Try again." << endl;
            }
        } else {
            cout << "Email does not match. Try again." << endl;
        }
    }
};

// Admin Class
class Admin {
public:
    string username = "admin", password = "admin123";

    bool adminLogin() {
        string enteredUsername, enteredPassword;
        cout << "Enter Admin Username: ";
        cin >> enteredUsername;
        cout << "Enter Admin Password: ";
        cin >> enteredPassword;
        return (enteredUsername == username && enteredPassword == password);
    }
};

// Main Menu Function with Login Success Animation
void mainMenu() {
    Employee emp;
    Admin admin;
    int choice;

    while (true) {
        clearScreen();
        printCentered("==============================================");
        printCentered("                 Main Menu                   ");
        printCentered("==============================================");
        printCentered("1. Employee Login");
        printCentered("2. Admin Login");
        printCentered("3. Exit");
        printCentered("==============================================");
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            clearScreen();
            printCentered("==============================================");
            printCentered("                 Employee Login               ");
            printCentered("==============================================");
            if (emp.login()) {
                cout << "\nLogin Successful!\n";
                animateMessage("Logging in as Employee...", 3000); // Display "Login successful" animation for 3 seconds
                emp.viewProfile(); // Show Employee profile
            } else {
                cout << "Employee information not found.\n";
                cout << "Press any key to go back to Main Menu.";
                cin.get(); cin.ignore();
            }
        } else if (choice == 2) {
            clearScreen();
            printCentered("==============================================");
            printCentered("                   Admin Login                ");
            printCentered("==============================================");
            if (admin.adminLogin()) {
                cout << "\nLogin Successful!\n";
                animateMessage("Logging in as Admin...", 3000); // Display "Login successful" animation for 3 seconds
                // Admin-related functionalities here
            } else {
                cout << "Admin login failed.\n";
                cout << "Press any key to go back to Main Menu.";
                cin.get(); cin.ignore();
            }
        } else if (choice == 3) {
            break;
        }
    }
}

int main() {
    startupAnimation(); // Show startup animation
    mainMenu();         // Go to main menu
    return 0;
}
