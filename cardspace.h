// Made by Arthur Jansen

#ifndef CARDSPACE_H
#define CARDSPACE_H

#include <QQueue>

#include "space.h"


class CardSpace : public Space
{
public:
    CardSpace(QQueue<ActionCard*>* p_cards);
    //see abstract class Space
    virtual void DoAction(Player * p_player);
private:
    QQueue<ActionCard*>* m_actionCards;

};

#endif // CARDSPACE_H
