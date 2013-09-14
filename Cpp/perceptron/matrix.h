#pragma once

#include <iostream>
#include <vector>

using namespace std;

#include "vectors.h"

class Matrix
{
public:
    Matrix();
    Matrix(const int amountRow, const int amountCol);
    Matrix(const Matrix &copyMatrix);

    static bool isEqualDimensions(const Matrix &a, const Matrix &b);
    static bool isMultiable(const Matrix &a, const Matrix &b);
    bool isSquare();
    void transpose();
    double determinant();
    Matrix getMinor(const int ii, const int jj);

    Vector operator [] (int const index) const;
    Vector& operator [] (int const index);

    friend Matrix operator + (const Matrix &a, const Matrix &b);
    friend Matrix operator * (const double k, const Matrix &b);
    friend Matrix operator * (const Matrix &b, const double k);
    friend Matrix operator - (const Matrix &a, const Matrix &b);
    friend Matrix operator * (const Matrix &a, const Matrix &b);

    void randomInit();
    int getAmountRows() const;
    int getAmountCols() const;
    friend std::ostream &operator << (std::ostream &os, const Matrix &m);
private:
    int amountRows;
    int amountCols;
    vector<Vector> matrix;
    double determinant(Matrix *a);
};
