#include "Comment.h"
#include "User.h"
#include "gtest/gtest.h"
#include <string>

TEST(TestComment, comment_id) {
    User* jane = new User(0, "Jane");
    Comment* comment1 = new Comment(0, jane, "This is comment 1");
    Comment* comment2 = new Comment(1, jane, "This is comment 2");

    User* bob = new User(1, "Bob");
    Comment* comment3 = new Comment(2, bob, "This is comment 3");
    Comment* comment4 = new Comment(3, bob, "This is comment 4");

    EXPECT_EQ(comment1->getID(), 0);
    EXPECT_EQ(comment2->getID(), 1);
    EXPECT_EQ(comment3->getID(), 2);
    EXPECT_EQ(comment4->getID(), 3);

    delete comment1;
    delete comment2;
    delete comment3;
    delete comment4;
    delete jane;
    delete bob;
}

TEST(TestComment, setting_and_getting_comment) {
    std::string comment = "";
    User* jane = new User(0, "Jane");

    // blank comment
    comment = "";
    Comment* myComment = new Comment(0, jane, comment);
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
    User* jane = new User(0, "Jane");
    Comment* myComment = new Comment(0, jane, "sample comment");
    EXPECT_EQ(myComment->getCommenter()->getName(), "Jane");

    // change commenter to Bob
    User* bob = new User(1, "Bob");
    myComment->setCommenter(bob);
    EXPECT_EQ(myComment->getCommenter()->getName(), "Bob");

    delete myComment;
    delete jane;
    delete bob;
}
