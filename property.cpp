#include "property.h"
#include "player.h"

int Property::GetPropertyCount(Property::StreetColor color)
{
    if (color == PURPLE || color == DARK_BLUE)
        return 3;
    return 4;
}

QString Property::ToString(Property::StreetColor p_color)
{
    switch (p_color)
    {
        case Property::PURPLE:
            return "Purple";
        case Property::LIGHT_BLUE:
            return "Light blue";
        case Property::PINK:
            return "Pink";
        case Property::ORANGE:
            return "Orange";
        case Property::RED:
            return "Red";
        case Property::YELLOW:
            return "Yellow";
        case Property::GREEN:
            return "Green";
        case Property::DARK_BLUE:
            return "Dark blue";
        case Property::RAILROAD:
            return "Railroad";
        default:
            return "";
    }
}

Property::StreetColor Property::FromString(QString p_color)
{
    if (p_color == "Purple")
        return PURPLE;
    else if (p_color == "Light blue")
        return LIGHT_BLUE;
    else if (p_color ==  "Pink")
        return PINK;
    else if (p_color ==  "Orange")
        return ORANGE;
    else if (p_color ==  "Red")
        return RED;
    else if (p_color ==  "Yellow")
        return YELLOW;
    else if (p_color ==  "Green")
        return GREEN;
    else if (p_color ==  "Dark blue")
        return DARK_BLUE;
    else if(p_color == "Railroad")
        return RAILROAD;
}

Property::Property(int p_location)
{
    m_location=p_location;
}

int Property::GetBuyPrice() const
{
    return m_buyPrice;
}

int Property::GetBuildPrice() const
{
    return m_buildPrice;
}

int Property::GetMortgagePrice() const
{
    return (int)(m_buyPrice / 2);
}

int Property::GetOutOfMortgagePrice() const
{
    return (int)(m_buyPrice/2)*1.1;
}

int Property::GetPosition() const
{
    return m_location;
}

void Property::SetBuildTier(int p_buildTier)
{
    if (p_buildTier <= m_maxBuildTier && p_buildTier >= 0)
    {
        m_buildTier = p_buildTier;
        emit(BuildTierChanged(p_buildTier,m_location));
    }
}

int Property::GetBuildTier() const
{
    return m_buildTier;
}

bool Property::IsAvailable() const
{
    return !m_isBought;
}

void Property::SetInMortgage(bool p_inMortage)
{
    m_isInMortgage = p_inMortage;
}

bool Property::GetInMortgage() const
{
    return m_isInMortgage;
}

QString Property::GetName() const
{
    return m_name;
}

Player *Property::GetOwner() const
{
    return m_owner;
}

void Property::SetOwner(Player *p_newOwner)
{
    m_owner=p_newOwner;
    if(m_owner==NULL)
    {
        m_isBought = false;
        m_isInMortgage = false;
        m_buildTier=0;
    }
    else
    {
        if(p_newOwner->GetBuildOnStreet(m_streetColor) && m_isInMortgage){
            p_newOwner->Pay(GetOutOfMortgagePrice());
            SetInMortgage(false);
        }
        m_isBought=true;
        m_owner->AddProperty(this);
    }
}

Property::StreetColor Property::GetColor() const
{
    return m_streetColor;
}

int Property::GetMaxBuildTier() const
{
    return m_maxBuildTier;
}

void Property::WriteToFile(QJsonObject &json) const
{
    json["maxBuildTier"] = m_maxBuildTier;
    json["buyPrice"] = m_buyPrice;
    json["buildPrice"] = m_buildPrice;

    json["buildTier"] = m_buildTier;
    json["name"] = m_name;
    if (m_owner != NULL)
        json["owner"] = m_owner->GetNumber();
    json["streetColor"] = Property::ToString(m_streetColor);
    json["location"] = m_location;

    QJsonArray rentPrices;
    for (int i = 0; i < m_rentPrices.length(); i++)
    {
        QJsonObject price;
        price["value"] = m_rentPrices[i];
        rentPrices.append(price);
    }
    json["rentPrices"] = rentPrices;

}


void Property::ReadFromFile(const QJsonObject &json, QList<Player*> p_players)
{

    m_maxBuildTier = json["maxBuildTier"].toInt();
    m_buyPrice = json["buyPrice"].toInt();
    m_buildPrice = json["buildPrice"].toInt();
    m_name = json["name"].toString();
    SetBuildTier(json["buildTier"].toInt());
    if(json.contains("owner"))
    {
        int playerNumber = json["owner"].toInt();
        m_owner = p_players[playerNumber];
        p_players[playerNumber]->AddProperty(this);
        m_isBought = true;
    }
    m_streetColor = Property::FromString(json["streetColor"].toString());

    QJsonArray rentPrices = json["rentPrices"].toArray();
    for (int i = 0; i < rentPrices.size(); i++)
    {
        QJsonObject price = rentPrices[i].toObject();
        m_rentPrices.append(price["value"].toInt());
    }


}
