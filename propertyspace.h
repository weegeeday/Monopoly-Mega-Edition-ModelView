// Made by Arthur Jansen

#ifndef PROPERTYSPACE_H
#define PROPERTYSPACE_H
#include "space.h"
#include "property.h"

class PropertySpace : public Space
{
    Q_OBJECT
public:
    PropertySpace(Property* p_property);
    //see abstract class Space
    virtual void DoAction(Player* p_player);

private:
    Property* m_property;

};

#endif // PROPERTYSPACE_H
