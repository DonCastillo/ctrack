#ifndef COMMENT_H_INCLUDED
#define COMMENT_H_INCLUDED

#include "User.h"
#include <string>
#include <vector>

class Comment {
 public:
    /*!
       \brief   Constructor
       \brief   Initializes comment id, the commenter, and the comment
       \param   pId         - comment id (unsigned int)
       \param   pCommenter  - the user who comments (User*)
       \param   pComment    - the user's comment (string)
    */
     Comment(unsigned int pId, User* pCommenter, std::string pComment);

     /*!
        \brief  Destructor
     */
     virtual ~Comment();

     /*!
        \brief  Sets the comment.
        \param  pComment    - the comment (string)
     */
     void setComment(std::string pComment);

     /*!
        \brief  Gets the comment.
        \return returns the comment (string)
     */
     std::string getComment();

     /*!
        \brief  Sets the commenter.
        \param  pCommenter    - the user who comments (User*)
     */
     void setCommenter(User* pCommenter);

     /*!
        \brief  Gets the commenter.
        \return returns the commenter (User*)
     */
     User* getCommenter();

     /*!
        \brief  Gets the comment's id
        \return returns the comment's id (unsigned int)
     */
     unsigned int getID();

 private:
     /** comment id */
     unsigned int id;

     /** comment itself */
     std::string comment;

     /** commenter */
     User* commenter;
};


#endif // ISSUE_H_INCLUDED
