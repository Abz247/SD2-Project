#ifndef STAFF_H
#define STAFF_H

#include "user.h"
#include "appointment.h"
#include <iostream>

class Staff : public User {
public:
    Staff(const string& username, const string& password) : User(username, password) {}

    void displayMenu() override {
        cout << "Staff Menu:" << endl;
        cout << "3. Schedule Appointment" << endl;
        cout << "4. View Appointments" << endl;
        cout << "10. Logout" << endl;
    }

    void addPet() override {
        cout << "Unauthorized action for Staff!" << endl;
    }

    void addOwner() override {
        cout << "Unauthorized action for Staff!" << endl;
    }

    void scheduleAppointment() override {
        Appointment::scheduleAppointment(); 
    }

    void viewAppointments() override {
        Appointment::viewAppointments(); 
    }

    
    void deleteAppointment() override {
     
        cout << "unauthorised action for Staff!" << endl;
    }

    void deletePet() override {

        cout << "unauthorised action for Staff!" << endl;
    }
    void deleteOwner() override {
        cout << "unauthorised action for Staff!" << endl;
    }
};

#endif
 