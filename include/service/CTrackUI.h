#ifndef CTRACKUI_H_INCLUDED
#define CTRACKUI_H_INCLUDED
#include <string>
#include <vector>
#include <map>
#include "../../include/service/User.h"
#include "../../include/service/Issue.h"
#include "../../include/service/Comment.h"

/** UI class */
class CTrackUI {
 public:
   /*!
      \brief    Constructor
   */
    CTrackUI() {}

    /*!
       \brief   Destructor
    */
    virtual ~CTrackUI() {}

    /*!
       \brief   Prints the welcome message of the program
    */
    void welcome();

    /*!
       \brief   Displays the main menu of the program
                and asks user to enter what action to do
                with the program
       \return  returns the choice of action based on the
                integer entered (unsigned int)
    */
    unsigned int menu();

    /*!
       \brief   Asks the user whether to continue using the
                program or not
       \return  true to continue, otherwise false (bool)
    */
    bool continueUsing();

    /*!
       \brief   Checks if the integer entered is valid, meaning it
                is within the range of values from 0 through maximum
                integer specified.
       \param   choice        - integer entered in the cin (string)
       \param   choicesSize   - maximum integer (unsigned int)
       \return  true if it is valid, otherwise false
    */
    bool choiceValid(std::string choice, unsigned int choicesSize);

    /*!
       \brief   Checks if the string passed is valid, meaning it
                is not blank and it does not contain only spaces
       \param   text          - string to check (string)
       \return  true if valid, otherwise false
    */
    bool stringValid(std::string text);

    /*!
       \brief   Removes any leading and trailing spaces in the string
       \param   text          - string to process (string)
    */
    void sanitizeString(std::string &text);

    /*!
       \brief   Lets the user choose among the choices
       \param   choices       - collection of string that will serve
                                as the choices (vector<string>)
       \return the integer that is entered by the user that represents
               the choice (unsigned int)
    */
    unsigned int choose(std::vector<std::string> choices);

    /*!
       \brief   Creates a user based on the values entered by the
                user in the terminal
       \return  User object (User*)
    */
    User* createUser();

    /*!
       \brief   Lets the user view users
       \return  returns the string of url based on how the user
                specified how s/he wants to view the users (string)
    */
    std::string viewUser();

    /*!
       \brief   Lets the user delete a user
       \return  returns the string of url based on
                id of the user to be deleted
    */
    //std::string deleteUser();

    /*!
       \brief   Asks the user to enter an ID
       \return  returns the ID entered (unsigned int)
    */
    unsigned int askForID();

    /*!
       \brief  Asks the user to enter the issue title
       \return issue title (string)
    */
    std::string askIssueTitle();

    /*!
       \brief  Asks the user to enter the issue description
       \return issue description (string)
    */
    std::string askIssueDescription();

    /*!
       \brief  Asks the user to enter the issue type
       \return issue type (unsigned int)
    */
    unsigned int askIssueType();

    /*!
       \brief  Asks the user to enter the issue status
       \return issue status (unsigned int)
    */
    unsigned int askIssueStatus();

    /*!
       \brief  Asks the user to enter user objects to be
               assigned to the issue
       \param  users      - vector of users to be b chosen from
       \return returns the vector of users assigned to the issue
    */
    std::vector<User*> askIssueAssignees(const std::vector<User*>& users);

    /*!
       \brief  Asks the user to choose a user from the list
               of users presented
       \param  usersOptions   - list of users as options
       \return returns a user selected (User*)
    */
    User* askWhichUser(std::vector<User*> usersOptions);

    /*!
       \brief   Checks if the user's choice is among the valid choices
       \param   choice    - user's choice (unsigned int)
       \param   choices   - valid choices
       \return  true if the choice is among the valid choices,
                otherwise false
    */
    bool isAmongChoices(unsigned int choice, std::vector<unsigned int> choices);

    /*!
       \brief  Asks the user to choose between the choices
       \param  mapChoices   - choices to choose from
       \return returns the ID or integer of choice (unsigned int)
    */
    unsigned int choose(std::map<unsigned int, std::string> mapChoices);

    /*!
       \brief  Asks the user to provide a comment to an issue
       \return returns a comment (string)
    */
    std::string askComment();

    /*!
       \brief  Asks the user to add a comment to an issue
       \param  users      - vector of users to choose from
                            to be assigned as a commenter
       \return vector of comments to be added to an issue
    */
    std::vector<Comment*> askIssueComments(const std::vector<User*>& users);

    /*!
       \brief  Asks the user to choose an issue from the list of issues
       \param  issueOptions   - list of issues to choose from
       \return chosen Issue object (Issue)
    */
    Issue* askWhichIssue(std::vector<Issue*> issueOptions);

    /*!
       \brief   Asks the user which property of the Issue to edit/update
       \return  Chosen propery as indicated by its integer representation
    */
    unsigned int askWhichIssueProperty();

    /*!
       \brief  Asks the user what kind of update he wants to a comment
       \return Chosen action as indicated by its integer representation
    */
    unsigned int updateCommentAction();

    /*!
       \brief Asks the user if he wants to continue adding a comment
       \return true if he wants to continue, otherwise false
    */
    bool continueAddingComment();

    /*!
       \brief Asks the user to choose which comment to edit/delete
       \return chosen comment
    */
    Comment* askWhichComment(std::vector<Comment*> commentOptions);

    /*!
       \brief Lets the user view the issues
       \return string url of the issue to be viewed
    */
    std::string viewIssue();


    /*!
       \brief   prints text in a new line
       \param   message       - text to be printed (string)
    */
    void println(const std::string& message);

    /*!
       \brief   prints text in the same line
       \param   message       - text to be printed (string)
    */
    void print(const std::string& message);

    /*!
       \brief   prints title
       \param   title         - heading to be printed (string)
    */
    void printTitle(const std::string& title);

    /*!
       \brief   prints a row of text with filler characters
                in between the left and right text
       \param   left          - text to be displayed in the left side (string)
       \param   right         - text to be displayed in the right side (string)
    */
    void printRow(const std::string& left, const std::string& right);

    /*!
       \brief   formats text into a row with filler
                characters in between the left and right text
       \param   left          - text to be displayed in the left side (string)
       \param   right         - text to be displayed in the right side (string)
       \return  returns text (string) in the format:
                left-text.......................right-text
    */
    std::string formatRow(const std::string& left, const std::string& right);

    /*!
       \brief   formats text with number in the left side and string
                in the right side
       \param   id            - text to be displayed in the left side
                                (unsigned int)
       \param   right         - text to be displayed in the right side
                                (string)
       \return returns text (string) in the format:
               (id) right-text
    */
    std::string formatIDRow(unsigned int id, const std::string& right);

    /*!
       \brief   formats text with a string in the left side and string
                in the right side
       \param   left          - text to be displayed in the left side
                                (string)
       \param   right         - text to be displayed in the right side
                                (string)
       \return returns text (string) in the format:
               (left-text) right-text
    */
    //std::string formatStringRow(std::string left, std::string right);

 protected:
    /** line width */
    const unsigned int LINE_WIDTH = 40;

    /** character fillers in the title */
    const char TITLE_FILL = '=';

    /** character fillers in the line */
    const char LINE_FILL = '.';
};

#endif // CTRACKUI_H_INCLUDED
