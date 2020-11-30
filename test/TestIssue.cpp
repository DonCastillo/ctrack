#include <string>
#include <vector>
#include "Issue.h"
#include "Comment.h"
#include "User.h"
#include "gtest/gtest.h"

/**
 * //TODO: Fix this
TEST(TestIssue, Deconstructor) {
    User* John = new User(1, "John");
    User* Henry = new User(2, "henry");
    Issue* issue1 = new Issue(0, "CPSC3720", John);
    Comment* comment1 = new Comment(4, Henry, "Added Comment");

    issue1->addComment(comment1);

    issue1->~Issue();

    EXPECT_NE(issue1->getComment(4), comment1);

    delete John;
    delete Henry;
    delete comment1;
}*/

TEST(TestIssue, setTitle) {
    User* Alex = new User(0, "Alex");
    Issue* issue1 = new Issue(1, "Cat on roof", Alex);

    std::string newTitle1 = "Cat on ground";
    issue1->setTitle(newTitle1);
    EXPECT_EQ(issue1->getTitle(), newTitle1);

    std::string newTitle2 = "Cat in box";
    issue1->setTitle(newTitle2);
    EXPECT_EQ(issue1->getTitle(), newTitle2);

    std::string newTitle3 = "asdfgjlkfdslf";
    issue1->setTitle(newTitle3);
    EXPECT_EQ(issue1->getTitle(), newTitle3);

    std::string newTitle4 = "-----123131231";
    issue1->setTitle(newTitle4);
    EXPECT_EQ(issue1->getTitle(), newTitle4);

    std::string newTitle5 = "";
    issue1->setTitle(newTitle5);
    EXPECT_EQ(issue1->getTitle(), newTitle5);

    delete Alex;
    delete issue1;
}

TEST(TestIssue, getTitle) {
    User* George = new User(0, "George");
    Issue* issue1 = new Issue(1, "On button turns things off", George);

    std::string value = issue1->getTitle();
    EXPECT_EQ(value, "On button turns things off");

    delete George;
    delete issue1;
}

TEST(TestIssue, setIssuer) {
    User* InitialIssuer = new User(4, "Micheal");
    User* UpdatedIssuer = new User(5, "Harold");
    Issue* issue1 = new Issue(1, "Title of Issue", InitialIssuer);

    EXPECT_EQ(InitialIssuer, issue1->getIssuer());

    issue1->setIssuer(UpdatedIssuer);
    EXPECT_EQ(UpdatedIssuer, issue1->getIssuer());

    delete InitialIssuer;
    delete UpdatedIssuer;
    delete issue1;
}

TEST(TestIssue, getID) {
    User* Fred = new User(3, "Fred");
    Issue* issue1 = new Issue(43, "Title of issue", Fred);

    EXPECT_EQ(issue1->getID(), 43);
    delete Fred;
    delete issue1;
}

TEST(TestIssue, setType) {
    User* George = new User(0, "George");
    Issue* issue1 = new Issue(1, "On button turns things off", George);
    //Test Issue::BUG
    issue1->setType(1);
    EXPECT_EQ(issue1->getType(), 1);
    //Test Issue::FEATURE
    issue1->setType(0);
    EXPECT_EQ(issue1->getType(), 0);
    //Test Issue::TASK, and Test default
    issue1->setType(2);
    EXPECT_EQ(issue1->getType(), 2);
    delete George;
    delete issue1;
}

TEST(TestIssue, getTypeString) {
    User* George = new User(0, "George");
    Issue* issue1 = new Issue(1, "On button turns things off", George);
    issue1->setType(0);

    std::string value = issue1->getTypeString();
    std::cout << "Feature: " << value << "\n";
    EXPECT_EQ(value, "feature");

    issue1->setType(1);
    value = issue1->getTypeString();
    EXPECT_EQ(value, "bug");

    issue1->setType(2);
    value = issue1->getTypeString();
    EXPECT_EQ(value, "task");

    delete George;
    delete issue1;
}

TEST(TestIssue, getTypeInt) {
    User* George = new User(0, "George");
    Issue* issue1 = new Issue(1, "On button turns things off", George);

    issue1->setType(0);
    EXPECT_EQ(issue1->getTypeInt(), 0);

    issue1->setType(1);
    EXPECT_EQ(issue1->getTypeInt(), 1);

    issue1->setType(2);
    EXPECT_EQ(issue1->getTypeInt(), 2);

    delete George;
    delete issue1;
}

