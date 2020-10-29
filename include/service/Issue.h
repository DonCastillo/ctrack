#ifndef ISSUE_H
#define ISSUE_H

#include "service/User.h"
#include "service/Comment.h"
#include <string>
#include <vector>

class Issue {
 public:
     enum Type {FEATURE, BUG, TASK};
     enum Status {NEW, ASSIGNED, FIXED, WONTFIX};


     Issue(std::string pTitle, User* pIssuer) :
         title(pTitle), issuer(pIssuer), type(Type::TASK), status(Status::NEW) {}
     virtual ~Issue() {}

     void setTitle(std::string pTitle);
     std::string getTitle();

     void setIssuer(User* pIssuer);
     User* getIssuer();

     void setType(unsigned int pInt);
     std::string getType();

     void setStatus(unsigned int pInt);
     std::string getStatus();

     void assignTo(User* pUser);
     std::vector<User*> getAssignedUsers();

     Comment* getDescription();

     void addComment(Comment* pComment);
     std::vector<Comment*> getComments();

 private:
     std::string title;
     unsigned int id;
     User* issuer;
     Type type;
     Status status;
     std::vector<User*> assigned;
     Comment* description;
     std::vector<Comment*> comments;
};


#endif // ISSUE_H
