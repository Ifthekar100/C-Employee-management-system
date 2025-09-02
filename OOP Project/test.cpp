#include <iostream>
#include <string>
#include <map>
#include <cstdlib> // For system("clear")

using namespace std;

class Employee {
public:
    string firstName, lastName, department, email, contact, password, empID;
    map<string, bool> payrollStatus; // Maps month/year to paid status
    bool isActive;  // Tracks whether the account is active or disabled
    vector<string> adminMessages;  // Vector to store admin messages


    Employee() : isActive(true) {} // Default constructor, sets isActive to true

    Employee(string first, string last, string dep, string email, string contact, string pass)
        : firstName(first), lastName(last), department(dep), email(email), contact(contact), password(pass), isActive(true) {}

    void displayProfile() {
        cout << "\nEmployee Profile:\n";
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "Department: " << department << endl;
        cout << "Email: " << email << endl;
        cout << "Contact: " << contact << endl;
    }

    void markAsPaid(const string& month) {
        payrollStatus[month] = true;
    }

    bool isPaid(const string& month) const {
        auto it = payrollStatus.find(month);
        return it != payrollStatus.end() && it->second;
    }

    // Function to deactivate or activate the account
    void toggleAccountStatus() {
        isActive = !isActive;
        cout << (isActive ? "Account activated." : "Account deactivated.") << endl;
    }

    void addAdminMessage(const string& message) {
        adminMessages.push_back(message);
    }

    void viewAdminMessages() {
        if (adminMessages.empty()) {
            cout << "No new messages from Admin.\n";
        } else {
            cout << "\nAdmin Messages:\n";
            for (const auto& msg : adminMessages) {
                cout << "- " << msg << endl;
            }
        }
    }

};




class Admin {
public:
    string username = "admin";
    string password = "admin123";
};

map<string, Employee> employeeDatabase;
Admin admin;

string generateEmployeeID(string department) {
    static map<string, int> departmentCounters = {
        {"ENG", 101}, {"MKT", 201}, {"SAL", 301}, {"PM", 401}, {"CS", 501},
        {"FIN", 601}, {"HR", 701}, {"OPS", 801}, {"LEG", 901}, {"DES", 1001}
    };

    string id = department + "-" + to_string(departmentCounters[department]);
    departmentCounters[department]++;
    return id;
}

void employeeDashboard(string empID);
void adminDashboard();

void displayWelcomeMessage(const string& empID) {
    if (employeeDatabase.find(empID) != employeeDatabase.end()) {
        cout << "Welcome, " << employeeDatabase[empID].firstName << " " << employeeDatabase[empID].lastName << "!\n";
    } else {
        cout << "Employee not found.\n";
    }
}

void viewProfile(const string& empID) {
    if (employeeDatabase.find(empID) != employeeDatabase.end()) {
        employeeDatabase[empID].displayProfile();
    } else {
        cout << "Employee not found.\n";
    }
}

void viewPayslip() {
    string empID, month;
    cout << "Enter Employee ID to view the payslip: ";
    cin >> empID;

    if (employeeDatabase.find(empID) != employeeDatabase.end()) {
        Employee& emp = employeeDatabase[empID];

        cout << "Enter the month for which you want to view the payslip (e.g., Jan 2025): ";
        cin.ignore(); // To clear the input buffer
        getline(cin, month);

        if (emp.isPaid(month)) {
            cout << "\nPayslip for " << emp.firstName << " " << emp.lastName << " (ID: " << emp.empID << "):\n";
            cout << "-------------------------------------\n";
            cout << "Employee ID   : " << emp.empID << endl;
            cout << "Name          : " << emp.firstName << " " << emp.lastName << endl;
            cout << "Department    : " << emp.department << endl;
            cout << "Month         : " << month << endl;
            cout << "Status        : Paid\n";
            cout << "-------------------------------------\n";
        } else {
            cout << "No payslip available. Payment for " << month << " has not been marked as paid.\n";
        }
    } else {
        cout << "Employee ID not found.\n";
    }
}


