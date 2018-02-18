// Made by Louis Hendrikx

#ifndef PROPERTY_H
#define PROPERTY_H

#include <QVector>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QObject>

class Player;

class Property: public QObject
{
    Q_OBJECT
public:
    enum StreetColor
    {
        PURPLE =        0,
        LIGHT_BLUE =    1,
        PINK =          2,
        ORANGE =        3,
        RED =           4,
        YELLOW =        5,
        GREEN =         6,
        DARK_BLUE =     7,
        RAILROAD =      8,
        UTILITY=        9
    };

    static int GetPropertyCount(StreetColor color);
    static QString ToString(StreetColor p_color);
    static StreetColor FromString(QString p_color);

    Property(int p_location);

    int GetBuyPrice() const;
    int GetBuildPrice() const;
    /**
     * @brief GetMortgagePrice: Gives the mortgage price (buyprice/2)
     * @return
     */
    int GetMortgagePrice() const;
    /**
     * @brief GetOutOfMortgagePrice: gives back the mortage price + 10% of mortgage costs
     * @return : the price
     */
    int GetOutOfMortgagePrice() const;
    int GetPosition()const;

    /**
     * @brief GetRentPrice: gets te rent price with the current build tier
     * @return
     */
    virtual int GetRentPrice() const = 0;

    /**
     * @brief SetBuildTier: updates the build tier level
     * @param p_buildTier: the value bield tier needs to be
     */
    void SetBuildTier(int p_buildTier);

    int GetBuildTier() const;

    /**
     * @brief IsAvailable:gives if the property is still available
     * @return
     */
    bool IsAvailable() const;

    /**
     * @brief SetInMortgage: sets the property in mortgage or not mortgage
     * @param p_inMortage: bool if it needs to be mortgaged
     */
    void SetInMortgage(bool p_inMortage);
    bool GetInMortgage() const;

    /**
     * @brief GetName: gives the name of the property
     * @return : a QString with the name
     */
    QString GetName() const;

    /**
     * @brief GetOwner: gives the current owner of the property
     * @return : the Player * of the current owner
     */
    Player* GetOwner() const;
    /**
     * @brief SetOwner: setter for the Owner of the property
     * @param p_newOwner: the player who needs to be the new owner
     */
    void SetOwner(Player *p_newOwner);

    StreetColor GetColor() const;
    int GetMaxBuildTier()const;

    /**
     * WriteToFile and ReadFromFile made by Arthur Jansen
     */
    void WriteToFile(QJsonObject& json) const;
    void ReadFromFile(const QJsonObject& json, QList<Player*> p_players);
signals:
    void BuildTierChanged(int p_numberOfHouses, int p_location);
protected:
    int m_maxBuildTier = 6;

    int m_buyPrice;
    int m_buildPrice; // Price to build a house/hotel/skyscraper
    QVector<int> m_rentPrices; // Rent prices, index: amount of houses (5 = hotel, 6 = skyscraper)

    int m_buildTier = 0; // Amount of houses up to 4, 5 = hotel, 6 = skyscraper

    bool m_isBought = false;
    bool m_isInMortgage = false;

    QString m_name;

    Player* m_owner = NULL;

    StreetColor m_streetColor;
    int m_location;
};

#endif // PROPERTY_H
