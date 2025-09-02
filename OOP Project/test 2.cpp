#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>  // For system("cls")
#include <ctime>    // For date and time functionality

using namespace std;

// Employee Class
class Employee {
public:
    string firstName;
    string lastName;
    string department;
    string email;
    string contact;
    string password;
    string employeeID;
    string position;
    vector<string> attendance;   // To track attendance (P = Present, A = Absent)
    vector<string> tasks;        // To store tasks
    vector<string> leaveRequests; // To store leave requests
    float salary;  // Store salary details for each employee

    Employee(string fName, string lName, string dept, string mail, string cont, string pass, string pos, float sal)
        : firstName(fName), lastName(lName), department(dept), email(mail), contact(cont), password(pass), position(pos), salary(sal) {}

    Employee() {}

    void showProfile() {
        cout << "\nEmployee Name: " << firstName << " " << lastName << endl;
        cout << "Employee ID: " << employeeID << endl;
        cout << "Department: " << department << endl;
        cout << "Position: " << position << endl;
        cout << "Contact: " << contact << endl;
        cout << "Email: " << email << endl;
    }

    bool login(string id, string pass) {
        return (employeeID == id && password == pass);
    }

    // Method to mark attendance
    void markAttendance(bool isPresent) {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        string date = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
        string status = (isPresent) ? "P" : "A";
        attendance.push_back(date + ": " + status);
    }

    // View Attendance for the month
    void viewAttendance() {
        cout << "\nAttendance Record for " << firstName << " " << lastName << ":\n";
        for (const auto& record : attendance) {
            cout << record << endl;
        }
    }

    // Method to submit a leave request
    void submitLeaveRequest(string leaveType) {
        leaveRequests.push_back(leaveType);
    }

    // View tasks assigned to the employee
    void viewTasks() {
        cout << "\nTasks assigned to " << firstName << " " << lastName << ":\n";
        for (const auto& task : tasks) {
            cout << task << endl;
        }
    }

    // Add a new task for the employee
    void addTask(string task) {
        tasks.push_back(task);
    }

    // View full details of the employee for Admin
    void viewFullDetails() {
        cout << "\nEmployee ID: " << employeeID << endl;
        cout << "Full Name: " << firstName << " " << lastName << endl;
        cout << "Department: " << department << endl;
        cout << "Position: " << position << endl;
        cout << "Email: " << email << endl;
        cout << "Contact: " << contact << endl;
        cout << "Salary: " << salary << endl;

        cout << "\nAttendance Record:\n";
        for (const auto& record : attendance) {
            cout << record << endl;
        }
        cout << "\nLeave Requests:\n";
        for (const auto& leave : leaveRequests) {
            cout << leave << endl;
        }

        cout << "\nAssigned Tasks:\n";
        for (const auto& task : tasks) {
            cout << task << endl;
        }
    }
};

// Admin Class
class Admin {
public:
    string username = "admin";
    string password = "admin123";

    bool login(string user, string pass) {
        return (user == username && pass == password);
    }

