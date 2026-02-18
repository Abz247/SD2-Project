#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

class Appointment {
public:
    static void scheduleAppointment() {
        int petID;
        string name;
        string date;
        string time;
        regex datePattern(R"(\d{2}-\d{2}-\d{4})");
        regex timePattern(R"(^([01]\d|2[0-3]):([0-5]\d)$)");

        cout << "Enter pet ID: ";
        cin >> petID;
        cin.ignore(); 
        cout << "Enter pet name: ";
        getline(cin, name);

        while (true) {
            cout << "Enter appointment date (dd-mm-yyyy): ";
            cin >> date;

            if (!regex_match(date, datePattern)) {
                cout << "Invalid format! Please enter date in dd-mm-yyyy format.\n";
                continue;
            }

          
            int day = stoi(date.substr(0, 2));
            int month = stoi(date.substr(3, 2));
            int year = stoi(date.substr(6, 4));

            if (month < 1 || month > 12) {
                cout << "Invalid date! Please enter a correct date.\n";
            }
            else if (day < 1 || day > 31) {
                cout << "Invalid date! Please enter a correct date.\n";
            }
            else {
                break; 
            }
        }

        cin.ignore(); 

        while (true) {
            cout << "Enter appointment time (HH:MM): ";
            getline(cin, time);

            if (regex_match(time, timePattern)) {
                break; 
            }

            cout << "Invalid format! Please enter time in HH:MM\n";
        }

        ofstream appointmentFile("appointments.txt", ios::app);
        if (appointmentFile.is_open()) {
            appointmentFile << petID << " " << name << " " << date << " " << time << endl;
            appointmentFile.close();
            cout << "Appointment scheduled for " << name << " on " << date << " at " << time << endl;
        }
        else {
            cout << "Error opening file to save appointment!" << endl;
        }
    }

    static void viewAppointments() {
        ifstream appointmentFile("appointments.txt");
        if (!appointmentFile.is_open()) {
            cout << "Error opening file to view appointments!" << endl;
            return;
        }

        string line;
        bool found = false;
        cout << "Scheduled Appointments:\n";
        while (getline(appointmentFile, line)) {
            cout << line << endl;
            found = true;
        }

        if (!found) cout << "No appointments found.\n";
        appointmentFile.close();
    }

    static void deleteAppointment() {
        int petID;
        string date;
        regex datePattern(R"(\d{2}-\d{2}-\d{4})");

        cout << "Enter pet ID of the appointment to delete: ";
        cin >> petID;
        cout << "Enter appointment date (dd-mm-yyyy): ";
        cin >> date;

        if (!regex_match(date, datePattern)) {
            cout << "Invalid date format. Deletion canceled.\n";
            return;
        }

        ifstream appointmentFile("appointments.txt");
        if (!appointmentFile.is_open()) {
            cout << "Error opening file!" << endl;
            return;
        }

        vector<string> updatedAppointments;
        string line;
        bool deleted = false;

        while (getline(appointmentFile, line)) {
            if (line.find(to_string(petID) + " ") == 0 && line.find(date) != string::npos) {
                deleted = true;
            }
            else {
                updatedAppointments.push_back(line);
            }
        }
        appointmentFile.close();

        if (deleted) {
            ofstream outFile("appointments.txt", ios::trunc);
            for (const string& appointment : updatedAppointments) {
                outFile << appointment << endl;
            }
            outFile.close();
            cout << "Appointment for pet ID " << petID << " on " << date << " deleted successfully!\n";
        }
        else {
            cout << "No matching appointment found.\n";
        }
    }
};

#endif
