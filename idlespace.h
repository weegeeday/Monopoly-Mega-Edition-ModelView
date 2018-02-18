// Made by Arthur Jansen

#ifndef IDLESPACE_H
#define IDLESPACE_H

#include "space.h"

class IdleSpace : public Space
{
public:
    IdleSpace();
    //see abstract class Space
    void DoAction(Player* p_player);
};

#endif // IDLESPACE_H
