#ifndef OWNER_H
#define OWNER_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Owner {
private:
    int petID;
    string name;
    string phoneNumber;
    string email;

public:
    Owner(int petID, string name, string phoneNumber, string email)
        : petID(petID), name(name), phoneNumber(phoneNumber), email(email) {}

    void saveToFile() {
        ofstream ownerFile("owners.txt", ios::app);
        if (ownerFile.is_open()) {
            
            ownerFile << petID << " " << name << " " << phoneNumber << " " << email << endl;
            ownerFile.close();
        }
        else {
            cout << "Error opening file to save owner!" << endl;
        }
    }


    static void viewOwners() {
        ifstream ownerFile("owners.txt");
        if (!ownerFile.is_open()) {
            cout << "Error opening file to view owners!" << endl;
            return;
        }

        cout << "Owner List with Linked Pets:\n";
        string line;
        while (getline(ownerFile, line)) {
            stringstream ss(line);
            int petID;
            string ownerName, phoneNumber, email;
            ss >> petID >> ownerName >> phoneNumber >> email;

            cout << "Owner Name: " << ownerName << " | Phone: " << phoneNumber << " | Email: " << email << " | Pet ID: " << petID;

            
            ifstream petFile("pets.txt");
            if (petFile.is_open()) {
                string petLine;
                while (getline(petFile, petLine)) {
                    stringstream petSS(petLine);
                    int storedPetID;
                    string petName, breed, medicalHistory;
                    int age;
                    string vaccinationStatus;

                    petSS >> storedPetID >> petName >> breed >> age >> medicalHistory >> vaccinationStatus;

                    if (storedPetID == petID) {
                        cout << " | Pet Name: " << petName << " | Breed: " << breed << " | Age: " << age << endl;
                        break;
                    }
                }
                petFile.close();
            }
            else {
                cout << " (Pet information not available)" << endl;
            }
        }
        ownerFile.close();
    }

};

#endif
