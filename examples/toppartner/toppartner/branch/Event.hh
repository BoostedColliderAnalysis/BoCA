#pragma once

#include "boca/branch/Event.hh"

namespace toppartner
{

/**
* @brief Branches
*
*/
namespace branch
{

/**
 * @brief Class for saving event informations to root
 *
 */
class Event : public boca::branch::Event
{
public:
    Event();

    float veto_bdt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        boca::branch::Event::Fill(multiplet);
        veto_bdt = multiplet.Signature().ExtraInfo();
    }
    boca::Observables Variables();

private:
    ClassDef(Event, 1)
};

}

}
