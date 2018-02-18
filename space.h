// Made by Arthur Jansen

#ifndef SPACE_H
#define SPACE_H

#include <QObject>

#include "player.h"
#include "actioncard.h"

class Space : public QObject
{
    Q_OBJECT
public:
    Space(QObject* parent = NULL);
    virtual void DoAction(Player* p_player)=0;
signals:
    void RentPayed(int p_amount, Property* p_property);
    void AvailablePropertyVisited(Property* p_property, bool p_propertyNeedsToGetAuctioned=false);
    void LandedOnIncomeTax();
    void LandedOnBusTicketSpace(bool p_birthdayGift);
    void ActionCardDrawn(ActionCard* p_card);
};

#endif // SPACE_H
