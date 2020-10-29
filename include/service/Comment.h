#ifndef COMMENT_H_INCLUDED
#define COMMENT_H_INCLUDED

#include "User.h"
#include <string>
#include <vector>

class Comment {
 public:

     Comment(User* pCommenter, std::string pComment);
     virtual ~Comment();

     void setComment(std::string pComment);
     std::string getComment();

     void setCommenter(User* pCommenter);
     User* getCommenter();

     unsigned int getID();
     static unsigned int counter;




 private:
     unsigned int id;
     std::string comment;
     User* commenter;
};


#endif // ISSUE_H_INCLUDED
