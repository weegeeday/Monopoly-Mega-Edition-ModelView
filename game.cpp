#include "game.h"

Game::Game()
{
    m_board = new Board();
    m_die=new Die;
    InitializeBusTickets();

}

Game::~Game()
{
    delete m_board;
    delete m_die;
    m_busTickets.clear();
}

void Game::InitializePlayers(int p_numberOfPlayers)
{
    for(int i=0;i<p_numberOfPlayers;i++)
    {
        m_players.append(new Player(i));
        m_players[i]->SetPosition(0);
    }
    m_currentPlayer=m_players[0];
}

void Game::InitializeBusTickets()
{
    for(int i=0;i<NUMBER_OF_BUSTICKETS;i++)
    {
        m_busTickets.append(new BusTicket());
    }
    QList<int> places;
    places << 0 << 0 <<0;
    // while all places are different
    while(places[0]==places[1] || places[1]==places[2])
    {
        places.clear();
        places<< m_die->GetRandomNumber(1,NUMBER_OF_BUSTICKETS-1) << m_die->GetRandomNumber(1,NUMBER_OF_BUSTICKETS-1) << m_die->GetRandomNumber(1,NUMBER_OF_BUSTICKETS-1);
    }
    for(int i=0;i<3;i++)
        m_busTickets[places[i]]->SetLabeled(true);
}

const QList<Player *> &Game::GetPlayers()const
{
    return m_players;
}

Board *Game::GetBoard() const
{
    return m_board;
}

void Game::RollDice()
{
    if(m_currentPlayerHasThrown && m_doublesThrown==0)
        return;
    m_currentPlayerHasThrown=true;
    int die3=0;

//    //test code
//    int die1=3;
//    int die2=3;
//    if(!m_currentPlayer->IsInJail())
//        die3=3;

    int die1=m_die->RollDie();
    int die2=m_die->RollDie();
    if(!m_currentPlayer->IsInJail())
        die3=m_die->RollDie();

    QString speedDie;
    int total=die1+die2;

    if(die3<=3){ // then the number
        total+=die3;
        speedDie=QString::number(die3);
        m_currentPlayerHasExecutedSpeedDie=true;
    }
    else if(die3<6) // then mr monopoly
        speedDie="Mr Monopoly";
    else // then bus ticket
        speedDie="Bus Ticket";

    bool hasDoubleThrown=HasThrownDouble(die1,die2);
    bool hasTripleThrown=HasThrownTriple(die1,die2,die3);
    m_currentPlayer->SetThrownNumbers(die1,die2,die3);

    HandleDoubleThrown(hasDoubleThrown);
    emit(DiceRolled(die1,die2,speedDie,hasDoubleThrown,hasTripleThrown));
    HandlePlayerMoveDice(total,hasTripleThrown);
}

void Game::HandleDoubleThrown(bool p_hasDoubleThrown)
{
    if(p_hasDoubleThrown){
        m_currentPlayer->GoToJail(false);
        m_doublesThrown++;
    }
    else // reset numbers of doubles
        m_doublesThrown=0;
}

void Game::HandlePlayerMoveDice(int p_totalThrown, bool p_hasTripleThrown){
    if(p_hasTripleThrown)
    {
        m_doublesThrown=0;
        emit(PlayerHasThrownTriple());
    }
    else if(m_doublesThrown==3) // if 3 triples in a row --> to jail
        m_currentPlayer->GoToJail(true);
    else
        MoveCurrentPlayer(p_totalThrown);
}

void Game::MoveCurrentPlayer(int p_steps)
{
    MoveCurrentPlayerTo( (p_steps + m_currentPlayer->GetPosition()) % NUMBER_OF_SPACES);
}

void Game::MoveCurrentPlayerTo(int p_location)
{
    if(!m_currentPlayer->IsInJail())
    {
        if(m_currentPlayer->GetPosition() >= p_location)
            m_currentPlayer->Pay(-200);

        m_currentPlayer->SetPosition(p_location);
        m_board->PlayerMove(m_currentPlayer, m_currentPlayer->GetPosition());
    }
}

void Game::BuyProperty(Property *p_property)
{
    // if the property is bought
    if(m_currentPlayer->Pay(p_property->GetBuyPrice()))
        p_property->SetOwner(m_currentPlayer);
}

void Game::BuyPropertyToPlayer(Property *p_property, int p_price, int p_toPlayer, int p_fromPlayer)
{
    if(m_players[p_toPlayer]->Pay(p_price))
    {
        p_property->SetOwner(m_players[p_toPlayer]);
        // if it is bought from another player
        if(p_fromPlayer!=0)
            m_players[p_fromPlayer]->Pay(-p_price);
    }
}

void Game::PayIncomeTaxFixed()
{
    m_currentPlayer->Pay(200);
}

