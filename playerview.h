// Made by Arthur Jansen

#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

#include "player.h"


class PlayerView : public QFrame
{
    Q_OBJECT
public:
    PlayerView(Player *p_player, QWidget* parent = NULL);
    ~PlayerView();

public slots:
    /**
     * @brief UpdateMoneyValue: updates the money value in the view
     */
    void UpdateMoneyValue();
    /**
     * @brief ViewInfo: opens a dialog with the player info
     */
    void ViewInfo();
    /**
     * @brief PlayerDied: updates the dialog with
     * dead-player relevant information
     */
    void PlayerDied();
private:
    Player* m_player;
    QLabel* m_playerNameLabel;
    QVBoxLayout* m_vLayout;
    QPushButton* m_viewInfoButton;
    QLabel* m_amountOfMoneyLabel;
};

#endif // PLAYERVIEW_H