    void manageEmployees(vector<Employee>& employees) {
        system("cls");
        cout << "Admin Dashboard - Manage Employees\n";
        cout << "1. View Employees\n2. Register Employee\n3. Edit Employee\n4. Delete Employee\n5. Back to Main Menu\n";
        int choice;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            viewEmployees(employees);
            break;
        case 2:
            registerEmployee(employees);
            break;
        case 3:
            editEmployee(employees);
            break;
        case 4:
            deleteEmployee(employees);
            break;
        case 5:
            return;
        default:
            cout << "Invalid choice, try again.\n";
            break;
        }
    }

    void viewEmployees(vector<Employee>& employees) {
        system("cls");
        cout << "Employee List (Full Details):\n";
        for (auto& emp : employees) {
            emp.viewFullDetails();  // Show full details of each employee
            cout << "\n---------------------------------------------------\n";
        }
        cout << "Press any key to go back...\n";
        cin.get();  // To catch the newline character left by the previous cin
        cin.get();  // Wait for the user to press a key
    }

    void registerEmployee(vector<Employee>& employees) {
        system("cls");
        string fName, lName, dept, email, contact, pass, pos;
        float salary;

        cout << "Enter First Name: ";
        cin >> fName;
        cout << "Enter Last Name: ";
        cin >> lName;
        cout << "Enter Department (Engineering, Marketing, Sales, Product Management, Customer Support, Finance, HR, Operations, Legal, Design): ";
        cin >> dept;
        cout << "Enter Email: ";
        cin >> email;
        cout << "Enter Contact: ";
        cin >> contact;
        cout << "Enter Password: ";
        cin >> pass;
        cout << "Enter Position: ";
        cin >> pos;
        cout << "Enter Salary: ";
        cin >> salary;

        // Generate Employee ID based on department and number of employees in that department
        string empID;
        int departmentCount = 0;

        for (auto& emp : employees) {
            if (emp.department == dept) {
                departmentCount++;
            }
        }

        // Generate Employee ID based on the department count
        if (dept == "Engineering") empID = "ENG-" + to_string(101 + departmentCount);
        else if (dept == "Marketing") empID = "MKT-" + to_string(201 + departmentCount);
        else if (dept == "Sales") empID = "SAL-" + to_string(301 + departmentCount);
        else if (dept == "Product Management") empID = "PM-" + to_string(401 + departmentCount);
        else if (dept == "Customer Support") empID = "CS-" + to_string(501 + departmentCount);
        else if (dept == "Finance") empID = "FIN-" + to_string(601 + departmentCount);
        else if (dept == "HR") empID = "HR-" + to_string(701 + departmentCount);
        else if (dept == "Operations") empID = "OPS-" + to_string(801 + departmentCount);
        else if (dept == "Legal") empID = "LEG-" + to_string(901 + departmentCount);
        else if (dept == "Design") empID = "DES-" + to_string(1001 + departmentCount);
        else {
            cout << "Invalid department. Please enter a valid department.\n";
            return;
        }

        // Create and save the Employee object
        Employee newEmployee(fName, lName, dept, email, contact, pass, pos, salary);
        newEmployee.employeeID = empID;
        employees.push_back(newEmployee);

        // Save the employees to the file
        saveEmployees(employees);

        system("cls");
        cout << "\nRegistration successful! Employee ID: " << empID << endl;
        cout << "Press any key to go back to the admin dashboard...\n";
        cin.get();  // Wait for the user to press a key
        cin.get();  // Consume the newline character left behind by cin
    }

    void editEmployee(vector<Employee>& employees) {
        system("cls");
        string empID;
        cout << "Enter Employee ID to edit: ";
        cin >> empID;

        for (auto& emp : employees) {
            if (emp.employeeID == empID) {
                string newContact;
                cout << "Enter new contact for " << emp.firstName << ": ";
                cin >> newContact;
                emp.contact = newContact;
                cout << "Employee details updated!\n";
                break;
            }
        }
        cout << "Press any key to go back...\n";
        cin.get();  // To catch the newline character left by the previous cin
        cin.get();  // Wait for the user to press a key
    }

    void deleteEmployee(vector<Employee>& employees) {
        system("cls");
        string empID;
        cout << "Enter Employee ID to delete: ";
        cin >> empID;

        for (auto it = employees.begin(); it != employees.end(); ++it) {
            if (it->employeeID == empID) {
                employees.erase(it);
                cout << "Employee deleted successfully!\n";
                break;
            }
        }
        cout << "Press any key to go back...\n";
        cin.get();  // To catch the newline character left by the previous cin
        cin.get();  // Wait for the user to press a key
    }

    void saveEmployees(vector<Employee>& employees) {
        ofstream file("employees.txt", ios::trunc);
        for (auto& emp : employees) {
            file << emp.firstName << "," << emp.lastName << "," << emp.department << ","
                 << emp.email << "," << emp.contact << "," << emp.password << ","
                 << emp.position << "," << emp.employeeID << "," << emp.salary << endl;
        }
    }

};

// System Class (Handles File Operations)
class System {
private:
    vector<Employee> employees;

    // Helper function to load employees from the file
    void loadEmployees() {
        ifstream file("employees.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string fName, lName, dept, email, contact, pass, pos, empID;
            float salary;
            getline(ss, fName, ',');
            getline(ss, lName, ',');
            getline(ss, dept, ',');
            getline(ss, email, ',');
            getline(ss, contact, ',');
            getline(ss, pass, ',');
            getline(ss, pos, ',');
            getline(ss, empID, ',');
            ss >> salary;

            Employee emp(fName, lName, dept, email, contact, pass, pos, salary);
            emp.employeeID = empID;
            employees.push_back(emp);
        }
    }

public:
    System() {
        loadEmployees();
    }

    void showMainMenu() {
        system("cls");
        int choice;
        cout << "*********** Employee Management System ***********\n";
        cout << "1. Employee Login\n2. Admin Login\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            employeeLogin();
            break;
        case 2:
            adminLogin();
            break;
        case 3:
            exit(0);
        default:
            cout << "Invalid choice, please try again.\n";
            break;
        }
    }

    // Employee login function
    void employeeLogin() {
        string id, pass;
        system("cls");
        cout << "Enter Employee ID: ";
        cin >> id;
        cout << "Enter Password: ";
        cin >> pass;

        bool found = false;
        for (auto& emp : employees) {
            if (emp.login(id, pass)) {
                found = true;
                emp.showProfile();
                emp.viewAttendance();
                emp.viewTasks();
                break;
            }
        }
        if (!found) {
            cout << "Employee info not found or not registered.\n";
        }

        cout << "Press any key to go back...\n";
        cin.get();  // To catch the newline character left behind by the previous cin
        cin.get();  // Wait for the user to press a key
    }

    // Admin login function
    void adminLogin() {
        string user, pass;
        system("cls");
        cout << "Enter Admin Username: ";
        cin >> user;
        cout << "Enter Admin Password: ";
        cin >> pass;

        Admin admin;
        if (admin.login(user, pass)) {
            admin.manageEmployees(employees);
        } else {
            cout << "Invalid Admin credentials.\n";
        }
    }
};

int main() {
    System system;
    system.showMainMenu();
    return 0;
}

