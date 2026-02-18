#ifndef VETERINARIAN_H
#define VETERINARIAN_H

#include "user.h"
#include "appointment.h"
#include <iostream>

class Veterinarian : public User {
public:
    Veterinarian(const string& username, const string& password) : User(username, password) {}

    void displayMenu() override {
        cout << "Veterinarian Menu:" << endl;
        cout << "1. Add Pet" << endl;
        cout << "2. Add Owner" << endl;
        cout << "3. Schedule Appointment" << endl;
        cout << "4. View Appointments" << endl;
        cout << "5. View Pets" << endl;
        cout << "6. View Owners" << endl;
        cout << "10. Logout" << endl;
    }

    void addPet() override {
        int petID, age;
        string name, breed, medicalHistory;
        bool vaccinationStatus;

        cout << "Enter Pet ID: ";
        cin >> petID;
        cout << "Enter Pet Name: ";
        cin >> name;
        cout << "Enter Breed: ";
        cin >> breed;
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Medical History: ";
        cin >> medicalHistory;
        cout << "Vaccinated (1 for Yes, 0 for No): ";
        cin >> vaccinationStatus;

        Pet pet(petID, name, breed, age, medicalHistory, vaccinationStatus);
        pet.saveToFile();
        cout << "Pet added successfully!" << endl;
    }

    void addOwner() override {
        int petID;
        string name, phoneNumber, postcode;

        cout << "Enter Pet ID (associated with the owner): ";
        cin >> petID;
        cout << "Enter Owner's Name: ";
        cin >> name;
        cout << "Enter Owner's Phone Number: ";
        cin >> phoneNumber;
        while (phoneNumber.length() != 11) {
            cout << "Invalid number! Please enter a valid 11-digit phone number: ";
            cin >> phoneNumber;
        }
        cout << "Enter Owner's Postcode: ";
        cin >> postcode;

        Owner owner(petID, name, phoneNumber, postcode);
        owner.saveToFile();
        cout << "Owner added successfully!" << endl;
    }

    void scheduleAppointment() override {
        Appointment::scheduleAppointment(); 
    }

    void viewAppointments() override {
        Appointment::viewAppointments(); 
    }

   
    void deleteAppointment() override {
        cout << "unauthorised action for Vets!" << endl;
    }
    void deletePet() override {

        cout << "unauthorised action for Vets!" << endl;
    }
    void deleteOwner() override {
        cout << "unauthorised action for Vets!" << endl;
    }
};

#endif
