#include "User.h"
#include <string>

User::User(unsigned int pId, std::string pName) {
    id = pId;
    name = pName;
    group = User::USER;
}

unsigned int User::getID() {
    return id;
}

void User::setName(std::string pName){
    name = pName;
}

std::string User::getName() {
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

std::string User::getGroup() {
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
