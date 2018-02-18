#include "playerview.h"
#include <QMessageBox>

PlayerView::PlayerView(Player *p_player, QWidget* parent) : QFrame(parent)
{
    m_player=p_player;


    setMaximumHeight(150);
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setLineWidth(4);

    QString playerName = "Player " + QString::number(m_player->GetNumber() + 1);
    m_playerNameLabel = new QLabel(playerName, this);
    m_amountOfMoneyLabel = new QLabel("Money: $" + QString::number(m_player->GetMoney()), this);
    m_viewInfoButton = new QPushButton("View info", this);

    m_vLayout = new QVBoxLayout(this);
    setLayout(m_vLayout);
    m_vLayout->addWidget(m_playerNameLabel);
    m_vLayout->addWidget(m_amountOfMoneyLabel);
    m_vLayout->addWidget(m_viewInfoButton);

    connect(m_player, SIGNAL(AmountOfMoneyChanged()), this, SLOT(UpdateMoneyValue()));
    connect(m_player,SIGNAL(PlayerDied()),this,SLOT(PlayerDied()));
    connect(m_viewInfoButton,SIGNAL(clicked()),this,SLOT(ViewInfo()));
}

PlayerView::~PlayerView()
{
    delete m_amountOfMoneyLabel;
    delete m_playerNameLabel;
    delete m_viewInfoButton;
    delete m_vLayout;
}

void PlayerView::UpdateMoneyValue()
{
    m_amountOfMoneyLabel->setText("Money: $" + QString::number(m_player->GetMoney()));
}

void PlayerView::ViewInfo()
{
    QList<Property*> properties = m_player->GetProperties();
    QString displaytext;
    if(m_player->IsInJail())
        displaytext+="Currently in Jail\n";
    displaytext+="Money: $"+ QString::number(m_player->GetMoney()) + "\n\nProperties:";
    if(properties.length()==0)
        displaytext+="\nno properties";
    else
    {
        for(int i=0;i<properties.length();i++)
        {
            displaytext+="\n"+properties[i]->GetName();
            if(properties[i]->GetInMortgage())
                displaytext+="\n\tIn mortgage";
            else if(properties[i]->GetBuildTier()>0)
                displaytext+="\n\tBuild Tier: "+ QString::number(properties[i]->GetBuildTier());
        }
    }
    displaytext+="\n\nNumber of Out Of Jail Cards: "+ QString::number(m_player->GetNumberOfOutOfJailCards());



    displaytext+="\n\nBus Tickets: " + QString::number(m_player->GetNumberOfBusTickets());
    QMessageBox msgBox(QMessageBox::NoIcon, "Player info", displaytext, QMessageBox::Ok, this);
    msgBox.exec();
}

void PlayerView::PlayerDied()
{
    UpdateMoneyValue();
    m_amountOfMoneyLabel->setText("Dead");
    m_viewInfoButton->setEnabled(false);
}