void contactHR(const string& empID) {
    if (employeeDatabase.find(empID) != employeeDatabase.end()) {
        cout << "Contact HR for " << employeeDatabase[empID].firstName << " " << employeeDatabase[empID].lastName << ":\n";
        cout << "HR contact details: hr@company.com or call 123-456-7890.\n";
    } else {
        cout << "Employee not found.\n";
    }
}

void viewAdminMessages(const string& empID) {
    string empID;
    cout << "Enter Employee ID to view admin messages: ";
    cin >> empID;

    // Check if the employee exists in the database
    if (employeeDatabase.find(empID) != employeeDatabase.end()) {
        Employee& emp = employeeDatabase[empID];
        cout << "\nAdmin Messages for " << emp.firstName << " " << emp.lastName << " (ID: " << empID << "):\n";

        // Call the employee's method to view messages
        emp.viewAdminMessages();
    } else {
        cout << "Employee not found.\n";
    }
}




void employeeDashboard(string empID) {
    int choice;
    do {
        system("clear");
        displayWelcomeMessage(empID);  // Display Welcome Message
        cout << "\nEmployee Dashboard:\n";
        cout << "1. View Profile\n";
        cout << "2. View Attendance\n";
        cout << "3. View Payslip\n";
        cout << "4. View Tasks\n";
        cout << "5. Submit Requests\n";
        cout << "6. Contact HR\n";
        cout << "7. View Admin Message\n";
        cout << "8. Change Password\n";
        cout << "9. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: viewProfile(empID); break;
            case 2: viewAttendance(empID); break;
            case 3: viewPayslip(empID); break;
            case 4: viewTasks(empID); break;
            case 5: submitRequest(empID); break;
            case 6: contactHR(empID); break;
            case 7: viewAdminMessages(empID); break;
            case 8: changePassword(empID); break;
            case 9: logout(empID); break;
            default: cout << "Invalid choice.\n"; break;
        }
    } while (choice != 9);
}


void login() {
    string empID, pass;
    cout << "Enter Employee ID: ";
    cin >> empID;
    cout << "Enter Password: ";
    cin >> pass;

    if (employeeDatabase.find(empID) != employeeDatabase.end() && employeeDatabase[empID].password == pass) {
        cout << "Login successful!\n";
        employeeDashboard(empID);
    } else {
        cout << "Invalid credentials. Please try again.\n";
    }
}

void registerEmployee() {
    string firstName, lastName, department, email, contact, password;
    map<string, string> departmentMap = {
        {"Engineering", "ENG"}, {"Marketing", "MKT"}, {"Sales", "SAL"},
        {"Project Management", "PM"}, {"Customer Support", "CS"},
        {"Finance", "FIN"}, {"Human Resources", "HR"},
        {"Operations", "OPS"}, {"Legal", "LEG"}, {"Design", "DES"}
    };

    cout << "Enter First Name: ";
    cin.ignore();
    getline(cin, firstName);
    cout << "Enter Last Name: ";
    getline(cin, lastName);

    cout << "Available Departments:\n";
    for (const auto& dep : departmentMap) {
        cout << dep.first << endl;
    }
    cout << "Enter Department (Full Name): ";
    getline(cin, department);

    if (departmentMap.find(department) == departmentMap.end()) {
        cout << "Invalid department. Please try again.\n";
        return;
    }

    string departmentCode = departmentMap[department];

    cout << "Enter Email: ";
    getline(cin, email);
    cout << "Enter Contact: ";
    getline(cin, contact);
    cout << "Enter Password: ";
    getline(cin, password);

    string empID = generateEmployeeID(departmentCode);
    Employee newEmployee(firstName, lastName, department, email, contact, password);
    newEmployee.empID = empID;
    employeeDatabase[empID] = newEmployee;

    cout << "Registration successful! Your Employee ID is: " << empID << endl;
}

