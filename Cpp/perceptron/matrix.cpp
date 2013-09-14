
#include "matrix.h"

Matrix::Matrix():
    amountRows(0),
    amountCols(0)
{
}

Matrix::Matrix(const int amountRow, const int amountCol):
    amountRows(amountRow),
    amountCols(amountCol)
{
    for (int i = 0; i < amountRows; ++i)
    {
        matrix.push_back(Vector(amountCols));
    }
}

Matrix::Matrix(const Matrix &copyMatrix):
    amountRows(copyMatrix.getAmountRows()),
    amountCols(copyMatrix.getAmountCols())
{
    matrix.clear();
    for (int i = 0; i < amountRows; ++i)
    {
        matrix.push_back(Vector(amountCols));
        for (int j = 0; j < amountCols; ++j)
        {
            matrix[i][j] = copyMatrix[i][j];
        }
    }
}

bool Matrix::isEqualDimensions(const Matrix &a, const Matrix &b)
{
    return a.getAmountCols() == b.getAmountCols() && a.getAmountRows() == b.getAmountRows();
}

bool Matrix::isMultiable(const Matrix &a, const Matrix &b)
{
    return a.getAmountCols() == b.getAmountRows() && a.getAmountRows() == b.getAmountCols();
}

bool Matrix::isSquare()
{
    return amountRows == amountCols;
}

void Matrix::transpose()
{
    Matrix temp(getAmountCols(), getAmountRows());
    for (int i = 0; i < amountRows; ++i)
    {
        for (int j = 0; j < amountCols; ++j)
        {
            temp[j][i] = matrix[i][j];
        }
    }
    *this = temp;
}

double Matrix::determinant()
{
    return (isSquare()) ? determinant(this) : 0.0;
}

Matrix Matrix::getMinor(const int ii, const int jj)
{
    Matrix temp(amountRows - 1, amountCols - 1);
    for (int i = 0; i < amountRows; ++i)
    {
        for (int j = 0; j < amountCols; ++j)
        {
            if (i == ii || j == jj)
            {
                continue;
            }
            int di = (i > ii) ? 1 : 0;
            int dj = (j > jj) ? 1 : 0;
            temp[i - di][j - dj] = matrix[i][j];
        }
    }
    return temp;
}

Vector Matrix::operator [](const int index) const
{
    return matrix[index];
}

Vector &Matrix::operator [](const int index)
{
    return matrix[index];
}

void Matrix::randomInit()
{
    for (int i = 0; i < amountRows; ++i)
    {
        matrix[i].randomInit(10);
    }
}

int Matrix::getAmountRows() const
{
    return amountRows;
}

int Matrix::getAmountCols() const
{
    return amountCols;
}

std::ostream &operator <<(std::ostream &os, const Matrix &m)
{
    for (int i = 0; i < m.getAmountRows(); ++i)
    {
        os << m[i] << "\n";
    }
    return os;
}

Matrix operator +(const Matrix &a, const Matrix &b)
{
    const int aRows = a.getAmountRows();
    const int aCols = a.getAmountCols();
    const int bRows = b.getAmountRows();
    const int bCols = b.getAmountCols();
    const int tRows = std::max(aRows, bRows);
    const int tCols = std::max(aCols, bCols);
    Matrix temp(tRows, tCols);
    for (int i = 0; i < tRows; ++i)
    {
        for (int j = 0; j < tCols; ++j)
        {
            temp[i][j] = ((i < aRows && j < aCols) ? a[i][j] : 0.0) + ((i < bRows && j < bCols) ? b[i][j] : 0.0);
        }
    }
    return temp;
}

Matrix operator *(const double k, const Matrix &b)
{
    Matrix temp(b.getAmountRows(), b.getAmountCols());
    for (int i = 0; i < temp.getAmountRows(); ++i)
    {
        for (int j = 0; j < temp.getAmountCols(); ++j)
        {
            temp[i][j] = k * b[i][j];
        }
    }
    return temp;
}

Matrix operator *(const Matrix &b, const double k)
{
    return k * b;
}

Matrix operator -(const Matrix &a, const Matrix &b)
{
    return a + ((-1.0) * b);
}

Matrix operator *(const Matrix &a, const Matrix &b)
{
    const int tempDimension = std::min(a.getAmountCols(), b.getAmountRows());
    const int aRows = a.getAmountRows();
    const int bCols = b.getAmountCols();
    Matrix tempMatrix(aRows, bCols);
    for (int i = 0; i < aRows; ++i)
    {
        for (int j = 0; j < bCols; ++j)
        {
            double temp = 0.0;
            for (int k = 0; k < tempDimension; ++k)
            {
                temp += a[i][k] * b[k][j];
            }
            tempMatrix[i][j] = temp;
        }
    }
    return tempMatrix;
}

double Matrix::determinant(Matrix *a)
{
    if (a->getAmountCols() == 1)
    {
        return (*a)[0][0];
    }
    double temp = 0.0;
    Matrix minorMatrix(0, 0);
    for (int i = 0; i < a->getAmountCols(); ++i)
    {
        minorMatrix = a->getMinor(0, i);
        temp += (i % 2 == 1 ? -1.0 : 1.0) * (*a)[0][i] * determinant(&minorMatrix);
    }
    return temp;
}
