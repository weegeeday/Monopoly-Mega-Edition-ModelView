// Made by Arthur Jansen

#ifndef SPACEVIEW_H
#define SPACEVIEW_H

#include <QGraphicsRectItem>
#include "property.h"
#include "game.h"
#include "space.h"
#include "auctiondialog.h"

class SpaceView : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    SpaceView(Space* p_space, Game* p_game, int p_position,QGraphicsItem* parent = NULL);
    int GetPosition() const;
public slots:
    /**
     * @brief RentPayed: makes a pop up with the information about the payed rent
     * @param p_amount: the amount of rent that is payed
     * @param p_property: the property where the rent is payed for
     */
    void RentPayed(int p_amount, Property* p_property);
    /**
     * @brief AvailablePropertyVisited: Provides a dialog for when a player
     * lands on a property
     * @param p_property: the property that is visited
     * @param p_propertyNeedsToGetAuctioned: if the property needs to get auctioned
     */
    void AvailablePropertyVisited(Property* p_property, bool p_propertyNeedsToGetAuctioned);
    /**
     * @brief LandedOnIncomeTax: provides a dialog that handles the incomtax
     */
    void LandedOnIncomeTax();
    /**
     * @brief LandedOnBusTicketSpace: handles the view when a player landed on a busticket
     * @param p_birthdayGift: if the was also a birthdaygift space, this needs to be true
     */
    void LandedOnBusTicketSpace(bool p_birthdayGift);
    /**
     * @brief ActionCardDrawn: gives a dialog with the message on the action card
     * @param p_card: the drawn action card
     */
    void ActionCardDrawn(ActionCard* p_card);

private:
    Game* m_game;
    Space* m_space;
    int m_position;
};

#endif // SPACEVIEW_H