void adminLogin() {
    string inputUsername, inputPassword;
    cout << "Enter Admin Username: ";
    cin >> inputUsername;
    cout << "Enter Admin Password: ";
    cin >> inputPassword;

    if (inputUsername == admin.username && inputPassword == admin.password) {
        cout << "Admin login successful!\n";
        adminDashboard();
    } else {
        cout << "Invalid admin credentials.\n";
    }
}

void employeeDashboard(string empID) {
    int choice;
    do {
        system("clear");
        cout << "\nEmployee Dashboard:\n";
        cout << "1. View Profile\n";
        cout << "2. View Attendance\n";
        cout << "3. View Payslip\n";
        cout << "4. Task Management\n";
        cout << "5. Submit Requests\n";
        cout << "6. Contact HR\n";
        cout << "7. Change Password\n";
        cout << "8. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: employeeDatabase[empID].displayProfile(); break;
            case 2: cout << "Attendance records.\n"; break;
            case 3: cout << "Payslip details.\n"; break;
            case 4: cout << "Manage tasks.\n"; break;
            case 5: cout << "Submit requests.\n"; break;
            case 6: cout << "Contact HR.\n"; break;
            case 7: {
                string newPass;
                cout << "Enter new password: ";
                cin >> newPass;
                employeeDatabase[empID].password = newPass;
                cout << "Password updated successfully.\n";
                break;
            }
            case 8: cout << "Logging out...\n"; break;
            default: cout << "Invalid choice.\n"; break;
        }
    } while (choice != 8);
}

void viewAllEmployees() {
    if (employeeDatabase.empty()) {
        cout << "No employees found.\n";
    } else {
        cout << "\nEmployee List:\n";
        for (const auto& emp : employeeDatabase) {
            cout << "ID: " << emp.second.empID << ", Name: " << emp.second.firstName << " " << emp.second.lastName
                 << ", Department: " << emp.second.department << endl;
        }
    }
}

void editEmployee() {
    string empID;
    cout << "Enter Employee ID to edit: ";
    cin >> empID;

    if (employeeDatabase.find(empID) != employeeDatabase.end()) {
        string firstName, lastName, department, email, contact, password;
        cin.ignore();
        cout << "Enter new first name or leave blank: ";
        getline(cin, firstName);
        cout << "Enter new last name or leave blank: ";
        getline(cin, lastName);
        if (!firstName.empty()) employeeDatabase[empID].firstName = firstName;
        if (!lastName.empty()) employeeDatabase[empID].lastName = lastName;
        // Repeat for other fields as needed
        cout << "Employee details updated.\n";
    } else {
        cout << "Employee not found.\n";
    }
}

void deleteEmployee() {
    string empID;
    cout << "Enter Employee ID to delete: ";
    cin >> empID;
    if (employeeDatabase.erase(empID)) {
        cout << "Employee deleted.\n";
    } else {
        cout << "Employee not found.\n";
    }
}
void manageEmployees() {
    int choice;
    do {
        system("clear");
        cout << "\nManage Employees:\n";
        cout << "1. View All Employees\n";
        cout << "2. Edit Employee\n";
        cout << "3. Delete Employee\n";
        cout << "4. Back to Admin Dashboard\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: viewAllEmployees(); break;
            case 2: editEmployee(); break;
            case 3: deleteEmployee(); break;
            case 4: cout << "Returning to Admin Dashboard...\n"; break;
            default: cout << "Invalid choice. Please try again.\n"; break;
        }
    } while (choice != 4);
}

void viewPayrollRecords() {
    if (employeeDatabase.empty()) {
        cout << "No payroll records available. Employee database is empty.\n";
    } else {
        string currentMonth;
        cout << "Enter the current month to check payroll status (e.g., Jan 2025): "; // INPUT
        cin.ignore();
        getline(cin, currentMonth); // Collect input for the month

        cout << "\nPayroll Records:\n";
        for (const auto& emp : employeeDatabase) {
            cout << "ID: " << emp.second.empID << ", Name: "
                 << emp.second.firstName << " " << emp.second.lastName
                 << ", Department: " << emp.second.department
                 << ", Paid Status: " << (emp.second.isPaid(currentMonth) ? "Paid" : "Unpaid") << endl;
        }
    }
}


