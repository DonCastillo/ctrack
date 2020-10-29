#include "Comment.h"
#include "User.h"
#include "gtest/gtest.h"
#include <string>

TEST(TestComment, setting_and_getting_comment) {
    std::string comment = "";
    User* jane = new User("Jane");

    // blank comment
    comment = "";
    Comment* myComment = new Comment(jane, comment);
    EXPECT_EQ(myComment->getComment().length(), 0);

    // one char comment
    comment = "x";
    myComment->setComment(comment);
    EXPECT_EQ(myComment->getComment(), comment);

    // short comment
    comment = "this is a short comment.";
    myComment->setComment(comment);
    EXPECT_EQ(myComment->getComment(), comment);

    // long comment
    comment = "this is a very long long long long comment.";
    myComment->setComment(comment);
    EXPECT_EQ(myComment->getComment(), comment);

    delete myComment;
    delete jane;
}


TEST(TestComment, setting_and_getting_commenter) {
    // jane as original commenter
    User* jane = new User("Jane");
    Comment* myComment = new Comment(jane, "sample comment");
    EXPECT_EQ(myComment->getCommenter()->getName(), "Jane");

    // change commenter to Bob
    User* bob = new User("Bob");
    myComment->setCommenter(bob);
    EXPECT_EQ(myComment->getCommenter()->getName(), "Bob");


    delete myComment;
    delete jane;
    delete bob;
}