// Made by Louis Hendrikx

#ifndef ACTIONCARD_H
#define ACTIONCARD_H

#include <QString>
#include <QStringList>
#include <QList>

class Game;
class Player;

class ActionCard
{
public:

    enum ActionType {
        GO_TO_JAIL                  = 0,
        GET_OUT_OF_JAIL             = 1,
        NEAREST_UTILITY             = 2,
        NEAREST_RAILROAD            = 3,
        REPAIR_BUILDINGS            = 4,
        MONEY_CHANGE_OTHER_PLAYERS  = 5,
        MONEY_CHANGE                = 6,
        MOVE_TO_TARGET              = 7,
        MOVE_SPACES                 = 8
    };


    ActionCard(QString p_inputLine);

    const QString& GetText() const;
    ActionType GetType() const;

    /**
     * @brief DoAction: does the action associated with the type of card
     * @param p_game: needed for performing the action
     * @param p_currentPlayer: needed for performing the action
     */
    void DoAction(Game* p_game, Player* p_currentPlayer);

private:
    QString m_text;
    /**
     * @brief MoneyChangeOtherPlayers: makes all the other players paying a value
     * to one player and vice versa
     * @param p_game: needed for getting the other players
     * @param p_currentPlayer: the current player who needs to pay or get the money
     * @param p_value: the value that needs to be payed to the current player
     */
    void MoneyChangeOtherPlayers(Game *p_game, Player* p_currentPlayer, int p_value);
    /**
     * @brief GoToNearestRailroad: makes the player move to the nearest railroad
     * @param p_game: needed for the move
     * @param p_currentPlayer
     */
    void GoToNearestRailroad(Game * p_game, Player*p_currentPlayer);
    /**
     * @brief GoToNearestUtility: mkakes the player move to the nearest utility
     * @param p_game: needed for the move
     * @param p_currentPlayer: the player that need to be moved
     */
    void GoToNearestUtility(Game * p_game, Player* p_currentPlayer);
    int m_actionValue;
    ActionType m_actionType;
};

#endif // ACTIONCARD_H
