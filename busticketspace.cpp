#include "busticketspace.h"

BusTicketSpace::BusTicketSpace()
{
}

void BusTicketSpace::DoAction(Player *p_player)
{
    //if player on birthdaygiftlocation, ask what he wants to do
    emit(LandedOnBusTicketSpace(p_player->GetPosition()==BIRTHDAYGIFT_LOCATION));
}
