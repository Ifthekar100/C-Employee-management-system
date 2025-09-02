#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>
#include <limits>
#include <sstream>

using namespace std;

void clearScreen() {
    system("cls");
}

void displayHeader(string title) {
    clearScreen();
    cout << "===================================" << endl;
    cout << "        " << title << endl;
    cout << "===================================" << endl << endl;
}

// Employee Class
class Employee {
public:
    string empID, firstName, lastName, department, email, contact, password, username, position, salary;

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

        // Save to file
        ofstream outFile("employees.txt", ios::app);
        outFile << email << " " << password << " " << empID << " " << firstName << " " << lastName << " " << department << " " << contact << endl;
        outFile.close();

        cout << "Employee registered successfully! Unique Employee ID: " << empID << endl;
    }

    bool login() {
        string enteredEmail, enteredPassword;
        cout << "Enter your Email: ";
        cin >> enteredEmail;
        cout << "Enter your Password: ";
        cin >> enteredPassword;

        // Check if login is successful
        if (enteredEmail == email && enteredPassword == password) {
            return true;
        }
        return false;
    }

    void viewProfile() {
        cout << "\nEmployee Profile:\n";
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "Department: " << department << endl;
        cout << "Email: " << email << endl;
        cout << "Contact: " << contact << endl;
        cout << "Employee ID: " << empID << endl;
        cout << "Position: " << position << endl;
        cout << "Salary: " << salary << endl;
        cout << "\nPress 1 to return to Employee Menu: ";
        int choice;
        cin >> choice;
    }

    void changePassword() {
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

    void manageEmployees() {
        int choice;
        while (true) {
            displayHeader("Admin Menu: Manage Employees");
            cout << "1. View All Employees\n";
            cout << "2. Register New Employee\n";
            cout << "3. Edit Employee\n";
            cout << "4. Delete Employee\n";
            cout << "5. Back to Admin Menu\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1) {
                viewAllEmployees();
            } else if (choice == 2) {
                Employee emp;
                emp.registerEmployee();
                cout << "Press any key to return to Admin Menu.";
                cin.get(); cin.ignore(); // Wait for key press
            } else if (choice == 3) {
                editEmployee();
            } else if (choice == 4) {
                deleteEmployee();
            } else if (choice == 5) {
                break;
            }
        }
    }

    void viewAllEmployees() {
        ifstream inFile("employees.txt");
        string line;
        displayHeader("Employee List");
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        cout << "Press any key to go back to Admin Menu.";
        cin.get(); cin.ignore();
    }

    void editEmployee() {
        string empID;
        cout << "Enter Employee ID to edit: ";
        cin >> empID;

        ifstream inFile("employees.txt");
        ofstream tempFile("temp.txt");
        string line;
        bool found = false;

        while (getline(inFile, line)) {
            stringstream ss(line);
            string email, password, id;
            ss >> email >> password >> id;

            if (id == empID) {
                found = true;
                cout << "Edit Employee details (Email, Password, Department, Contact): ";
                string newEmail, newPassword, newDept, newContact;
                cin >> newEmail >> newPassword >> newDept >> newContact;
                tempFile << newEmail << " " << newPassword << " " << empID << " " << newDept << " " << newContact << endl;
            } else {
                tempFile << line << endl;
            }
        }

        inFile.close();
        tempFile.close();
        remove("employees.txt");
        rename("temp.txt", "employees.txt");

        if (found) {
            cout << "Employee details updated successfully." << endl;
        } else {
            cout << "Employee ID not found." << endl;
        }

        cout << "Press any key to return to Admin Menu.";
        cin.get(); cin.ignore(); // Wait for key press
    }

    void deleteEmployee() {
        string empID;
        cout << "Enter Employee ID to delete: ";
        cin >> empID;

        ifstream inFile("employees.txt");
        ofstream tempFile("temp.txt");
        string line;
        bool found = false;

        while (getline(inFile, line)) {
            stringstream ss(line);
            string email, password, id;
            ss >> email >> password >> id;

            if (id == empID) {
                found = true;
                continue; // Skip the employee line to delete it
            }

            tempFile << line << endl;
        }

        inFile.close();
        tempFile.close();
        remove("employees.txt");
        rename("temp.txt", "employees.txt");

        if (found) {
            cout << "Employee deleted successfully." << endl;
        } else {
            cout << "Employee ID not found." << endl;
        }

        cout << "Press any key to return to Admin Menu.";
        cin.get(); cin.ignore(); // Wait for key press
    }
};

// Main Menu
void mainMenu() {
    int choice;
    Admin admin;
    Employee emp;

    while (true) {
        displayHeader("Main Menu");
        cout << "1. Employee Login\n";
        cout << "2. Admin Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            displayHeader("Employee Login");
            bool loginSuccessful = false;
            ifstream inFile("employees.txt");
            string line;

            cout << "Enter your Email and Password\n";
            string email, password;
            cin >> email >> password;

            while (getline(inFile, line)) {
                stringstream ss(line);
                string fileEmail, filePassword;
                ss >> fileEmail >> filePassword;

                if (fileEmail == email && filePassword == password) {
                    emp.email = email;
                    emp.password = password;
                    loginSuccessful = true;
                    break;
                }
            }

            if (loginSuccessful) {
                displayHeader("Employee Dashboard");
                int employeeChoice;
                while (true) {
                    cout << "1. View Profile\n";
                    cout << "2. Change Password\n";
                    cout << "3. Logout\n";
                    cout << "Enter your choice: ";
                    cin >> employeeChoice;

                    if (employeeChoice == 1) {
                        emp.viewProfile();
                    } else if (employeeChoice == 2) {
                        emp.changePassword();
                    } else if (employeeChoice == 3) {
                        break;
                    }
                }
            } else {
                cout << "Employee information not found or not registered.\n";
            }
        } else if (choice == 2) {
            displayHeader("Admin Login");
            if (admin.adminLogin()) {
                admin.manageEmployees();
            } else {
                cout << "Admin login failed.\n";
            }
        } else if (choice == 3) {
            break;
        }
    }
}

int main() {
    mainMenu();
    return 0;
}
