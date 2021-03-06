#ifndef COMMENT_H_INCLUDED
#define COMMENT_H_INCLUDED

#include "User.h"
#include <string>
#include <vector>

/** Comment class */
class Comment {
 public:
    /*!
       \brief   Constructor
       \brief   Initializes comment id, the commenter, and the comment
       \param   pId         - comment id (unsigned int)
       \param   pCommenter  - the user who comments (User*)
       \param   pComment    - the user's comment (string)
    */
     Comment(unsigned int pId, User* pCommenter, const std::string& pComment);

     /*!
        \brief  Destructor
     */
     virtual ~Comment();

     /*!
        \brief  Sets the comment.
        \param  pComment    - the comment (string)
     */
     void setComment(const std::string& pComment);

     /*!
        \brief  Gets the comment.
        \return returns the comment (string)
     */
     std::string getComment() const;

     /*!
        \brief  Sets the commenter.
        \param  pCommenter    - the user who comments (User*)
     */
     void setCommenter(User* pCommenter);

     /*!
        \brief  Gets the commenter.
        \return returns the commenter (User*)
     */
     User* getCommenter() const;

     /*!
        \brief  Gets the comment's id
        \return returns the comment's id (unsigned int)
     */
     unsigned int getID() const;

    /*!
        \brief  Sets the comment's id
        \param  pInt       - integer to be assigned as the
                             comment's id (unsigned int)
     */
     void setID(unsigned int pInt);

     /*!
        \brief  Compares two comments if they have equal id
        \param  a         - first comment (Comment)
        \param  b         - second comment (Comment)
        \return returns true if they are equal, otherwise false (bool)
     */
     friend bool operator==(const Comment& a, const Comment& b);

     /*!
        \brief  Compares two comments if they have unequal id
        \param  a         - first comment (Comment)
        \param  b         - second comment (Comment)
        \return returns true if they are unequal, otherwise false (bool)
     */
     friend bool operator!=(const Comment& a, const Comment& b);

     /*!
        \brief  prints comment information
        \param  os        - ostream (ostream)
        \param  c         - comment (Comment)
     */
     friend std::ostream& operator<<(std::ostream& os, const Comment& c);

 private:
     /** comment id */
     unsigned int id;

     /** comment itself */
     std::string comment;

     /** commenter */
     User* commenter;
};


#endif // ISSUE_H_INCLUDED
