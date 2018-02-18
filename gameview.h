// Made by Louis Hendrikx

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QApplication>

#include "game.h"
#include "playerview.h"
#include "boardview.h"
#include "startdialog.h"
#include "turnview.h"
#include "auctiondialog.h"

class GameView: public QHBoxLayout
{
    Q_OBJECT
public:
    GameView(Game * p_game, QWidget* parent);
public slots:
    void EndOfGame(Player* p_player);
private:
    Game * m_game;
    BoardView * m_boardView;
    /**
     * @brief AskNumberOfPlayers: Asks the user how many players are going to participate
     * @return the number of players that are going to participate
     */
    void AskNumberOfPlayers();
    QList<PlayerView*> m_playerViews;
    QVBoxLayout* m_playerViewLayout;

    TurnView* m_turnView;
};

#endif // GAMEVIEW_H
