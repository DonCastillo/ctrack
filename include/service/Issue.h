#ifndef ISSUE_H
#define ISSUE_H

#include "service/User.h"
#include <string>
#include <vector>

class Issue {
 public:
     enum Type { Feature, Bug, Task };
     enum Status { New, Assigned, Fixed, WontFix };


     Issue() {}
     virtual ~Issue() {}
     void setTitle(std::string pTitle);
     std::string getTitle();


 private:
     std::string title;
     unsigned int id;
     std::vector<User*> assigned;
     //Comment* description
     //std::vector<Comment*> comments
};


#endif // ISSUE_H
