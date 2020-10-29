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


     Issue(unsigned int pId, std::string pTitle, User* pIssuer);
     virtual ~Issue();

     void setTitle(std::string pTitle);
     std::string getTitle();

     void setIssuer(User* pIssuer);
     User* getIssuer();

     void setType(unsigned int pInt);
     std::string getType();

     void setStatus(unsigned int pInt);
     std::string getStatus();

     void addAssignee(User* pUser);
     std::vector<User*> getAssignees();

     Comment* getDescription();

     void addComment(Comment* pComment);
     std::vector<Comment*> getComments();
     Comment* getComment(unsigned int pId);
     bool deleteComment(unsigned int pId);


     unsigned int getID();

 private:
     std::string title;
     unsigned int id;
     User* issuer;
     Type type;
     Status status;
     std::vector<User*> assignees;
     std::vector<Comment*> comments;
};


#endif // ISSUE_H_INCLUDED
