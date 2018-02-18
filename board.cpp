#include "board.h"

#include <ctime>

Board::Board() : QObject()
{
    std::srand(unsigned(std::time(0)));
    m_chanceCards = LoadActionCards(":/Data/chanceText.txt");
    m_communityCards = LoadActionCards(":/Data/communityChestText.txt");
    LoadSpaces();
}

void Board::PlayerMove(Player *p_player, int p_location)
{
    m_spaces[p_location]->DoAction(p_player);
}

Property *Board::GetProperty(int p_position)
{
    for(int i=0;i<m_properties.length();i++)
        if(m_properties[i]->GetPosition()==p_position)
            return m_properties[i];
    return NULL;
}

Space* Board::GetSpace(int p_location) const
{
    return m_spaces[p_location];
}

int Board::GetFirstFollowingActionSpacePosition(int p_currentLocation) const
{
    // if current location is between the last actioncard space and the first
    // then return the first actioncard space position
    if(p_currentLocation>=m_actionCardSpaces.last())
        return m_actionCardSpaces.first();

    int i=0;
    //making m_actionCardSpaces[i] the first following action card space
    while (i<m_actionCardSpaces.length() && p_currentLocation>=m_actionCardSpaces[i])
        i++;
    return m_actionCardSpaces[i];
}

int Board::GetFirstFollowingUnownedPropertyPosition(int p_currentLocation) const
{
    int propertyListLocation=0;
    // making propertyListLocation the last property behind the current location
    for(int i=0;i<m_properties.length();i++)
        if(m_properties[i]->GetPosition()<=p_currentLocation)
            propertyListLocation=i;

    // making propertyListLocation the first unowned property infront of the current location
    propertyListLocation=(propertyListLocation+1)%m_properties.length();

    // if all properties are owned --> go to first property where rent paying is needed
    if(AllPropertiesOwned())
    {
        while(m_properties[propertyListLocation]->GetOwner())
        {
            propertyListLocation=(propertyListLocation+1)%m_properties.length();
        }
    }
    else // go to first unowned property
    {
        while(!m_properties[propertyListLocation]->IsAvailable())
        {
            propertyListLocation=(propertyListLocation+1)%m_properties.length();
        }
    }
    return m_properties[propertyListLocation]->GetPosition();
}

bool Board::AllPropertiesOwned() const
{
    for(int i=0;i<m_properties.length();i++)
    {
        if(m_properties[i]->IsAvailable())
            return false;
    }
    return true;
}

Property *Board::GetHighestRentProperty(Player * p_player) const
{
    Property * propertyWithHighestRent=m_properties[0];

    for(int i=0;i<m_properties.length();i++)
        if(!m_properties[i]->IsAvailable() && m_properties[i]->GetOwner()!=p_player)
            if(propertyWithHighestRent->GetRentPrice()<m_properties[i]->GetRentPrice())
                propertyWithHighestRent=m_properties[i];

    return propertyWithHighestRent;
}

void Board::SetPlayerHasLandedOnAuctionSpace(bool p_value)
{
    m_playerHasLandedOnAuctionSpace=p_value;
}

bool Board::GetPlayerHasLandedOnAuctionSpace() const
{
    return m_playerHasLandedOnAuctionSpace;
}

int Board::GetNumProperties() const
{
    return m_properties.length();
}

void Board::WriteToFile(QJsonObject &json)
{

    json["playerLandenOnAuctionSpace"] = m_playerHasLandedOnAuctionSpace;

    QJsonArray properties;
    for (int i = 0; i < m_properties.length(); i++)
    {
        QJsonObject property;
        m_properties[i]->WriteToFile(property);
        properties.append(property);
    }
    json["properties"] = properties;
}

void Board::ReadFromFile(const QJsonObject &json, QList<Player*> p_players)
{
    m_playerHasLandedOnAuctionSpace = json["playerLandenOnAuctionSpace"].toBool();

    QJsonArray properties = json["properties"].toArray();
    for (int i = 0; i < properties.size(); i++)
    {
        QJsonObject obj = properties[i].toObject();
        m_properties[i]->ReadFromFile(obj, p_players);
    }
}

void Board::LoadSpaces()
{
    QFile file(":/Data/spaceInformation.txt");
    file.open(QFile::ReadOnly);
    QTextStream textStream(&file);
    int i=0;
    while(!textStream.atEnd())
    {
        QString line = textStream.readLine();

        // TODO: load all types of spaces
        if (line.startsWith("P "))
        {
            m_properties.append(new StreetProperty(line,i));
            m_spaces.append(new PropertySpace(m_properties.last()));
        }
        else if (line.startsWith("R "))
        {
            m_properties.append(new RailRoad(line,i));
            m_spaces.append(new PropertySpace(m_properties.last()));
        }
        else if(line.startsWith("U "))
        {
            m_properties.append(new UtilityProperty(line,i));
            m_spaces.append(new PropertySpace(m_properties.last()));
        }
        else if(line.startsWith("T "))
            m_spaces.append(new TaxSpace());
        else if(line.startsWith("B "))
            m_spaces.append(new BusTicketSpace());
        else if(line.startsWith("A "))
            m_spaces.append(new AuctionSpace(this));
        else if(line.startsWith("J "))
            m_spaces.append(new GoToJailSpace());
        else if(line.startsWith("Ch ")){
            m_spaces.append(new CardSpace(m_chanceCards));
            m_actionCardSpaces.append(i);
        }
        else if(line.startsWith("C ")){
            m_spaces.append(new CardSpace(m_communityCards));
            m_actionCardSpaces.append(i);
            }
        else
            m_spaces.append(new IdleSpace());
        i++;
    }

    file.close();
}

QQueue<ActionCard*>* Board::LoadActionCards(QString p_fileName)
{
    QFile file(p_fileName);
    file.open(QFile::ReadOnly);
    QTextStream textStream(&file);

    QList<ActionCard*> cards;

    while(!textStream.atEnd())
    {
        QString line = textStream.readLine();

        cards.append(new ActionCard(line));

    }

    QQueue<ActionCard*>* result = new QQueue<ActionCard*>();

    ShuffleCards(&cards);

    for (int i = 0; i < cards.length(); i++)
    {
        result->append(cards[i]);
    }

    return result;
}

void Board::ShuffleCards(QList<ActionCard *> *p_cards)
{

    std::random_shuffle(p_cards->begin(), p_cards->end());
}
