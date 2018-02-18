// Made by Arthur Jansen

#ifndef AUCTIONSPACE_H
#define AUCTIONSPACE_H

#include "space.h"

class Board;

class AuctionSpace : public Space
{
public:
    AuctionSpace(Board* p_board);
    // see abstract class Space
    virtual void DoAction(Player* p_player);

private:
    Board* m_board;
};

#endif // AUCTIONSPACE_H
