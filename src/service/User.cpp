#include <string>
#include <iostream>
#include "../../include/service/User.h"
#include "../../include/service/CTrackUI.h"

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


std::string User::getGroupString() const {
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

User::Group User::getGroup() const {
    return group;
}


std::string User::getGroup(unsigned int pInt) {
    std::string groupLabel = "";
    switch (pInt) {
        case 0:
            groupLabel = "developer";
            break;
        case 1:
            groupLabel = "tester";
            break;
        case 2:
            groupLabel = "manager";
            break;
        case 3:
        default:
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
    CTrackUI* ui = new CTrackUI();
    //os << ui->formatRow("USER ID",    std::to_string(u.id));
    os << ui->formatRow("USER NAME",  u.name);
    os << ui->formatRow("USER GROUP", u.getGroupString());
    os << "\n";
    delete ui;
    return os;
}
