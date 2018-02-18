#include "spaceview.h"
#include <QMessageBox>

SpaceView::SpaceView(Space* p_space, Game* p_game, int p_position,QGraphicsItem* parent) : QGraphicsRectItem(parent)
{
    m_game = p_game;
    m_space = p_space;
    m_position=p_position;
    connect(m_space, SIGNAL(AvailablePropertyVisited(Property*,bool)), this, SLOT(AvailablePropertyVisited(Property*,bool)));
    connect(m_space,SIGNAL(RentPayed(int,Property*)),this,SLOT(RentPayed(int,Property*)));
    connect(m_space,SIGNAL(LandedOnIncomeTax()),this,SLOT(LandedOnIncomeTax()));
    connect(m_space,SIGNAL(LandedOnBusTicketSpace(bool)),this,SLOT(LandedOnBusTicketSpace(bool)));
    connect(m_space,SIGNAL(ActionCardDrawn(ActionCard*)),this,SLOT(ActionCardDrawn(ActionCard*)));
}

int SpaceView::GetPosition() const
{
    return m_position;
}

void SpaceView::RentPayed(int p_amount, Property *p_property)
{
    QString message="You payed: $"+QString::number(p_amount);
    message+="\nFor the following property: " + p_property->GetName();
    QMessageBox::information(NULL,"Payed",message,"OK");
}

void SpaceView::AvailablePropertyVisited(Property *p_property, bool p_propertyNeedsToGetAuctioned=false)
{
    int response=1;
    if(!p_propertyNeedsToGetAuctioned)
    {
        QString message = "You visited the property: " + p_property->GetName();
        message += ".\nDo you want to buy this property?";
        message += "\n(Price: $" + QString::number(p_property->GetBuyPrice()) + ")";
        response = QMessageBox::question(NULL, "Available property visited", message, "Yes", "No (auction)" );
    }

    if (response == 0)
    {
        m_game->BuyProperty(p_property);
    }
    else //if (response == 1)
    {
        AuctionDialog auction(m_game->GetPlayers());
        auction.exec();
        m_game->BuyPropertyToPlayer(p_property,auction.GetHighestBid(),auction.GetHighestBidPlayer());

    }
}

void SpaceView::LandedOnIncomeTax()
{
    QString message="You landed on 'Income Tax'\n";
    message+="You can choose between paying $200 or 10% of your total value";

    int response = QMessageBox::question(NULL, "Landed on Income Tax", message, "$200", "10%" );
    if (response == 0)
    {
        m_game->PayIncomeTaxFixed();
    }
    else //if (response == 1)
    {
        m_game->PayIncomeTaxDynamic();
    }

}

void SpaceView::LandedOnBusTicketSpace(bool p_birthdayGift)
{
    int response=1;
    if(p_birthdayGift)
    {
        QString message="You landed on 'Birthday Gift'\n";
        message+="You can choose between taking $100 or a Bus Ticket";

        response = QMessageBox::question(NULL, "Birthday Gift", message, "$100", "Bus Ticket" );
    }
    if (response == 0)
    {
        m_game->GetBirthdayGift();
    }
    else //if (response == 1)
    {
        m_game->GetBusTicket();
    }
}

void SpaceView::ActionCardDrawn(ActionCard *p_card)
{
    QString message= "You just drawn this card:\n";
    message+=p_card->GetText();
    QMessageBox::question(NULL, "Action card", message, "OK");
    m_game->HandleActionCard(p_card);
}
