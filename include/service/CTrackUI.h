#ifndef CTRACKUI_H_INCLUDED
#define CTRACKUI_H_INCLUDED

#include <string>

class CTrackUI {
 public:
   void static println(std::string message);
   void static print(std::string message);
   void static printTitle(std::string title);
   void static printRow(std::string left, std::string right);
   std::string static formatRow(std::string left, std::string right);
   std::string static formatIDRow(unsigned int id, std::string right);
   std::string static formatStringRow(std::string left, std::string right); 
   static const int LINE_WIDTH = 35;
   static const char TITLE_FILL = '=';
   static const char LINE_FILL = '.';
};

#endif // CTRACKUI_H_INCLUDED
