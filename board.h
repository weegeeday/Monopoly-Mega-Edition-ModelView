// Made by Arthur Jansen

#ifndef BOARD_H
#define BOARD_H

#include <player.h>
#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QQueue>
#include <QJsonArray>
#include <QJsonObject>

#include "propertyspace.h"
#include "streetproperty.h"
#include "utilityproperty.h"

#include "space.h"
#include "idlespace.h"
#include "railroad.h"
#include "taxspace.h"
#include "busticketspace.h"
#include "auctionspace.h"
#include "gotojailspace.h"
#include "cardspace.h"

class Board : public QObject
{

    Q_OBJECT

public:
    Board();
    /**
     * @brief PlayerMove: moves the player on the board
     * @param p_player: the player that needs to be moved
     * @param p_location: the location where the player needs to be moved
     */
    void PlayerMove(Player* p_player, int p_location);

    /**
     * @brief GetProperty: returns the property on a specific position
     * @param p_position: the positions where we need the property
     * @return : the property that is on the position
     */
    Property* GetProperty(int p_position);

    /**
     * @brief GetSpace: returns the space on a specific position
     * @param p_location: the location of the space we need
     * @return : the space on the location
     */
    Space* GetSpace(int p_location) const;

    /**
     * @brief GetFirstFollowingActionSpacePosition: Gives the first following Communitychest/chance
     * card space in front of the the currentlocation
     * @param p_currentLocation: the location from where we start searching
     * @return : the spacenumber of the founded space
     */
    int GetFirstFollowingActionSpacePosition(int p_currentLocation) const;
    /**
     * @brief GetFirstFollowingUnownedPropertyPosition: gives back the first following
     * unowned property in front of the given location
     * if all properties are owned, it gives back the one with the highest rentprice
     * @param p_currentLocation: the locatoin from where we start searching
     * @param p_currentPlayer: the current player, for getting the highest rent price
     * so we don't give back a space that's from the current player
     * @return
     */
    int GetFirstFollowingUnownedPropertyPosition(int p_currentLocation) const;
    /**
     * @brief AllPropertiesOwned: checks if all propeperties are owned
     * @return : true if everything is owned
     */
    bool AllPropertiesOwned()const;
    /**
     * @brief GetHighestRentProperty: gives the property where you need to pay the highest rent
     * @param p_player: so we don't take your own property
     * @return
     */
    Property* GetHighestRentProperty(Player * p_player)const;

    /**
     * @brief SetPlayerHasLandedOnAuctionSpace: setter for the bool PlayerHasLandedOnAuctionSpace
     * @param p_value
     */
    void SetPlayerHasLandedOnAuctionSpace(bool p_value);
    /**
     * @brief GetPlayerHasLandedOnAuctionSpace: getter for the bool PlayerHasLanededOnAcutionspace
     * @return
     */
    bool GetPlayerHasLandedOnAuctionSpace()const;


    int GetNumProperties() const;

    void WriteToFile(QJsonObject& json);
    void ReadFromFile(const QJsonObject& json, QList<Player*> p_players);

signals:
    void PlayerMoved(int p_playerNumber, int p_location);
private:
    /**
     * @brief LoadSpaces: loads all the space information in to the game
     */
    void LoadSpaces();

    QQueue<ActionCard*>* LoadActionCards(QString p_fileName);
    void ShuffleCards(QList<ActionCard*>* p_cards);

    QList<Property*> m_properties;
    QList<Space*> m_spaces;
    QList<int> m_actionCardSpaces; // is needed for the busticket speeddie

    QQueue<ActionCard*>* m_chanceCards;
    QQueue<ActionCard*>* m_communityCards;
    bool m_playerHasLandedOnAuctionSpace=false;

};

#endif // BOARD_H
