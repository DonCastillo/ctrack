#include "service/Comment.h"
#include "service/User.h"
#include <string>

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
