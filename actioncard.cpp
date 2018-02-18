#include "actioncard.h"
#include "game.h"
#include "player.h"

ActionCard::ActionCard(QString p_inputLine)
{
    QStringList stringList = p_inputLine.split(" ");

    m_actionType = (ActionType) stringList[0].toInt();
    m_actionValue = stringList[1].toInt();

    for (int i = 2; i < stringList.length(); i++)
    {
        m_text += stringList[i] + " ";
    }
    m_text = m_text.trimmed();

}

const QString &ActionCard::GetText() const
{
    return m_text;
}

ActionCard::ActionType ActionCard::GetType() const
{
    return m_actionType;
}

void ActionCard::DoAction(Game *p_game, Player *p_currentPlayer)
{
    switch (m_actionType) {
    case GO_TO_JAIL:
        p_currentPlayer->GoToJail(true);
        break;
    case NEAREST_UTILITY:
        GoToNearestUtility(p_game, p_currentPlayer);
        break;
    case GET_OUT_OF_JAIL:
        p_currentPlayer->AddOutOfJailCard();
        break;
    case NEAREST_RAILROAD:
        GoToNearestRailroad(p_game, p_currentPlayer);
        break;
    case REPAIR_BUILDINGS:
        p_currentPlayer->RepairBuildings(m_actionValue);
        break;
    case MONEY_CHANGE_OTHER_PLAYERS:
        MoneyChangeOtherPlayers(p_game,p_currentPlayer,m_actionValue);
        break;
    case MONEY_CHANGE:
        p_currentPlayer->Pay(-m_actionValue);
        break;
    case MOVE_TO_TARGET:
        p_game->MoveCurrentPlayerTo(m_actionValue);
        break;
    case MOVE_SPACES:
        p_game->MoveCurrentPlayer(m_actionValue);
        break;
    default:
        break;
    }
}

void ActionCard::MoneyChangeOtherPlayers(Game *p_game, Player *p_currentPlayer, int p_value)
{
    QList <Player*> playerList=p_game->GetPlayers();
    p_currentPlayer->Pay(-p_value);
    for(int i=0;i<playerList.length();i++)
    {
        if(playerList[i]->IsAlive() && playerList[i]!=p_currentPlayer)
        {
            // the current players always first get the money
            p_currentPlayer->Pay(-p_value);
            // then the other player pays the money
            playerList[i]->Pay(p_value);
        }
    }
}

void ActionCard::GoToNearestRailroad(Game * p_game, Player *p_currentPlayer)
{
    int playerLocation=p_currentPlayer->GetPosition();
    p_currentPlayer->SetFromCard(true);

    if(playerLocation>=0 && playerLocation<6)
        p_game->MoveCurrentPlayerTo(6);
    else if(playerLocation>6 && playerLocation<20)
        p_game->MoveCurrentPlayerTo(20);
    else if(playerLocation>20 && playerLocation<33)
        p_game->MoveCurrentPlayerTo(33);
    else
        p_game->MoveCurrentPlayerTo(45);
}

void ActionCard::GoToNearestUtility(Game * p_game, Player *p_currentPlayer)
{
    int playerLocation=p_currentPlayer->GetPosition();
    p_currentPlayer->SetFromCard(true);

    if(playerLocation>=0 && playerLocation<10)
        p_game->MoveCurrentPlayerTo(10);
    else if(playerLocation>10 && playerLocation<17)
        p_game->MoveCurrentPlayerTo(17);
    else
        p_game->MoveCurrentPlayerTo(36);
}
