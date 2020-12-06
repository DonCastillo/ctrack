#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "../../include/service/Issue.h"
#include "../../include/service/Comment.h"
#include "../../include/service/User.h"
#include "../../include/service/CTrackUI.h"


Issue::Issue(unsigned int pId, std::string pTitle, User* pIssuer) {
    id              = pId;
    title           = pTitle;
    issuer          = pIssuer;
    type            = Issue::TASK;
    status          = Issue::NEW;
    description     = "";
    numOfComments   = 0;
}

Issue::~Issue() {
    for (int i = 0; i < comments.size(); ++i)
        delete comments[i];
}

unsigned int Issue::getID() const {
    return id;
}

void Issue::setTitle(std::string pTitle) {
    title = pTitle;
}

std::string Issue::getTitle() const {
    return title;
}

void Issue::setIssuer(User* pIssuer) {
    issuer = pIssuer;
}

User* Issue::getIssuer() const {
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

std::string Issue::getTypeString() const {
    std::string typeLabel = "";
    switch (type) {
        case Issue::FEATURE:
            typeLabel = "feature";
            break;
        case Issue::BUG:
            typeLabel = "bug";
            break;
        case Issue::TASK:
            typeLabel = "task";
            break;
    }
    return typeLabel;
}


unsigned int Issue::getTypeInt() const {
    unsigned int typeInt;
    switch (type) {
        case Issue::FEATURE:
            typeInt = 0;
            break;
        case Issue::BUG:
            typeInt = 1;
            break;
        case Issue::TASK:
            typeInt = 2;
            break;
    }
    return typeInt;
}

Issue::Type Issue::getType() const {
    return type;
}


std::string Issue::getTypeT(unsigned int pInt) {
  std::string typeLabel = "";
  switch (pInt) {
    case 0:
      typeLabel = "feature";
      break;
    case 1:
      typeLabel = "bug";
      break;
    case 2:
    default:
        typeLabel = "task";
        break;
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


std::string Issue::getStatusString() const {
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

unsigned int Issue::getStatusInt() const {
    unsigned int statusInt;
    switch (status) {
        case Issue::NEW:
            statusInt = 0;
            break;
        case Issue::ASSIGNED:
            statusInt = 1;
            break;
        case Issue::FIXED:
            statusInt = 2;
            break;
        case Issue::WONTFIX:
            statusInt = 3;
            break;
    }
    return statusInt;
}

Issue::Status Issue::getStatus() const {
    return status;
}

std::string Issue::getStatusT(unsigned int pInt) {
  std::string statusLabel = "";
  switch (pInt) {
    case 0:
      statusLabel = "new";
      break;
    case 1:
      statusLabel = "assigned";
      break;
    case 2:
      statusLabel = "fixed";
      break;
    case 3:
    default:
      statusLabel = "won't fix";
      break;
  }
  return statusLabel;
}

void Issue::addAssignee(User* pUser) {
    assignees.push_back(pUser);
    //status = Issue::ASSIGNED;
}

std::vector<User*> Issue::getAssignees() const {
    return assignees;
}

User* Issue::getAssignee(unsigned int pId) const {
    for (User* u : assignees) {
        if (u->getID() == pId)
            return u;
    }
    return nullptr;
}

bool Issue::deleteAssignee(unsigned int pId) {
    bool isSuccessful = false;
    for (int i = 0; i < assignees.size(); ++i) {
        if (assignees[i]->getID() == pId) {
            assignees.erase(assignees.begin() + i);
            isSuccessful = true;
        }
    }
    // change the card back to new
    if (assignees.empty()) {
        status = Issue::NEW;
    }
    return isSuccessful;
}

std::string Issue::getDescription() const {
    return description;
}

void Issue::setDescription(std::string pDesc) {
    description = pDesc;
}

void Issue::clearComments() {
    comments.clear();
    numOfComments = 0;
}

void Issue::addComment(Comment* pComment) {
    pComment->setID(numOfComments++);
    comments.push_back(pComment);
}

std::vector<Comment*> Issue::getComments() const {
    return comments;
}

Comment* Issue::getComment(unsigned int pId) const {
    for (Comment* c : comments) {
        if (c->getID() == pId)
            return c;
    }
    return nullptr;
}

bool Issue::deleteComment(unsigned int pId) {
    for (int i = 0; i < comments.size(); ++i) {
        if (comments[i]->getID() == pId) {
            comments.erase(comments.begin() + i);
            return true;
        }
    }
    return false;
}

//void Issue::setNumOfComments(unsigned int pInt) {
//    numOfComments = pInt;
//}

unsigned int Issue::getNumOfComments() const {
    return numOfComments;
}

bool operator== (const Issue& a, const Issue& b) {
    return (a.id == b.id);
}

bool operator!= (const Issue& a, const Issue& b) {
    return (a.id != b.id);
}

std::ostream& operator<<(std::ostream& os, const Issue& i) {
    CTrackUI* ui = new CTrackUI();
    unsigned int left;
    std::string right = "";

    //os << ui->formatRow("ISSUE ID",         std::to_string(i.id));
    os << ui->formatRow("TITLE",            i.title);
    os << ui->formatRow("DESCRIPTION",      i.description);

    left  = i.issuer->getID();
    right = i.issuer->getName();
    os << ui->formatRow("CREATED BY",       ui->formatIDRow(left, right));

    os << ui->formatRow("TYPE",             i.getTypeString());
    os << ui->formatRow("STATUS",           i.getStatusString());

    for (User* x : i.assignees) {
        left  = x->getID();
        right = x->getName();
        os << ui->formatRow("ASSIGNED TO",  ui->formatIDRow(left, right));
    }

    os << ui->formatRow("COMMENTS",         "");

    for (Comment* x : i.comments) {
        std::string top     = "POSTED BY: " + x->getCommenter()->getName();
        std::string bottom  = "COMMENT  : " + x->getComment();
        os << "\t" << top << "\n";
        os << "\t" << bottom << "\n";
    }

    os << "\n";
    delete ui;
    return os;
}
