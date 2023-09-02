#include <DS/stack.h>
#include <DS/string.h>

#include <gtest/gtest.h>
#include <iostream>

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

TEST(DS, TestFunc_generate_next) {
  String s{"ababc"};
  auto next = String::generate_next(s);

  EXPECT_EQ(5, next.size());
  EXPECT_EQ(-1, next[0]);
  EXPECT_EQ(0, next[1]);
  EXPECT_EQ(0, next[2]);
  EXPECT_EQ(1, next[3]);
  EXPECT_EQ(2, next[4]);
}

TEST(DS, TestString) {
  String s1 = "hello world.";
  String s2 = s1;
  s2[1] = 'a';

  EXPECT_STREQ(s1.cstr(), "hello world.");
  EXPECT_STREQ(s2.cstr(), "hallo world.");
}

TEST(DS, TestFUNC_String_find) {
  String s1 = "AAAAAAAAB";
  String p1 = "AAB";

  EXPECT_EQ(6, s1.find(p1));

  String s2 = "playground.c/DS/src/main.cpp";
  String p2 = "source";

  EXPECT_TRUE(String::npos == s2.find(p2));
}
