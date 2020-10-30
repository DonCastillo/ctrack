#ifndef ISSUE_H_INCLUDED
#define ISSUE_H_INCLUDED

#include "User.h"
#include "Comment.h"
#include <string>
#include <vector>

class Issue {
 public:
     /** type categories */
     enum Type {FEATURE, BUG, TASK};

     /** status categories */
     enum Status {NEW, ASSIGNED, FIXED, WONTFIX};

     /*!
        \brief  Constructor
        \brief  Initializes issue id, title, and the issuer
        \param  pId     - issue id (unsigned int)
        \param  pTitle  - issue title (string)
        \param  pIssuer - the user who issues the issue (User*)
     */
     Issue(unsigned int pId, std::string pTitle, User* pIssuer);

     /*!
        \brief  Destructor
        \brief  Also deletes the comments in this issue
     */
     virtual ~Issue();

     /*!
        \brief  Sets the title of the issue.
        \param  pTitle  - title of the issue (string)
     */
     void setTitle(std::string pTitle);

     /*!
        \brief  Gets the title of the issue.
        \return returns the title of the issue (string)
     */
     std::string getTitle();

     /*!
        \brief  Sets the issuer.
        \param  pIssuer - the user who issues the issue (User*)
     */
     void setIssuer(User* pIssuer);

     /*!
        \brief  Gets the issuer.
        \return returns the issuer (User*)
     */
     User* getIssuer();

     /*!
        \brief  Sets the issue type.
        \param  pInt    - sets the type of the issue
                          based on the integer passed (unsigned int):
                0         FEATURE
                1         BUG
                2         TASK
                any       TASK
     */
     void setType(unsigned int pInt);

     /*!
        \brief  Gets the issue type.
        \return returns the type of the issue (string)
     */
     std::string getType();

     /*!
        \brief  Sets the issue status.
        \param  pInt    - sets the status of the issue
                          based on the integer passed (unsigned int):
                0         NEW
                1         ASSIGNED
                2         FIXED
                3         WONTFIX
                any       NEW
     */
     void setStatus(unsigned int pInt);

     /*!
        \brief  Gets the status of the issue.
        \return returns the status of the issue (string)
     */
     std::string getStatus();

     /*!
        \brief  Adds a user to the list of users assigned to this issue.
        \param  pUser   - user to be assigned to this issue (User*)
     */
     void addAssignee(User* pUser);

     /*!
        \brief  Gets all the users assigned to this issue.
        \return returns all the users assigned to this issue (vector<User*>)
     */
     std::vector<User*> getAssignees();

     /*!
        \brief  Gets the specific user assigned to this issue.
        \param  pId     - id of the user to be returned (unsigned int)
        \return returns the assigned user based on the id (User*)
     */
     User* getAssignee(unsigned int pId);

     /*!
        \brief  Deletes a specific user assigned to this issue.
        \param  pId     - id of the user to be deleted (unsigned int)
        \return returns a boolean:
                true    means the user was successfully deleted as one
                        of the assignees (bool)
                false   means the user was not successfully deleted either
                        because the list of assignees is empty or the user
                        is not one of the assignees (bool)
     */
     bool deleteAssignee(unsigned int pId);

     /*!
        \brief  Gets the issue's description.
        \return returns the description or the first comment (Comment*)
     */
     Comment* getDescription();

     /*!
        \brief  Adds a comment to this issue.
        \param  pComment  - comment to be added (Comment*)
     */
     void addComment(Comment* pComment);

     /*!
        \brief  Gets all the comments of this issue.
        \return returns all the comments of this issue (vector<Comment*>)
     */
     std::vector<Comment*> getComments();

     /*!
        \brief  Gets a specific comment from this issue.
        \param  pId       - id of the comment you want returned (unsigned int)
        \return returns the comment based on the id (Comment*)
     */
     Comment* getComment(unsigned int pId);

     /*!
        \brief  Deletes a specific comment of this issue.
        \param  pId       - id of the comment to be deleted (unsigned int)
        \return returns a boolean:
                true      means the comment was successfully deleted (bool)
                false     means the comment was not successfully deleted
                          either because the list of comments in this issue
                          is empty or the comment does not exist (bool)
     */
     bool deleteComment(unsigned int pId);

     /*!
        \brief  Gets the issue's id
        \return returns the issues's id (unsigned int)
     */
     unsigned int getID();

 private:
     /** issue title */
     std::string title;

     /** issue id */
     unsigned int id;

     /** the user who posted or issue this issue */
     User* issuer;

     /** type of the issue */
     Type type;

     /** status of the issue */
     Status status;

     /** users assigned to this issue */
     std::vector<User*> assignees;

     /** comments added to this issue*/
     std::vector<Comment*> comments;
};


#endif // ISSUE_H_INCLUDED
