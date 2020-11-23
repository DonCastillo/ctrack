#ifndef CTRACKUI_H_INCLUDED
#define CTRACKUI_H_INCLUDED

#include <string>

class CTrackUI {
 public:
    static void println(std::string message);
    static void print(std::string message);
    static void printTitle(std::string title);
    static void printRow(std::string left, std::string right);
    static std::string formatRow(std::string left, std::string right);
    static std::string formatIDRow(unsigned int id, std::string right);
    static std::string formatStringRow(std::string left, std::string right);

 protected:
    const int LINE_WIDTH = 35;
    const char TITLE_FILL = '=';
    const char LINE_FILL = '.';
};

#endif // CTRACKUI_H_INCLUDED
