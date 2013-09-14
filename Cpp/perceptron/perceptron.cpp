#include "perceptron.h"

Perceptron::Perceptron(int newDemision):
    learningFactor(1e-3)
{
    Vector temp(newDemision + 1);
    temp[0] = boundary;
    weight = temp;
}

Perceptron::~Perceptron()
{
//    ofstream output;
//    output.open("init");
//    for (int i = 1; i < weight.getDimension(); ++i)
//    {
//        output << weight[i] << " ";
//    }
//    output.close();
}

void Perceptron::init(ifstream &input)
{
    for (int i = 1; i < weight.getDimension(); ++i)
    {
        input >> weight[i];
    }
}

void Perceptron::learn(const Vector &x, int answer)
{
    int result = sign(weight * x);
    for (int i = 0; i < weight.getDimension(); ++i)
    {
        weight[i] += learningFactor * x[i] * (answer - result);
    }
    weight[0] = boundary;
}

int Perceptron::ask(const Vector &x)
{
    return sign(weight * x);
}

ostream &operator <<(ostream &os, const Perceptron &p)
{
    os << p.weight;
    return os;
}

int Perceptron::sign(const double result) const
{
    return (result > 0) ? 1 : -1;
}
