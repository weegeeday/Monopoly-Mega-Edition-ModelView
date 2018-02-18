// Made by Arthur Jansen

#ifndef BUSTICKETSPACE_H
#define BUSTICKETSPACE_H

#include "space.h"

class BusTicketSpace : public Space
{
public:
    const int BIRTHDAYGIFT_LOCATION=47;
    BusTicketSpace();
    //see abstract class Space
    virtual void DoAction(Player* p_player);
};

#endif // BUSTICKETSPACE_H
