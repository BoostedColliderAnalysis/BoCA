#pragma once

#include "boca/branch/Bdt.hh"

namespace toppartner
{

using namespace boca;

namespace branch
{

/**
 * @brief Class for saving event informations to root
 *
 */
class NewEvent : public boca::branch::Bdt
{
public:
    NewEvent();

    float signature_bdt;
    float global_bdt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Bdt::Fill(multiplet);
        signature_bdt = multiplet.Signature().Bdt();
        global_bdt = multiplet.GlobalObservables().Bdt();
    }
    Observables Variables();

private:
    ClassDef(NewEvent, 1)
};

}

}
