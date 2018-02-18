// Made by Arthur Jansen

#ifndef BUYHOUSESDIALOG_H
#define BUYHOUSESDIALOG_H

#include "property.h"
#include "player.h"

#include <QDialog>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class BuyHousesDialog : public QDialog
{
    Q_OBJECT
public:
    BuyHousesDialog(Property::StreetColor p_color, Player* p_player, QWidget* p_parent = 0);
    ~BuyHousesDialog();

    QList<int> GetResult();

public slots:
    void UpdateCost();

private:

    void SetUpSpinBoxes();

    Property::StreetColor m_streetColor;
    Player* m_player;

    QHBoxLayout* m_propertiesLayout;
    QVBoxLayout* m_mainLayout;

    QList<QSpinBox*> m_spinBoxList;

    QLabel* m_infoMessage;

    QHBoxLayout* m_buttonLayout;
    QPushButton* m_cancelButton;
    QPushButton* m_okButton;
    QLabel* m_costLabel;

    int m_buildPrice;
    QList<int> m_currentBuildTiers;
};

#endif // BUYHOUSESDIALOG_H