void updatePayrollDetails() {
    string empID, month;
    cout << "Enter Employee ID to update payroll details: ";
    cin >> empID;

    if (employeeDatabase.find(empID) != employeeDatabase.end()) {
        cout << "Enter the month to update (e.g., Jan 2025): ";
        cin.ignore();
        getline(cin, month);

        string paidStatus;
        cout << "Mark as paid (Yes/No): ";
        cin >> paidStatus;

        if (paidStatus == "Yes" || paidStatus == "yes") {
            employeeDatabase[empID].markAsPaid(month); // Mark payment
            cout << "Payroll marked as paid for " << empID << " for " << month << ".\n";
        } else if (paidStatus == "No" || paidStatus == "no") {
            cout << "Payroll status not updated.\n";
        } else {
            cout << "Invalid input. Please enter 'Yes' or 'No'.\n";
        }
    } else {
        cout << "Employee ID not found.\n";
    }
}

void generatePayslips() {
    if (employeeDatabase.empty()) {
        cout << "No employees found to generate payslips.\n";
    } else {
        string currentMonth;
        cout << "Enter the current month (e.g., Jan 2025): "; // INPUT
        cin.ignore();
        getline(cin, currentMonth); // Collect input for the month

        cout << "\nGenerating Payslips...\n";
        for (auto& emp : employeeDatabase) {
            if (emp.second.isPaid(currentMonth)) {
                cout << "Payslip already generated for " << emp.second.firstName
                     << " " << emp.second.lastName << " (ID: " << emp.second.empID << ").\n";
            } else {
                emp.second.markAsPaid(currentMonth); // Mark the employee as paid for the month
                cout << "Payslip for " << emp.second.firstName << " "
                     << emp.second.lastName << " (ID: " << emp.second.empID
                     << ") has been generated and marked as paid.\n";
            }
        }
    }
}



