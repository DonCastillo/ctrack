#include "User.h"
#include <string>
#include <iostream>

User::User(unsigned int pId, std::string pName) {
    id = pId;
    name = pName;
    group = User::USER;
}

unsigned int User::getID() const {
    return id;
}

void User::setName(std::string pName) {
    name = pName;
}

std::string User::getName() const {
    return name;
}

void User::setGroup(unsigned int pInt) {
    switch (pInt) {
        case 0:
            group = User::DEVELOPER;
            break;
        case 1:
            group = User::TESTER;
            break;
        case 2:
            group = User::MANAGER;
            break;
        case 3:
        default:
            group = User::USER;
            break;
    }
}

std::string User::getGroup() const {
    std::string groupLabel = "";

    switch (group) {
        case User::DEVELOPER:
            groupLabel = "developer";
            break;
        case User::TESTER:
            groupLabel = "tester";
            break;
        case User::MANAGER:
            groupLabel = "manager";
            break;
        case User::USER:
            groupLabel = "user";
            break;
    }

    return groupLabel;
}

bool operator== (const User& a, const User& b) {
    return (a.id == b.id);
}

bool operator!= (const User& a, const User& b) {
    return (a.id != b.id);
}

std::ostream& operator<<(std::ostream& os, const User& u) {
    os << "========\n";
    os << "USER\n";
    os << "========\n";
    os << "ID:    " << std::to_string(u.id) << "\n";
    os << "NAME:  " << u.name << "\n";
    os << "GROUP: " << u.getGroup() << "\n";
    os << "\n";
    return os;
}


