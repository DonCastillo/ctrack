#include "Comment.h"
#include "User.h"
#include "gtest/gtest.h"
#include <string>
#include <iostream>


TEST(TestComment, getID) {
    User* Bob = new User(0, "Bob");
    Comment* comment1 = new Comment(3, Bob, "Bobs Testing Comment");
    Comment* comment2 = new Comment(15, Bob, "Bob's second Test");
    Comment* comment3 = new Comment(4000, Bob, "Bob's second Test");
    Comment* comment4 = new Comment(12, Bob, "Bob's second Test");
    Comment* comment5 = new Comment(100, Bob, "Bob's second Test");

    EXPECT_EQ(comment1->getID(), 3);
    EXPECT_EQ(comment2->getID(), 15);
    EXPECT_EQ(comment3->getID(), 4000);
    EXPECT_EQ(comment4->getID(), 12);
    EXPECT_EQ(comment5->getID(), 100);
}