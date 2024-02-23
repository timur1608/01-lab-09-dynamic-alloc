// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>

#include <matrix.hpp>
#include <string.hpp>
#include <cstring>

TEST(String, CopyString)
{
    const char* p = "some string";

    char* str = CopyString(p);
    p = "hello, world!";

    ASSERT_EQ(strlen(str), 11);
    EXPECT_EQ(str[0], 's');
    EXPECT_EQ(str[1], 'o');
    EXPECT_EQ(str[2], 'm');
    EXPECT_EQ(str[3], 'e');
    EXPECT_EQ(str[4], ' ');
    EXPECT_EQ(str[5], 's');
    EXPECT_EQ(str[6], 't');
    EXPECT_EQ(str[7], 'r');
    EXPECT_EQ(str[8], 'i');
    EXPECT_EQ(str[9], 'n');
    EXPECT_EQ(str[10], 'g');
    EXPECT_EQ(str[11], 0);
    delete[] str;
}

TEST(String, ConcatenateStrings)
{
    const char* a = "hello,";
    const char* b = "world!";

    char* str = ConcatenateStrings(a, b);

    ASSERT_EQ(strlen(str), 12);
    EXPECT_EQ(str[0], 'h');
    EXPECT_EQ(str[1], 'e');
    EXPECT_EQ(str[2], 'l');
    EXPECT_EQ(str[3], 'l');
    EXPECT_EQ(str[4], 'o');
    EXPECT_EQ(str[5], ',');
    EXPECT_EQ(str[6], 'w');
    EXPECT_EQ(str[7], 'o');
    EXPECT_EQ(str[8], 'r');
    EXPECT_EQ(str[9], 'l');
    EXPECT_EQ(str[10], 'd');
    EXPECT_EQ(str[11], '!');
    EXPECT_EQ(str[12], 0);
    
    delete[] str;
}

TEST(Matrix, Construct) {
  Matrix m;
  Construct(m, 10, 10);

  EXPECT_EQ(m.width, 10);
  EXPECT_EQ(m.height, 10);

  for (size_t i = 0; i < 10; ++i) {
   for (size_t j = 0; j < 10; ++j) {
     EXPECT_EQ(m.data[i][j], 0);
   }
  }
  Destruct(m);
  EXPECT_EQ(m.data, nullptr);
  EXPECT_EQ(m.width, 0);
  EXPECT_EQ(m.height, 0);
  Destruct(m);
}

TEST(Matrix, Copy) {
  Matrix m;
  Construct(m, 2, 2);
  m.data[0][0] = 1;
  m.data[0][1] = 2;
  m.data[1][0] = 3;
  m.data[1][1] = 4;

  Matrix c = Copy(m);
  Destruct(m);

  EXPECT_EQ(c.width, 2);
  EXPECT_EQ(c.height, 2);

  EXPECT_EQ(c.data[0][0], 1);
  EXPECT_EQ(c.data[0][1], 2);
  EXPECT_EQ(c.data[1][0], 3);
  EXPECT_EQ(c.data[1][1], 4);
  Destruct(c);
}

TEST(Matrix, Transposition) {
  Matrix m;
  Construct(m, 2, 2);
  m.data[0][0] = 1;
  m.data[0][1] = 2;
  m.data[1][0] = 3;
  m.data[1][1] = 4;

  Transpose(m);
  EXPECT_EQ(m.data[0][0], 1);
  EXPECT_EQ(m.data[0][1], 3);
  EXPECT_EQ(m.data[1][0], 2);
  EXPECT_EQ(m.data[1][1], 4);

  Transpose(m);
  EXPECT_EQ(m.data[0][0], 1);
  EXPECT_EQ(m.data[0][1], 2);
  EXPECT_EQ(m.data[1][0], 3);
  EXPECT_EQ(m.data[1][1], 4);

  Destruct(m);
}

TEST(Matrix, Eq) {
  Matrix m;
  Construct(m, 2, 2);
  m.data[0][0] = 1;
  m.data[0][1] = 2;
  m.data[1][0] = 3;
  m.data[1][1] = 4;

  Matrix m2;
  Construct(m2, 2, 2);
  m2.data[0][0] = 1;
  m2.data[0][1] = 2;
  m2.data[1][0] = 3;
  m2.data[1][1] = 4;

  EXPECT_EQ(m, m2);

  Matrix c2 = Copy(m2);
  Matrix c = Copy(m);
  EXPECT_EQ(m, c2);
  EXPECT_EQ(m2, c);

  c.data[0][1] = 3;
  c.data[1][0] = 0;
  EXPECT_NE(c, m2);

  Destruct(m);
  Destruct(m2);
  Destruct(c);
  Destruct(c2);
}

TEST(Matrix, Add) {
  Matrix m;
  Construct(m, 2, 2);
  m.data[0][0] = 1;
  m.data[0][1] = 2;
  m.data[1][0] = 3;
  m.data[1][1] = 4;

  Matrix c = Copy(m);

  Matrix s = Add(m, c);
  Matrix s2 = Add(c, m);
  EXPECT_EQ(s2, s);
  Destruct(s2);
  s2 = Add(m, m);
  EXPECT_EQ(s, s2);

  ASSERT_EQ(s.width, 2);
  ASSERT_EQ(s.height, 2);
  EXPECT_EQ(s.data[0][0], 2);
  EXPECT_EQ(s.data[0][1], 4);
  EXPECT_EQ(s.data[1][0], 6);
  EXPECT_EQ(s.data[1][1], 8);

  Destruct(m);
  Destruct(c);
  Destruct(s);
  Destruct(s2);
}

