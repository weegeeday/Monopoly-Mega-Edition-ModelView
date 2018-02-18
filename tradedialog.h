// Made by Arthur Jansen

#ifndef TRADEDIALOG_H
#define TRADEDIALOG_H

#include "player.h"

#include <QCheckBox>
#include <QSpinBox>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPair>

class TradeDialog : public QDialog
{
    Q_OBJECT
public:
    TradeDialog(Player* p_player1, Player* p_player2, QWidget* parent = NULL);
    QList<Property*>* GetTradedProperties();
    Player* GetTradePlayer()const;
    int GetMoneyChange()const;
public slots:
    void OkButtonClicked();

private:

    QVBoxLayout* GeneratePlayerLayout(Player* p_player, QMap<int, QPair<QCheckBox*,Property*>*>* p_checkBoxes, QSpinBox** p_spinBox);

    Player* m_player1;
    Player* m_player2;

    QMap<int, QPair<QCheckBox*,Property*>*> m_player1Properties;
    QMap<int, QPair<QCheckBox*,Property*>*> m_player2Properties;
    //QMap<QCheckBox*,Property*> m_player1Properties;
    //QMap<QCheckBox*,Property*> m_player2Properties;

    QList<Property*> m_SelectedProperties;
    //QList<Property*> m_player2SelectedProperties;
    int m_player1AmountOfMoney=0;
    int m_player2AmountOfMoney=0;

    QSpinBox* m_player1Money;
    QSpinBox* m_player2Money;


};

#endif // TRADEDIALOG_H
