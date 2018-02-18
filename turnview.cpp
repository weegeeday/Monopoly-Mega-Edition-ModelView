#include "turnview.h"
#include "buyhousesdialog.h"
#include "buttondialog.h"
#include "mortgagedialog.h"
#include "askplayertradedialog.h"
#include "tradedialog.h"

#include <QMessageBox>
#include <QFileDialog>

TurnView::TurnView(Game * p_game, QWidget *parent) : QWidget(parent)
{
    m_currentPlayer = p_game->GetPlayers()[0];
    InitPushButtons();

    m_infoMessage= new QLabel;
    m_currentPlayerMessage= new QLabel("Turn: Player 1",this);

    CreateLayout();

    m_game=p_game;

    BeginOfRoundButtons();
    MakeConnects();
    AddMessageToNotifications("Welcome to Monopoly\nThis is the notification center");
}

void TurnView::InitPushButtons()
{
    m_diceButton=new QPushButton("Roll the die",this);
    m_speedDieButton=new QPushButton("Execute speeddie",this);
    m_endTurnButton=new QPushButton("End turn",this);
    m_buildHousesButton=new QPushButton("Build houses",this);
    m_getOutOfJailButton=new QPushButton("Get out of jail", this);
    m_useBusTicketButton=new QPushButton("Use Bus Ticket",this);
    m_mortgageButton = new QPushButton("Mortgage" ,this);
    m_tradeButton = new QPushButton("Trade", this);
    m_quitPlayerButton=new QPushButton("Quit",this);
    m_saveGameButton = new QPushButton("Save", this);
}

void TurnView::CreateLayout()
{
    m_vLayout=new QVBoxLayout(this);
    setLayout(m_vLayout);
    m_vLayout->addWidget(m_currentPlayerMessage);
    m_vLayout->addWidget(m_diceButton);
    m_vLayout->addWidget(m_speedDieButton);
    m_vLayout->addWidget(m_buildHousesButton);
    m_vLayout->addWidget(m_mortgageButton);
    m_vLayout->addWidget(m_tradeButton);
    m_vLayout->addWidget(m_getOutOfJailButton);
    m_vLayout->addWidget(m_useBusTicketButton);
    m_vLayout->addWidget(m_endTurnButton);
    m_vLayout->addWidget(m_quitPlayerButton);
    m_vLayout->addWidget(m_saveGameButton);

    m_vLayout->addWidget(m_infoMessage);
}

TurnView::~TurnView()
{
    delete m_infoMessage;
    delete m_currentPlayerMessage;
    delete m_diceButton;
    delete m_speedDieButton;
    delete m_endTurnButton;
    delete m_buildHousesButton;
    delete m_mortgageButton;
    delete m_getOutOfJailButton;
    delete m_useBusTicketButton;
    delete m_quitPlayerButton;
    delete m_vLayout;
}

void TurnView::MakeConnects()
{
    connect(m_diceButton,SIGNAL(clicked()),this,SLOT(DiceButtonClicked()));
    connect(m_endTurnButton,SIGNAL(clicked()),this,SLOT(EndTurn()));
    connect(m_buildHousesButton,SIGNAL(clicked()),this,SLOT(BuildHousesButtonClicked()));
    connect(m_useBusTicketButton,SIGNAL(clicked()),this,SLOT(BusTicketButtonClicked()));
    connect(m_getOutOfJailButton,SIGNAL(clicked()),this,SLOT(GetOutOfJail()));
    connect(m_speedDieButton,SIGNAL(clicked()),this,SLOT(ExecuteSpeedDie()));
    connect(m_mortgageButton, SIGNAL(clicked()), this, SLOT(MortgageButtonClicked()));
    connect(m_tradeButton, SIGNAL(clicked()), this, SLOT(TradeButtonClicked()));
    connect(m_game,SIGNAL(NextTurn(Player*)),this,SLOT(SwitchTurn(Player*)));
    connect(m_game,SIGNAL(DiceRolled(int,int,QString,bool,bool)),this,SLOT(DiceRolled(int,int,QString,bool,bool)));
    connect(m_game,SIGNAL(PlayerMadeTripleMove()),this,SLOT(PlayerMadeTripleMove()));
    connect(m_game,SIGNAL(PlayerHasNegativeMoneyValue()),this,SLOT(PlayerHasNegativeMoneyValue()));
    connect(m_quitPlayerButton,SIGNAL(clicked()),this,SLOT(PlayerWantsToQuit()));
    connect(m_saveGameButton, SIGNAL(clicked()), this, SLOT(SaveGameButtonClicked()));
    connect(m_game,SIGNAL(PropertyCanNotBeInMortgage(Property*)),this,SLOT(PropertyCanNotBeInMortgage(Property*)));
    QList <Player*> players=m_game->GetPlayers();
    for(int i=0;i<players.length();i++)
    {
        connect(players[i],SIGNAL(PlayerHasPayed(Player*,int)),this,SLOT(PlayerHasPayed(Player*,int)));
        connect(players[i],SIGNAL(PlayerMustGoToJail()),this,SLOT(PlayerMustGoToJail()));
    }
}

