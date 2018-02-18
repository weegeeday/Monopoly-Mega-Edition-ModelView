#include "player.h"

Player::Player(int p_playerNumber)
{
    m_playerNumber = p_playerNumber;
}

int Player::GetNumber() const
{
    return m_playerNumber;
}

int Player::GetPosition() const
{
    return m_position;
}

void Player::SetPosition(int p_position)
{
    if(!m_inJail)
        m_position = p_position;
    else
    {
        m_roundsInJail++;
        if(m_roundsInJail==3){
            GoToJail(false);
        }
    }
    emit(PlayerMoved(GetNumber(), GetPosition()));
}

bool Player::OwnsStreetCompletely(Property::StreetColor p_streetColor)
{
    int maxProperties = Property::GetPropertyCount(p_streetColor);
    int ownedProperties = GetAmountOfPropertiesOwned(p_streetColor);

    return ownedProperties == maxProperties;
}

bool Player::OwnsStreetPartially(Property::StreetColor p_streetColor)
{

    if (p_streetColor == Property::RAILROAD)
    {
        // Only one railroad is required to build on it
        return GetAmountOfPropertiesOwned(p_streetColor) >= 1;
    }

    int maxProperties = Property::GetPropertyCount(p_streetColor);
    int ownedProperties = GetAmountOfPropertiesOwned(p_streetColor);

    return ownedProperties >= maxProperties - 1;
}

bool Player::Pay(int p_amount)
{
    emit(PlayerHasPayed(this,p_amount));
    AddMoney(-p_amount);
    if (m_money >= p_amount)
        return true;
    else
        return false;
}

bool Player::PayPlayer(Player *p_player, int p_amount)
{
    Pay(p_amount);
    p_player->Pay(-p_amount);
    if (m_money >= p_amount)
        return true;
    else
        return false;
}

QList<Property *> Player::GetProperties()
{
    return m_properties;
}

QList<Property *> Player::GetProperties(Property::StreetColor p_streetColor)
{
    QList<Property*> result;

    for (int i = 0; i < m_properties.length(); i++)
    {
        if(m_properties[i]->GetColor() == p_streetColor)
        {
            result.append(m_properties[i]);
        }
    }

    return result;
}

int Player::GetAmountOfPropertiesOwned(Property::StreetColor p_streetColor)
{
    int count = 0;
    for (int i = 0; i < m_properties.length(); i++)
    {
        if (m_properties[i]->GetColor() == p_streetColor && !m_properties[i]->GetInMortgage())
            count++;
    }
    return count;
}

void Player::SetThrownNumbers(int p_die1, int p_die2, int p_die3)
{
    m_lastThrown.clear();
    m_lastThrown << p_die1 <<p_die2 <<p_die3;
}

int Player::GetTotalThrown() const
{
    if (m_lastThrown[2] <= 3)
        return m_lastThrown[0] + m_lastThrown[1] + m_lastThrown[2];
    else
        return m_lastThrown[0] + m_lastThrown[1];
}

void Player::AddBusTicket(BusTicket *p_busTicket)
{
    m_busTickets.append(p_busTicket);
}

void Player::BusTicketsExpires()
{
    m_busTickets.clear();
}

int Player::GetNumberOfBusTickets() const
{
    return m_busTickets.length();
}

bool Player::IsInJail() const
{
    return m_inJail;
}

void Player::AddOutOfJailCard()
{
    m_outOfJailCards++;
}

void Player::RepairBuildings(int p_priceLevel)
{
    int housePrice=p_priceLevel;
    int hotelPrice=115;
    if(p_priceLevel==25)
    {
        housePrice=25;
        hotelPrice=100;
    }

    for(int i=0;i<m_properties.length();i++)
    {
        // if hotel or skyscraper
        if(m_properties[i]->GetBuildTier()>=5)
            Pay(hotelPrice);
        // if houses or nothing
        else
            Pay(m_properties[i]->GetBuildTier()*housePrice);
    }
}

bool Player::ComesFromCard() const
{
    return m_comesFromCard;
}

void Player::SetFromCard(bool p_value)
{
    m_comesFromCard=p_value;
}

void Player::SetBusTicketUsed()
{
    m_busTickets.removeLast();
}

void Player::GetOutOfJail()
{
    if(IsInJail())
    {
        // if player has out of jail cards
        if(m_outOfJailCards>0)
            m_outOfJailCards--;
        else
            Pay(50);
        GoToJail(false);
    }
}

void Player::BuildHouses(QList<int> p_houseNumbers, Property::StreetColor p_streetColor)
{
    QList<Property*> streetProperties = GetProperties(p_streetColor);

    for (int i = 0; i < streetProperties.length(); i++)
    {
        int current = streetProperties[i]->GetBuildTier();

        // make player pay / give back money
        int diff = p_houseNumbers[i] - current;

        // Houses are payed back at half the price
        if (diff < 0)
            Pay(diff * (streetProperties[i]->GetBuildPrice() / 2));
        else
            Pay(diff * streetProperties[i]->GetBuildPrice());



        streetProperties[i]->SetBuildTier(p_houseNumbers[i]);

    }

}

