#ifndef CTRACKUI_H_INCLUDED
#define CTRACKUI_H_INCLUDED

#include <string>

class CTrackUI {
 public:
    CTrackUI() {}
    virtual ~CTrackUI() {}
    void println(std::string message);
    void print(std::string message);
    void printTitle(std::string title);
    void printRow(std::string left, std::string right);
    std::string formatRow(std::string left, std::string right);
    std::string formatIDRow(unsigned int id, std::string right);
    std::string formatStringRow(std::string left, std::string right);

 protected:
    const unsigned int LINE_WIDTH = 35;
    const char TITLE_FILL = '=';
    const char LINE_FILL = '.';
};

#endif // CTRACKUI_H_INCLUDED
