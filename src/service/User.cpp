#include "service/User.h"
#include <string>

void User::setName(std::string pName){
    name = pName;
}

std::string User::getName() {
    return name;
}

