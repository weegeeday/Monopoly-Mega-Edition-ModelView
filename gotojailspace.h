// Made by Arthur Jansen

#ifndef GOTOJAILSPACE_H
#define GOTOJAILSPACE_H

#include "space.h"
class GoToJailSpace : public Space
{
public:
    GoToJailSpace();
    //see abstract class Space
    virtual void DoAction(Player* p_player);
};

#endif // GOTOJAILSPACE_H
