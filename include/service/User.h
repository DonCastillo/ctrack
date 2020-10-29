#ifndef USER_H
#define USER_H

#include <string>

class User {
 public:
     enum Group {DEVELOPER, TESTER, MANAGER, USER};

     User(std::string pName) : name(pName), group(Group::USER) {}
     virtual ~User() {}

     void setName(std::string pName);
     std::string getName();

     void setGroup(unsigned int pInt);
     std::string getGroup();


 private:
     std::string name;
     unsigned int id;
     Group group;
};


#endif // USER_H
