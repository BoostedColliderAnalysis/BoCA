#pragma once

#include "boca/branch/Bdt.hh"
#include "boca/branch/EventShapesBase.hh"
#include "boca/branch/GlobalBase.hh"


namespace toppartner
{

namespace branch
{

/**
 * @brief Class for saving event informations to root
 *
 */
class NewEvent4 : public boca::branch::Bdt, boca::branch::GlobalBase, boca::branch::EventShapesBase
{
public:
    NewEvent4();
    float signature_bdt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Bdt::Fill(multiplet);
        GlobalBase::Fill(multiplet.GlobalObservables());
        EventShapesBase::Fill(multiplet);
        signature_bdt = multiplet.Signature().Bdt();
    }
    boca::Observables Variables();
    boca::Observables Spectators();

private:
    ClassDef(NewEvent4, 1)
};

}

}
