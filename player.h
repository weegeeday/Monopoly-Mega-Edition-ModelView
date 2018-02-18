// Made by Louis Hendrikx

#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QList>
#include <QVector>

#include "property.h"
#include "busticket.h"

class Player : public QObject
{
    Q_OBJECT
public:
    const int JAIL_LOCATION =13;
    Player(int p_playerNumber);
    /**
     * @brief GetNumber: gives the playernumber (starts with 0)
     * @return : the number of the player
     */
    int GetNumber() const;
    /**
     * @brief GetPosition: gives the position of the player (starts with 0)
     * @return : the position of the player
     */
    int GetPosition() const;
    /**
     * @brief SetPosition: sets the position of the player to a specific location
     * @param p_position: the location where the player needs to be moved
     */
    void SetPosition(int p_position);
    /**
     * @brief AddProperty: adds a property to the properties of the player
     * @param p_property: the property that needs to be added
     */
    void AddProperty(Property* p_property);
    /**
     * @brief DeleteProperty: deletes the given property in the propertylist
     * from the player
     * @param p_property: the property that nees to be removed
     */
    void DeleteProperty(Property* p_property);
    /**
     * @brief GetMoney: gives the amount of money of the player
     * @return : the amount of money
     */
    int GetMoney() const;
    /**
     * @brief GetTotalWorth: gives the total worth of the player so:
     * - money
     * - all properties with their buyprice (also the mortgaged)
     * - all the buildings on the properties
     * @return : the sum of the things above
     */
    int GetTotalWorth() const;
    /**
     * @brief GoToJail: makes the player goes in or out of the jail
     * @param p_direction: true for going in to the jail, false for going out
     */
    void GoToJail(bool p_direction);
    /**
     * @brief OwnsStreetCompletely: returns if the player owns the street
     * of a particular color completly
     * @param p_streetNumber: the Property::StreetColor which color the street is
     * @return : a bool if it is true or not
     */
    bool OwnsStreetCompletely(Property::StreetColor p_streetColor);
    /**
     * @brief OwnsStreetPartially: returns if the player owns the street
     * of a particular color partially
     * @param p_streetNumber: the Property::StreetColor which color the street is
     * @return : a bool if it is true or not
     */
    bool OwnsStreetPartially(Property::StreetColor p_streetColor);
    /**
     * @brief Pay: makes the player pays or get an amount of money
     * @param p_amount: the amount the player needs to pay
     * negative for getting money
     * @return : returns if the player had enough money
     */
    bool Pay(int p_amount);
    /**
     * @brief PayPlayer: if a player needs to pay another player
     * @param p_player: the player that needs to be payed
     * @param p_amount: the amount that needs to be payed
     * negative for getting money
     * @return : returns if the player had enough money
     */
    bool PayPlayer(Player* p_player, int p_amount);
    /**
     * @brief GetProperties: gives the list of properties the player owns
     * @return : the list of properties
     */
    QList<Property*> GetProperties();

    /**
     * @brief GetProperties: gives the list of properties the player owns with the specified street color
     * @return : the list of properties
     */
    QList<Property*> GetProperties(Property::StreetColor p_streetColor);

    /**
     * @brief GetAmountOfPropertiesOwned: gives back how many properties
     * the player owns of a specific color
     * @param p_streetColor: the color the properties needs to be
     * @return the number of properties of the specific color the player owns
     */
    int GetAmountOfPropertiesOwned(Property::StreetColor p_streetColor);
    /**
     * @brief SetThrownNumbers: sets the numbers the player just had thrown
     * @param p_die1
     * @param p_die2
     * @param p_die3
     */
    void SetThrownNumbers(int p_die1,int p_die2,int p_die3);
    /**
     * @brief GetTotalThrown: gives back the sum of what the player has thrown
     * @return : the sum of what the player has thrown with the dices
     */

