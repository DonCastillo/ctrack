#include <string>
#include "User.h"
#include "gtest/gtest.h"

TEST(TestUser, getID) {
    User* Bob = new User(0, "Bob");
    User* Amy = new User(1, "Amy");

    EXPECT_EQ(Amy->getID(), 1);
    EXPECT_EQ(Bob->getID(), 0);

    delete Bob;
    delete Amy;
}

TEST(TestUser, setName) {
    User* user1 = new User(0, "user1");
    EXPECT_EQ(user1->getName(), "user1");

    user1->setName("user2");
    EXPECT_EQ(user1->getName(), "user2");

    user1->setName("user3");
    EXPECT_EQ(user1->getName(), "user3");

    user1->setName("user4");
    EXPECT_EQ(user1->getName(), "user4");

    user1->setName("user5");
    EXPECT_EQ(user1->getName(), "user5");

    delete user1;
}

TEST(TestUser, setGroup) {
    std::string testGroup;
    User* user1 = new User(0, "user1");

    user1->setGroup(0);
    testGroup = user1->getGroupString();
    EXPECT_EQ(testGroup, "developer");

    user1->setGroup(1);
    testGroup = user1->getGroupString();
    EXPECT_EQ(testGroup, "tester");

    user1->setGroup(2);
    testGroup = user1->getGroupString();
    EXPECT_EQ(testGroup, "manager");

    user1->setGroup(3);
    testGroup = user1->getGroupString();
    EXPECT_EQ(testGroup, "user");

    delete user1;
}

TEST(TestUser, getGroup) {
    std::string testGroup;
    User* user1 = new User(0, "user1");

    user1->setGroup(0);
    EXPECT_EQ(user1->getGroup(), user1->DEVELOPER);

    user1->setGroup(1);
    EXPECT_EQ(user1->getGroup(), user1->TESTER);

    user1->setGroup(2);
    EXPECT_EQ(user1->getGroup(), user1->MANAGER);

    user1->setGroup(3);
    EXPECT_EQ(user1->getGroup(), user1->USER);

    delete user1;
}

TEST(TestUser, getGroupString) {
    std::string testGroup;
    User* user1 = new User(0, "user1");

    user1->setGroup(0);
    testGroup = user1->getGroup(0);
    EXPECT_EQ(testGroup, user1->getGroupString());

    user1->setGroup(1);
    testGroup = user1->getGroup(1);
    EXPECT_EQ(testGroup, user1->getGroupString());

    user1->setGroup(2);
    testGroup = user1->getGroup(2);
    EXPECT_EQ(testGroup, user1->getGroupString());

    user1->setGroup(3);
    testGroup = user1->getGroup(3);
    EXPECT_EQ(testGroup, user1->getGroupString());

    delete user1;
}