void Game::PayIncomeTaxDynamic()
{
    int totalWorth=m_currentPlayer->GetTotalWorth();
    int toPay=(int)totalWorth/10;
    m_currentPlayer->Pay(toPay);
}

void Game::GetBirthdayGift()
{
    m_currentPlayer->Pay(-100);
}

bool Game::GetBusTicket()
{
    m_currentPlayerHasExecutedSpeedDie=true;
    BusTicket* busTicket=NULL;
    if(!m_busTickets.isEmpty())
    {
        busTicket=m_busTickets.dequeue();
        if(busTicket->GetLabeled())
            AllBusTicketsExpires();
        m_currentPlayer->AddBusTicket(busTicket);
        return true;
    }
    return false;
}

void Game::AllBusTicketsExpires()
{
    for(int i=0;i<m_players.length();i++)
    {
        m_players[i]->BusTicketsExpires();
    }
}

void Game::MakeTripleMove(int p_position)
{
    MoveCurrentPlayerTo(p_position);
    emit(PlayerMadeTripleMove());
}

bool Game::EndTurn()
{
    if(PlayerHasDoneEverything() || !m_currentPlayer->IsAlive())
    {
        m_currentPlayerHasThrown=false;
        m_currentPlayerHasExecutedSpeedDie=false;
        int currentPlayerNumber=m_currentPlayer->GetNumber();
        do{
            currentPlayerNumber++;
            m_currentPlayer=m_players[(currentPlayerNumber)%m_players.length()];
         }while(!m_currentPlayer->IsAlive());
        if(GetNumberOfPlayersAlive()>1){
            emit(NextTurn(m_currentPlayer));
            return true;
        }
        else {
            emit(EndOfGame(m_currentPlayer));
            return true;
        }
    }
    return false;
}

bool Game::PlayerHasDoneEverything()
{
    if (m_currentPlayer->GetMoney()<0)
    {
        emit(PlayerHasNegativeMoneyValue());
        return false;
    }
    return m_currentPlayerHasThrown && m_doublesThrown==0 && m_currentPlayerHasExecutedSpeedDie;
}

void Game::MakePlayerHasDoneEverything()
{
    m_currentPlayerHasThrown=true;
    m_doublesThrown=0;
    m_currentPlayerHasExecutedSpeedDie=true;
}

void Game::PlayerUsedBusTicket()
{
    if(m_currentPlayer->GetNumberOfBusTickets()>0)
        m_currentPlayerUsesBusTicket=true;
    else
        m_currentPlayerUsesBusTicket=false;
}

bool Game::GetPlayerUsingBusTicket() const
{
    return m_currentPlayerUsesBusTicket;
}

bool Game::MakeBusTicketMove(int p_location)
{
    // if want to go to GO space, p_location is seen as number of spaces+1 = 53
    if(p_location==0)
        p_location=RIGHT_LOW_CORNER;

    int currentLocation=m_currentPlayer->GetPosition();
    QList<int> corners;
    corners << LEFT_LOW_CORNER << LEFT_UP_CORNER << RIGHT_UP_CORNER << RIGHT_LOW_CORNER ;

    int i=0;
    // making corners[i] the next following corner
    while(currentLocation>=corners[i])
        i++;
    // check if the location where the players wants to go
    // is between the current location and the next corner
    if(p_location>currentLocation && p_location<=corners[i])
    {
        if(p_location==RIGHT_LOW_CORNER)
            p_location=0;
        MoveCurrentPlayerTo(p_location);
        m_currentPlayer->SetBusTicketUsed();
        m_currentPlayerHasThrown=true;
        MakePlayerHasDoneEverything();
        m_currentPlayerUsesBusTicket=false;
        return true;
    }

    return false;
}

void Game::DoMrMonopolyMove()
{
    m_currentPlayerHasExecutedSpeedDie=true;
    int location=m_board->GetFirstFollowingUnownedPropertyPosition(m_currentPlayer->GetPosition());
    MoveCurrentPlayerTo(location);
}

void Game::DoActionSpaceMove()
{
    m_currentPlayerHasExecutedSpeedDie=true;
    int location=m_board->GetFirstFollowingActionSpacePosition(m_currentPlayer->GetPosition());
    MoveCurrentPlayerTo(location);
}

