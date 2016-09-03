#pragma once

#include "boca/branch/GlobalBase.hh"
#include "toppartner/branch/SignatureSingleHadronic.hh"

namespace toppartner
{

namespace branch
{

/**
 * @brief Class for saving event informations to root
 *
 */
class Complete : public SignatureSingleHadronicBranch, boca::branch::GlobalBase
{
public:
    Complete();

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        SignatureSingleHadronicBranch::Fill(multiplet.Signature());
        GlobalBase::Fill(multiplet.GlobalObservables());
    }
    boca::Observables Variables();
    boca::Observables Spectators();

private:
    ClassDef(Complete, 1)
};

}

using CompleteBranch = branch::Complete;

}
