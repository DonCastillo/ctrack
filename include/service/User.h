#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <string>

class User {
 public:
     enum Group {DEVELOPER, TESTER, MANAGER, USER};

     /*!
        \brief  Constructor
        \brief  Initializes user id and name. Defaults the group to USER.
        \param  pId     - user id (int)
        \param  pName   - user name (string)
     */
     User(unsigned int pId, std::string pName);

     /*!
        \brief  Destructor
     */
     virtual ~User() {}

     /*!
        \brief  Sets the name of the user.
        \param  pName    - name to be set (string)
     */
     void setName(std::string pName);

     /*!
        \brief  Gets the name of the user.
        \return returns the name of the user (string)
     */
     std::string getName();

     /*!
        \brief  Sets the user to a group
        \param  pInt    - sets user to a group based on integer
                          passed (unsigned int):
                0       DEVELOPER
                1       TESTER
                2       MANAGER
                3       USER
                any     USER
     */
     void setGroup(unsigned int pInt);

     /*!
        \brief  Gets the group which the user belongs to.
        \return returns the group name (string)
     */
     std::string getGroup();

     /*!
        \brief  Gets the user's id
        \return returns the user's id (unsigned int)
     */
     unsigned int getID();


 private:
     std::string name;
     unsigned int id;
     Group group;
};


#endif // USER_H_INCLUDED