void Game::SetMortgages(QMap<Property *, bool> p_propertiesMortgage)
{
    for (int i = 0; i < p_propertiesMortgage.count(); i++)
    {
        Property* property = p_propertiesMortgage.keys()[i];

        if (property->GetOwner() != m_currentPlayer)
        {
            // Property is not owned by current player
        }
        else if (!property->GetInMortgage() && p_propertiesMortgage[property])
        {
            // Set property in mortgage
            if(property->GetBuildTier() == 0)
            {
                m_currentPlayer->Pay(-(property->GetMortgagePrice()));
                property->SetInMortgage(true);
            }
            else
            {
                // Property has buildings so cannot be set in mortgage
                emit(PropertyCanNotBeInMortgage(property));
            }
        }
        else if (property->GetInMortgage() && !p_propertiesMortgage[property])
        {
            // Set property out of mortgage
            int price=property->GetOutOfMortgagePrice();
            m_currentPlayer->Pay(price);
            property->SetInMortgage(false);
        }

    }
}

void Game::WriteToFile(QString p_fileName)
{

    QFile file(p_fileName);

    if (!file.open(QIODevice::WriteOnly))
    {
        // Failed to open file
        return;
    }

    QJsonObject json;

    json["doublesThrown"] = m_doublesThrown;
    json["currentPlayerHasThrown"] = m_currentPlayerHasThrown;
    json["numPlayers"] = m_players.length();
    json["currentPlayer"] = m_currentPlayer->GetNumber();
    json["playerHasExecutedSpeedDie"] = m_currentPlayerHasExecutedSpeedDie;


    QJsonArray players;
    for (int i = 0; i < m_players.length(); i++)
    {
        QJsonObject player;
        m_players[i]->WriteToFile(player);
        players.append(player);
    }
    json["players"] = players;

    QJsonArray busTickets;
    for (int i = 0; i < m_busTickets.length(); i++)
    {
        QJsonObject busTicket;
        m_busTickets[i]->WriteToFile(busTicket);
        busTickets.append(busTicket);
    }
    json["busTickets"] = busTickets;

    QJsonObject board;
    m_board->WriteToFile(board);

    json["board"] = board;

    // Dice are not necessary to read/write


    QJsonDocument doc(json);
    file.write(doc.toJson());
}

void Game::ReadFromFile(QString p_fileName)
{

    QFile file(p_fileName);

   if (!file.open(QIODevice::ReadOnly))
   {
       // ERROR
       return;
   }

    QByteArray savedGameData = file.readAll();

    QJsonDocument doc(QJsonDocument::fromJson(savedGameData));

    QJsonObject json = doc.object();

    m_doublesThrown = json["doublesThrown"].toInt();
    m_currentPlayerHasThrown = json["currentPlayerHasThrown"].toBool();
    m_currentPlayerHasExecutedSpeedDie = json["playerHasExecutedSpeedDie"].toBool();

    int numPlayers = json["numPlayers"].toInt();
    InitializePlayers(numPlayers);

    int currentPlayer = json["currentPlayer"].toInt();

    QJsonArray players = json["players"].toArray();
    for (int i = 0; i < players.size(); i++)
    {
        QJsonObject playerObj = players[i].toObject();
        m_players[i]->ReadFromFile(playerObj);
    }

    m_currentPlayer = m_players[currentPlayer];

    QJsonArray busTickets = json["busTicket"].toArray();
    for (int i = 0; i < busTickets.size(); i++)
    {
        QJsonObject busTicketObj = busTickets[i].toObject();
        BusTicket* busTicket = new BusTicket();
        busTicket->ReadFromFile(busTicketObj);
        m_busTickets.append(busTicket);
    }

    QJsonObject boardObj = json["board"].toObject();
    //m_board = new Board();
    m_board->ReadFromFile(boardObj, m_players);

}

int Game::GetNumberOfPlayersAlive() const
{
    int numberOfPlayersAlive=0;
    for(int i=0;i<m_players.length();i++)
        if(m_players[i]->IsAlive())
            numberOfPlayersAlive++;

    return numberOfPlayersAlive;
}

void Game::TradeMoney(Player *p_toPlayer, int p_money)
{
    p_toPlayer->Pay(-p_money);
    m_currentPlayer->Pay(p_money);
}

void Game::TradeProperties(Player *p_toPlayer, QList<Property *> p_properties)
{
    for(int i=0;i<p_properties.length();i++)
    {
        if(p_properties[i]->GetOwner()==p_toPlayer)
        {
            p_properties[i]->SetOwner(m_currentPlayer);
            p_toPlayer->DeleteProperty(p_properties[i]);
        }
        else
        {
            p_properties[i]->SetOwner(p_toPlayer);
            m_currentPlayer->DeleteProperty(p_properties[i]);
        }
    }
}

bool Game::HasThrownDouble(int die1, int die2) const
{
    return die1==die2;
}

bool Game::HasThrownTriple(int die1, int die2, int die3) const
{
    if(die3<=3)
        return (die1==die2 && die2==die3);
    return false;
}

void Game::HandleActionCard(ActionCard *p_card)
{
    p_card->DoAction(this, m_currentPlayer);
}
