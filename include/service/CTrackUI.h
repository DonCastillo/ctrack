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
    void welcome();
    unsigned int menu();
    bool continueUsing();
    bool choiceValid(std::string choice, unsigned int choicesSize);
    bool stringValid(std::string text);
    void sanitizeString(std::string &text);
    unsigned int choose(std::vector<std::string> choices);

    User* createUser();
   //  Issue* createIssue();
    std::string viewUser();
    std::string deleteUser();
    std::string generateUrl();
    unsigned int askForID();
    

    std::string askIssueTitle();
    std::string askIssueDescription();
    unsigned int askIssueType();
    unsigned int askIssueStatus();
    std::vector<User*> askIssueAssignees(std::vector<User*> users);
    User* askWhichUser(std::vector<User*> usersOptions);
    bool isAmongChoices(unsigned int choice, std::vector<unsigned int> choices);
    unsigned int choose(std::map<unsigned int, std::string> mapChoices);



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
