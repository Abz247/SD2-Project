#ifndef PET_H
#define PET_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class Pet {
private:
    int petID;
    string name;
    string breed;
    int age;
    string medicalHistory;
    bool vaccinationStatus;

public:
    Pet(int petID, const string& name, const string& breed, int age, const string& medicalHistory, bool vaccinationStatus)
        : petID(petID), name(name), breed(breed), age(age), medicalHistory(medicalHistory), vaccinationStatus(vaccinationStatus) {
    }

    int getPetID() const { return petID; }
    string getName() const { return name; }
    string getBreed() const { return breed; }
    int getAge() const { return age; }
    string getMedicalHistory() const { return medicalHistory; }
    bool isVaccinated() const { return vaccinationStatus; }

    void display() const {
        cout << "Pet ID: " << petID << endl;
        cout << "Name: " << name << endl;
        cout << "Breed: " << breed << endl;
        cout << "Age: " << age << endl;
        cout << "Medical History: " << medicalHistory << endl;
        cout << "Vaccination Status: " << (vaccinationStatus ? "Vaccinated" : "Not Vaccinated") << endl;
    }

    static bool petIDExists(int petID) {
        ifstream file("pets.txt");
        if (!file.is_open()) {
            return false;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int existingID;
            ss >> existingID;
            if (existingID == petID) {
                return true;
                break;
            }
        }
        return false;
    }

    void saveToFile() const {
        if (petIDExists(petID)) {
            cout << "This petID already exists, please create a different ID number." << endl;
            return;

        }

        ofstream file("pets.txt", ios::app);
        if (file.is_open()) {
            file << petID << " " << name << " " << breed << " " << age << " " << medicalHistory << " " << (vaccinationStatus ? "Vaccinated" : "Not Vaccinated") << endl;
            file.close();
            cout << "Pet added successfully!" << endl;
        }
        else {
            cerr << "Error opening pets file!" << endl;
        }
    }
};

#endif
