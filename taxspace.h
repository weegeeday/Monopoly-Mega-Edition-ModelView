// Made by Arthur Jansen

#ifndef TAXSPACE_H
#define TAXSPACE_H
#include "space.h"


class TaxSpace : public Space
{
public:
    const int INCOME_TAX_LOCATION=5;
    const int RICH_TAX_LOCATION=50;
    TaxSpace();    
    //see abstract class Space
    virtual void DoAction(Player* p_player);
};

#endif // TAXSPACE_H
