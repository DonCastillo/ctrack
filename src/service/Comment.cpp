#include "service/Comment.h"
#include "service/User.h"
#include <string>

Comment::Comment(User* pCommenter, std::string pComment) {
    commenter = pCommenter;
    comment = pComment;
}

Comment::~Comment() {
    delete commenter;
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
