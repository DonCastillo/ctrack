#include "service/Issue.h"
#include <string>

void Issue::setTitle(std::string pTitle){
    title = pTitle;
}

std::string Issue::getTitle() {
    return title;
}

