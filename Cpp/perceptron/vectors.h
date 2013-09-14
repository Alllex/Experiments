#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Vector
{
public:
    Vector();
    Vector(const int newDimension);
    Vector(const Vector &copyVector);

    double operator [] (int const index) const;
    double& operator [] (int const index);

    friend Vector operator + (const Vector &a, const Vector &b);
    friend Vector operator * (const double k, const Vector &b);
    friend Vector operator * (const Vector &b, const double k);
    friend Vector operator - (const Vector &a, const Vector &b);
    friend double operator * (const Vector &a, const Vector &b);

    Vector &operator *= (const double k);
    Vector &operator += (const Vector &b);
    Vector &operator -= (const Vector &b);


    void sort();
    void randomInit(int mod);
    void initMix();
    int getDimension() const;
    friend std::ostream &operator << (std::ostream &os, const Vector &v);
private:
    int dimension;
    vector<double> array;
};
