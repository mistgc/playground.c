#include "stack.h"

#include <gtest/gtest.h>

using namespace DS;

TEST(DS, TestLinkStackWithoutHead) {
    Stack<int> *s1 = new LinkStackWithoutHead<int>();
    s1->push(1);
    s1->push(2);
    s1->push(3);

    EXPECT_EQ(s1->size(), 3);
    EXPECT_EQ(s1->peek(), 3);
    EXPECT_EQ(s1->pop(), 3);
    EXPECT_EQ(s1->pop(), 2);

    EXPECT_EQ(s1->size(), 1);

    EXPECT_EQ(s1->peek(), 1);
    EXPECT_EQ(s1->pop(), 1);

    s1->push(100);
    EXPECT_EQ(s1->pop(), 100);
    s1->push(120);
    EXPECT_EQ(s1->pop(), 120);

    EXPECT_EQ(s1->is_empty(), true);
    EXPECT_EQ(s1->size(), 0);
}
