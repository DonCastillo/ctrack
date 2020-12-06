#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <string>

/** User class */
class User {
 public:
     /** group categories */
     enum Group {DEVELOPER, TESTER, MANAGER, USER};

     /*!
        \brief  converts an integer representation of
                any group into a string
        \param  pInt      integer representation of
                          a group to be converted to
                          string (unsigned int)
        \return returns the string representation of a group (string)
     */
     static std::string getGroup(unsigned int pInt);

     /*!
        \brief  Constructor
        \brief  Initializes user id and name. Defaults the group to USER.
        \param  pId     - user id (int)
        \param  pName   - user name (string)
     */
     User(unsigned int pId, const std::string& pName);

     /*!
        \brief  Destructor
     */
     virtual ~User() {}

     /*!
        \brief  Sets the name of the user.
        \param  pName    - name to be set (string)
     */
     void setName(const std::string& pName);

     /*!
        \brief  Gets the name of the user.
        \return returns the name of the user (string)
     */
     std::string getName() const;

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
        \return returns the group (Group)
     */
     Group getGroup() const;

     /*!
        \brief  Gets the user's group's string representation
        \return returns the group name in string (string)
     */
     std::string getGroupString() const;

     /*!
        \brief  Gets the user's id
        \return returns the user's id (unsigned int)
     */
     unsigned int getID() const;

     /*!
        \brief  Compares two users if they have equal id
        \param  a       - first user (User)
        \param  b       - second user (User)
        \return returns true if they are equal, otherwise false (bool)
     */
     friend bool operator==(const User& a, const User& b);

     /*!
        \brief  Compares two users if they have unequal id
        \param  a       - first user (User)
        \param  b       - second user (User)
        \return returns true if they are unequal, otherwise false (bool)
     */
     friend bool operator!=(const User& a, const User& b);

     /*!
        \brief  prints user information
        \param  os      - ostream (ostream)
        \param  u       - user (User)
     */
     friend std::ostream& operator<<(std::ostream& os, const User& u);



 private:
     /** user group */
     Group group;

     /** user name */
     std::string name;

     /** user id */
     unsigned int id;
};


#endif // USER_H_INCLUDED
