// Made by Louis Hendrikx

#ifndef TURNVIEW_H
#define TURNVIEW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QQueue>

#include "game.h"
#include "buttondialog.h"

class TurnView : public QWidget
{
    Q_OBJECT
public:
    const int MAX_NOTIFICATIONS=5;
    TurnView(Game* p_game, QWidget *parent = 0);
    ~TurnView();

public slots:
    /**
     * @brief DiceButtonClicked: handles the click of the dicebutton
     */
    void DiceButtonClicked();
    /**
     * @brief DiceRolled: handels the view when the dices are rolled
     * @param p_die1: number rolled with die 1
     * @param p_die2: number rolled with die 2
     * @param p_speedDie: string rolled with speed die
     * @param p_double: bool if double is thrown
     * @param p_triple: bool if triple is thrown
     */
    void DiceRolled(int p_die1, int p_die2, QString p_speedDie, bool p_double, bool p_triple);
    void BuildHousesButtonClicked();
    /**
     * @brief SwitchTurn: updates the view when the turn is switched
     * @param p_player
     */
    void SwitchTurn(Player* p_player);
    /**
     * @brief PropertyCanNotBeInMortgage: gives the player a notification that he
     * can't put the property in mortgage
     * @param p_property: the property that can't be set in mortgage
     */
    void PropertyCanNotBeInMortgage(Property* p_property);
    /**
     * @brief PlayerHasPayed: adds a notificatoin that the player
     * has payed or received an amount of money
     * @param p_player: the player that has payer or received
     * @param p_amount: the amount of money
     */
    void PlayerHasPayed(Player* p_player,int p_amount);
    void PlayerMustGoToJail();
    /*
     * all below handles a specific button
     * /*/
    void EndTurn();
    void GetOutOfJail();
    void PlayerMadeTripleMove();
    void BusTicketButtonClicked();
    void ExecuteSpeedDie();
    void MortgageButtonClicked();
    void TradeButtonClicked();
    void PlayerHasNegativeMoneyValue();
    void PlayerWantsToQuit();
    void SaveGameButtonClicked();

private:
    void InitPushButtons();
    void MakeConnects();
    void AddMessageToNotifications(QString p_message);
    void FillInfoMessageWithNotifications();
    void DisableAllButtons();
    void EnableAllButtons();
    void SetButtons(QList<bool> p_buttonValues);
    void BeginOfRoundButtons();
    void JustRolledButtons();
    void JustRolledSpeedDieButtons();
    void MustRollMrMonopolyButtons();
    void TripleButtons();
    void DoubleThrownSpeedDieButtons();
    void SaveButtons();
    void RestoreButtons();

    void CreateLayout();

    QList<int> AskNumberOfHouses(Player* p_player, Property::StreetColor p_color);

    Game * m_game;

    QLabel * m_infoMessage;
    QLabel * m_currentPlayerMessage;
    QPushButton* m_diceButton;
    QPushButton* m_speedDieButton;
    QPushButton* m_buildHousesButton;
    QPushButton* m_mortgageButton;
    QPushButton* m_tradeButton;
    QPushButton* m_getOutOfJailButton;
    QPushButton* m_useBusTicketButton;
    QPushButton* m_endTurnButton;
    QPushButton* m_quitPlayerButton;
    QPushButton* m_saveGameButton;
    QVBoxLayout* m_vLayout;

    QList<bool> m_restoreButtonValues;

    QString m_speedDie;
    QQueue <QString> m_notificationCenter;
    Player* m_currentPlayer;
    bool m_playerHadThrownDouble=false;
};

#endif // TURNVIEW_H
