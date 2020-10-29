#include "Issue.h"
#include "Comment.h"
#include "User.h"
#include <string>
#include <vector>

Issue::Issue(unsigned int pId, std::string pTitle, User* pIssuer) {
    id = pId;
    title = pTitle;
    issuer = pIssuer;
    type = Issue::TASK;
    status = Issue::NEW;
}

Issue::~Issue() {
    for (int i = 0; i < comments.size(); ++i)
        delete comments[i];
}

unsigned int Issue::getID() {
    return id;
}

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
            type = Issue::FEATURE;
            break;
        case 1:
            type = Issue::BUG;
            break;
        case 2:
        default:
            type = Issue::TASK;
            break;
    }
}

std::string Issue::getType() {
    std::string typeLabel = "";
    switch(type) {
        case Issue::FEATURE:
            typeLabel = "feature";
            break;
        case Issue::BUG:
            typeLabel = "bug";
            break;
        case Issue::TASK:
            typeLabel = "task";
    }
    return typeLabel;
}

void Issue::setStatus(unsigned int pInt) {
    switch (pInt) {
        case 0:
            status = Issue::NEW;
            break;
        case 1:
            status = Issue::ASSIGNED;
            break;
        case 2:
            status = Issue::FIXED;
            break;
        case 3:
            status = Issue::WONTFIX;
            break;
        default:
            status = Issue::NEW;
            break;
    }
}


std::string Issue::getStatus() {
    std::string statusLabel = "";
    switch (status) {
        case Issue::NEW:
            statusLabel = "new";
            break;
        case Issue::ASSIGNED:
            statusLabel = "assigned";
            break;
        case Issue::FIXED:
            statusLabel = "fixed";
            break;
        case Issue::WONTFIX:
            statusLabel = "won't fix";
            break;
    }
    return statusLabel;
}

void Issue::addAssignee(User* pUser) {
    assignees.push_back(pUser);
    status = Issue::ASSIGNED;
}

std::vector<User*> Issue::getAssignees() {
    if (assignees.empty()) {
        status = Issue::NEW;
    }
    return assignees;
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

Comment* Issue::getComment(unsigned int pId) {
    for(Comment* c : comments) {
        if (c->getID() == pId)
            return c;
    }
    return nullptr;
}

bool Issue::deleteComment(unsigned int pId) {
    for (int i = 0; i < comments.size(); ++i) {
        if (c->getID() == pID) {
            comments.erase(comments.begin() + i);
            return true;
        }
    }
    return false;
}

