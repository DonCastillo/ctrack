#ifndef USER_H
#define USER_H

#include <string>

class User {
 public:
     User(std::string pName) : name(pName) {}
     virtual ~User() {}
     void setName(std::string pName);
     std::string getName();


 private:
     std::string name;
     unsigned int id;
};


#endif // USER_H
