#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"
#include "pet.h"
#include "owner.h"
#include "appointment.h"
#include <iostream>

class Admin : public User {
public:
    Admin(const string& username, const string& password) : User(username, password) {}

    void displayMenu() override {
        cout << "Admin Menu:" << endl;
        cout << "1. Add Pet" << endl;
        cout << "2. Add Owner" << endl;
        cout << "3. Schedule Appointment" << endl;
        cout << "4. View Appointments" << endl;
        cout << "5. View Pets" << endl;
        cout << "6. View Owners" << endl;
        cout << "7. Delete Appointment" << endl;
        cout << "8. Delete Pet" << endl;
        cout << "9. Delete Owner" << endl;  
        cout << "10. Logout" << endl;
    }
    bool deleteOwner(int petID) {
        ifstream ownerFile("owners.txt");  
        if (!ownerFile.is_open()) {
            cout << "Error opening owners file!" << endl;
            return false;
        }

        string line;
        vector<string> lines;  // To store all lines except the one to delete
        bool found = false;   // Flag to track if the owner is found

        // Read the file line by line
        while (getline(ownerFile, line)) {
            stringstream ss(line);
            int filePetID;
            string name, phoneNumber, email;

            // Read the petID from the current line
            ss >> filePetID;
            if (filePetID == petID) {
                found = true;  // PetID matched, we skip this line (i.e., "delete" this owner)
                continue;  // Skip adding this line to the vector
            }

            // If not the correct petID, keep the line
            lines.push_back(line);
        }

        ownerFile.close();  // Close the input file

        if (!found) {
            cout << "Owner with PetID " << petID << " not found!" << endl;
            return false;
        }

        // Open the file again for writing the updated list
        ofstream ownerFileOut("owners.txt");
        if (!ownerFileOut.is_open()) {
            cout << "Error opening owners file for writing!" << endl;
            return false;
        }

        // Write the remaining lines back to the file
        for (const string& line : lines) {
            ownerFileOut << line << endl;
        }

        ownerFileOut.close();  // Close the output file

        cout << "Owner with PetID " << petID << " deleted successfully!" << endl;
        return true;
    }


    void deleteOwner() override {
        int petID;
        cout << "Enter Pet ID to delete associated owner: ";
        cin >> petID;

        ifstream petFile("pets.txt");
        if (!petFile.is_open()) {
            cout << "Error opening pets file!" << endl;
            return;
        }

        vector<string> updatedPets;
        string line;
        int ownerID = -1;
        bool petFound = false;

        // Search for the pet by PetID and retrieve the associated OwnerID
        while (getline(petFile, line)) {
            stringstream ss(line);
            int currentPetID;
            ss >> currentPetID;

            if (currentPetID == petID) {
                petFound = true;
                ss >> ownerID;  // Get the associated OwnerID from the pet record
                break;
            }
            updatedPets.push_back(line);
        }
        petFile.close();

        if (!petFound) {
            cout << "Pet with ID " << petID << " not found!" << endl;
            return;
        }

        // Now, delete the owner from the owners.txt file
        ifstream ownerFile("owners.txt");
        if (!ownerFile.is_open()) {
            cout << "Error opening owners file!" << endl;
            return;
        }

        vector<string> updatedOwners;
        bool ownerFound = false;

        // Search for the owner and remove their record based on the OwnerID
        while (getline(ownerFile, line)) {
            stringstream ss(line);
            int currentOwnerID;
            ss >> currentOwnerID;

            if (currentOwnerID == ownerID) {
                ownerFound = true;
                continue;  // Skip the owner record to delete it
            }
            updatedOwners.push_back(line);  // Keep other owners
        }
        ownerFile.close();

        // If the owner is found, overwrite the owner file
        if (ownerFound) {
            ofstream outFile("owners.txt", ios::trunc);
            for (const string& owner : updatedOwners) {
                outFile << owner << endl;
            }
            outFile.close();
            cout << "Owner associated with PetID " << petID << " deleted successfully!" << endl;
        }
        else {
            cout << "Owner associated with PetID " << petID << " not found!" << endl;
        }
    }


    void deletePet() override {
        int petID;
        cout << "Enter Pet ID to delete: ";
        cin >> petID;

        ifstream petFile("pets.txt");
        if (!petFile.is_open()) {
            cout << "Error opening pets file!" << endl;
            return;
        }

        vector<string> updatedPets;
        string line;
        bool petFound = false;

        while (getline(petFile, line)) {
            stringstream ss(line);
            int existingPetID;
            ss >> existingPetID;

            if (existingPetID == petID) {
                petFound = true;
                continue;  // Skip the pet record to delete it
            }
            updatedPets.push_back(line);  // Keep other pets in the vector
        }
        petFile.close();

        if (petFound) {
            // Overwrite the pet file with the remaining pets
            ofstream outFile("pets.txt", ios::trunc);
            for (const string& pet : updatedPets) {
                outFile << pet << endl;
            }
            outFile.close();
            cout << "Pet with ID " << petID << " deleted successfully!" << endl;
        }
        else {
            cout << "Pet with ID " << petID << " not found!" << endl;
        }
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
        
    }

    void addOwner() override {
        int petID;
        string name, phoneNumber, email;

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
        cout << "Enter Owner's email: ";
        cin >> email;

        Owner owner(petID, name, phoneNumber, email);
        owner.saveToFile();
        cout << "Owner added successfully!" << endl;
    }

    void scheduleAppointment() override {
        Appointment::scheduleAppointment(); // Call the static method in Appointment class
    }

    void viewAppointments() override {
        Appointment::viewAppointments(); // Call the static method in Appointment class
    }
    void deleteAppointment() override {
        Appointment::deleteAppointment();
    }

    
};

#endif