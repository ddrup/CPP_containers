#include "head_test.h"

TEST(Map, Insert_pair) {
  // Arrange
  s21::map<int, int> nik;
  // Act
  s21::pair<const int, int> n1(1, 1);
  s21::pair<const int, int> n2(1, 2);
  nik.insert(n1);
  auto Pair = nik.insert(n2);
  std::cout << (*Pair.first).second << std::endl;
  // Assert
  EXPECT_EQ(Pair.second, false);
}

TEST(Map, Insert) {
  // Arrange
  s21::map<int, int> nik;
  // Act
  nik.insert(1, 2);
  auto Pair = nik.insert(1, 3);
  std::cout << (*Pair.first).second << std::endl;
  // Assert
  EXPECT_EQ(Pair.second, false);
}

TEST(Map, Insert_or_assign) {
  // Arrange
  s21::map<int, int> nik;
  // Act
  nik.insert(1, 2);
  auto Pair = nik.insert_or_assign(1, 3);
  std::cout << (*Pair.first).second << std::endl;
  // Assert
  EXPECT_EQ(Pair.second, true);
}

TEST(Map, Iterator) {
  // Arrange
  s21::map<int, int> nik;
  // Act
  nik.AVLTree<s21::pair<const int, int>>::insert(
      s21::pair<const int, int>(1, 2));
  nik.AVLTree<s21::pair<const int, int>>::insert(
      s21::pair<const int, int>(1, 3));
  auto it = nik.begin();
  // Assert
  EXPECT_EQ((*it).second, 3);
}

TEST(Map, Contains) {
  // Arrange
  s21::map<int, int> nik;
  // Act
  nik.AVLTree<s21::pair<const int, int>>::insert(
      s21::pair<const int, int>(1, 2));
  nik.AVLTree<s21::pair<const int, int>>::insert(
      s21::pair<const int, int>(1, 5));
  if (!nik.contains(1))
    nik.AVLTree<s21::pair<const int, int>>::insert(
        s21::pair<const int, int>(1, 4));
  auto it = nik.begin();
  // Assert
  EXPECT_EQ(nik.contains(1), true);
}

TEST(Map, Erase) {
  // When deleting an element, the iterator points to an uninitialized
  // area in memory, you cannot use it after
  s21::map<int, int> nik = {{2, 4}, {3, 2}, {10, 1}, {1, 7}};
  for (auto it = nik.begin(); it != nik.end(); ++it) {
    std::cout << (*it).first << std::endl;
  }
  auto it = nik.begin();
  for (; it != nik.end();) {
    nik.erase(it);
    it = nik.begin();
  }
  EXPECT_EQ(nik.empty(), true);
}

TEST(Map, Remove) {
  AVLTree<int> nik = {2, 1, 10, 3};

  nik.Remove(1);
  nik.Remove(2);
  nik.Remove(3);
  nik.Remove(10);
  EXPECT_EQ(nik.empty(), true);
}

TEST(Map, Destructor) {
  s21::map<int, int> nik = {{2, 4}, {3, 2}, {10, 1}, {1, 7}};
  nik.clear();
  EXPECT_EQ(nik.empty(), true);
}

TEST(Map, at) {
  // Arrange
  s21::map<int, int> nik = {{2, 4}, {3, 2}, {10, 1}, {1, 7}};
  // Act
  std::cout << nik.at(1) << std::endl;
  std::cout << nik.at(10) << std::endl;
  nik.at(10) = 10;
  // Assert
  EXPECT_EQ(nik.at(1), 7);
  EXPECT_EQ(nik.at(10), 10);
}

TEST(Map, at_const) {
  // Arrange
  const s21::map<int, int> nik = {{2, 4}, {3, 2}, {10, 1}, {1, 7}};
  // Act
  std::cout << nik.at(1) << std::endl;
  std::cout << nik.at(3) << std::endl;
  // Assert
  EXPECT_EQ(nik.at(1), 7);
  EXPECT_EQ(nik.at(3), 2);
}

