#include "utilityproperty.h"

UtilityProperty::UtilityProperty(QString& p_inputLine,int p_position): Property(p_position)
{
    m_buyPrice=150;
    m_rentPrices << 4 << 10 << 20;
    m_streetColor=Property::UTILITY;

    QStringList strList = p_inputLine.split(" ");

    if(strList[0] == "U")
    {
        for (int i = 1; i < strList.length(); i++)
        {
            m_name += strList[i] + " ";
        }
        m_name = m_name.trimmed();
    }
}

int UtilityProperty::GetRentPrice() const
{
    if(m_owner->GetAmountOfPropertiesOwned(Property::UTILITY)==1)
    {
        return m_owner->GetTotalThrown()*m_rentPrices[0];
    }
    else if(m_owner->GetAmountOfPropertiesOwned(Property::UTILITY)==2)
    {
        return m_owner->GetTotalThrown()*m_rentPrices[1];
    }
    else
        return m_owner->GetTotalThrown()*m_rentPrices[2];
}
