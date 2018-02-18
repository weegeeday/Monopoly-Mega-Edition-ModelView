#include "cardspace.h"

CardSpace::CardSpace(QQueue<ActionCard*>* p_cards)
{
    m_actionCards = p_cards;
}

void CardSpace::DoAction(Player *p_player)
{
    ActionCard * card=m_actionCards->dequeue();
    emit(ActionCardDrawn(card));
}
