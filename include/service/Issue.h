#ifndef ISSUE_H_INCLUDED
#define ISSUE_H_INCLUDED

#include "User.h"
#include "Comment.h"
#include <string>
#include <vector>

class Issue {
 public:
     enum Type {FEATURE, BUG, TASK};
     enum Status {NEW, ASSIGNED, FIXED, WONTFIX};


     Issue(std::string pTitle, User* pIssuer);
     virtual ~Issue();

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
     std::vector<Comment*> comments;
};


#endif // ISSUE_H_INCLUDED
