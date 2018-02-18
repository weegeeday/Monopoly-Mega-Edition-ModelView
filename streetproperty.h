// Made by Louis Hendrikx

#ifndef STREETPROPERTY_H
#define STREETPROPERTY_H

#include "property.h"

class StreetProperty : public Property
{
public:
    StreetProperty(QString& p_inputLine, int p_position);
    // see Property class
    virtual int GetRentPrice() const;

};

#endif // STREETPROPERTY_H
