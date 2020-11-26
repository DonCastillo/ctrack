#ifndef CTRACKUI_H_INCLUDED
#define CTRACKUI_H_INCLUDED

#include <string>

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
    const unsigned int LINE_WIDTH = 35;

    /** character fillers in the title */
    const char TITLE_FILL = '=';

    /** character fillers in the line */
    const char LINE_FILL = '.';
};

#endif // CTRACKUI_H_INCLUDED
