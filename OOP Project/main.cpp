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

        cout << "Create a Password: ";
        cin >> password;

        cout << "Confirm Password: ";
        cin >> confirmPassword;
        while (confirmPassword != password) {
            cout << "Passwords do not match! Try again." << endl;
            cout << "Confirm Password: ";
            cin >> confirmPassword;
        }

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

        cout << "Enter Salary: ";
        cin >> salary;
        cout << "Enter Contract Period (in years): ";
        cin >> contractPeriod;

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
        displayHeader("Employee Profile");
        cout << "Employee ID: " << empID << endl;
        cout << "First Name: " << firstName << endl;
        cout << "Last Name: " << lastName << endl;
        cout << "Department: " << department << endl;
        cout << "Email: " << email << endl;
        cout << "Contact: " << contact << endl;
        cout << "Salary: " << salary << endl;
        cout << "Contract Period: " << contractPeriod << " years" << endl;
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

            while (!(cin >> choice) || (choice < 1 || choice > 5)) {
                cout << "Invalid input! Please enter a number between 1 and 5: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if (choice == 1) {
                viewAllEmployees();
            } else if (choice == 2) {
                clearScreen();
                Employee emp;
                emp.registerEmployee();
                cout << "Press any key to return to Admin Menu.";
                cin.get(); cin.ignore();
                clearScreen();
            } else if (choice == 3) {
                clearScreen();
                editEmployee();
                clearScreen();
            } else if (choice == 4) {
                clearScreen();
                deleteEmployee();
                clearScreen();
            } else if (choice == 5) {
                break;
            }
        }
    }

    void viewAllEmployees() {
        ifstream inFile("employees.txt");
        string line;
        bool employeeFound = false;
        displayHeader("Employee List");

        while (getline(inFile, line)) {
            employeeFound = true;
            stringstream ss(line);
            string email, password, empID, firstName, lastName, department, contact, salary, contractPeriod;

            ss >> email >> password >> empID >> firstName >> lastName >> department >> contact >> salary >> contractPeriod;
            cout << "\nEmployee ID: " << empID << endl;
            cout << "Name: " << firstName << " " << lastName << endl;
            cout << "Department: " << department << endl;
            cout << "Email: " << email << endl;
            cout << "Contact: " << contact << endl;
            cout << "Salary: " << salary << endl;
            cout << "Contract Period: " << contractPeriod << " years" << endl;
        }

        if (!employeeFound) {
            cout << "No employee information found." << endl;
        }

        cout << "\nPress any key to return to Admin Menu.";
        cin.get(); cin.ignore();
    }

    void editEmployee() {
        cout << "Enter Employee Email to Edit: ";
        string email;
        cin >> email;

        ifstream inFile("employees.txt");
        ofstream tempFile("temp.txt");
        string line;
        bool found = false;

        while (getline(inFile, line)) {
            stringstream ss(line);
            string fileEmail, password, empID, firstName, lastName, department, contact, salary, contractPeriod;

            ss >> fileEmail >> password >> empID >> firstName >> lastName >> department >> contact >> salary >> contractPeriod;

            if (fileEmail == email) {
                found = true;

                cout << "Edit First Name: ";
                cin >> firstName;
                cout << "Edit Last Name: ";
                cin >> lastName;
                cout << "Edit Department: ";
                cin >> department;
                cout << "Edit Contact: ";
                cin >> contact;
                cout << "Edit Salary: ";
                cin >> salary;
                cout << "Edit Contract Period (in years): ";
                cin >> contractPeriod;

                tempFile << fileEmail << " " << password << " " << empID << " " << firstName << " " << lastName << " " << department << " " << contact << " " << salary << " " << contractPeriod << endl;
            } else {
                tempFile << line << endl;
            }
        }

        inFile.close();
        tempFile.close();
        remove("employees.txt");
        rename("temp.txt", "employees.txt");

        if (found) {
            cout << "Employee information updated successfully!" << endl;
        } else {
            cout << "Employee with email not found!" << endl;
        }
    }

    void deleteEmployee() {
        cout << "Enter Employee Email to Delete: ";
        string email;
        cin >> email;

        ifstream inFile("employees.txt");
        ofstream tempFile("temp.txt");
        string line;
        bool found = false;

        while (getline(inFile, line)) {
            stringstream ss(line);
            string fileEmail, password, empID, firstName, lastName, department, contact, salary, contractPeriod;

            ss >> fileEmail >> password >> empID >> firstName >> lastName >> department >> contact >> salary >> contractPeriod;

            if (fileEmail != email) {
                tempFile << line << endl;
            } else {
                found = true;
            }
        }

        inFile.close();
        tempFile.close();
        remove("employees.txt");
        rename("temp.txt", "employees.txt");

        if (found) {
            cout << "Employee deleted successfully!" << endl;
        } else {
            cout << "Employee with email not found!" << endl;
        }
    }
};

void mainMenu() {
    Employee emp;
    Admin admin;
    int choice;

    while (true) {
        displayHeader("Main Menu");
        cout << "1. Employee Login\n";
        cout << "2. Admin Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice) || (choice < 1 || choice > 3)) {

            cout << "Invalid input! Please enter a number between 1 and 3: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (choice == 1) {
            displayHeader("Employee Login");
            if (emp.login()) {
                int employeeChoice;
                while (true) {
                    displayHeader("Employee Menu");
                    cout << "1. View Profile\n";
                    cout << "2. Change Password\n";
                    cout << "3. Logout\n";
                    cout << "Enter your choice: ";

                    while (!(cin >> employeeChoice) || (employeeChoice < 1 || employeeChoice > 3)) {

                        cout << "Invalid input! Please enter a number between 1 and 3: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    if (employeeChoice == 1) {
                        emp.viewProfile();
                    } else if (employeeChoice == 2) {
                        clearScreen();
                        emp.changePassword();
                    } else if (employeeChoice == 3) {
                        break;
                    }
                }
            } else {
                cout << "Employee login failed. Press any key to go back.";
                cin.get(); cin.ignore();
            }
        } else if (choice == 2) {
            displayHeader("Admin Login");
            if (admin.adminLogin()) {
                admin.manageEmployees();
            } else {
                cout << "Admin login failed. Press any key to go back.";
                cin.get(); cin.ignore();
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
