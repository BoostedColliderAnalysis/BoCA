#pragma once

#include "boca/branch/GlobalBase.hh"
#include "include/branch/SignatureSingleHadronic.hh"

namespace toppartner
{

namespace branch
{

/**
 * @brief Class for saving event informations to root
 *
 */
class CompleteBranch : public SignatureSingleHadronicBranch, boca::branch::GlobalBase
{
public:
    CompleteBranch();

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        SignatureSingleHadronicBranch::Fill(multiplet.Signature());
        GlobalBase::Fill(multiplet.GlobalObservables());
    }
    boca::Observables Variables();
    boca::Observables Spectators();

private:
    ClassDef(CompleteBranch, 1)
};

}

}
