#pragma once

#include "boca/branch/Bdt.hh"
#include "boca/branch/GlobalBase.hh"

namespace boca
{

namespace branch
{

/**
 * @brief Class for saving event informations to root
 *
 */
class Event : public boca::branch::Bdt, boca::branch::GlobalBase
{
public:
    Event();

    float signature_bdt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Bdt::Fill(multiplet);
        GlobalBase::Fill(multiplet.GlobalObservables());
        signature_bdt = multiplet.Signature().Bdt();
    }
    Observables Variables();
    Observables Spectators();

private:
    ClassDef(Event, 1)
};

}

}
