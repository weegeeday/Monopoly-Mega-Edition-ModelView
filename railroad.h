// Made by Louis Hendrikx

#ifndef RAILROAD_H
#define RAILROAD_H

#include <QString>
#include <QList>

#include "property.h"
#include "player.h"

class RailRoad : public Property
{
public:
    RailRoad(const QString& p_inputLine,int p_position);
    virtual int GetRentPrice() const;


private:

};

#endif // RAILROAD_H
