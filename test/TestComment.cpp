#include <string>
#include <iostream>
#include "Comment.h"
#include "User.h"
#include "gtest/gtest.h"

TEST(TestComment, getID) {
    User* Bob = new User(0, "Bob");
    Comment* comment1 = new Comment(3, Bob, "Bobs Testing Comment");
    Comment* comment2 = new Comment(15, Bob, "Bob's second Test");
    Comment* comment3 = new Comment(4000, Bob, "Bob's asdf Test");
    Comment* comment4 = new Comment(12, Bob, "Bob's lasdjf Test");
    Comment* comment5 = new Comment(100, Bob, "Bob's asdfwegddaf");

    EXPECT_EQ(comment1->getID(), 3);
    EXPECT_EQ(comment2->getID(), 15);
    EXPECT_EQ(comment3->getID(), 4000);
    EXPECT_EQ(comment4->getID(), 12);
    EXPECT_EQ(comment5->getID(), 100);

    delete Bob;
    delete comment1;
    delete comment2;
    delete comment3;
    delete comment4;
    delete comment5;
}

TEST(TestComment, setComment) {
    User* John = new User(1, "John");
    Comment* comment1 = new Comment(1, John, "Set Test");

    std::string newComment1 = "abc dhe eiru aldkei";
    comment1->setComment(newComment1);
    EXPECT_EQ(comment1->getComment(), newComment1);

    std::string newComment2 = "Software engineering";
    comment1->setComment(newComment2);
    EXPECT_EQ(comment1->getComment(), newComment2);

    std::string newComment3 = "Comment test";
    comment1->setComment(newComment3);
    EXPECT_EQ(comment1->getComment(), newComment3);

    std::string newComment4 = "I'm a new comment";
    comment1->setComment(newComment4);
    EXPECT_EQ(comment1->getComment(), newComment4);

    delete John;
    delete comment1;
}

//Need to redo this test.
TEST(TestComment, setCommenter) {
    User* Fred = new User(15, "Fred");
    Comment* comment1 = new Comment(10, Fred, "Testing setCommenter");
    EXPECT_EQ(comment1->getCommenter(), Fred);

    delete Fred;
    delete comment1;
}

TEST(TestComment, setID) {
    User* nUser = new User(1, "user1");
    Comment* comment1 = new Comment(10, nUser, "This comment");

    EXPECT_EQ(comment1->getID(), 10);
    comment1->setID(5);
    EXPECT_EQ(comment1->getID(), 5);

    delete nUser;
    delete comment1;
}

TEST(TestComment, setCommentator) {
    User* user1 = new User(16, "user");
    User* user2 = new User(1, "user2");
    Comment* comment1 = new Comment(5, user1, "Hello World!");

    EXPECT_EQ(user1, comment1->getCommenter());

    comment1->setCommenter(user2);

    EXPECT_EQ(user2, comment1->getCommenter());

    delete user1;
    delete user2;
    delete comment1;
}

TEST(TestComment, operator==) {
    
}
