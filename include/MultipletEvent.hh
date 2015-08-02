#pragma once

#include "GlobalObservables.hh"
#include "TwoBody.hh"

namespace analysis {

/**
 * @brief An event composed of a multiplet an a singlet made up from the remaining jets
 *
 */
template <typename Multiplet_1>
class MultipletEvent : public analysis::TwoBody<Multiplet_1, analysis::Singlet> {

public:

    MultipletEvent(const Multiplet_1& multiplet, const Event& event, Jets& jets) {
        global_observables_.SetEvent(event);
        Jets unique_jets;
        for (const auto &jet : jets) if (!multiplet.Overlap(jet)) unique_jets.emplace_back(jet);
        global_observables_.SetJets(unique_jets);
        analysis::TwoBody<Multiplet_1, analysis::Singlet>::SetMultiplets(multiplet,global_observables_.Singlet());
    }

    Multiplet_1 Multiplet() const
    {
        return analysis::TwoBody<Multiplet_1, analysis::Singlet>::Multiplet1();
    }

    analysis::Singlet Singlet() const
    {
        return analysis::TwoBody<Multiplet_1, analysis::Singlet>::Multiplet2();
    }

    const analysis::GlobalObservables& GlobalObservables() const
    {
        return global_observables_;
    }

private:

    analysis::GlobalObservables global_observables_;

};

}


