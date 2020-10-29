#ifndef COMMENT_H
#define COMMENT_H

#include "service/User.h"
#include <string>
#include <vector>

class Comment {
 public:

     Comment(User* pCommenter, std::string pComment) :
         commenter(pCommenter), comment(pComment) {}
     virtual ~Comment() {}

     void setComment(std::string pComment);
     std::string getComment();

     void setCommenter(User* pCommenter);
     User* getCommenter();


 private:
     unsigned int id;
     std::string comment;
     User* commenter;
};


#endif // ISSUE_H