void managePayroll() {
    int choice;
    do {
        system("clear");
        cout << "\nPayroll Management:\n";
        cout << "1. View Payroll Records\n";
        cout << "2. Update Payroll Details\n";
        cout << "3. Generate Payslips\n";
        cout << "4. Back to Admin Dashboard\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewPayrollRecords();
                break;
            case 2:
                updatePayrollDetails();
                break;
            case 3:
                generatePayslips();
                break;
            case 4:
                cout << "Returning to Admin Dashboard...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 4);
}
void changeEmployeePassword() {
    string empID, newPassword;
    cout << "Enter Employee ID to change password: ";
    cin >> empID;

    if (employeeDatabase.find(empID) != employeeDatabase.end()) {
        cout << "Enter new password for employee: ";
        cin >> newPassword;
        employeeDatabase[empID].password = newPassword;
        cout << "Password successfully updated for employee " << empID << ".\n";
    } else {
        cout << "Employee ID not found.\n";
    }
}

void disableOrActivateAccount() {
    string empID;
    cout << "Enter Employee ID to disable/activate: ";
    cin >> empID;

    if (employeeDatabase.find(empID) != employeeDatabase.end()) {
        employeeDatabase[empID].toggleAccountStatus();
    } else {
        cout << "Employee ID not found.\n";
    }
}


void userAccountManagement() {
    int accountChoice;
    do {
        system("clear");
        cout << "\nUser Account Management:\n";
        cout << "1. Change Employee Passwords\n";
        cout << "2. Disable/Activate Accounts\n";
        cout << "3. Back to Admin Dashboard\n";
        cout << "Enter your choice: ";
        cin >> accountChoice;

        switch (accountChoice) {
            case 1: changeEmployeePassword(); break;
            case 2: disableOrActivateAccount(); break;
            case 3: cout << "Returning to Admin Dashboard...\n"; break;
            default: cout << "Invalid choice. Please try again.\n"; break;
        }
    } while (accountChoice != 3);
}

void manageProjects() {
        int choice;
        do {
            cout << "\nManage Project" << endl;
            cout << "1. Assign Task" << endl;
            cout << "2. Monitor Task" << endl;
            cout << "3. Return to Admin Dashboard" << endl;
            cout << "Enter choice: ";
            cin >> choice;

            switch(choice) {
                case 1:
                    assignTask();
                    break;
                case 2:
                    monitorTasks();
                    break;
                case 3:
                    returnToDashboard();
                    break;
                default:
                    cout << "Invalid choice! Please try again." << endl;
            }
        } while (choice != 3);
    }      cout << "\nManage Tasks:\n";




void sendNotifications() {
    int choice;
    do {
        system("clear");
        cout << "\nSend Company-Wide Announcements:\n";
        cout << "1. Send Message to All Employees\n";
        cout << "2. Send Message to Specific Department\n";
        cout << "3. Back to Admin Dashboard\n";
        cout << "Enter choice: ";
        cin >> choice;

        cin.ignore(); // To clear the input buffer

        switch (choice) {
            case 1: {
                string message;
                cout << "Enter message to send to all employees: ";
                getline(cin, message);
                for (auto& emp : employeeDatabase) {
                    emp.second.addAdminMessage(message);
                }
                cout << "Message sent to all employees.\n";
                break;
            }
            case 2: {
                string department, message;
                cout << "Enter department name to send message to (e.g., Engineering, Marketing): ";
                getline(cin, department);

                map<string, string> departmentMap = {
                    {"Engineering", "ENG"}, {"Marketing", "MKT"}, {"Sales", "SAL"},
                    {"Project Management", "PM"}, {"Customer Support", "CS"},
                    {"Finance", "FIN"}, {"Human Resources", "HR"},
                    {"Operations", "OPS"}, {"Legal", "LEG"}, {"Design", "DES"}
                };

                // Check if the department exists
                if (departmentMap.find(department) != departmentMap.end()) {
                    string deptCode = departmentMap[department];
                    cout << "Enter message to send to " << department << " department: ";
                    getline(cin, message);

                    for (auto& emp : employeeDatabase) {
                        if (emp.second.department == deptCode) {
                            emp.second.addAdminMessage(message);
                        }
                    }
                    cout << "Message sent to all employees in the " << department << " department.\n";
                } else {
                    cout << "Invalid department name. Please try again.\n";
                }
                break;
            }
            case 3:
                cout << "Returning to Admin Dashboard...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 3);
}



void adminDashboard() {
    int choice;
    do {
        system("clear");
        cout << "\nAdmin Dashboard:\n";
        cout << "1. Manage Employees\n";
        cout << "2. Employee Attendance Management\n";
        cout << "3. Payroll Management\n";
        cout << "4. User Account Management\n";
        cout << "5. Manage Projects\n"; // Added "Manage Projects" option
        cout << "6. Company Policies and Documents\n";
        cout << "7. Reports and Analytics\n";
        cout << "8. Notifications\n";  // Added Notifications option
        cout << "9. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: manageEmployees(); break;
            // case 2: manageAttendance(); break;
            case 3: managePayroll(); break;
            case 4: userAccountManagement(); break;
            case 5: manageProjects(); break; // Linked to manageProjects function
            case 6: cout << "Displaying Company Policies and Documents...\n"; break;
            case 7: cout << "Generating Reports and Analytics...\n"; break;
            case 8: sendNotifications(); break;
            case 9: cout << "Logging out...\n"; break;
            default: cout << "Invalid choice. Please try again.\n"; break;
        }
    } while (choice != 9);
}

void displayMainMenu() {
    int choice;
    do {
        system("clear");
        cout << "\nMain Menu:\n";
        cout << "1. Employee Login\n";
        cout << "2. Register Employee\n";
        cout << "3. Admin Login\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: login(); break;
            case 2: registerEmployee(); break;
            case 3: adminLogin(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n"; break;
        }
    } while (choice != 4);
}

int main() {
    displayMainMenu();
    return 0;
}
