// Made by Arthur Jansen

#ifndef ASKPLAYERTRADEDIALOG_H
#define ASKPLAYERTRADEDIALOG_H

#include "player.h"
#include "game.h"

#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>

class AskPlayerTradeDialog : public QDialog
{
    Q_OBJECT
public:
    AskPlayerTradeDialog(Player* p_currentPlayer, Game* p_game, QWidget* parent = NULL);

public slots:
    void PlayerButtonClicked();

    /**
     * @brief GetChosenPlayer: gives back the player that is chosen in the dialog
     * @return : the chosen Player *
     */
    Player* GetChosenPlayer();

private:
    QHBoxLayout* m_mainLayout;
    QMap<QPushButton*, Player*> m_buttonsToPlayers;
    Player* m_chosenPlayer;

};

#endif // ASKPLAYERTRADEDIALOG_H
