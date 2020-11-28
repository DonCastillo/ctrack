#ifndef CTRACKUI_H_INCLUDED
#define CTRACKUI_H_INCLUDED

#include "../../include/service/User.h"
#include "../../include/service/Issue.h"
#include "../../include/service/Comment.h"
#include <string>
#include <vector>
#include <map>

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
                specified how s/he wants to view the users
    */
    std::string viewUser();

    /*!
       \brief   Lets the user delete a user
       \return  returns the string of url based on how the user
                specified how s/he wants to view the users
    */
    std::string deleteUser();
    unsigned int askForID();
    std::string askIssueTitle();
    std::string askIssueDescription();
    unsigned int askIssueType();
    unsigned int askIssueStatus();
    std::vector<User*> askIssueAssignees(std::vector<User*> users);
    User* askWhichUser(std::vector<User*> usersOptions);
    bool isAmongChoices(unsigned int choice, std::vector<unsigned int> choices);
    unsigned int choose(std::map<unsigned int, std::string> mapChoices);
    std::string askComment();
    std::vector<Comment*> askIssueComments(std::vector<User*> users);



    /*!
       \brief   prints text in a new line
       \param   message       - text to be printed (string)
    */
    void println(std::string message);

    /*!
       \brief   prints text in the same line
       \param   message       - text to be printed (string)
    */
    void print(std::string message);

    /*!
       \brief   prints title
       \param   title         - heading to be printed (string)
    */
    void printTitle(std::string title);

    /*!
       \brief   prints a row of text with filler characters
                in between the left and right text
       \param   left          - text to be displayed in the left side (string)
       \param   right         - text to be displayed in the right side (string)
    */
    void printRow(std::string left, std::string right);

    /*!
       \brief   formats text into a row with filler
                characters in between the left and right text
       \param   left          - text to be displayed in the left side (string)
       \param   right         - text to be displayed in the right side (string)
       \return  returns text (string) in the format:
                left-text.......................right-text
    */
    std::string formatRow(std::string left, std::string right);

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
    std::string formatIDRow(unsigned int id, std::string right);

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
    std::string formatStringRow(std::string left, std::string right);

 protected:
    /** line width */
    const unsigned int LINE_WIDTH = 40;

    /** character fillers in the title */
    const char TITLE_FILL = '=';

    /** character fillers in the line */
    const char LINE_FILL = '.';
};

#endif // CTRACKUI_H_INCLUDED
