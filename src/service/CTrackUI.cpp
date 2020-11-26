#include "../../include/service/CTrackUI.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <vector>

void CTrackUI::welcome() {
    printTitle("C-TRACK");
    println("A text-based issue tracking system");
}

bool CTrackUI::continueUsing() {
    println("Do you want to continue using C-Track?");
    printRow("0", "No");
    printRow("1", "Yes");

    bool isValid = false;
    std::string choice;
    const unsigned int NUM_OF_CHOICES = 2;


    do {
        print("Choice: ");
        std::getline(std::cin, choice);
        isValid = choiceValid(choice, NUM_OF_CHOICES);
    } while (isValid == false);

    return std::stoi(choice, nullptr, 10);
}

unsigned int CTrackUI::menu() {
    printTitle("MENU");
    println("Enter the number of the corresponding\naction that you want to do.");
    printRow("0", "Create an Issue");
    printRow("1", "View an Issue");
    printRow("2", "Delete an Issue");
    printRow("3", "Edit an Issue");
    printRow("4", "Create a User");
    printRow("5", "View a User");
    printRow("6", "Delete a User");

    bool isValid = false;
    std::string choice;
    const unsigned int NUM_OF_CHOICES = 7;

    do {
        print("Choice: ");
        std::getline(std::cin, choice);
        isValid = choiceValid(choice, NUM_OF_CHOICES);
    } while (isValid == false);

    return std::stoul(choice, nullptr, 10);
}



bool CTrackUI::choiceValid(std::string choice, unsigned int choicesSize) {
    if (choice == "")
      return false;

    // check if it's not a digit
    for (char c : choice) {
        if (!isdigit(c))
            return false;
    }

    // check if it's out of range
    unsigned int choiceTemp = std::stoul(choice, nullptr, 10);
    if (choiceTemp < 0 || choiceTemp > (choicesSize - 1))
        return false;

    return true;
}


void CTrackUI::println(std::string message) {
  std::cout << message
            << std::endl;
}

void CTrackUI::print(std::string message) {
  std::cout << message;
}

void CTrackUI::printTitle(std::string title) {
    std::cout << std::endl;
    title = " " + title;
    std::cout << std::setw(LINE_WIDTH)
              << std::setfill(TITLE_FILL)
              << title
              << std::endl;
}

void CTrackUI::printRow(std::string left, std::string right) {
  std::cout << std::setfill(LINE_FILL)
            << std::left
            << std::setw((LINE_WIDTH/2) - 2)
            << left
            << std::setfill(LINE_FILL)
            << std::right
            << std::setw((LINE_WIDTH/2) - 2)
            << right
            << std::endl;
}

std::string CTrackUI::formatRow(std::string left, std::string right) {
  std::ostringstream oss;
  oss       << std::setfill(LINE_FILL)
            << std::left
            << std::setw((LINE_WIDTH/2) - 2)
            << left
            << std::setfill(LINE_FILL)
            << std::right
            << std::setw(LINE_WIDTH)
            << right
            << std::endl;
  std::string row = oss.str();
  return row;
}

std::string CTrackUI::formatIDRow(unsigned int id, std::string right) {
  std::string row;
  std::string left = std::to_string(id);
  row = "(" + left + ") " + right;
  return row;
}

std::string CTrackUI::formatStringRow(std::string left, std::string right) {
  return "(" + left + ") " + right;
}
