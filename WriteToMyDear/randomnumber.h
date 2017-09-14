#ifndef RANDOMNUMBER_H
#define RANDOMNUMBER_H

#include <QTime>

class RandomNumber
{
public:
    RandomNumber(int start, int end);
    ~RandomNumber();
    int getRandomNumber();

private:
    int start;
    int end;
    int basis;
};

#endif // RANDOMNUMBER_H
