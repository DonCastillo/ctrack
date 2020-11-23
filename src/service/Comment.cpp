#include "Comment.h"
#include "User.h"
#include "CTrackUI.h"
#include <string>
#include <iostream>

Comment::Comment(unsigned int pId, User* pCommenter, std::string pComment) {
    id = pId;
    commenter = pCommenter;
    comment = pComment;
}

Comment::~Comment() {}

unsigned int Comment::getID() const {
    return id;
}

void Comment::setComment(std::string pComment) {
    comment = pComment;
}

std::string Comment::getComment() const {
    return comment;
}

void Comment::setCommenter(User* pCommenter) {
    commenter = pCommenter;
}

User* Comment::getCommenter() const {
    return commenter;
}


bool operator== (const Comment& a, const Comment& b) {
    return (a.id == b.id);
}

bool operator!= (const Comment& a, const Comment& b) {
    return (a.id != b.id);
}

std::ostream& operator<<(std::ostream& os, const Comment& c) {
    os << CTrackUI::formatRow("COMMENT ID",    std::to_string(c.id));

    unsigned int left = (c.commenter)->getID();
    std::string right = (c.commenter)->getName();
    os << CTrackUI::formatRow("POSTED BY",
                              CTrackUI::formatIDRow(left, right));

    os << CTrackUI::formatRow("COMMENT",     c.comment);
    os << "\n";
    return os;
}
