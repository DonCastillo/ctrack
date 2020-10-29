#include "User.h"
#include "gtest/gtest.h"
#include <string>

TEST(TestUser, setting_and_getting_name) {
    User* jane = new User("Jane");

    // check original name
    EXPECT_EQ(jane->getName(), "Jane");

    // change name to John
    jane->setName("John");
    EXPECT_EQ(jane->getName(), "John");

    delete jane;
}
