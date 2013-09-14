#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "perceptron.h"
#include "vectors.h"

int checker1(const int x)
{
    return (x == 7) ? 1 : -1;
}

int checker2(const Vector &v)
{
    for (int i = 1; i < v.getDimension(); ++i)
    {
        if (v[i] < v[i - 1])
        {
            return -1;
        }
    }
    return 1;
}

void createLearningFile(const int amountLearningExamples)
{
    ofstream output;
    output.open("learn");
    output << amountLearningExamples << endl;
    const int size = 10;
    output << size << endl;
    for (int i = 0; i < amountLearningExamples; ++i)
    {
        Vector x(size);
        x.initMix();
        if (rand() % 2 == 0)
        {
            x.sort();
        }
        output << x << " " << checker2(x) << endl;
    }
    output.close();
}

void createTestFile(const int amountTests)
{
    ofstream output;
    output.open("tests");
    const int size = 10;
    output << amountTests << endl;
    output << size << endl;
    for (int i = 0; i < amountTests; ++i)
    {
        Vector x(size);
        x.initMix();
        if (rand() % 2 == 0)
        {
            x.sort();
        }
        output << x << " " << checker2(x) << endl;
    }
    output.close();
}

void learn(Perceptron &p)
{
    cout << "learning.....\n";
    ifstream input;
    input.open("learn");
    int size = 10;
    int amount = 0;
    input >> amount;
    input >> size;
    for (int i = 0; i < amount; ++i)
    {
        Vector x(11);
        for (int j = 0; j < size; ++j)
        {
            input >> x[j + 1];
        }
        int answer = 0;
        input >> answer;
        x[0] = 1;
        p.learn(x, answer);
        cout << i + 1 << ") " << x << ", " << answer << "\nw: " << p << endl;
    }
    cout << amount << " tests\n";
    cout << "w: " << p << endl;
    input.close();
}

void test(Perceptron &p)
{
    ifstream input;
    input.open("tests");
    int amount = 0;
    int size = 10;
    input >> amount;
    input >> size;
    int amountRight = 0;
    for (int i = 0; i < amount; ++i)
    {
        Vector x(11);
        for (int j = 0; j < size; ++j)
        {
            input >> x[j + 1];
        }
        int answer = 0;
        input >> answer;
        x[0] = 1;
        int result = p.ask(x);
        cout << i + 1 << ") test" << x << ", " << answer << "; result: " << result << endl;
        cout << ((result == answer) ? "\t\t\t\t\t\t...ok\n" : "\t\t\t\t\t\t...fail\n");
        if (result == answer)
        {
            amountRight++;
        }
    }
    double precent = amountRight * 100.0 / amount;
    cout << "count tests = " << amount << endl;
    cout << "count fails = " << amount - amountRight << endl;
    cout << "precent " << precent << "%" << endl;
    input.close();
}

int main()
{
    srand((unsigned)time(NULL));
    int mult = 1;
    for (int i = 0; i < 1; ++i)
    {
        mult *= 2;
        createLearningFile(100);
        createTestFile(100);
        Perceptron p(10);
        learn(p);
        test(p);
        cout << p << endl;
    }
    return 0;
}