int Player::GetNumberOfOutOfJailCards() const
{
    return m_outOfJailCards;
}

void Player::WriteToFile(QJsonObject &json) const
{
    json["number"] = m_playerNumber;
    json["inJail"] = m_inJail;
    json["roundsInJail"] = m_roundsInJail;
    json["position"] = m_position;
    json["money"] = m_money;
    json["outOfJailCards"] = m_outOfJailCards;
    json["alive"] = m_isAlive;
}

void Player::ReadFromFile(const QJsonObject &json)
{
    m_playerNumber = json["number"].toInt();
    m_inJail = json["inJail"].toBool();
    m_roundsInJail = json["roundsInJail"].toInt();
    SetPosition(json["position"].toInt());
    SetMoney(json["money"].toInt());
    m_outOfJailCards = json["outOfJailCards"].toInt();
    m_isAlive = json["alive"].toBool();
    if (!m_isAlive)
    {
        emit PlayerDied();
    }
}

bool Player::IsAlive() const
{
    return m_isAlive;
}

void Player::RedistributeBuildings(Property::StreetColor p_streetColor)
{
    if (!OwnsStreetCompletely(p_streetColor))
        return;

    QList<int> numbersOfBuildings;
    QList<Property*> ownedProperties = GetProperties(p_streetColor);
    for (int i = 0; i < ownedProperties.length(); i++)
    {
        numbersOfBuildings.append(ownedProperties[i]->GetBuildTier());
    }

    if (!ValidBuildingNumbers(numbersOfBuildings, p_streetColor))
    {
        int totalBuildings = 0;
        for (int i = 0; i < numbersOfBuildings.length(); i++)
        {
            totalBuildings += numbersOfBuildings[i];
        }

        int buildingsLeft = totalBuildings;
        int counter = 0;
        int numProperties = ownedProperties.length();
        QVector<int> redistributedBuildings(numProperties);
        while (buildingsLeft > 0)
        {
            //.Property* prop = ownedProperties[counter % numProperties];
            redistributedBuildings[counter % numProperties]++;
            buildingsLeft--;
            counter++;
        }

        BuildHouses(redistributedBuildings.toList(), p_streetColor);

    }

}

bool Player::GetBuildOnStreet(Property::StreetColor p_streetColor)
{
    QList<Property*> street=GetProperties(p_streetColor);
    for(int i=0;i<street.length();i++)
    {
        if(street[i]->GetBuildTier()>0)
            return true;
    }
    return false;
}

bool Player::ValidBuildingNumbers(QList<int> p_houseNumbers, Property::StreetColor p_streetColor)
{
    if (p_houseNumbers.isEmpty() || !OwnsStreetPartially(p_streetColor))
        return false;

    int min = p_houseNumbers[0];
    int max = p_houseNumbers[0];

    for (int i = 0; i < p_houseNumbers.length(); i++)
    {
        if (p_houseNumbers[i] < min)
            min = p_houseNumbers[i];
        if (p_houseNumbers[i] > max)
            max = p_houseNumbers[i];
    }

    int max_buildings = 5;
    if (OwnsStreetCompletely(p_streetColor))
        max_buildings = 6;

    return (min >= 0 && max <= max_buildings) && (max - min) <= 1;

}

void Player::Die()
{
    m_isAlive=false;
    m_money=0;
    for(int i=0;i<m_properties.length();i++)
    {
        m_properties[i]->SetOwner(NULL);
    }
    m_properties.clear();
    emit(PlayerDied());

}

void Player::AddMoney(int p_amount)
{
    SetMoney(m_money + p_amount);
}

void Player::SetMoney(int p_amount)
{
    m_money = p_amount;
    emit(AmountOfMoneyChanged());
}

void Player::AddProperty(Property *p_property)
{
    m_properties.append(p_property);

    if (OwnsStreetCompletely(p_property->GetColor()))
        RedistributeBuildings(p_property->GetColor());
}

void Player::DeleteProperty(Property *p_property)
{
    for(QList<Property*>::iterator it=m_properties.begin()
        ;it != m_properties.end();it++)
    {
        if(*it==p_property)
        {
            m_properties.erase(it);
            return;
        }
    }
}

int Player::GetMoney() const
{
    return m_money;
}

int Player::GetTotalWorth() const
{
    int total=0;
    // money
    total+=m_money;

    // properties
    for(int i=0;i<m_properties.length();i++)
    {
        // add the BuyPrice of a Property
        total+=m_properties[i]->GetBuyPrice();
        // add building prices on the property
        total+=(m_properties[i]->GetBuildPrice()*m_properties[i]->GetBuildTier());
    }
    return total;
}

void Player::GoToJail(bool p_direction)
{
    if(p_direction){
        SetPosition(JAIL_LOCATION);
        emit(PlayerMustGoToJail());
    }
    else
        m_roundsInJail=0;
    m_inJail=p_direction;
}
