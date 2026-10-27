#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 1. Vehicle Structure (Node for Linked List)
struct Vehicle {
    int id;
    string name;
    string type;      // e.g., Express, Passenger, Freight
    string status;    // Available, In Use, Maintenance
    string driver;
    Vehicle* next;    // Pointer to next node
};

// 2. Railway System Class demonstrating DSA Concepts
class RailwaySystem {
private:
    Vehicle* head;                     // Head pointer for Linked List
    queue<string> maintenanceQueue;    // Queue (FIFO) for maintenance tracking

public:
    // Constructor with Sample Pre-loaded Data
    RailwaySystem() {
        head = nullptr;
        addVehicle(101, "Rajdhani Express", "Express", "Available", "Amit Sharma");
        addVehicle(102, "Vande Bharat", "Passenger", "In Use", "Rahul Verma");
        addVehicle(103, "Freight Titan", "Freight", "Maintenance", "Suresh Kumar");
        
        maintenanceQueue.push("Train #103 (Freight Titan)");
    }

    // Destructor to free dynamically allocated memory
    ~RailwaySystem() {
        Vehicle* current = head;
        while (current != nullptr) {
            Vehicle* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // CREATE: Add Vehicle (Linked List Insertion)
    bool addVehicle(int id, string name, string type, string status, string driver) {
        if (searchVehicle(id) != nullptr) return false; // Duplicate check

        Vehicle* newVehicle = new Vehicle{id, name, type, status, driver, nullptr};
        
        if (!head) {
            head = newVehicle;
        } else {
            Vehicle* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newVehicle;
        }

        if (status == "Maintenance") {
            maintenanceQueue.push("Train #" + to_string(id) + " (" + name + ")");
        }
        return true;
    }

    // READ: Get all vehicles as a vector for display/sorting
    vector<Vehicle> getAllVehicles() {
        vector<Vehicle> list;
        Vehicle* temp = head;
        while (temp != nullptr) {
            list.push_back(*temp);
            temp = temp->next;
        }
        return list;
    }

    // SEARCH: Linear Search Algorithm
    Vehicle* searchVehicle(int id) {
        Vehicle* temp = head;
        while (temp != nullptr) {
            if (temp->id == id) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    // UPDATE: Update Vehicle Details & Status
    bool updateVehicle(int id, string name, string type, string status, string driver) {
        Vehicle* v = searchVehicle(id);
        if (!v) return false;

        v->name = name;
        v->type = type;
        if (v->status != status && status == "Maintenance") {
            maintenanceQueue.push("Train #" + to_string(id) + " (" + name + ")");
        }
        v->status = status;
        v->driver = driver;
        return true;
    }

    // DELETE: Remove Vehicle by ID from Linked List
    bool deleteVehicle(int id) {
        if (!head) return false;

        if (head->id == id) {
            Vehicle* toDelete = head;
            head = head->next;
            delete toDelete;
            return true;
        }

        Vehicle* prev = head;
        Vehicle* curr = head->next;
        while (curr != nullptr) {
            if (curr->id == id) {
                prev->next = curr->next;
                delete curr;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }

    // QUEUE OPERATIONS (FIFO)
    string getNextMaintenance() {
        if (maintenanceQueue.empty()) return "No pending maintenance.";
        return maintenanceQueue.front();
    }

    void popMaintenance() {
        if (!maintenanceQueue.empty()) {
            maintenanceQueue.pop();
        }
    }

    int getMaintenanceQueueSize() {
        return maintenanceQueue.size();
    }

    // SORTING ALGORITHM: Sort records by ID or Name
    vector<Vehicle> sortVehicles(string criteria) {
        vector<Vehicle> list = getAllVehicles();
        if (criteria == "id") {
            sort(list.begin(), list.end(), [](const Vehicle& a, const Vehicle& b) {
                return a.id < b.id;
            });
        } else if (criteria == "name") {
            sort(list.begin(), list.end(), [](const Vehicle& a, const Vehicle& b) {
                return a.name < b.name;
            });
        }
        return list;
    }
};

// Main Console Interface for Online Compiler
int main() {
    RailwaySystem rs;
    int choice;

    cout << "========================================\n";
    cout << " SMART RAILWAY NETWORK OPTIMIZATION SYS \n";
    cout << "========================================\n";

    do {
        cout << "\n--- DSA PBL MENU ---\n";
        cout << "1. View All Trains (Linked List Traversal)\n";
        cout << "2. Add New Train\n";
        cout << "3. Search Train by ID (Linear Search)\n";
        cout << "4. Update Train Status & Driver\n";
        cout << "5. Delete Train (Linked List Deletion)\n";
        cout << "6. View & Process Maintenance Queue (FIFO)\n";
        cout << "7. Sort Trains (Sorting Algorithm)\n";
        cout << "8. Exit\n";
        cout << "Enter your choice (1-8): ";
        
        if (!(cin >> choice)) {
            cout << "Invalid input. Exiting.\n";
            break;
        }

        switch (choice) {
            case 1: {
                vector<Vehicle> vehicles = rs.getAllVehicles();
                cout << "\n--------------------------------------------------------------------\n";
                cout << " ID   | Train Name         | Type      | Status      | Driver       \n";
                cout << "--------------------------------------------------------------------\n";
                for (const auto& v : vehicles) {
                    cout << " #" << v.id << " | " << v.name;
                    // Format spacing
                    for(int i = v.name.length(); i < 18; i++) cout << " ";
                    cout << " | " << v.type;
                    for(int i = v.type.length(); i < 9; i++) cout << " ";
                    cout << " | " << v.status;
                    for(int i = v.status.length(); i < 11; i++) cout << " ";
                    cout << " | " << v.driver << "\n";
                }
                cout << "--------------------------------------------------------------------\n";
                break;
            }
            case 2: {
                int id; string name, type, status, driver;
                cout << "Enter Train ID (e.g. 104): "; cin >> id;
                cout << "Enter Train Name: "; cin.ignore(); getline(cin, name);
                cout << "Enter Train Type (Express/Passenger/Freight): "; getline(cin, type);
                cout << "Enter Status (Available/In Use/Maintenance): "; getline(cin, status);
                cout << "Enter Driver Name: "; getline(cin, driver);

                if (rs.addVehicle(id, name, type, status, driver)) {
                    cout << "[SUCCESS] Train added successfully!\n";
                } else {
                    cout << "[ERROR] Train ID already exists in the system.\n";
                }
                break;
            }
            case 3: {
                int id;
                cout << "Enter Train ID to search: "; cin >> id;
                Vehicle* v = rs.searchVehicle(id);
                if (v) {
                    cout << "\n[FOUND] Train Details:\n";
                    cout << "ID: " << v->id << " | Name: " << v->name << " | Type: " << v->type 
                         << " | Status: " << v->status << " | Driver: " << v->driver << "\n";
                } else {
                    cout << "[NOT FOUND] Train with ID #" << id << " does not exist (Linear Search completed).\n";
                }
                break;
            }
            case 4: {
                int id; string name, type, status, driver;
                cout << "Enter Train ID to update: "; cin >> id;
                cout << "Enter New Name: "; cin.ignore(); getline(cin, name);
                cout << "Enter New Type: "; getline(cin, type);
                cout << "Enter New Status (Available/In Use/Maintenance): "; getline(cin, status);
                cout << "Enter New Driver: "; getline(cin, driver);

                if (rs.updateVehicle(id, name, type, status, driver)) {
                    cout << "[SUCCESS] Train updated successfully!\n";
                } else {
                    cout << "[ERROR] Train ID not found.\n";
                }
                break;
            }
            case 5: {
                int id;
                cout << "Enter Train ID to delete: "; cin >> id;
                if (rs.deleteVehicle(id)) {
                    cout << "[SUCCESS] Train deleted from Linked List successfully!\n";
                } else {
                    cout << "[ERROR] Train ID not found.\n";
                }
                break;
            }
            case 6: {
                cout << "\n--- Maintenance Queue (FIFO) ---\n";
                cout << "Pending in Queue: " << rs.getMaintenanceQueueSize() << "\n";
                cout << "Next Train in line for service: " << rs.getNextMaintenance() << "\n";
                
                if (rs.getMaintenanceQueueSize() > 0) {
                    char opt;
                    cout << "Process/Clear next maintenance item? (y/n): "; cin >> opt;
                    if (opt == 'y' || opt == 'Y') {
                        rs.popMaintenance();
                        cout << "[SUCCESS] Maintenance processed! Train status set back to Available.\n";
                    }
                }
                break;
            }
            case 7: {
                string criteria;
                cout << "Sort by criteria ('id' or 'name'): "; cin >> criteria;
                vector<Vehicle> sorted = rs.sortVehicles(criteria);
                cout << "\n--- Sorted Trains ---\n";
                for (const auto& v : sorted) {
                    cout << "ID: " << v.id << " | Name: " << v.name << " | Status: " << v.status << "\n";
                }
                break;
            }
            case 8:
                cout << "Exiting system. Best of luck with your college DSA PBL viva!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 8.\n";
        }
    } while (choice != 8);

    return 0;
}
