#include "head_test.h"

TEST(Set, Insert) {
  // Arrange
  s21::set<int> nik;
  // Act
  nik.insert(3);
  auto Pair = nik.insert(3);
  std::cout << *Pair.first << "   " << Pair.second << std::endl;
  // Assert
  EXPECT_EQ(*Pair.first, 3);
  EXPECT_EQ(Pair.second, false);
}

TEST(Set, Erase) {
  // When deleting an element, the iterator points to an uninitialized
  // area in memory, you cannot use it after
  s21::set<int> nik = {3, 2, 4, 15, 7, 8};
  int array_answer[6] = {2, 3, 4, 7, 8, 15};
  int i = 0;
  for (auto it = nik.begin(); it != nik.end(); ++it, ++i) {
    std::cout << *it << std::endl;
    EXPECT_EQ(*it, array_answer[i]);
  }
  auto it = nik.begin();
  for (; it != nik.end();) {
    nik.erase(it);
    it = nik.begin();
  }
  EXPECT_EQ(nik.empty(), true);
}

TEST(Set, Destructor) {
  s21::set<int> nik = {3, 2, 4, 15, 7, 8};
  nik.clear();
  EXPECT_EQ(nik.empty(), true);
}

TEST(Set, EquallyMove) {
  // Arrange
  s21::set<int> nik = {3, 2, 4, 15, 7, 8};
  s21::set<int> tmp = {1, 2};
  // Act
  nik = std::move(tmp);
  std::cout << nik.size() << std::endl;
  // Assert
  EXPECT_EQ(nik.size(), 2);
}

TEST(Set, EquallyCopy) {
  // Arrange
  s21::set<int> nik = {3, 2, 4, 15, 7, 8};
  s21::set<int> tmp = {1, 2};
  // Act
  tmp = nik;
  std::cout << tmp.size() << std::endl;
  // Assert
  EXPECT_EQ(nik.size(), 6);
}

TEST(Set, Merge) {
  // Arrange
  s21::set<int> nik = {3, 2, 4, 15, 7, 8};
  s21::set<int> tmp = {1, 2};
  // Act
  tmp.merge(nik);
  std::cout << tmp.size() << std::endl;
  auto it = tmp.begin();
  // Assert
  EXPECT_EQ(nik.size(), 6);
  EXPECT_EQ(tmp.size(), 7);
  EXPECT_EQ((*it), 1);
}

TEST(Set, InsertMani) {
  // Arrange
  s21::set<int> nik = {300, 2, 4, 15, 7, 8};
  int array_answer[9] = {1, 2, 4, 7, 8, 10, 15, 100, 300};
  // Act
  nik.insert_many(100, 10, 1, 2, 4);
  // Assert
  int i = 0;
  for (auto it = nik.begin(); it != nik.end(); ++it, ++i) {
    std::cout << (*it) << std::endl;
    EXPECT_EQ((*it), array_answer[i]);
  }
}

TEST(Set, Find) {
  // Arrange
  s21::set<int> nik = {300, 2, 4, 15, 7, 8};
  // Act
  auto it1 = nik.find(2);
  auto it2 = nik.find(300);
  auto it3 = nik.find(3000);
  // Assert
  EXPECT_EQ(*it1, 2);
  std::cout << (*it1) << std::endl;
  EXPECT_EQ(*it2, 300);
  std::cout << (*it2) << std::endl;
  EXPECT_EQ(it3--, 300);
}