

#include "vectors.h"

Vector::Vector():
    dimension(0)
{
}

Vector::Vector(const int newDimension):
    dimension(newDimension)
{
    for (int i = 0; i < dimension; ++i)
    {
        array.push_back(0.0);
    }
}

Vector::Vector(const Vector &copyVector):
    dimension(copyVector.getDimension())
{
    for (int i = 0; i < dimension; ++i)
    {
        array.push_back(copyVector[i]);
    }
}

double Vector::operator [](const int index) const
{
    return array[index];
}

double &Vector::operator [](const int index)
{
    return array[index];
}

Vector operator +(const Vector &a, const Vector &b)
{
    int dimension = std::min(a.getDimension(), b.getDimension());
    Vector result(dimension);
    for (int i = 0; i < dimension; ++i)
    {
        result[i] = a[i] + b[i];
    }
    return result;
}

Vector operator *(const double k, const Vector &b)
{
    int dimension = b.getDimension();
    Vector result(dimension);
    for (int i = 0; i < dimension; ++i)
    {
        result[i] = k * b[i];
    }
    return result;
}

int Vector::getDimension() const
{
    return dimension;
}

Vector operator *(const Vector &b, const double k)
{
    return k * b;
}

Vector operator -(const Vector &a, const Vector &b)
{
    return a + ((-1.0) * b);
}

double operator *(const Vector &a, const Vector &b)
{
    double result = 0.0;
    int dimension = std::min(a.getDimension(), b.getDimension());
    for (int i = 0; i < dimension; ++i)
    {
        result += a[i] * b[i];
    }
    return result;
}

Vector &Vector::operator *=(const double k)
{
    *this = *this * k;
    return *this;
}

Vector &Vector::operator +=(const Vector &b)
{
    *this = *this + b;
    return *this;
}

Vector &Vector::operator -=(const Vector &b)
{
    *this = *this - b;
    return *this;
}

void _quick(vector<double> &a, int left, int right);
void Vector::sort()
{
    _quick(array, 0, dimension - 1);
}

std::ostream &operator << (std::ostream &os, const Vector &v)
{
    if (v.getDimension() == 0)
    {
        //os << "()";
        return os;
    }
    //os << "(";
    os << v[0];
    for (int i = 1; i < v.getDimension(); ++i)
    {
        os << " ";
        os << v[i];
    }
    //os << ")";
    return os;
}

void Vector::randomInit(int mod)
{
    for (int i = 0; i < dimension; ++i)
    {
        array[i] = rand() % mod;
    }
}

void Vector::initMix()
{
    for (int i = 0; i < dimension; ++i)
    {
        array[i] = i + 1;
    }
    for (int i = 0; i < dimension; ++i)
    {
        std::swap(array[rand() % dimension], array[rand() % dimension]);
    }
}

void _quick(vector<double> &a, int left, int right)
{
    double x = a[left + (rand() % (right - left + 1))];
    int i = right;
    int j = left;
    while (i >= j)
    {
        while (a[i] > x)
        {
            i--;
        }
        while (a[j] < x)
        {
            j++;
        }
        if (i >= j)
        {
            swap(a[i--], a[j++]);
        }
    }
    if (i > left)
    {
        _quick(a, left, i);
    }
    if (j < right)
    {
        _quick(a, j, right);
    }
}

