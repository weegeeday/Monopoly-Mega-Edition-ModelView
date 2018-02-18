#include "die.h"
#include <time.h>

Die::Die()
{
    srand(time(NULL));
}

int Die::RollDie() const
{
    return GetRandomNumber(1,6);
}


int Die::GetRandomNumber(int p_min, int p_max) const
{
    return rand() % (p_max + 1 - p_min) + p_min;
}
