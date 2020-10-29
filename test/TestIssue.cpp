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
    issue1->setTitle(title, jane);
    EXPECT_EQ(issue1->getTitle(), title);

    delete jane;
}
