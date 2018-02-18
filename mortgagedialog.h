// Made by Louis Hendrikx

#ifndef MORTGAGEDIALOG_H
#define MORTGAGEDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QMap>

#include "player.h"

class MortgageDialog : public QDialog
{
    Q_OBJECT
public:
    MortgageDialog(Player* p_player, QWidget* parent = NULL);

    QMap<Property *, bool> GetMortgagedProperties() const;

public slots:
    void OkButtonClicked();

private:

    void CreateCheckBoxes(QVBoxLayout* p_mainLayout);

    QList<QCheckBox*> m_checkboxes;

    QMap<Property*, bool> m_mortgageProperties;

    Player* m_currentPlayer;
};

#endif // MORTGAGEDIALOG_H
