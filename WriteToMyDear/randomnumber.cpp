#include "randomnumber.h"

RandomNumber::RandomNumber(int start, int end)
{
    this->start = start;
    this->end   = end;
    this->basis = end - start + 1;

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}

RandomNumber::~RandomNumber()
{

}

int RandomNumber::getRandomNumber()
{
    return (qrand() % basis) + start;
}
