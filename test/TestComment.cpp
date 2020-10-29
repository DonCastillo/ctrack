#include "Comment.h"
#include "User.h"
#include "gtest/gtest.h"
#include <string>

TEST(TestComment, setting_and_getting_comment) {
    std::string comment = "";
    User* jane = new User("Jane");

    // blank comment
    comment = "";
    Comment* comment1 = new Comment(jane, comment);

    EXPECT_EQ(comment1->getComment().length(), 0);


}
