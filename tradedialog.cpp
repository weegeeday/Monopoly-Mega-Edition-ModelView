#include "tradedialog.h"

#include <QLabel>
#include <QPushButton>
#include <QFrame>

TradeDialog::TradeDialog(Player* p_player1, Player* p_player2, QWidget* parent) : QDialog(parent)
{
    m_player1 = p_player1;
    m_player2 = p_player2;

    QVBoxLayout* mainLayout = new QVBoxLayout();
    setLayout(mainLayout);


    QHBoxLayout* tradeLayout = new QHBoxLayout();
    QVBoxLayout* player1Layout = GeneratePlayerLayout(m_player1, &m_player1Properties, &m_player1Money);
    QVBoxLayout* player2Layout = GeneratePlayerLayout(m_player2, &m_player2Properties, &m_player2Money);

    tradeLayout->addLayout(player1Layout);

    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setMidLineWidth(3);
    tradeLayout->addWidget(line);

    tradeLayout->addLayout(player2Layout);

    mainLayout->addLayout(tradeLayout);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* okButton = new QPushButton("Ok");
    QPushButton* cancelButton = new QPushButton("Cancel");

    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);

    connect(okButton, SIGNAL(clicked()), this, SLOT(OkButtonClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

}

QList<Property *> *TradeDialog::GetTradedProperties()
{
    return &m_SelectedProperties;
}

Player *TradeDialog::GetTradePlayer() const
{
    return m_player2;
}

int TradeDialog::GetMoneyChange() const
{
    return m_player1AmountOfMoney-m_player2AmountOfMoney;
}

void TradeDialog::OkButtonClicked()
{
    // getting the money value
    m_player1AmountOfMoney=m_player1Money->value();
    m_player2AmountOfMoney=m_player2Money->value();

    // getting the checked properties from the first player
    for(int i=0;i<m_player1Properties.size();i++)
        if(m_player1Properties[i]->first->isChecked())
            m_SelectedProperties.append(m_player1Properties[i]->second);

    // getting the checked properties from the second player
    for(int i=0;i<m_player2Properties.size();i++)
        if(m_player2Properties[i]->first->isChecked())
            m_SelectedProperties.append(m_player2Properties[i]->second);

    accept();

}

QVBoxLayout *TradeDialog::GeneratePlayerLayout(Player *p_player, QMap<int, QPair<QCheckBox*,Property*>*>*p_checkBoxes, QSpinBox **p_spinBox)
{
    QVBoxLayout* result = new QVBoxLayout();
    result->setAlignment(Qt::AlignTop);

    QLabel* name = new QLabel("Player " + QString::number(p_player->GetNumber() + 1));
    result->addWidget(name);

    // Add all properties
    QList<Property*> properties = p_player->GetProperties();
    for (int i = 0; i < properties.length(); i++)
    {
        QCheckBox* propertyCheckBox = new QCheckBox(properties[i]->GetName());

        if (properties[i]->GetBuildTier() != 0)
        {
           propertyCheckBox->setEnabled(false);
           propertyCheckBox->setToolTip("You cannot trade properties with buildings");
        }
        else if (properties[i]->GetInMortgage())
        {
            propertyCheckBox->setToolTip("This property is in mortgage.");
        }

        result->addWidget(propertyCheckBox);
        // p_checkBoxes->append(property,properties[i]);
        //p_checkBoxes[property]=properties[i];
        QPair<QCheckBox*,Property*>* propertyButton=new QPair<QCheckBox*,Property*>(propertyCheckBox,properties[i]);//(property,properties[i]);

        p_checkBoxes->insert(i,propertyButton);
    }

    QHBoxLayout* moneyLayout = new QHBoxLayout();
    result->addLayout(moneyLayout);
    QSpinBox* moneySpinBox = new QSpinBox();

    moneyLayout->addWidget(new QLabel("Money: "));

    moneySpinBox->setMinimum(0);
    if(p_player->GetMoney()>=0)
        moneySpinBox->setMaximum(p_player->GetMoney());
    else
        moneySpinBox->setMaximum(0);
    *p_spinBox = moneySpinBox;
    moneyLayout->addWidget(moneySpinBox);


    return result;

}