TEST(TestIssue, setStatus) {
    User* George = new User(0, "George");
    Issue* issue1 = new Issue(1, "On button turns things off", George);
    //Status New
    issue1->setStatus(0);
    EXPECT_EQ(issue1->NEW, issue1->getStatus());

    //Status Assigned
    issue1->setStatus(1);
    EXPECT_EQ(issue1->ASSIGNED, issue1->getStatus());

    //Status Fixed
    issue1->setStatus(2);
    EXPECT_EQ(issue1->FIXED, issue1->getStatus());

    //Status Wont Fix
    issue1->setStatus(3);
    EXPECT_EQ(issue1->WONTFIX, issue1->getStatus());

    //Status New
    issue1->setStatus(4);
    EXPECT_EQ(issue1->NEW, issue1->getStatus());

    delete George;
    delete issue1;
}

TEST(TestIssue, addAssignee) {
    User* George = new User(0, "George");
    User* Fred = new User(1, "Fred");
    User* Amy = new User(2, "Amy");
    Issue* issue1 = new Issue(1, "On button turns things off", George);

    issue1->addAssignee(Fred);
    issue1->addAssignee(Amy);

    std::vector<User*> newUsers;
    newUsers.push_back(Fred);
    newUsers.push_back(Amy);
    std::vector<User*> testVect;
    testVect = issue1->getAssignees();

    for (unsigned int i = 0; i < testVect.size(); i++) {
        std::cout << newUsers[i] << " == " << testVect[i] << std::endl;
        EXPECT_EQ(newUsers[i], testVect[i]);
    }
    delete George;
    delete Fred;
    delete Amy;
    delete issue1;
}


