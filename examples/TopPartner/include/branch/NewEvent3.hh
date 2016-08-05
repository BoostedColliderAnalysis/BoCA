#pragma once

#include "boca/branch/Bdt.hh"
#include "boca/branch/GlobalBase.hh"

namespace toppartner
{

namespace branch
{

/**
 * @brief Class for saving event informations to root
 *
 */
class NewEvent3 : public boca::branch::Bdt, boca::branch::GlobalBase
{
public:
    NewEvent3();

    float signature_bdt;
    float veto_bdt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Bdt::Fill(multiplet);
        GlobalBase::Fill(multiplet.GlobalObservables());
        signature_bdt = multiplet.Signature().Bdt();
        veto_bdt = multiplet.Signature().VetoBdt();
    }
    boca::Observables Variables();
    boca::Observables Spectators();

private:
    ClassDef(NewEvent3, 1)
};

}

}