TEST(Matrix, AddEmpty) {
  Matrix m;
  Construct(m, 2, 2);

  Matrix c;
  Construct(c, 3, 3);

  Matrix s = Add(m, c);

  EXPECT_EQ(s.data, nullptr);
  EXPECT_EQ(s.width, 0);
  EXPECT_EQ(s.height, 0);

  Matrix uninit;

  Destruct(s);
  s = Add(uninit, m);
  EXPECT_EQ(s.data, nullptr);
  EXPECT_EQ(s.width, 0);
  EXPECT_EQ(s.height, 0);

  s = Add(m, uninit);
  EXPECT_EQ(s.data, nullptr);
  EXPECT_EQ(s.width, 0);
  EXPECT_EQ(s.height, 0);

  Destruct(m);
  Destruct(c);
}

TEST(Matrix, Sub) {
  Matrix m;
  Construct(m, 2, 2);
  m.data[0][0] = 1;
  m.data[0][1] = 2;
  m.data[1][0] = 3;
  m.data[1][1] = 4;

  Matrix c = Copy(m);

  Matrix s = Sub(m, c);

  ASSERT_EQ(s.width, 2);
  ASSERT_EQ(s.height, 2);
  EXPECT_EQ(s.data[0][0], 0);
  EXPECT_EQ(s.data[0][1], 0);
  EXPECT_EQ(s.data[1][0], 0);
  EXPECT_EQ(s.data[1][1], 0);
  Destruct(s);

  s = Sub(c, c);
  ASSERT_EQ(s.width, 2);
  ASSERT_EQ(s.height, 2);
  EXPECT_EQ(s.data[0][0], 0);
  EXPECT_EQ(s.data[0][1], 0);
  EXPECT_EQ(s.data[1][0], 0);
  EXPECT_EQ(s.data[1][1], 0);

  Destruct(m);
  Destruct(c);
  Destruct(s);
}

TEST(Matrix, SubEmpty) {
  Matrix m;
  Construct(m, 2, 2);

  Matrix c;
  Construct(c, 3, 3);

  Matrix s = Sub(m, c);

  EXPECT_EQ(s.data, nullptr);
  EXPECT_EQ(s.width, 0);
  EXPECT_EQ(s.height, 0);

  Matrix uninit;

  Destruct(s);
  s = Sub(uninit, m);
  EXPECT_EQ(s.data, nullptr);
  EXPECT_EQ(s.width, 0);
  EXPECT_EQ(s.height, 0);

  s = Sub(m, uninit);
  EXPECT_EQ(s.data, nullptr);
  EXPECT_EQ(s.width, 0);
  EXPECT_EQ(s.height, 0);
  Destruct(m);
  Destruct(c);
}

TEST(Matrix, Mult) {
  Matrix m;
  Construct(m, 2, 3);
  
  /*
  2 0 1
  0 2 1
  */
  // first row
  m.data[0][0] = 2;
  m.data[0][1] = 0;
  m.data[0][2] = 1;

  // second row
  m.data[1][0] = 0;
  m.data[1][1] = 2;
  m.data[1][2] = 1;

  Matrix c;
  Construct(c, 3, 2);
  /*
   1 1
   0 3
  -6 2
  */
  c.data[0][0] = 1;
  c.data[0][1] = 1;
  c.data[1][0] = 0;
  c.data[1][1] = 3;
  c.data[2][0] = -6;
  c.data[2][1] = 2;

  Matrix s = Mult(m, c);

  ASSERT_EQ(s.width, 2);
  ASSERT_EQ(s.height, 2);
  /*
  -4 4
  -6 8
  */
  EXPECT_EQ(s.data[0][0], -4);
  EXPECT_EQ(s.data[0][1], 4);
  EXPECT_EQ(s.data[1][0], -6);
  EXPECT_EQ(s.data[1][1], 8);

  Destruct(m);
  Destruct(c);
  Destruct(s);
}

TEST(Matrix, MultEmpty) {
  Matrix m;
  Construct(m, 3, 2);

  Matrix c;
  Construct(c, 3, 3);

  Matrix s = Mult(m, c);

  EXPECT_EQ(s.data, nullptr);
  EXPECT_EQ(s.width, 0);
  EXPECT_EQ(s.height, 0);

  Destruct(s);
  Matrix uninit;
  s = Mult(uninit, m);
  EXPECT_EQ(s.data, nullptr);
  EXPECT_EQ(s.width, 0);
  EXPECT_EQ(s.height, 0);

  s = Mult(m, uninit);
  EXPECT_EQ(s.data, nullptr);
  EXPECT_EQ(s.width, 0);
  EXPECT_EQ(s.height, 0);

  Destruct(m);
  Destruct(c);
  Destruct(s);
}