void TurnView::DiceButtonClicked()
{
    m_game->RollDice();
}

void TurnView::DiceRolled(int p_die1, int p_die2, QString p_speedDie, bool p_double, bool p_triple)
{
    QString text= "You rolled: ";
    text+= QString::number(p_die1) + " and ";
    text+= QString::number(p_die2);
    m_playerHadThrownDouble=false;
    if(p_speedDie!="0")
    {
        text += "\nand with the Speed die: ";
        text+= p_speedDie;
        m_speedDie=p_speedDie;
        // if speeddie is a special action
        if(p_speedDie=="Mr Monopoly")
            MustRollMrMonopolyButtons();
        else if(p_speedDie=="Bus Ticket")
            JustRolledSpeedDieButtons();
        else
            JustRolledButtons();
    }
    if(m_currentPlayer->IsInJail())
        JustRolledButtons();

    if(p_double && !p_triple){
        text+="\nYou have thrown a double!";
        m_playerHadThrownDouble=true;
        if(p_speedDie=="Mr Monopoly")
            MustRollMrMonopolyButtons();
        else if(p_speedDie=="Bus Ticket")
            JustRolledSpeedDieButtons();
        else
            BeginOfRoundButtons();
    }
    if(p_triple){
        m_playerHadThrownDouble=false;
        TripleButtons();
        text+="\nYou have thrown a triple!";
    }
    AddMessageToNotifications(text);
    if(p_triple)
    {
        QString chooseSpaceText="You must choose a space now!\nSelect a space by clicking on it";
        AddMessageToNotifications(chooseSpaceText);
    }
}

void TurnView::BuildHousesButtonClicked()
{
    // Get possible streets
    QStringList streetList;

    for (int i = 0; i < 9; i++) // Loop over all street colors and railroad, except utility
    {
        Property::StreetColor color = (Property::StreetColor) i;

        if (m_currentPlayer->OwnsStreetPartially(color))
        {
            streetList.append(Property::ToString(color));
        }
    }

    // Ask user what street
    if(streetList.isEmpty())
    {
        AddMessageToNotifications("You have no\nproperties to build on");
        return;
    }
    ButtonDialog btnDialog("Please select the street you want to build on:", streetList);

    btnDialog.exec();

    if (btnDialog.result() != QDialog::Accepted)
    {
        return;
    }

    Property::StreetColor response = Property::FromString(streetList[btnDialog.GetClickedButtonNumber()]);

    // Ask number of houses for each property

    QList<int> houseNumbers = AskNumberOfHouses(m_currentPlayer, response);

    if (!houseNumbers.isEmpty())
    {
        m_currentPlayer->BuildHouses(houseNumbers, response);
        // m_game->BuildHouses(houseNumbers,response);
    }
}

void TurnView::SwitchTurn(Player *p_player)
{
    m_currentPlayer=p_player;
    m_currentPlayerMessage->setText("Turn: Player "+QString::number(m_currentPlayer->GetNumber() + 1));

    BeginOfRoundButtons();
}

void TurnView::PropertyCanNotBeInMortgage(Property *p_property)
{
    QString message=p_property->GetName()+"\ncan't be set in mortgage";
    AddMessageToNotifications(message);
}

void TurnView::PlayerHasPayed(Player*p_player,int p_amount)
{
    QString message;
    if(p_player!=m_currentPlayer)
        message+="Player "+ QString::number(p_player->GetNumber()+1)+" has\n";
    else
        message+="You ";

    if(p_amount>=0)
        message+="payed $"+QString::number(p_amount);
    else
        message+="received $"+QString::number(-p_amount);
    AddMessageToNotifications(message);
}

void TurnView::PlayerMustGoToJail()
{
    AddMessageToNotifications("I moved to the jail!");
    m_game->MakePlayerHasDoneEverything();
    JustRolledButtons();
}