TEST(Map, SquareBrackets) {
  // Arrange
  s21::map<int, int> nik = {{2, 4}, {3, 2}, {10, 1}, {1, 7}};
  // Act
  std::cout << nik[1] << std::endl;
  std::cout << nik[4] << std::endl;
  // Assert
  EXPECT_EQ(nik[1], 7);
  EXPECT_EQ(nik[4], 0);
}

TEST(Map, Size_MaxSize) {
  // Arrange
  s21::map<int, int> nik = {{2, 4}, {3, 2}, {10, 1}, {1, 7}};
  // Act
  std::cout << nik.size() << std::endl;
  std::cout << nik.max_size() << std::endl;
  // Assert
  EXPECT_EQ(nik.size(), 4);
  EXPECT_EQ(nik.max_size(), 192153584101141162);
}

TEST(Map, EquallyMove) {
  // Arrange
  s21::map<int, int> nik = {{2, 4}, {3, 2}, {10, 1}, {1, 7}};
  s21::map<int, int> tmp = {{1, 2}};
  // Act
  tmp = std::move(nik);
  std::cout << tmp.size() << std::endl;
  // Assert
  EXPECT_EQ(nik.size(), 4);
}

TEST(Map, EquallyCopy) {
  // Arrange
  s21::map<int, int> nik = {{2, 4}, {3, 2}, {10, 1}, {1, 7}};
  s21::map<int, int> tmp = {{1, 2}};
  // Act
  tmp = nik;
  std::cout << tmp.size() << std::endl;
  // Assert
  EXPECT_EQ(nik.size(), 4);
}

TEST(Map, Equally1) {
  // Arrange
  AVLTree<int> nik = {2, 4, 1, 6};
  AVLTree<int> tmp = {1, 2, 6};
  std::cout << tmp.size() << std::endl;
  // Act
  tmp = nik;
  // std::cout << tmp.size() << std::endl;
  // Assert
  // EXPECT_EQ(nik.size(), 4 );
}

TEST(AVLTree, Swap) {
  // Arrange
  AVLTree<int> nik = {2, 4, 1, 6, 8};
  AVLTree<int> tmp = {1, 2, 6};
  std::cout << tmp.size() << std::endl;
  // Act
  tmp.swap(nik);
  std::cout << tmp.size() << std::endl;
  // Assert
  EXPECT_EQ(nik.size(), 3);
}

TEST(Map, Swap) {
  // Arrange
  s21::map<int, int> nik = {{2, 4}, {3, 2}, {10, 1}, {1, 7}};
  s21::map<int, int> tmp = {{1, 2}};
  tmp.insert(std::pair<const int, int>(19, 2));
  std::pair<const int, int> v = s21::pair<const int, int>(0, 4);
  // Act
  tmp.swap(nik);
  std::cout << tmp.size() << std::endl;
  std::cout << v.first << std::endl;
  // Assert
  EXPECT_EQ(nik.size(), 2);
}

TEST(Map, Merge) {
  // Arrange
  s21::map<int, int> nik = {{2, 4}, {3, 2}, {10, 1}, {1, 7}};
  s21::map<int, int> tmp = {{1, 2}};
  // Act
  tmp.merge(nik);
  std::cout << tmp.size() << std::endl;
  auto it = tmp.begin();
  // Assert
  EXPECT_EQ(nik.size(), 4);
  EXPECT_EQ((*it).second, 2);
}

TEST(Map, InsertMani) {
  // Arrange
  s21::map<int, int> nik = {{1, 2}, {4, 2}, {2, 3}};
  // Act
  nik.insert_many(std::pair<int, int>(6, 1), std::pair<int, int>(3, 1),
                  std::pair<int, int>(5, 1));
  // Assert
  int i = 1;
  for (auto it = nik.begin(); it != nik.end(); ++it, ++i) {
    std::cout << (*it).first << std::endl;
    EXPECT_EQ((*it).first, i);
  }
}