#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
protected:
    string username;
    string password;

public:
    User(const string& username, const string& password) : username(username), password(password) {}

    virtual void displayMenu() = 0;
    virtual void addPet() = 0;     // Pure virtual function for adding a pet
    virtual void addOwner() = 0;   // Pure virtual function for adding an owner
    virtual void scheduleAppointment() = 0;
    virtual void viewAppointments() = 0;
    virtual void deleteAppointment() = 0;
    virtual void deletePet() = 0;  // Pure virtual function to delete a pet
    virtual void deleteOwner() = 0;  // Pure virtual function to delete an owner

};

#endif