    int GetTotalThrown() const;
    /**
     * @brief AddBusTicket: adds a busticket to the Players busticketlist
     * @param p_busTicket: the busticket that needs to be added
     */
    void AddBusTicket(BusTicket* p_busTicket);
    /**
     * @brief BusTicketsExpires: makes all the bustickets of the player expire
     */
    void BusTicketsExpires();
    /**
     * @brief GetNumberOfBusTickets: gives the number of bustickets
     * @return
     */
    int GetNumberOfBusTickets() const;
    /**
     * @brief IsInJail: checks if the player is in jail or not
     * @return : true if in jail, otherwhise false
     */
    bool IsInJail() const;
    /**
     * @brief AddOutOfJailCard: increases the number of outofjailcard with one
     */
    void AddOutOfJailCard();
    /**
     * @brief RepairBuildings: makes the player pay for repairing the buildings
     * @param p_priceLevel: gives the pricelevel for repairing
     */
    void RepairBuildings(int p_priceLevel);
    /**
     * @brief ComesFromCard: if the player has moved with a chance/communnitychest card
     * @return
     */
    bool ComesFromCard() const;
    /**
     * @brief SetFromCard: sets if the player comes from a chance/communitychestcard
     * @param p_value
     */
    void SetFromCard(bool p_value);
    /**
     * @brief SetBusTicketUsed: setter for using bus ticket
     */
    void SetBusTicketUsed();
    /**
     * @brief BuildHouses: makes the player build houses
     * @param p_houseNumbers: the number of houses on the street
     * @param p_streetColor: the streetcolor of the street
     */
    void BuildHouses(QList<int> p_houseNumbers, Property::StreetColor p_streetColor);

    /**
     * @brief GetNumberOfOutOfJailCards: gives the number of OOJ cards
     * @return
     */
    int GetNumberOfOutOfJailCards() const;


    /**
     * WriteToFile and ReadFromFile made by Arthur Jansen
     */
    void WriteToFile(QJsonObject& json) const;
    void ReadFromFile(const QJsonObject &json);
    /**
     * @brief Die: makes the player quit the game
     */
    void Die();
    /**
     * @brief IsAlive: chekcs if the player is still in the game
     * @return
     */
    bool IsAlive() const;

    /**
     * @brief RedistributeBuildings: Redistribute the buildings on the given street.
     *        Called when a player receives the property of a street
     * @param p_streetColor: The street where the buildings need to be redistributed
     */
    void RedistributeBuildings(Property::StreetColor p_streetColor);
    /**
     * @brief GetBuildOnStreet: checks if the player has already got buildings on the street
     * @param p_streetColor: the street color that needs to be checked
     * @return : true if there are buildings on the street
     */
    bool GetBuildOnStreet(Property::StreetColor p_streetColor);
    /**
      * @brief Checks if the given list of numbers of houses would be valid on a street
    */
    bool ValidBuildingNumbers(QList<int> p_validHouseNumbers, Property::StreetColor p_streetColor);
    /**
     * @brief GetOutOfJail: Makes the current player get out of jail if in jail
     * if the player has outOfJailCards this will be used
     * otherwhise the player pay 50
     */
    void GetOutOfJail();
signals:
    void AmountOfMoneyChanged();
    void PlayerHasPayed(Player*p_player,int p_amount);
    void PlayerDied();
    void PlayerMoved(int p_playerNumber, int p_location);
    void PlayerMustGoToJail();
private:
    /**
     * @brief AddMoney: add money to the current moneystack of the player
     * @param p_amount: the amount that needs to be added
     * negative for subtracting
     */
    void AddMoney(int p_amount);
    /**
     * @brief SetMoney: sets the money of the player to a specific value
     * @param p_amount: the money the player needs to has
     */
    void SetMoney(int p_amount);
    QList <int> m_lastThrown;
    QList <BusTicket*> m_busTickets;
    bool m_inJail=false;
    bool m_isAlive=true;
    int m_roundsInJail=0;
    bool m_comesFromCard=false;
    int m_playerNumber;
    int m_position;
    int m_money=2500;
    int m_outOfJailCards=0;
    QList <Property*> m_properties;
};

#endif // PLAYER_H
