#include "../../include/service/CTrackUI.h"
#include "../../include/service/User.h"
#include "../../include/service/Issue.h"
#include "../../include/service/Comment.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <vector>
#include <list>

void CTrackUI::welcome() {
    printTitle("C-TRACK");
    println("A text-based issue tracking system");
}


bool CTrackUI::continueUsing() {
    println("\nDo you want to continue using C-Track?");
    std::vector<std::string> choices;
    choices.push_back("No");
    choices.push_back("Yes");
    return choose(choices);
}


unsigned int CTrackUI::choose(std::vector<std::string> choices) {
    std::string choice;

    // print options
    for (int i = 0; i < choices.size(); ++i) {
        std::string index = std::to_string(i);
        printRow(index, choices.at(i));
    }

    do {
        std::cout << "Select a choice: ";
        std::getline(std::cin, choice);
    }while( !choiceValid(choice, choices.size()) );

    return std::stoul(choice, nullptr, 10);
}

unsigned int CTrackUI::menu() {
    printTitle("MENU");
    println("Enter the number of the corresponding\naction that you want to do.");
    std::vector<std::string> choices;
    choices.push_back("Create an Issue");
    choices.push_back("View an Issue");
    choices.push_back("Delete an Issue");
    choices.push_back("Edit an Issue");
    choices.push_back("Create a User");
    choices.push_back("View a User");
    choices.push_back("Delete a User");
    return choose(choices);
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


void CTrackUI::sanitizeString(std::string &text) {
  std::string newString = "";
  int startIndex = 0;
  int endIndex = text.length() - 1;

  // scan from the beginning
  for (int i = 0; i < text.length(); ++i) {
    if (text[i] == ' ') {
        continue;
    } else {
        startIndex = i;
        break;
    }
  }

  // scan from the end
  for (int i = text.length() - 1; i >= 0; --i) {
      if(text[i] == ' ') {
          continue;
      } else {
          endIndex = i;
          break;
      }
  }

  // only push non space characters
  for (int i = startIndex; i <= endIndex; ++i) {
      newString += text[i];
  }

  text = newString;
}


bool CTrackUI::stringValid(std::string text) {
    bool validA = !text.empty();
    bool validB = (text != " ") ? true : false;
    bool validC = false;
    for (int i = 0; i < text.length(); ++i) {
        if (text[i] == ' ') {
            validC = false;
        } else {
            validC = true;
            break;
        }
    }
    return  validA && validB && validC;
}


unsigned int CTrackUI::askForID() {
    std::string choice = "";
    bool isValid = false;
    do {
        print("Enter ID: ");
        std::getline(std::cin, choice);
        isValid = choiceValid(choice, 9999);
    } while(isValid == false);
    return std::stoul(choice, nullptr, 10);
}


std::string CTrackUI::viewUser() {
    println("Do you want to...");
    std::vector<std::string> choices;
    choices.push_back("View all users");
    choices.push_back("View user by ID");

    unsigned int targetChoice = choose(choices);
    std::string url = "";
    switch(targetChoice) {
        case 0:
            url = "/users";
            break;
        case 1: {
            unsigned int id = askForID();
            url = "/users/" + std::to_string(id); 
        }   break;
    }
    return url;
}

std::string CTrackUI::deleteUser() {
    println("Enter the ID of the user you want to delete.");
    unsigned int id = askForID();
    return "/users/" + std::to_string(id);
}


User* CTrackUI::createUser() {
    std::string name;
    unsigned int group;
    bool isValid;
    // ask name
    do {
        println("Enter Name: ");
        std::getline(std::cin, name);
        sanitizeString(name);
        isValid = stringValid(name);
    } while(isValid == false);

    // ask which group
    std::vector<std::string> choices;
    println("Which group?");
    choices.push_back("Developer");
    choices.push_back("Tester");
    choices.push_back("Manager");
    choices.push_back("User");

    group = choose(choices);
    User* dummyUser = new User(0, name);
    dummyUser->setGroup(group);
    return dummyUser;
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
