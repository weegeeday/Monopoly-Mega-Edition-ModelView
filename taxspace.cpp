#include "taxspace.h"

TaxSpace::TaxSpace()
{

}

void TaxSpace::DoAction(Player *p_player)
{
    // income tax $200 or 10%
    if(p_player->GetPosition()==INCOME_TAX_LOCATION)
    {
        emit(LandedOnIncomeTax());
    }
    // rich tax $75
    else if(p_player->GetPosition()==RICH_TAX_LOCATION)
    {
        p_player->Pay(75);
    }
}
