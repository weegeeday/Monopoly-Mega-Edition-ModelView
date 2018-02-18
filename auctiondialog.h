// Made by Louis Hendrikx

#ifndef AUCTIONDIALOG_H
#define AUCTIONDIALOG_H

#include <QDialog>
#include <QList>
#include <QMap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "player.h"

class AuctionDialog: public QDialog
{
    Q_OBJECT
public:
    AuctionDialog(QList<Player*> p_players);
    ~AuctionDialog();
    /**
     * @brief GetHighestBid: returns the highest bid value
     * @return : the highest bid
     */
    int GetHighestBid() const;
    /**
     * @brief GetHighestBidPlayer: gives the playernumber who has done the highest bid
     * @return
     */
    int GetHighestBidPlayer() const;
public slots:
    void NewBid();
private:
    void AddButtons(QList<Player*> p_players);
    QVBoxLayout* m_vLayout;
    QHBoxLayout* m_hLayout;
    QList <QVBoxLayout*> m_playerSpaces;
    QList <QLabel*> m_playerTexts;
    QMap <QPushButton*,int> m_playerBidButtons;
    QPushButton* m_okButton;
    QLabel* m_displayText;
    int m_highestBid=0;
    int m_highestBidPlayer=0;
};

#endif // AUCTIONDIALOG_H
