#include <stack>

#include "head_test.h"

TEST(StackTests, BaseConstructor) {
  s21::stack<int> my_stack;
  std::stack<int> std_stack;

  EXPECT_EQ(my_stack.empty(), std_stack.empty());
  EXPECT_EQ(my_stack.size(), std_stack.size());
}

TEST(StackTests, CopyConstructor) {
  s21::stack<int> my_stack({10, 23, 23});
  std::stack<int> std_stack({10, 23, 23});

  EXPECT_EQ(my_stack.size(), std_stack.size());
  while (my_stack.empty() && std_stack.empty()) {
    EXPECT_EQ(my_stack.top(), std_stack.top());
    my_stack.pop();
    std_stack.pop();
  }
}

TEST(StackTests, MoveConstructor) {
  s21::stack<int> my_stack({10, 23, 23});
  std::stack<int> std_stack({10, 23, 23});

  s21::stack<int> my_stack1(std::move(my_stack));
  std::stack<int> std_stack1(std::move(std_stack));

  EXPECT_EQ(my_stack.empty(), std_stack.empty());
  EXPECT_EQ(my_stack.size(), std_stack.size());

  EXPECT_EQ(my_stack1.size(), std_stack1.size());
  while (my_stack1.empty() && std_stack1.empty()) {
    EXPECT_EQ(my_stack1.top(), std_stack1.top());
    my_stack1.pop();
    std_stack1.pop();
  }
}

TEST(StackTests, AssignmentOperator) {
  s21::stack<int> my_stack({10, 23, 23});
  std::stack<int> std_stack({10, 23, 23});

  s21::stack<int> my_stack1({1, 1, 1});
  std::stack<int> std_stack1({1, 1, 1});

  my_stack = my_stack1;
  std_stack = std_stack1;

  EXPECT_EQ(my_stack.empty(), std_stack.empty());
  EXPECT_EQ(my_stack.size(), std_stack.size());
  while (my_stack.empty() && std_stack.empty()) {
    EXPECT_EQ(my_stack.top(), std_stack.top());
    EXPECT_EQ(my_stack.top(), my_stack1.top());
    my_stack.pop();
    std_stack.pop();
    my_stack1.pop();
  }
}

TEST(StackTests, TopAndPushAndPop) {
  s21::stack<int> my_stack;

  EXPECT_TRUE(my_stack.empty());
  EXPECT_EQ(my_stack.size(), 0);

  my_stack.push(1);

  EXPECT_FALSE(my_stack.empty());
  EXPECT_EQ(my_stack.size(), 1);
  EXPECT_EQ(my_stack.top(), 1);

  my_stack.push(34);

  EXPECT_FALSE(my_stack.empty());
  EXPECT_EQ(my_stack.size(), 2);
  EXPECT_EQ(my_stack.top(), 34);

  my_stack.push(45);
  my_stack.push(4);
  my_stack.push(89);
  my_stack.pop();

  EXPECT_FALSE(my_stack.empty());
  EXPECT_EQ(my_stack.size(), 4);
  EXPECT_EQ(my_stack.top(), 4);
}

TEST(StackTests, Swap) {
  s21::stack<int> my_stack1;
  s21::stack<int> my_stack2;
  std::stack<int> std_stack1;
  std::stack<int> std_stack2;

  my_stack1.push(11);
  my_stack1.push(22);
  my_stack1.push(33);
  std_stack1.push(11);
  std_stack1.push(22);
  std_stack1.push(33);

  my_stack1.swap(my_stack2);
  std_stack1.swap(std_stack2);

  EXPECT_EQ(my_stack1.empty(), std_stack1.empty());
  EXPECT_EQ(my_stack1.size(), std_stack1.size());

  EXPECT_EQ(my_stack2.empty(), std_stack2.empty());
  EXPECT_EQ(my_stack2.size(), std_stack2.size());

  EXPECT_EQ(my_stack2.top(), std_stack2.top());
}

TEST(StackTests, InsertManyFront) {
  s21::stack<int> my_stack;
  my_stack.insert_many_front(1, 2, 3);
  EXPECT_EQ(my_stack.top(), 3);
  EXPECT_EQ(my_stack.size(), 3);
}