//TEST(TestIssue, issue_id) {
//    User* jane = new User(0, "Jane");
//    Issue* issue1 = new Issue(0, "Not working properly", jane);
//    Issue* issue2 = new Issue(1, "Not really working properly", jane);
//
//    User* bob = new User(1, "Bob");
//    Issue* issue3 = new Issue(2, "Can't close the tab", bob);
//    Issue* issue4 = new Issue(3, "Can't really close the tab", bob);
//
//    EXPECT_EQ(issue1->getID(), 0);
//    EXPECT_EQ(issue2->getID(), 1);
//    EXPECT_EQ(issue3->getID(), 2);
//    EXPECT_EQ(issue4->getID(), 3);
//
//    delete issue1;
//    delete issue2;
//    delete issue3;
//    delete issue4;
//    delete jane;
//    delete bob;
//}
//
//TEST(TestIssue, setting_and_getting_title) {
//    User* jane = new User(0, "Jane");
//
//    std::string title = "";
//    title = "Search bar is working!";
//    Issue* issue1 = new Issue(0, title, jane);
//
//    // check original title
//    EXPECT_EQ(issue1->getTitle(), title);
//
//    // change title
//    title = "Header section is small.";
//    issue1->setTitle(title);
//    EXPECT_EQ(issue1->getTitle(), title);
//
//    delete issue1;
//    delete jane;
//}
//
//
//TEST(TestIssue, setting_and_getting_issuer) {
//    User* jane = new User(0, "Jane");
//    User* michael = new User(1, "Michael");
//    User* dwight = new User(2, "Dwight");
//
//    Issue* issue1 = new Issue(0, "Background color is too dark", jane);
//
//    // check original issuer
//    EXPECT_EQ(issue1->getIssuer()->getName(), "Jane");
//
//    // change issuer to Michael
//    issue1->setIssuer(michael);
//    EXPECT_EQ(issue1->getIssuer()->getName(), "Michael");
//
//    // change issuer to Dwight
//    issue1->setIssuer(dwight);
//    EXPECT_EQ(issue1->getIssuer()->getName(), "Dwight");
//
//    delete issue1;
//    delete jane;
//    delete michael;
//    delete dwight;
//}
//
//TEST(TestIssue, setting_and_getting_type) {
//    User* pam = new User(0, "Pam");
//    Issue* myIssue = new Issue(0, "Error on line 5", pam);
//
//    // check default type
//    EXPECT_EQ(myIssue->getType(), "task");
//
//    // change type to feature
//    myIssue->setType(0);
//    EXPECT_EQ(myIssue->getType(), "feature");
//
//    // change type to bug
//    myIssue->setType(1);
//    EXPECT_EQ(myIssue->getType(), "bug");
//
//    // change type to task
//    myIssue->setType(2);
//    EXPECT_EQ(myIssue->getType(), "task");
//
//    myIssue->setType(999);
//    EXPECT_EQ(myIssue->getType(), "task");
//
//    delete myIssue;
//    delete pam;
//}
//
//
//TEST(TestIssue, setting_and_getting_status) {
//    User* andy = new User(0, "Andy");
//    Issue* myIssue = new Issue(0, "Error on line 5", andy);
//
//    // check default status
//    EXPECT_EQ(myIssue->getStatus(), "new");
//
//    // change to new
//    myIssue->setStatus(0);
//    EXPECT_EQ(myIssue->getStatus(), "new");
//
//    // change to assigned
//    myIssue->setStatus(1);
//    EXPECT_EQ(myIssue->getStatus(), "assigned");
//
//    // change to fixed
//    myIssue->setStatus(2);
//    EXPECT_EQ(myIssue->getStatus(), "fixed");
//
//    // change to won't fix
//    myIssue->setStatus(3);
//    EXPECT_EQ(myIssue->getStatus(), "won't fix");
//
//    // change to new
//    myIssue->setStatus(999);
//    EXPECT_EQ(myIssue->getStatus(), "new");
//
//    delete myIssue;
//    delete andy;
//}
//
//
//TEST(TestIssue, adding_assignee) {
//    User* phyllis = new User(0, "Phyllis");
//    User* daryll = new User(1, "Daryll");
//    Issue* myIssue = new Issue(0, "Error on line 5", phyllis);
//
//    // if noone is assigned
//    EXPECT_EQ(myIssue->getAssignees().size(), 0);
//    EXPECT_EQ(myIssue->getStatus(), "new");
//
//    // assigning one user
//    myIssue->addAssignee(phyllis);
//    EXPECT_EQ(myIssue->getAssignees().size(), 1);
//    EXPECT_EQ(myIssue->getStatus(), "assigned");
//
//    // assigned more user
//    myIssue->addAssignee(daryll);
//    EXPECT_EQ(myIssue->getAssignees().size(), 2);
//    EXPECT_EQ(myIssue->getStatus(), "assigned");
//
//    delete myIssue;
//    delete phyllis;
//    delete daryll;
//}
//
//TEST(TestIssue, getting_removing_specific_assignee) {
//    User* trump = new User(0, "Trump");
//    User* biden = new User(1, "Biden");
//    User* harris = new User(2, "Harris");
//    User* pence = new User(3, "Pence");
//    User* pelosi = new User(4, "Pelosi");
//
//    Issue* zoomIssue = new Issue(0, "Cannot sign in to my account", pelosi);
//
//    // no assignee yet
//    EXPECT_EQ(zoomIssue->getType(), "task");
//    EXPECT_EQ(zoomIssue->getStatus(), "new");
//    EXPECT_EQ(zoomIssue->getAssignee(0), nullptr);
//    EXPECT_FALSE(zoomIssue->deleteAssignee(0));
//
//    // with assignees
//    zoomIssue->addAssignee(trump);
//    zoomIssue->addAssignee(biden);
//    zoomIssue->addAssignee(harris);
//    zoomIssue->addAssignee(pence);
//    EXPECT_EQ(zoomIssue->getStatus(), "assigned");
//    EXPECT_NE(zoomIssue->getAssignee(0), nullptr);
//    EXPECT_EQ(zoomIssue->getAssignee(0)->getName(), trump->getName());
//    EXPECT_FALSE(zoomIssue->deleteAssignee(4)); // pelosi isnt one of the assignees
//    EXPECT_FALSE(zoomIssue->deleteAssignee(5)); // out of range
//    EXPECT_TRUE(zoomIssue->deleteAssignee(0));
//    EXPECT_EQ(zoomIssue->getAssignee(0), nullptr);
//
//    // removed all assignees
//    zoomIssue->deleteAssignee(1);
//    zoomIssue->deleteAssignee(2);
//    zoomIssue->deleteAssignee(3);
//    EXPECT_EQ(zoomIssue->getStatus(), "new");
//    delete trump;
//    delete biden;
//    delete harris;
//    delete pence;
//    delete pelosi;
//    delete zoomIssue;
//}
//
//
//TEST(TestIssue, getting_setting_description) {
//     User* karen = new User(0, "Karen");
//     Issue* myIssue = new Issue(0, "Slow response", karen);
//     std::string desc = "";
//
//     // no description
//     EXPECT_EQ(myIssue->getDescription(), desc);
//
//     // add a description
//     desc = "This is a description";
//     myIssue->setDescription(desc);
//     EXPECT_EQ(myIssue->getDescription(), desc);
//
//     delete myIssue;
//     delete karen;
//}
//
//
//TEST(TestIssue, adding_getting_comments){
//    // declare all users
//    User* stanley = new User(0, "Stanley");
//    User* kelly = new User(1, "Kelly");
//
//    Issue* printerIssue = new Issue(0, "Printer not working!", stanley);
//
//    // no comment
//    EXPECT_EQ(printerIssue->getComments().size(), 0);
//
//    // add comments
//    std::vector<std::string> comments;
//    comments.push_back("Printer prints b&w instead of colored");
//    comments.push_back("It also jams paper");
//    comments.push_back("Seriously we need a new printer.");
//
//    std::vector<User*> commenters;
//    commenters.push_back(stanley);
//    commenters.push_back(kelly);
//    commenters.push_back(kelly);
//
//    printerIssue->addComment(new Comment(0, commenters[0], comments[0]));
//    printerIssue->addComment(new Comment(1, commenters[1], comments[1]));
//    printerIssue->addComment(new Comment(2, commenters[2], comments[2]));
//
//
//    for(int i = 0; i < printerIssue->getComments().size(); ++i) {
//        Comment* thisComment = printerIssue->getComments()[i];
//        bool isSameID = thisComment->getID() == i;
//        bool isSameCommenter = thisComment->getCommenter()->getID() == commenters[i]->getID();
//        bool isSameComments = thisComment->getComment() == comments[i];
//        EXPECT_TRUE(isSameID && isSameCommenter && isSameComments);
//    }
//
//    delete stanley;
//    delete kelly;
//    delete printerIssue;
//}
//
//
//TEST(TestIssue, getting_removing_specific_comment) {
//    User* donna = new User(0, "Donna");
//    Issue* uiError = new Issue(0, "Error in the ui", donna);
//
//    // no comment
//    // search for comment with id = 0
//    EXPECT_EQ(uiError->getComment(0), nullptr);
//    EXPECT_FALSE(uiError->deleteComment(0));
//
//    // search for comment with id = 5
//    EXPECT_EQ(uiError->getComment(5), nullptr);
//    EXPECT_FALSE(uiError->deleteComment(5));
//
//    // add a comment
//    uiError->addComment(new Comment(0, donna, "ui not mobile responsive"));
//    EXPECT_NE(uiError->getComment(0), nullptr);
//    EXPECT_EQ(uiError->getComment(0)->getID(), 0);
//    EXPECT_FALSE(uiError->deleteComment(5));
//    EXPECT_TRUE(uiError->deleteComment(0));
//    EXPECT_FALSE(uiError->deleteComment(0));
//
//    // added more commets
//    uiError->addComment(new Comment(0, donna, "ui has awful background"));
//    uiError->addComment(new Comment(1, donna, "font is bad"));
//    uiError->addComment(new Comment(2, donna, "scroll bar is invisible"));
//    EXPECT_EQ(uiError->getComment(0)->getCommenter()->getName(), donna->getName());
//    EXPECT_EQ(uiError->getComment(1)->getCommenter()->getName(), donna->getName());
//    EXPECT_FALSE(uiError->deleteComment(3));
//    EXPECT_TRUE(uiError->deleteComment(1));
//    EXPECT_EQ(uiError->getComment(1), nullptr);
//    EXPECT_EQ(uiError->getComments().size(), 2);
//
//    delete uiError;
//    delete donna;
//}
//
//TEST(TestIssue, operator_overload) {
//    User* jane = new User(0, "Jane");
//    User* john = new User(1, "John");
//    User* alice = new User(2, "Alice");
//    Comment* commentA = new Comment(0, jane, "first comment from jane");
//    Comment* commentB = new Comment(1, alice, "second comment from alice");
//    Comment* commentC = new Comment(2, alice, "another comment from alice");
//    Issue* issueA = new Issue(0, "Blue screen", jane);
//    Issue* issueB = new Issue(1, "Laptop sound is broken", alice);
//
//    // assign issues
//    issueA->addAssignee(john);
//    issueA->addComment(commentA);
//    issueA->setDescription("Here is a description");
//
//    issueB->addAssignee(john);
//    issueB->addAssignee(jane);
//    issueB->addComment(commentB);
//    issueB->addComment(commentC);
//
//    // same issues
//    EXPECT_TRUE(issueA == issueA);
//    EXPECT_FALSE(issueA != issueA);
//
//    // different issues
//    EXPECT_TRUE(issueA != issueB);
//    EXPECT_FALSE(issueA == issueB);
//
//    // cout
//    std::cout << *issueA;
//    std::cout << *issueB;
//
//    delete issueA;
//    delete issueB;
//    delete alice;
//    delete john;
//    delete jane;
//}