void TurnView::GetOutOfJail()
{
    m_currentPlayer->GetOutOfJail();
}

void TurnView::EndTurn()
{
    if(m_game->EndTurn())
        BeginOfRoundButtons();
}

void TurnView::PlayerMadeTripleMove()
{
    JustRolledButtons();
}

void TurnView::BusTicketButtonClicked()
{
    QString text = "You clicked the Bus Ticket button\nClick on the space where \nyou want to go";
    text+="\nYou can go to any \nspace in front of you\non the side where you are now";
    AddMessageToNotifications(text);

    JustRolledButtons();
    m_game->PlayerUsedBusTicket();
    // -> use bus ticket
}

void TurnView::ExecuteSpeedDie()
{
    m_speedDieButton->setEnabled(false);
    if(m_speedDie=="Bus Ticket")
    {
        QStringList buttons;
        buttons << "Bus Ticket" << "Chance/Communitychest";
        ButtonDialog askBusTicket("What would you like to do?\n Getting a bus ticket or\nGo to the nearest Chance/CommunityChest",buttons);
        askBusTicket.exec();
        if(askBusTicket.GetClickedButtonNumber()==0) // get bus ticket
            m_game->GetBusTicket();
        else // go to nearest chance/communitychest
            m_game->DoActionSpaceMove();
    }
    else if(m_speedDie=="Mr Monopoly")
    {
        m_game->DoMrMonopolyMove();
    }

    if(m_playerHadThrownDouble)
        BeginOfRoundButtons();
    else
        JustRolledButtons();
}

void TurnView::MortgageButtonClicked()
{
    MortgageDialog dlg(m_currentPlayer);
    int response = dlg.exec();

    if (response == QDialog::Accepted)
    {
        m_game->SetMortgages(dlg.GetMortgagedProperties());
    }
}

void TurnView::TradeButtonClicked()
{
    AskPlayerTradeDialog askPlayerDlg(m_currentPlayer, m_game, this);
    int response = askPlayerDlg.exec();

    if (response != QDialog::Accepted)
        return;

    Player* chosenPlayer = askPlayerDlg.GetChosenPlayer();
    if(chosenPlayer!=NULL)
    {
        TradeDialog tradeDlg(m_currentPlayer, chosenPlayer);
        tradeDlg.exec();
        QString text="Traded with player " + QString::number(chosenPlayer->GetNumber()+1);
        AddMessageToNotifications(text);
        m_game->TradeMoney(chosenPlayer,tradeDlg.GetMoneyChange());
        m_game->TradeProperties(chosenPlayer,*tradeDlg.GetTradedProperties());
    }
}

void TurnView::PlayerHasNegativeMoneyValue()
{
    QString text="You've got a negative balance, \nyou must morgage or trade \nsome properties if you want \nto continue playing.";
    text+="\nIf you want to quit: \nclick 'quit' ";
    AddMessageToNotifications(text);
}

void TurnView::PlayerWantsToQuit()
{
    AddMessageToNotifications("I quit the game");
    m_currentPlayer->Die();
    m_game->EndTurn();
}

void TurnView::SaveGameButtonClicked()
{

    QString fileName = QFileDialog::getSaveFileName(this, "Save game");
    m_game->WriteToFile(fileName);

}

void TurnView::AddMessageToNotifications(QString p_message)
{
    // add player number before message
    QString text;
    text+="Player "+QString::number(m_currentPlayer->GetNumber() + 1)+":\n";
    text+=p_message;
    // add message to the queue
    m_notificationCenter.enqueue(text);

    FillInfoMessageWithNotifications();
}

void TurnView::FillInfoMessageWithNotifications()
{
    // first deleting the redundant messages
    while(m_notificationCenter.length()>MAX_NOTIFICATIONS)
        m_notificationCenter.dequeue();

    // making one large QString of all the messages separates by double newline
    QString TotalText;
    int i=m_notificationCenter.length()-1;
    while(i>=0 && !m_notificationCenter[i].isEmpty())
    {
        TotalText+=m_notificationCenter[i];
        TotalText+="\n\n";
        i--;
    }
    m_infoMessage->setText(TotalText);
}

void TurnView::DisableAllButtons()
{
    QList <bool> values;
    for (int i=0;i<10;i++)
        values.append(false);
    SetButtons(values);
}

void TurnView::EnableAllButtons()
{
    QList <bool> values;
    for (int i=0;i<10;i++)
        values.append(true);
    SetButtons(values);
}



