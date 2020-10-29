#include "Comment.h"
#include "User.h"
#include <string>

Comment::Comment(unsigned int pId, User* pCommenter, std::string pComment) {
    id = pId;
    commenter = pCommenter;
    comment = pComment;
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
