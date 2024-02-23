#include <utility>
#include <matrix.hpp>

void Construct(Matrix& out, size_t n, size_t m)
{
    out.data = new int64_t*[n];
    for (size_t i = 0; i < n; i++){
        out.data[i] = new int64_t[m];
        for (size_t j = 0; j < m; j++)
            out.data[i][j] = 0;
    }
    out.width = m;
    out.height = n;
}
void Destruct(Matrix& in)
{
    for (size_t i = 0; i < in.height; i++)
        delete[] in.data[i];
    in.height = 0;
    in.width = 0;
    delete[] in.data;
    in.data = nullptr;
}

Matrix Copy(const Matrix& matrix)
{
    Matrix m;
    Construct(m, matrix.height, matrix.width);
    for (size_t i = 0; i < matrix.height; i++)
        for (size_t j = 0; j < matrix.width; j++)
            m.data[i][j] = matrix.data[i][j];
    return m;

}
Matrix Add(const Matrix& a, const Matrix& b)
{
    Matrix res;
    if (a.height != b.height || a.width != b.width)
        return res;
    Construct(res, a.height, b.width);
    for (size_t i = 0; i < a.height; i++)
        for (size_t j = 0; j < b.height; j++)
            res.data[i][j] = a.data[i][j] + b.data[i][j];
    return res;
}
Matrix Sub(const Matrix& a, const Matrix& b)
{
    Matrix res;
    if (a.height != b.height || a.width != b.width)
        return res;
    Construct(res, a.height, b.width);
    for (size_t i = 0; i < a.height; i++)
        for (size_t j = 0; j < b.height; j++)
            res.data[i][j] = a.data[i][j] - b.data[i][j];
    return res;
}
Matrix Mult(const Matrix& a, const Matrix& b)
{
    Matrix res;
    if (a.width != b.height)
        return res;
    Construct(res, a.height, b.width);
    for (size_t i = 0; i < b.width; i++)
        for (size_t j = 0; j < a.height;j++){
            int64_t sum = 0;
            for (size_t k = 0; k < a.width; k++)
                sum += a.data[j][k] * b.data[k][i];
            res.data[j][i] = sum;
        }
                
    return res;
}

void Transpose(Matrix& matrix)
{
    Matrix m;
    Construct(m, matrix.width, matrix.height);
    for (size_t i = 0; i < matrix.height; i++)
        for (size_t j = 0; j < matrix.width; j++)
            m.data[j][i] = matrix.data[i][j];
    Destruct(matrix);
    matrix = m;
}

bool operator==(const Matrix& a, const Matrix& b)
{
    if (&a == &b)
        return true;
    if (a.height != b.height || a.width != b.width)
        return false;
    for (size_t i = 0; i < a.height; i++)
        for (size_t j = 0; j < b.height; j++)
            if (a.data[i][j] != b.data[i][j])
                return false;
    return true;
}