#include "streetproperty.h"
#include "player.h"

StreetProperty::StreetProperty(QString& p_inputLine,int p_position) : Property(p_position)
{
    m_buildTier = 0;
    m_isBought = false;

    QStringList strList = p_inputLine.split(" ");

    if(strList[0] == "P")
    {
        m_buyPrice = strList[1].toInt();
        m_buildPrice = strList[2].toInt();

        for (int i = 3; i < 10; i++)
        {
            m_rentPrices << strList[i].toInt();
        }
        // TODO: add street color numbers in the file
        m_streetColor = (StreetColor) strList[10].toInt();
        for (int i = 11; i < strList.length(); i++)
        {
            m_name += strList[i] + " ";
        }

        m_name = m_name.trimmed();

    }
    else
    {
        // the inputLine was not a property
    }
}

int StreetProperty::GetRentPrice() const
{
    int modifier = 1;
    if (m_buildTier == 0)
    {
        if (m_owner->OwnsStreetCompletely(GetColor()))
        {
            modifier = 3;
        }
        else if (m_owner->OwnsStreetPartially(GetColor()))
        {
            modifier = 2;
        }
    }

    return m_rentPrices[m_buildTier] * modifier;
}
