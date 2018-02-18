#include "propertyspace.h"

PropertySpace::PropertySpace(Property* p_property)
{
    m_property = p_property;
}

void PropertySpace::DoAction(Player *p_player)
{

    if(m_property->IsAvailable())
    {
        emit(AvailablePropertyVisited(m_property));
    }
    else if (p_player != m_property->GetOwner() && !m_property->GetInMortgage())
    {

        // pay rent
        Player * propertyOwner=m_property->GetOwner();
        //bool partiallyOwned = propertyOwner->OwnsStreetPartially(m_property->GetColor());
        //bool completelyOwned = propertyOwner->OwnsStreetCompletely(m_property->GetColor());
        int rentAmount = m_property->GetRentPrice();

        // if the player comes from the chance card "Go to nearest rail road" it needs to pay double
        if(p_player->ComesFromCard())
        {
            p_player->SetFromCard(false);
            rentAmount*=2;
        }
        if(!p_player->PayPlayer(propertyOwner,rentAmount))
        {
            // player has nog enough money to pay the propertyOwner
            // TODO: ability to sell propertys to get enough money to pay
        }

        emit(RentPayed(rentAmount, m_property));

    }

}
