#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <vector>
#include <utility>
#include <list>
#include <map>
#include <limits>
#include "../../include/service/CTrackUI.h"
#include "../../include/service/User.h"
#include "../../include/service/Issue.h"
#include "../../include/service/Comment.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*              GENERAL DISPLAY FUNCTIONS              */
/*******************************************************/
void CTrackUI::welcome() {
    printTitle("C-TRACK");
    println("A text-based issue tracking system");
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*              VALIDATION FUNCTIONS                   */
/*******************************************************/
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

bool CTrackUI::isAmongChoices(unsigned int choice, std::vector<unsigned int> choices) {
    bool isValid = false;
    for (unsigned int i : choices) {
        if (i == choice)
            isValid = true;
    }
    return isValid;
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
      if (text[i] == ' ') {
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

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*              GENERAL I/O FUNCTIONS                  */
/*******************************************************/
unsigned int CTrackUI::askForID() {
    std::string choice = "";
    bool isValid = false;
    do {
        print("Enter ID: ");
        std::getline(std::cin, choice);
        std::cin.clear();
        isValid = choiceValid(choice, 9999);
    } while (isValid == false);
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


bool CTrackUI::continueUsing() {
    println("Do you want to continue using C-Track?");
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
        std::cin.clear();
    }while( !choiceValid(choice, choices.size()) );

    return std::stoul(choice, nullptr, 10);
}


unsigned int CTrackUI::choose(std::map<unsigned int, std::string> mapChoices) {
    std::map<unsigned int, std::string>::iterator mapIt;
    std::vector<unsigned int> indexes;
    std::string choice = "";
    unsigned int choiceInt;
    bool isValid = false;

    // print options
    for (mapIt = mapChoices.begin(); mapIt != mapChoices.end(); ++mapIt) {
        indexes.push_back(mapIt->first);
        std::string first   = std::to_string(mapIt->first);
        std::string second  = mapIt->second;
        printRow(first, second);
    }

    do {
        std::cout << "Select a choice: ";
        std::getline(std::cin, choice);
        std::cin.clear();
        isValid = choiceValid(choice, 9999);
        if (isValid) {
            choiceInt = std::stoul(choice, nullptr, 10);
            isValid = isAmongChoices(choiceInt, indexes);
        }
    } while (isValid == false);

    return choiceInt;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*          ISSUE-RELATED I/O FUNCTIONS                */
/*******************************************************/
std::string CTrackUI::askIssueTitle() {
    std::string title = "";
    bool isValid = false;
    do {
        println("Enter title of the issue: ");
        std::getline(std::cin, title);
        std::cin.clear();
        sanitizeString(title);
        isValid = stringValid(title);
    } while (isValid == false);
    return title;
}

std::string CTrackUI::askIssueDescription() {
    std::string description = "";
    bool isValid = false;
    do {
        println("Enter a short description of the issue: ");
        std::getline(std::cin, description);
        std::cin.clear();
        sanitizeString(description);
        isValid = stringValid(description);
    } while (isValid == false);
    return description;
}

User* CTrackUI::askWhichUser(std::vector<User*> usersOptions) {
    std::vector<unsigned int> indexes;
    std::map<unsigned int, std::string> mapUsers;
    println("Enter the ID of the user you want to add: ");
    for (User* u : usersOptions) {
        unsigned int index = u->getID();
        std::string name   = u->getName();
        mapUsers.insert(std::pair<unsigned int, std::string>(index, name));
    }

    unsigned int choice = choose(mapUsers);

    // create dummy user
    User* dummyUser = new User(choice, mapUsers.find(choice)->second);
    return dummyUser;
}

Issue* CTrackUI::askWhichIssue(std::vector<Issue*> issueOptions) {
    std::map<unsigned int, std::string> mapIssues;

    println("Enter the ID of the issue you want to edit/delete");
    for (Issue* i : issueOptions) {
        unsigned int index = i->getID();
        std::string title = i->getTitle();
        mapIssues.insert(std::pair<unsigned int, std::string>(index, title));
    }
    unsigned int choice = choose(mapIssues);

    // create dummy issue
    Issue* dummyIssue = new Issue(choice, "", nullptr);
    return dummyIssue;
}

Comment* CTrackUI::askWhichComment(std::vector<Comment*> commentOptions) {
    std::map<unsigned int, std::string> mapComments;

    println("Enter the ID of the comment you want to edit/delete");
    for (Comment* c : commentOptions) {
        unsigned int index = c->getID();
        std::string comment = c->getComment();
        mapComments.insert(std::pair<unsigned int, std::string>(index, comment));
    }
    unsigned int choice = choose(mapComments);

    // create dummy comment
    Comment* dummyComment = new Comment(choice, nullptr, "");
    return dummyComment;
}

unsigned int CTrackUI::askWhichIssueProperty() {
    println("Which issue property to edit?");
    std::vector<std::string> choices;
    choices.push_back("Title");
    choices.push_back("Description");
    choices.push_back("Status");
    choices.push_back("Type");
    choices.push_back("Comments");
    return choose(choices);
}

unsigned int CTrackUI::updateCommentAction() {
    println("What do you want?");
    std::vector<std::string> choices;
    choices.push_back("Add a comment");
    choices.push_back("Delete a comment");
    choices.push_back("Edit a comment");
    return choose(choices);
}

std::vector<User*> CTrackUI::askIssueAssignees(std::vector<User*> users) {
    std::vector<User*> selectedUsers;
    std::vector<std::string> choices;
    choices.push_back("No");
    choices.push_back("Yes");

    println("Enter the IDs of the user(s)");
    print("you want to assign to this issue.\n");

    unsigned int choice;
    do {
        User* tempUser = askWhichUser(users);
        selectedUsers.push_back(tempUser);
        println("Add another user?: ");
        choice = choose(choices);
    } while (choice == 1);
    return selectedUsers;
}

unsigned int CTrackUI::askIssueType() {
    println("Enter the type of this issue.");
    std::vector<std::string> choices;
    choices.push_back("Feature");
    choices.push_back("Bug");
    choices.push_back("Task");
    return choose(choices);
}

unsigned int CTrackUI::askIssueStatus() {
    println("Enter the status of this issue.");
    std::vector<std::string> choices;
    choices.push_back("New");
    choices.push_back("Assigned");
    choices.push_back("Fixed");
    choices.push_back("Wont't Fixed");
    return choose(choices);
}

std::string CTrackUI::askComment() {
    std::string comment = "";
    bool isValid = false;
    do {
        println("Write a comment: ");
        std::getline(std::cin, comment);
        std::cin.clear();
        sanitizeString(comment);
        isValid = stringValid(comment);
    } while (isValid == false);
    return comment;
}

std::vector<Comment*> CTrackUI::askIssueComments(std::vector<User*> users) {
    std::vector<Comment*> comments;
    std::vector<std::string> choices;
    choices.push_back("No");
    choices.push_back("Yes");
    unsigned int choice;
    do {
        // ask the commenter
        User* dummyUser = askWhichUser(users);
        std::string comment = askComment();
        Comment* dummyComment = new Comment(0, dummyUser, comment);
        comments.push_back(dummyComment);
        println("Add more comment?");
        choice = choose(choices);
    } while (choice == 1);
    return comments;
}


bool CTrackUI::continueAddingComment() {
    println("Do you want to continue updating comment?");
    std::vector<std::string> choices;
    choices.push_back("No");
    choices.push_back("Yes");
    return choose(choices);
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*          USER-RELATED I/O FUNCTIONS                 */
/*******************************************************/
User* CTrackUI::createUser() {
    std::string name;
    unsigned int group;
    bool isValid;
    // ask name
    do {
        println("Enter Name: ");
        std::getline(std::cin, name);
        std::cin.clear();
        sanitizeString(name);
        isValid = stringValid(name);
    } while (isValid == false);

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


std::string CTrackUI::deleteUser() {
    println("Enter the ID of the user you want to delete.");
    unsigned int id = askForID();
    return "/users/" + std::to_string(id);
}


std::string CTrackUI::viewUser() {
    println("Do you want to...");
    std::vector<std::string> choices;
    choices.push_back("View all users");
    choices.push_back("View user by ID");

    unsigned int targetChoice = choose(choices);
    std::string url = "";
    switch (targetChoice) {
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


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                   UI FORMATS                        */
/*******************************************************/
void CTrackUI::println(std::string message) {
  std::cout << std::endl
            << message
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
