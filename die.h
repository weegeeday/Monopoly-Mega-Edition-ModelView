// Made by Louis Hendrikx

#ifndef DIE_H
#define DIE_H
#include <QtGlobal>


class Die
{
public:
    Die();
    /**
     * @brief RollDie gives an integer between 1 and 6
     * @return returns the integer the die rolled
     */
    int RollDie() const;

    /**
     * @brief GetRandomNumber gives back a random integerbetween p_min and p_max
     * @param p_min: the minimum the number can be
     * @param p_max: the maximum the number can be
     * @return returns the random integer
     */
    int GetRandomNumber(int p_min, int p_max)const;

};

#endif // DIE_H
