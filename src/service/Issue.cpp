#include "service/Issue.h"
#include "service/Comment.h"
#include "service/User.h"
#include <string>
#include <vector>

void Issue::setTitle(std::string pTitle) {
    title = pTitle;
}

std::string Issue::getTitle() {
    return title;
}

void Issue::setIssuer(User* pIssuer) {
    issuer = pIssuer;
}

User* Issue::getIssuer() {
    return issuer;
}

void Issue::setType(unsigned int pInt) {
    switch (pInt) {
        case 0:
            type = Type::FEATURE;
            break;
        case 1:
            type = Type::BUG;
            break;
        case 2:
        default:
            type = Type::TASK;
            break;
    }
}

std::string Issue::getType() {
    std::string typeLabel = "";
    switch(type) {
        case Type::FEATURE:
            typeLabel = "feature";
            break;
        case Type::BUG:
            typeLabel = "bug";
            break;
        case Type::TASK:
            typeLabel = "task";
    }
    return typeLabel;
}

void Issue::setStatus(unsigned int pInt) {
    switch (pInt) {
        case 0:
            status = Status::NEW;
            break;
        case 1:
            status = Status::ASSIGNED;
            break;
        case 2:
            status = Status::FIXED;
            break;
        case 3:
            status = Status::WONTFIX;
            break;
        default:
            status = Status::NEW;
            break;
    }
}


std::string Issue::getStatus() {
    std::string statusLabel = "";
    switch (status) {
        case Status::NEW:
            statusLabel = "new";
            break;
        case Status::ASSIGNED:
            statusLabel = "assigned";
            break;
        case Status::FIXED:
            statusLabel = "fixed";
            break;
        case Status::WONTFIX:
            statusLabel = "won't fix";
            break;
    }
    return statusLabel;
}

void Issue::assignTo(User* pUser) {
    assigned.push_back(pUser);
    status = Status::ASSIGNED;
}

std::vector<User*> Issue::getAssignedUsers() {
    if (assigned.empty()) {
        status = Status::NEW;
    }
    return assigned;
}

Comment* Issue::getDescription() {
    if (!comments.empty()) {
        return comments[0];
    }
    return nullptr;
}

void Issue::addComment(Comment* pComment) {
    comments.push_back(pComment);
}

std::vector<Comment*> Issue::getComments() {
    return comments;
}