void TurnView::SetButtons(QList<bool> p_buttonValues)
{

    m_diceButton->setEnabled(p_buttonValues[0]);
    m_speedDieButton->setEnabled(p_buttonValues[1]);
    m_buildHousesButton->setEnabled(p_buttonValues[2]);
    m_mortgageButton->setEnabled(p_buttonValues[3]);
    m_tradeButton->setEnabled(p_buttonValues[4]);
    m_getOutOfJailButton->setEnabled(p_buttonValues[5]);
    m_useBusTicketButton->setEnabled(p_buttonValues[6]);
    m_endTurnButton->setEnabled(p_buttonValues[7]);
    m_quitPlayerButton->setEnabled(p_buttonValues[8]);
    m_saveGameButton->setEnabled(p_buttonValues[9]);
}

void TurnView::BeginOfRoundButtons()
{
    QList <bool> values;
    bool hasBusTickets=false,inJail;
    inJail=m_currentPlayer->IsInJail();
    if(m_currentPlayer->GetNumberOfBusTickets()>0) // if the player has bustickets, he can use the busticketbutton
        hasBusTickets=true;
    values << true << false << true<< true<< true << inJail<< hasBusTickets<<false<<true<<true;
    SetButtons(values);
}

void TurnView::JustRolledButtons()
{
    QList <bool> values;
    values << false << false << true<< true<< true << false<< false<<true<<true<<false;
    SetButtons(values);
}

void TurnView::JustRolledSpeedDieButtons()
{
    QList <bool> values;
    values << false << true << true<< true<< true << false<< false<<false<<true<<false;
    SetButtons(values);
}

void TurnView::MustRollMrMonopolyButtons()
{
    QList <bool> values;
    values << false << true << false<< true<< false << false<< false<<false<<true<<false;
    SetButtons(values);
}

void TurnView::TripleButtons()
{
    DisableAllButtons();
}

void TurnView::SaveButtons()
{
    m_restoreButtonValues[0]=m_diceButton->isEnabled();
    m_restoreButtonValues[1]=m_speedDieButton->isEnabled();
    m_restoreButtonValues[2]=m_buildHousesButton->isEnabled();
    m_restoreButtonValues[3]=m_mortgageButton->isEnabled();
    m_restoreButtonValues[4]=m_tradeButton->isEnabled();
    m_restoreButtonValues[5]=m_getOutOfJailButton->isEnabled();
    m_restoreButtonValues[6]=m_useBusTicketButton->isEnabled();
    m_restoreButtonValues[7]=m_endTurnButton->isEnabled();
    m_restoreButtonValues[8]=m_quitPlayerButton->isEnabled();
    m_restoreButtonValues[9]=m_saveGameButton->isEnabled();
}

void TurnView::RestoreButtons()
{
    m_diceButton->setEnabled(m_restoreButtonValues[0]);
    m_speedDieButton->setEnabled(m_restoreButtonValues[1]);
    m_buildHousesButton->setEnabled(m_restoreButtonValues[2]);
    m_mortgageButton->setEnabled(m_restoreButtonValues[3]);
    m_tradeButton->setEnabled(m_restoreButtonValues[4]);
    m_getOutOfJailButton->setEnabled(m_restoreButtonValues[5]);
    m_useBusTicketButton->setEnabled(m_restoreButtonValues[6]);
    m_endTurnButton->setEnabled(m_restoreButtonValues[7]);
    m_quitPlayerButton->setEnabled(m_restoreButtonValues[8]);
    m_saveGameButton->setEnabled(m_restoreButtonValues[9]);
}


QList<int> TurnView::AskNumberOfHouses(Player *p_player, Property::StreetColor p_color)
{
    QList<int> result;

    bool isValid = false;
    bool askingInput = true;

    while (askingInput)
    {

        BuyHousesDialog dlg(p_color, p_player);
        dlg.exec();

        if (dlg.result() == QDialog::Accepted)
        {
            result = dlg.GetResult();
            isValid = p_player->ValidBuildingNumbers(result, p_color);

            if (!isValid)
            {
                QString msg = "That input was not valid, make sure you build houses evenly on the street.";
                msg += "\nYou can only build skyscrapers if you completely own the street.";
                QMessageBox::warning(this, "Invalid number of houses", msg);
            }
            else
                askingInput = false;
        }
        else
        {
            askingInput = false;
        }

    }

    if (isValid)
        return result;
    else
        return QList<int>(); // Empty list
}
