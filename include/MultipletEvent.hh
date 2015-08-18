/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "GlobalObservables.hh"
#include "TwoBody.hh"

namespace boca {

/**
 * @brief An event composed of a multiplet an a singlet made up from the remaining jets
 *
 */
template <typename Multiplet_1>
class MultipletEvent : public boca::TwoBody<Multiplet_1, boca::Singlet> {

public:

    MultipletEvent(const Multiplet_1& multiplet, Event const& event, Jets& jets) {
        global_observables_.SetEvent(event);
        Jets unique_jets;
        for (auto const& jet : jets) if (!multiplet.Overlap(jet)) unique_jets.emplace_back(jet);
        global_observables_.SetJets(unique_jets);
        boca::TwoBody<Multiplet_1, boca::Singlet>::SetMultiplets(multiplet,global_observables_.Singlet());
    }

    Multiplet_1 Multiplet() const
    {
        return boca::TwoBody<Multiplet_1, boca::Singlet>::Multiplet1();
    }

    boca::Singlet Singlet() const
    {
        return boca::TwoBody<Multiplet_1, boca::Singlet>::Multiplet2();
    }

    const boca::GlobalObservables& GlobalObservables() const
    {
        return global_observables_;
    }

private:

    boca::GlobalObservables global_observables_;

};

}


