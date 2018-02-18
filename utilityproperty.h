// Made by Louis Hendrikx

#ifndef UTILITYPROPERTY_H
#define UTILITYPROPERTY_H

#include "property.h"
#include "player.h"

class UtilityProperty : public Property
{
public:
    UtilityProperty(QString& p_inputLine,int p_position);
    virtual int GetRentPrice() const;
};

#endif // UTILITYPROPERTY_H
