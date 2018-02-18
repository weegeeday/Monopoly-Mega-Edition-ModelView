#include "gotojailspace.h"

GoToJailSpace::GoToJailSpace()
{

}

void GoToJailSpace::DoAction(Player *p_player)
{
    //TODO: update piece icon on board DONE
    p_player->GoToJail(true);
}
