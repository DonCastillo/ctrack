#include "service/User.h"
#include <string>

User::User(std::string pName) {
    name = pName;
    group = Group::USER;
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
            group = Group::DEVELOPER;
            break;
        case 1:
            group = Group::TESTER;
            break;
        case 2:
            group = Group::MANAGER;
            break;
        case 3:
        default:
            group = Group::USER;
            break;
    }
}

std::string User::getGroup() {
    std::string groupLabel = "";

    switch (group) {
        case Group::DEVELOPER:
            groupLabel = "developer";
            break;
        case Group::TESTER:
            groupLabel = "tester";
            break;
        case Group::MANAGER:
            groupLabel = "manager";
            break;
        case Group::USER:
            groupLabel = "user";
            break;
    }

    return groupLabel;
}
