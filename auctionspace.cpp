#include "auctionspace.h"
#include "board.h"

AuctionSpace::AuctionSpace(Board* p_board)
{
    m_board=p_board;
}

void AuctionSpace::DoAction(Player *p_player)
{
    if(m_board->AllPropertiesOwned())
    {
        Property * highestRentProperty=m_board->GetHighestRentProperty(p_player);
        p_player->SetPosition(highestRentProperty->GetPosition());
        m_board->PlayerMove(p_player,highestRentProperty->GetPosition());
    }
    else // so the player can select a space
    {
        m_board->SetPlayerHasLandedOnAuctionSpace(true);
    }
}
