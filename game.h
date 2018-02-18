// Made by Arthur Jansen

#ifndef GAME_H
#define GAME_H
#include <QList>
#include <QObject>
#include <QQueue>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

#include "player.h"
#include "board.h"
#include "die.h"

class ActionCard;


class Game : public QObject
{
    Q_OBJECT
public:
    const int MAX_NUMBER_PLAYERS=8;
    const int NUMBER_OF_SPACES=52;
    const int NUMBER_OF_BUSTICKETS=16;
    const int RIGHT_LOW_CORNER=53; // we see the first corner as the last so number of spaces +1
    const int LEFT_LOW_CORNER=13;
    const int LEFT_UP_CORNER=26;
    const int RIGHT_UP_CORNER=39;
    Game();
    ~Game();
    /**
     * @brief InitializePlayers: initialize the players in the game
     * @param p_numberOfPlayers: the number of players that are going to be in the game
     */
    void InitializePlayers(int p_numberOfPlayers);
    /**
     * @brief InitializeBusTickets: initializes the bustickets
     */
    void InitializeBusTickets();
    /**
     * @brief GetPlayers: gives back the list of players in the game
     * @return : the playerlist
     */
    const QList<Player*> &GetPlayers() const;
    /**
     * @brief GetBoard: gives the board *
     * @return : the board *
     */
    Board* GetBoard() const;
    /**
     * @brief RollDice: this functions handles the Dices to roll
     * and redirect the needed actions
     */
    void RollDice();
    /**
     * @brief MoveCurrentPlayer: moves the current player some steps forward
     * @param p_steps: the number of steps the players needs to go forward
     */
    void MoveCurrentPlayer(int p_steps);

    /**
     * @brief MoveCurrentPlayerTo: moves the current playerr to a location
     * @param p_location: the location where the players needs to be moved
     */
    void MoveCurrentPlayerTo(int p_location);

    /**
     * @brief BuyProperty: handles the buying of a property
     * @param p_property: the property that need to be bought
     */   
    void BuyProperty(Property* p_property);
    /**
     * @brief BuyPropertyToPlayer: if the property is bought by an other player than the current player
     * @param p_property: the property that need to be bought
     * @param p_price: the price for what the property is bought
     * @param p_toPlayer: the player that has bought the property
     * @param p_fromPlayer: isn't necessary, if nothing filled in it is bought from bank
     * if you give a number, than this player has selled the property
     */
    void BuyPropertyToPlayer(Property* p_property,int p_price, int p_toPlayer, int p_fromPlayer=0);
    /**
     * @brief PayIncomeTaxFixed: handles the paying of income tax if fixed value
     */
    void PayIncomeTaxFixed();
    /**
     * @brief PayIncomeTaxDynamic: handles the paying of income tax if it is
     * the dynamic value, so if the player has chosen the 10%
     */
    void PayIncomeTaxDynamic();
    /**
     * @brief GetBirthdayGift: the player gets $100 for his birthday
     */
    void GetBirthdayGift();
    /**
     * @brief GetBusTicket: handles the busticket logic of the game
     */
    bool GetBusTicket();
    /**
     * @brief AllBusTicketsExpires: makes all the current bustickets
     * from all the players expired
     */
    void AllBusTicketsExpires();

    /**
     * @brief MakeTripleMove: handles the triplemovement of the player
     * @param p_position: the position where the player wants to move to
     */
    void MakeTripleMove(int p_position);

    /**
     * @brief HandleActionCard: calls the action from the actioncard
     * @param p_card: the action card that needs to be executed
     */
    void HandleActionCard(ActionCard* p_card);

    /**
     * @brief EndTurn: ends the turn off the current player
     */
    bool EndTurn();

    /**
     * @brief PlayerUsedBusTicket: sets the currentPlayerUsesBusTicket
     * if the player has some bustickets
     */
    void PlayerUsedBusTicket();
    /**
     * @brief GetPlayerUsingBusTicket: checks if the current player is using a bus ticket
     * @return
     */
    bool GetPlayerUsingBusTicket() const;
    /**
     * @brief MakeBusTicketMove: the logic behind the busticket move
     * @param p_location: the locatoin where the player wants to go
     * @return : gives true if move succeeded
     */
    bool MakeBusTicketMove(int p_location);
    /**
     * @brief DoMrMonopolyMove: handles the logic from mrmonopoly
     */
    void DoMrMonopolyMove();
    /**
     * @brief DoActionSpaceMove: Makes the player moves to the nearest acttionspace
     */
    void DoActionSpaceMove();

    /**
     * @brief GoToNearestActionCardSpace: makes the current player move to the nearest
     * communitychest/chance space
     */
    void GoToNearestActionCardSpace() const;


    /**
     * @brief TradeMoney: trades money from the current player to the given player
     * @param p_toPlayer: the player you are exchanging with
     * @param p_money: the value of money that needs to be exchanged
     */
    void TradeMoney(Player * p_toPlayer, int p_money);
    /**
     * @brief TradeProperties: trades properties from the current player to the given player
     * @param p_toPlayer: the player you are exchanging with
     * @param p_properties: the propertie that needs to be exchanged
     */
    void TradeProperties(Player* p_toPlayer, QList<Property*> p_properties);
    /**
     * @brief SetMortgages: sets the given properties in or out of mortgage
     * @param p_propertiesMortgage: the properties that needs to be (un)mortgaged
     */
    void SetMortgages(QMap<Property *, bool> p_propertiesMortgage);

    void WriteToFile(QString p_fileName);
    void ReadFromFile(QString p_fileName);

    /**
     * @brief GetNumberOfPlayersAlive: gives the number of players alive
     * @return
     */
    int GetNumberOfPlayersAlive() const;
    /**
     * @brief MakePlayerHasDoneEverything: sets all the needed boolean for
     * ending a turn true
     */
    void MakePlayerHasDoneEverything();
signals:
    void NextTurn(Player * p_player);
    void DiceRolled(int p_die1, int p_die2, QString p_speedDie, bool p_double, bool p_triple);
    void PlayerHasThrownTriple();
    void PlayerMadeTripleMove();
    void PlayerHasNegativeMoneyValue();
    void PropertyCanNotBeInMortgage(Property* p_property);
    void EndOfGame(Player* p_player);
private:
    void HandleDoubleThrown(bool p_hasDoubleThrown);
    void HandlePlayerMoveDice(int p_totalThrown, bool p_hasTripleThrown);

    /**
     * @brief HasThrownDouble: says if the player has thrown a double with the two white dices
     * @param die1: the first die
     * @param die2: the second die
     * @return : gives true if double, false if not
     */
    bool HasThrownDouble(int die1, int die2) const;
    /**
     * @brief HasThrownTriple: says if the player has thrown a double with the three dices
     * @param die1
     * @param die2
     * @param die3
     * @return gives true if triple, false if not
     */
    bool HasThrownTriple(int die1, int die2, int die3) const;
    bool PlayerHasDoneEverything();

    Player* m_currentPlayer;
    QList<Player*> m_players;
    QQueue<BusTicket*> m_busTickets;
    Board* m_board;
    Die * m_die;
    int m_doublesThrown=0;
    bool m_currentPlayerHasThrown=false;
    bool m_currentPlayerHasExecutedSpeedDie=false;
    bool m_currentPlayerUsesBusTicket=false;
};

#endif // GAME_H
