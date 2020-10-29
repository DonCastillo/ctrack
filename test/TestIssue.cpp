#include "Issue.h"
#include "User.h"
#include "gtest/gtest.h"
#include <string>

TEST(TestUser, setting_and_getting_title) {
    User* jane = new User("Jane");

    std::string title = "";
    title = "Search bar is working!";
    Issue* issue1 = new Issue(title, jane);

    // check original title
    EXPECT_EQ(issue1->getTitle(), title);

    // change title
    title = "Header section is small.";
    issue1->setTitle(title);
    EXPECT_EQ(issue1->getTitle(), title);

    delete issue1;
    delete jane;
}


TEST(TestUser, setting_and_getting_issuer) {
    User* jane = new User("Jane");
    User* michael = new User("Michael");
    User* dwight = new User("Dwight");

    Issue* issue1 = new Issue("Background color is too dark", jane);

    // check original issuer
    EXPECT_EQ(issue1->getIssuer()->getName(), "Jane");

    // change issuer to Michael
    issue1->setIssuer(michael);
    EXPECT_EQ(issue1->getIssuer()->getName(), "Michael");

    // change issuer to Dwight
    issue1->setIssuer(dwight);
    EXPECT_EQ(issue1->getIssuer()->getName(), "Dwight");

    delete issue1;
    delete jane;
    delete michael;
    delete dwight;
}

TEST(TestUser, setting_and_getting_type) {
    User* pam = new User("Pam");
    Issue* myIssue = new Issue("Error on line 5", pam);

    // check default type
    EXPECT_EQ(myIssue->getType(), "task");

    // change type to feature
    myIssue->setType(0);
    EXPECT_EQ(myIssue->getType(), "feature");

    // change type to bug
    myIssue->setType(1);
    EXPECT_EQ(myIssue->getType(), "bug");

    // change type to task
    myIssue->setType(2);
    EXPECT_EQ(myIssue->getType(), "task");

    myIssue->setType(999);
    EXPECT_EQ(myIssue->getType(), "task");

    delete myIssue;
    delete pam;
}


TEST(TestUser, setting_and_getting_status) {
    User* andy = new User("Andy");
    Issue* myIssue = new Issue("Error on line 5", andy);

    // check default status
    EXPECT_EQ(myIssue->getStatus(), "new");

    // change to new
    myIssue->setStatus(0);
    EXPECT_EQ(myIssue->getStatus(), "new");

    // change to assigned
    myIssue->setStatus(1);
    EXPECT_EQ(myIssue->getStatus(), "assigned");

    // change to fixed
    myIssue->setStatus(2);
    EXPECT_EQ(myIssue->getStatus(), "fixed");

    // change to won't fix
    myIssue->setStatus(3);
    EXPECT_EQ(myIssue->getStatus(), "won't fix");

    // change to new
    myIssue->setStatus(999);
    EXPECT_EQ(myIssue->getStatus(), "new");

    delete myIssue;
    delete andy;
}


