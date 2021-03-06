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

TEST(TestIssue, getTypeT) {
    std::string testType;
    User* George = new User(0, "George");
    Issue* issue1 = new Issue(1, "On button turns things off", George);

    testType = issue1->getTypeT(0);
    EXPECT_EQ(testType, "feature");

    testType = issue1->getTypeT(1);
    EXPECT_EQ(testType, "bug");

    testType = issue1->getTypeT(2);
    EXPECT_EQ(testType, "task");

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
        std::cout << newUsers.at(i) << " == " << testVect.at(i) << std::endl;
        EXPECT_EQ(newUsers[i], testVect[i]);
    }
    delete George;
    delete Fred;
    delete Amy;
    delete issue1;
}

TEST(TestIssue, getStatusString) {
    std::string testIssue;
    User* George = new User(0, "George");
    Issue* issue1 = new Issue(1, "On button turns things off", George);
    issue1->setStatus(2);
    testIssue = issue1->getStatusString();
    EXPECT_EQ(testIssue, "fixed");

    issue1->setStatus(0);
    testIssue = issue1->getStatusString();
    EXPECT_EQ(testIssue, "new");

    issue1->setStatus(3);
    testIssue = issue1->getStatusString();
    EXPECT_EQ(testIssue, "won't fix");

    issue1->setStatus(1);
    testIssue = issue1->getStatusString();
    EXPECT_EQ(testIssue, "assigned");

    delete George;
    delete issue1;
}

TEST(TestIssue, getStatusInt) {
    User* George = new User(0, "George");
    Issue* issue1 = new Issue(1, "On button turns things off", George);
    issue1->setStatus(2);
    EXPECT_EQ(issue1->getStatusInt(), 2);

    issue1->setStatus(0);
    EXPECT_EQ(issue1->getStatusInt(), 0);

    issue1->setStatus(3);
    EXPECT_EQ(issue1->getStatusInt(), 3);

    issue1->setStatus(1);
    EXPECT_EQ(issue1->getStatusInt(), 1);

    delete George;
    delete issue1;
}

TEST(TestIssues, getStatusT) {
    std::string testGetStatusT;
    User* user1 = new User(0, "user1");
    Issue* issue1 = new Issue(1, "Off button doesn't turn on pc", user1);

    testGetStatusT = issue1->getStatusT(0);
    EXPECT_EQ(testGetStatusT, "new");

    testGetStatusT = issue1->getStatusT(1);
    EXPECT_EQ(testGetStatusT, "assigned");

    testGetStatusT = issue1->getStatusT(2);
    EXPECT_EQ(testGetStatusT, "fixed");

    testGetStatusT = issue1->getStatusT(3);
    EXPECT_EQ(testGetStatusT, "won't fix");

    delete user1;
    delete issue1;
}

TEST(TestIssue, getAssignee) {
    User* user1 = new User(0, "user1");
    Issue* issue1 = new Issue(0, "Are there actual cookies in my pc Cache?", user1);

    User* user2 = new User(1, "user2");
    issue1->addAssignee(user2);

    User* grabbedAssignee = nullptr;
    grabbedAssignee = issue1->getAssignee(1);

    EXPECT_EQ(grabbedAssignee->getID(), user2->getID());

    grabbedAssignee = issue1->getAssignee(4);
    EXPECT_EQ(grabbedAssignee, nullptr);

    delete user1;
    delete user2;
    delete issue1;
    delete grabbedAssignee;
}

TEST(TestIssue, deleteAssignee) {
    User* user1 = new User(0, "user1");
    User* user2 = new User(1, "user2");
    User* user3 = new User(2, "user3");
    User* user4 = new User(3, "user4");
    Issue* issue1 = new Issue(0, "Are there actual cookies in my pc Cache?", user1);

    issue1->addAssignee(user2);
    issue1->addAssignee(user3);
    issue1->addAssignee(user4);

    std::vector<User*> testAssignee;
    // Test Initial Deletion
    std::cout << "Inital users: " << std::endl;
    testAssignee = issue1->getAssignees();
    for (unsigned int i = 0; i < testAssignee.size(); i++) {
        std::cout << testAssignee.at(i)->getName() << std::endl;
    }

    EXPECT_TRUE(issue1->deleteAssignee(2));
    EXPECT_NE(issue1->getAssignee(2), user3);

    std::cout << "After Deletion" << std::endl;
    testAssignee = issue1->getAssignees();
    for (unsigned int i = 0; i < testAssignee.size(); i++) {
        std::cout << testAssignee.at(i)->getName() << std::endl;
    }

    //testing full deletion of assignees
    EXPECT_TRUE(issue1->deleteAssignee(1));
    EXPECT_TRUE(issue1->deleteAssignee(3));
    EXPECT_EQ(issue1->getStatus(), issue1->NEW);

    delete user1;
    delete user2;
    delete user3;
    delete user4;
    delete issue1;
}

TEST(TestIssue, setAndGetDescriptions) {
    std::string testVal = "Is this person serious?";
    User* user1 = new User(0, "user1");
    Issue* issue1 = new Issue(0, "Are there actual cookies in my pc Cache?", user1);

    issue1->setDescription(testVal);
    EXPECT_EQ(issue1->getDescription(), testVal);

    issue1->setDescription("cache");
    EXPECT_NE(issue1->getDescription(), testVal);

    delete user1;
    delete issue1;
}

TEST(TestIssue, addComments) {
    User* user1 = new User(0, "user1");
    User* user2 = new User(1, "user2");
    User* user3 = new User(2, "user3");
    User* user4 = new User(3, "user4");

    Comment* comment1 = new Comment(0, user1, "Hello world!");
    Comment* comment2 = new Comment(1, user2, "I bet it's chocolate chip cookies!");
    Comment* comment3 = new Comment(2, user3, "asdfsadfsa");
    Comment* comment4 = new Comment(3, user4, "cookies");

    Issue* issue1 = new Issue(0, "Are there actual cookies in my pc Cache?", user1);

    issue1->addComment(comment1);
    issue1->addComment(comment2);
    issue1->addComment(comment3);
    issue1->addComment(comment4);

    EXPECT_EQ(issue1->getComment(3)->getID(), comment4->getID());

    EXPECT_EQ(issue1->getComment(15), nullptr);

    issue1->clearComments();

    delete issue1;

    delete comment1;
    delete comment2;
    delete comment3;
    delete comment4;

    delete user1;
    delete user2;
    delete user3;
    delete user4;
}

TEST(TestIssue, clearComments) {
    User* user1 = new User(0, "user1");
    User* user2 = new User(1, "user2");
    User* user3 = new User(2, "user3");
    User* user4 = new User(3, "user4");

    Comment* comment1 = new Comment(0, user1, "Hello world!");
    Comment* comment2 = new Comment(1, user2, "I bet it's chocolate chip cookies!");
    Comment* comment3 = new Comment(2, user3, "asdfsadfsa");
    Comment* comment4 = new Comment(3, user4, "cookies");

    Issue* issue1 = new Issue(0, "Are there actual cookies in my pc Cache?", user1);

    issue1->addComment(comment1);
    issue1->addComment(comment2);
    issue1->addComment(comment3);
    issue1->addComment(comment4);

    EXPECT_EQ(issue1->getNumOfComments(), 4);
    issue1->clearComments();
    EXPECT_EQ(issue1->getNumOfComments(), 0);

    delete issue1;

    delete comment1;
    delete comment2;
    delete comment3;
    delete comment4;

    delete user1;
    delete user2;
    delete user3;
    delete user4;
}

