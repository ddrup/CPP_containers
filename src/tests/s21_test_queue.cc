#include <queue>

#include "head_test.h"

TEST(queueTests, BaseConstructor) {
  s21::queue<int> my_queue;
  std::queue<int> std_queue;

  EXPECT_EQ(my_queue.empty(), std_queue.empty());
  EXPECT_EQ(my_queue.size(), std_queue.size());
}

TEST(queueTests, CopyConstructor) {
  s21::queue<int> my_queue({10, 23, 23});
  std::queue<int> std_queue({10, 23, 23});

  EXPECT_EQ(my_queue.size(), std_queue.size());
  while (my_queue.empty() && std_queue.empty()) {
    EXPECT_EQ(my_queue.front(), std_queue.front());
    my_queue.pop();
    std_queue.pop();
  }
}

TEST(queueTests, MoveConstructor) {
  s21::queue<int> my_queue({10, 23, 23});
  std::queue<int> std_queue({10, 23, 23});

  s21::queue<int> my_queue1(std::move(my_queue));
  std::queue<int> std_queue1(std::move(std_queue));

  EXPECT_EQ(my_queue.empty(), std_queue.empty());
  EXPECT_EQ(my_queue.size(), std_queue.size());

  EXPECT_EQ(my_queue1.size(), std_queue1.size());
  while (my_queue1.empty() && std_queue1.empty()) {
    EXPECT_EQ(my_queue1.front(), std_queue1.front());
    my_queue1.pop();
    std_queue1.pop();
  }
}

TEST(queueTests, AssignmentOperator) {
  s21::queue<int> my_queue({10, 23, 23});
  std::queue<int> std_queue({10, 23, 23});

  s21::queue<int> my_queue1({1, 1, 1});
  std::queue<int> std_queue1({1, 1, 1});

  my_queue = my_queue1;
  std_queue = std_queue1;

  EXPECT_EQ(my_queue.empty(), std_queue.empty());
  EXPECT_EQ(my_queue.size(), std_queue.size());
  while (my_queue.empty() && std_queue.empty()) {
    EXPECT_EQ(my_queue.front(), std_queue.front());
    EXPECT_EQ(my_queue.front(), my_queue1.front());
    my_queue.pop();
    std_queue.pop();
    my_queue1.pop();
  }
}

TEST(queueTests, FrontAndBack) {
  s21::queue<int> my_queue;

  EXPECT_TRUE(my_queue.empty());
  EXPECT_EQ(my_queue.size(), 0);

  my_queue.push(1);

  EXPECT_FALSE(my_queue.empty());
  EXPECT_EQ(my_queue.size(), 1);
  EXPECT_EQ(my_queue.front(), 1);

  my_queue.push(34);

  EXPECT_FALSE(my_queue.empty());
  EXPECT_EQ(my_queue.size(), 2);
  EXPECT_EQ(my_queue.back(), 34);

  my_queue.push(45);
  my_queue.push(4);
  my_queue.push(89);
  my_queue.pop();

  EXPECT_FALSE(my_queue.empty());
  EXPECT_EQ(my_queue.size(), 4);
  EXPECT_EQ(my_queue.front(), 34);
}

TEST(queueTests, Swap) {
  s21::queue<int> my_queue1;
  s21::queue<int> my_queue2;
  std::queue<int> std_queue1;
  std::queue<int> std_queue2;

  my_queue1.push(11);
  my_queue1.push(22);
  my_queue1.push(33);
  std_queue1.push(11);
  std_queue1.push(22);
  std_queue1.push(33);

  my_queue1.swap(my_queue2);
  std_queue1.swap(std_queue2);

  EXPECT_EQ(my_queue1.empty(), std_queue1.empty());
  EXPECT_EQ(my_queue1.size(), std_queue1.size());

  EXPECT_EQ(my_queue2.empty(), std_queue2.empty());
  EXPECT_EQ(my_queue2.size(), std_queue2.size());

  EXPECT_EQ(my_queue2.front(), std_queue2.front());
}

TEST(queueTests, InsertManyBack) {
  s21::queue<int> my_queue;
  my_queue.insert_many_back(1, 2, 3);
  EXPECT_EQ(my_queue.front(), 1);
  EXPECT_EQ(my_queue.back(), 3);
  EXPECT_EQ(my_queue.size(), 3);
}
