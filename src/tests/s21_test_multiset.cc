#include "head_test.h"

TEST(MultiSet, Insert) {
  // Arrange
  s21::multiset<int> nik;
  // Act
  nik.insert(3);
  auto it = nik.insert(3);
  std::cout << *it << std::endl;
  // Assert
  EXPECT_EQ(*it, 3);
}

TEST(MultiSet, Erase) {
  // When deleting an element, the iterator points to an uninitialized
  // area in memory, you cannot use it after
  s21::multiset<int> nik = {3, 4, 3, 7, 3, 7, 5, 2, 8, 8};
  int array_answer[10] = {2, 3, 3, 3, 4, 5, 7, 7, 8, 8};
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

TEST(MultiSet, EquallyMove) {
  // Arrange
  s21::multiset<int> nik = {3, 2, 4, 15, 7, 8};
  s21::multiset<int> tmp = {1, 2};
  // Act
  nik = std::move(tmp);
  std::cout << nik.size() << std::endl;
  // Assert
  EXPECT_EQ(nik.size(), 2);
}

TEST(MultiSet, EquallyCopy) {
  // Arrange
  s21::multiset<int> nik = {3, 2, 4, 15, 7, 8};
  s21::multiset<int> tmp = {1, 2};
  // Act
  tmp = nik;
  std::cout << tmp.size() << std::endl;
  // Assert
  EXPECT_EQ(nik.size(), 6);
}

TEST(MultiSet, Merge) {
  // Arrange
  s21::multiset<int> nik = {3, 2, 4, 15, 7, 8};
  s21::multiset<int> tmp = {1, 2};
  // Act
  tmp.merge(nik);
  std::cout << tmp.size() << std::endl;
  auto it = tmp.begin();
  // Assert
  EXPECT_EQ(nik.size(), 6);
  EXPECT_EQ(tmp.size(), 8);
  EXPECT_EQ((*it), 1);
}

TEST(MultiSet, InsertMani) {
  // Arrange
  s21::multiset<int> nik = {300, 2, 4, 15, 7, 8};
  int array_answer[12] = {1, 2, 2, 4, 4, 7, 8, 10, 15, 100, 100, 300};
  // Act
  nik.insert_many(100, 10, 1, 2, 4, 100);
  // Assert
  int i = 0;
  for (auto it = nik.begin(); it != nik.end(); ++it, ++i) {
    std::cout << (*it) << std::endl;
    EXPECT_EQ((*it), array_answer[i]);
  }
}

TEST(MultiSet, Find) {
  // Arrange
  s21::multiset<int> nik = {300, 2, 4, 15, 7, 8};
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

// size_type count(const Key& key);
// iterator lower_bound(const Key& key);
// iterator upper_bound(const Key& key);
// std::pair<iterator,iterator> equal_range(const Key& key);

TEST(MultiSet, Count) {
  // Arrange
  s21::multiset<int> nik = {300, 2, 8, 300, 300, 4, 15, 7, 8};
  // Act
  size_t it1 = nik.count(8);
  size_t it2 = nik.count(300);
  size_t it3 = nik.count(3000);
  // Assert
  EXPECT_EQ(it1, 2);
  std::cout << it1 << std::endl;
  EXPECT_EQ(it2, 3);
  std::cout << it2 << std::endl;
  EXPECT_EQ(it3, 0);
}

TEST(MultiSet, LowerBound_UpperBound) {
  // Arrange
  s21::multiset<int> nik = {300, 2, 8, 300, 300, 4, 15, 7, 8};
  // Act
  auto it1 = nik.lower_bound(300);
  auto it2 = nik.upper_bound(8);
  auto it3 = nik.upper_bound(3000);
  // Assert
  for (auto it = nik.begin(); it != nik.end(); ++it) {
    std::cout << (*it) << std::endl;
  }
  EXPECT_EQ(*it2, 15);
  it1++;
  EXPECT_EQ(*it1, 300);
  it1++;
  EXPECT_EQ(*it1, 300);
  it1++;
  if (it1 == nullptr) std::cout << "good" << std::endl;
}