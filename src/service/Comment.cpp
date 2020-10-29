#include "Comment.h"
#include "User.h"
#include <string>

Comment::Comment(User* pCommenter, std::string pComment) {
    commenter = pCommenter;
    comment = pComment;
    ++id;
}

Comment::~Comment() {}

unsigned int Comment::getID() {
    return id;
}

void Comment::setComment(std::string pComment) {
    comment = pComment;
}

std::string Comment::getComment() {
    return comment;
}

void Comment::setCommenter(User* pCommenter) {
    commenter = pCommenter;
}

User* Comment::getCommenter() {
    return commenter;
}
