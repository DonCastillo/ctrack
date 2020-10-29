#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <string>

class User {
 public:
     enum Group {DEVELOPER, TESTER, MANAGER, USER};
     static unsigned int counter;

     User(std::string pName);
     virtual ~User() {}

     void setName(std::string pName);
     std::string getName();

     void setGroup(unsigned int pInt);
     std::string getGroup();

     unsigned int getID();


 private:
     std::string name;
     unsigned int id;
     Group group;
};


#endif // USER_H_INCLUDED
