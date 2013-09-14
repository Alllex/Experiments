#pragma once

#include <iostream>
#include <fstream>

using namespace std;

#include "vectors.h"

class Perceptron
{
public:
    Perceptron(int newDemision);
    ~Perceptron();
    void init(ifstream &input);
    void learn(const Vector &x, int answer);
    int ask(const Vector &x);

    friend std::ostream &operator << (std::ostream &os, const Perceptron &p);
private:
    static const double boundary = 0.0;
    double learningFactor;
    Vector weight;

    int sign(const double result) const;
};
