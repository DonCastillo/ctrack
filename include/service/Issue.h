#ifndef ISSUE_H
#define ISSUE_H

#include "service/User.h"
#include <string>
#include <vector>

class Issue {
 public:
     enum Type {FEATURE, BUG, TASK};
     enum Status {NEW, ASSIGNED, FIXED, WONTFIX};


     Issue() {}
     virtual ~Issue() {}
     void setTitle(std::string pTitle);
     std::string getTitle();




 private:
     std::string title;
     unsigned int id;
     User* issuer;
     std::vector<User*> assigned;
     Comment* description
     std::vector<Comment*> comments;
};


#endif // ISSUE_H
