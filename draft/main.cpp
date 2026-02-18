#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "pet.h"
#include "owner.h"
#include "admin.h"
#include "staff.h"
#include "veterinarian.h"
#include "appointment.h"

using namespace std;

void viewPets() {
    ifstream petFile("pets.txt");
    if (!petFile.is_open()) {
        cout << "Error opening pets file!" << endl;
        return;
    }

    cout << "Pet List with Linked Owners:\n";
    string petLine;
    while (getline(petFile, petLine)) {
        stringstream petSS(petLine);
        int petID;
        string petName, breed, medicalHistory;
        int age;
        string vaccinationStatus;

        petSS >> petID >> petName >> breed >> age >> medicalHistory >> vaccinationStatus;

        cout << "Pet ID: " << petID << " | Name: " << petName << " | Breed: " << breed << " | Medical History: " << medicalHistory <<  " | Age: " << age << " | Vaccination: " << vaccinationStatus;

       
        ifstream ownerFile("owners.txt");
        if (ownerFile.is_open()) {
            string ownerLine;
            while (getline(ownerFile, ownerLine)) {
                stringstream ownerSS(ownerLine);
                int ownerPetID;
                string ownerName, phoneNumber, email;

                ownerSS >> ownerPetID >> ownerName >> phoneNumber >> email;

                if (ownerPetID == petID) {
                    cout << " | Owner Name: " << ownerName << " | Phone: " << phoneNumber << " | Email: " << email << endl;
                    break;
                }
            }
            ownerFile.close();
        }
        else {
            cout << " (Owner information not available)" << endl;
        }
    }
    petFile.close();
}


void viewOwners() {
    ifstream file("owners.txt");
    if (!file.is_open()) {
        cout << "Error opening owners file!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

int main() {
    string username, password;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    User* currentUser = nullptr;

    if (username == "admin_user" && password == "admin_pass") {
        currentUser = new Admin("admin_user", "admin_pass");
    }
    else if (username == "vet_user" && password == "vet_pass") {
        currentUser = new Veterinarian("vet_user", "vet_pass");
    }
    else if (username == "staff_user" && password == "staff_pass") {
        currentUser = new Staff("staff_user", "staff_pass");
    }
    else {
        cout << "Invalid credentials!" << endl;
        return 0;
    }

    cout << "Login successful!" << endl;

    bool loggedIn = true;
    while (loggedIn) {
        currentUser->displayMenu();
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: 
            currentUser->addPet();
            break;
        case 2:  
            currentUser->addOwner();
            break;
        case 3:  
            currentUser->scheduleAppointment();
            break;
        case 4: 
            currentUser->viewAppointments();
            break;
        
        case 5:  
            if (dynamic_cast<Admin*>(currentUser) || dynamic_cast<Veterinarian*>(currentUser)) {
                viewPets();
            }
            else {
                cout << "Unauthorized action!" << endl;
            }
            break;
        case 6:  
            if (dynamic_cast<Admin*>(currentUser) || dynamic_cast<Veterinarian*>(currentUser)) {
                viewOwners();
            }
            else {
                cout << "Unauthorized action!" << endl;
            }
            break;
        case 7:
            if (dynamic_cast<Admin*>(currentUser)) {
                currentUser->deleteAppointment();
            }
            break;
        case 8: 
            if (dynamic_cast<Admin*>(currentUser)) {
                currentUser->deletePet();  
            }
            break;
        case 9:  
            if (dynamic_cast<Admin*>(currentUser)) {
                currentUser->deleteOwner(); 
            }
            break;

        case 10:  
            loggedIn = false;
            cout << "Logging out..." << endl;
            break;
        default:
            cout << "Invalid option!" << endl;
            break;
        }
    }

    delete currentUser;
    return 0;
}
