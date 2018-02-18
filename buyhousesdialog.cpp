#include "buyhousesdialog.h"

BuyHousesDialog::BuyHousesDialog(Property::StreetColor p_color, Player* p_player, QWidget* p_parent) : QDialog(p_parent)
{
    m_streetColor = p_color;
    m_player = p_player;

    m_mainLayout = new QVBoxLayout();

    SetUpSpinBoxes();

    m_infoMessage = new QLabel("Hotel = 5\nSkyscraper = 6");

    m_mainLayout->addWidget(m_infoMessage);

    m_costLabel = new QLabel("Cost: 0");
    m_mainLayout->addWidget(m_costLabel);


    // Init buttons
    m_buttonLayout = new QHBoxLayout();

    m_okButton = new QPushButton("Ok");
    m_okButton->setMaximumWidth(100);
    m_buttonLayout->addWidget(m_okButton);

    m_cancelButton = new QPushButton("Cancel");
    m_cancelButton->setMaximumWidth(100);
    m_buttonLayout->addWidget(m_cancelButton);

    m_mainLayout->addLayout(m_buttonLayout);

    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_okButton, SIGNAL(clicked(bool)), this, SLOT(accept()));

    setLayout(m_mainLayout);
}

BuyHousesDialog::~BuyHousesDialog()
{
    for (int i = 0; i < m_spinBoxList.length(); i++)
        delete m_spinBoxList[i];

    delete m_costLabel;
    delete m_okButton;
    delete m_cancelButton;
    delete m_buttonLayout;
    delete m_propertiesLayout;
    delete m_mainLayout;
}

QList<int> BuyHousesDialog::GetResult()
{
    QList<int> result;

    for(int i = 0; i < m_spinBoxList.length(); i++)
    {
        result << m_spinBoxList[i]->value();
    }

    return result;

}

void BuyHousesDialog::UpdateCost()
{
    int cost = 0;
    for (int i = 0; i < m_spinBoxList.length(); i++)
    {
        int diff = m_spinBoxList[i]->value() - m_currentBuildTiers[i];

        // Houses are payed back at half the price
        if (diff < 0)
            cost += diff * (m_buildPrice / 2);
        else
            cost += diff * m_buildPrice;
    }
    m_costLabel->setText("Cost: " + QString::number(cost));
}

void BuyHousesDialog::SetUpSpinBoxes()
{

    m_propertiesLayout = new QHBoxLayout();
    m_mainLayout->addLayout(m_propertiesLayout);


    QList<Property*> properties = m_player->GetProperties(m_streetColor);
    for (int i = 0; i < properties.length(); i++)
    {
        if(!properties[i]->GetInMortgage())
        {
            m_buildPrice = properties[i]->GetBuildPrice();

            QVBoxLayout* vLayout = new QVBoxLayout();
            QSpinBox* spinBox = new QSpinBox();

            spinBox->setValue(properties[i]->GetBuildTier());
            m_currentBuildTiers << properties[i]->GetBuildTier();

            spinBox->setMinimum(0);
            spinBox->setMaximum(properties[0]->GetMaxBuildTier());

            connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(UpdateCost()));

            QLabel* label = new QLabel(properties[i]->GetName());

            m_spinBoxList.append(spinBox);

            vLayout->addWidget(label);
            vLayout->addWidget(spinBox);

            m_propertiesLayout->addLayout(vLayout);
        }
    }
}
