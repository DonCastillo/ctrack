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


//TEST(TestComment, setting_and_getting_commenter) {
//    // jane as original commenter
//    User* jane = new User("Jane");
//    Comment* myComment = new Comment(jane, "sample comment");
//    EXPECT_EQ(myComment->getCommenter()->getName(), "Jane");
//
//    // change commenter to Bob
//    User* bob = new User("Bob");
//    myComment->setCommenter(bob);
//    EXPECT_EQ(myComment->getCommenter()->getName(), "Bob");
//
//    delete myComment;
//    delete jane;
//    delete bob;
//}
