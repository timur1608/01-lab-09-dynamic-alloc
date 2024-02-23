// Copyright 2023 Your Name <your@email.tld>

#ifndef INCLUDE_MATRIX_HPP_
#define INCLUDE_MATRIX_HPP_

#include <cstdint>
#include <cstddef>

struct Matrix {
  int64_t** data = nullptr;
  size_t width = 0u;
  size_t height = 0u;
};

void Construct(Matrix& out, size_t n, size_t m);
void Destruct(Matrix& in);

Matrix Copy(const Matrix& matrix);
Matrix Add(const Matrix& a, const Matrix& b);
Matrix Sub(const Matrix& a, const Matrix& b);
Matrix Mult(const Matrix& a, const Matrix& b);

void Transpose(Matrix& matrix);

bool operator==(const Matrix& a, const Matrix& b);

#endif  // INCLUDE_MATRIX_HPP_
