#include "askplayertradedialog.h"

AskPlayerTradeDialog::AskPlayerTradeDialog(Player* p_currentPlayer, Game* p_game, QWidget* parent) : QDialog(parent)
{

    m_mainLayout = new QHBoxLayout();
    setLayout(m_mainLayout);

    QList<Player*> players = p_game->GetPlayers();

    for (int i = 0; i < players.length(); i++)
    {
        if (players[i] != p_currentPlayer && players[i]->IsAlive())
        {
            QPushButton* btn = new QPushButton("Player " + QString::number(players[i]->GetNumber() + 1));
            m_mainLayout->addWidget(btn);
            m_buttonsToPlayers[btn] = players[i];
            connect(btn, SIGNAL(clicked()), this, SLOT(PlayerButtonClicked()));
        }
    }
}

void AskPlayerTradeDialog::PlayerButtonClicked()
{
    QPushButton* btn = (QPushButton*)sender();
    m_chosenPlayer = m_buttonsToPlayers[btn];
    accept();
}

Player *AskPlayerTradeDialog::GetChosenPlayer()
{
    return m_chosenPlayer;
}
