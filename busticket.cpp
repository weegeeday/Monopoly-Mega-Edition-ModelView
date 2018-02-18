#include "busticket.h"

BusTicket::BusTicket()
{

}

void BusTicket::SetLabeled(bool p_label)
{
    m_labeled=p_label;
}

bool BusTicket::GetLabeled() const
{
    return m_labeled;
}

void BusTicket::WriteToFile(QJsonObject &json) const
{
    json["labeled"] = m_labeled;
}

void BusTicket::ReadFromFile(const QJsonObject &json)
{
    m_labeled = json["labeled"].toBool();
}
