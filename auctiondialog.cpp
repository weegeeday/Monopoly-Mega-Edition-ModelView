#include "auctiondialog.h"

AuctionDialog::AuctionDialog(QList<Player*> p_players)
{
    m_vLayout=new QVBoxLayout;
    m_okButton= new QPushButton("OK",this);
    QString text="The best bid is: " + QString::number(m_highestBid) + "\nEach time you press \"Do a bid\" you go $20 up";
    m_displayText=new QLabel(text,this);
    AddButtons(p_players);

    m_vLayout->addWidget(m_displayText);
    m_vLayout->addLayout(m_hLayout);
    m_vLayout->addWidget(m_okButton);
    setLayout(m_vLayout);

    //disable the close button (X)
    setWindowFlags(Qt::WindowTitleHint);
    m_okButton->setEnabled(false);

    connect(m_okButton,SIGNAL(clicked()),this, SLOT(accept()));
}

AuctionDialog::~AuctionDialog()
{
    delete m_okButton;
    m_playerBidButtons.clear();
    m_playerTexts.clear();
    m_playerSpaces.clear();
    delete m_hLayout;
    delete m_vLayout;
    delete m_displayText;
}

int AuctionDialog::GetHighestBid() const
{
    return m_highestBid;
}

int AuctionDialog::GetHighestBidPlayer() const
{
    return m_highestBidPlayer;
}

void AuctionDialog::NewBid()
{
    m_okButton->setEnabled(true);
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    m_highestBidPlayer=m_playerBidButtons[clickedButton];
    if (clickedButton) // this is the type we expect
    {
        for(QMap<QPushButton*, int>::iterator it=m_playerBidButtons.begin()
            ;it != m_playerBidButtons.end();it++)
        {
            it.key()->setEnabled(true);
        }
        clickedButton->setEnabled(false);
    }
    m_highestBid+=20;
    QString text="The best bid is: $" + QString::number(m_highestBid) + ". From Player " + QString::number(m_highestBidPlayer+1) + ".";
    text+="\nEach time you press \"Do a bid\" you go $20 up";
    m_displayText->setText(text);
}

void AuctionDialog::AddButtons(QList<Player*> p_players)
{
    m_hLayout=new QHBoxLayout;
    for(int i=0;i<p_players.length();i++)
    {
        if(p_players[i]->IsAlive())
        {
            QVBoxLayout* vLayout=new QVBoxLayout;
            QLabel* label=new QLabel("Player "+QString::number(i+1),this);
            QPushButton* bidButton=new QPushButton("Do a bid!",this);

            vLayout->addWidget(label);
            vLayout->addWidget(bidButton);
            m_hLayout->addLayout(vLayout);

            m_playerBidButtons.insert(bidButton,i);
            //m_playerBidButtons.append(bidButton);
            m_playerTexts.append(label);
            m_playerSpaces.append(vLayout);
            connect(bidButton,SIGNAL(clicked()),this,SLOT(NewBid()));
        }
    }
}
