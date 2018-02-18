#include "railroad.h"

RailRoad::RailRoad(const QString& p_inputLine,int p_position): Property(p_position)
{

    m_rentPrices << 25 << 50 << 100 << 200;
    m_buyPrice = 200;
    m_buildPrice = 100;
    m_streetColor = Property::RAILROAD;
    m_maxBuildTier=1;

    QStringList strList = p_inputLine.split(" ");

    if(strList[0] == "R")
    {
        for (int i = 1; i < strList.length(); i++)
        {
            m_name += strList[i] + " ";
        }
        m_name = m_name.trimmed();
    }
}

int RailRoad::GetRentPrice() const
{
    int numberOfProperties=m_owner->GetAmountOfPropertiesOwned(m_streetColor);
    int rentPrice= m_rentPrices[numberOfProperties-1];
    if(m_buildTier==1)
        return rentPrice*2;
    return rentPrice;
}
