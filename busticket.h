// Made by Louis Hendrikx

#ifndef BUSTICKET_H
#define BUSTICKET_H

#include <QJsonObject>
#include <QJsonArray>

class BusTicket
{
public:
    BusTicket();
    /**
     * @brief SetLabeled: sets if the busticket is labeled or not
     * @param p_label: the value labeled needs to be
     */
    void SetLabeled(bool p_label);
    /**
     * @brief GetLabeled: gives back if it is a labeled card or not
     * @return : the bool if it is labeled or not
     */
    bool GetLabeled()const;

    /**
     * WriteToFile and ReadFromFile made by Arthur Jansen
     */
    void WriteToFile(QJsonObject& json) const;
    void ReadFromFile(const QJsonObject& json);

private:
    bool m_labeled=false;
};

#endif // BUSTICKET_H
