/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "GlobalObservables.hh"
#include "multiplets/TwoBody.hh"

namespace boca
{

/**
 * @brief An event composed of a multiplet an a singlet made up from the remaining jets
 *
 */
template <typename Multiplet_1>
class MultipletEvent : public boca::TwoBody<Multiplet_1, boca::Singlet>
{

public:

    MultipletEvent(Multiplet_1 const& multiplet, Event const& event, std::vector<Jet>& jets) {
        global_observables_.SetEvent(event);
        global_observables_.SetJets(CopyIf(jets, [&](Jet const & jet) {
            return !multiplet.Overlap(jet);
        }));
        TwoBody<Multiplet_1, boca::Singlet>::SetMultiplet1(multiplet);
        TwoBody<Multiplet_1, boca::Singlet>::SetMultiplet2(global_observables_.Singlet());
    }

    MultipletEvent(Multiplet_1 const& multiplet, std::vector<Jet>& jets, GlobalObservables const& global_observables) {
        global_observables_ = global_observables;
        global_observables_.SetJets(jets, CopyIf([&](Jet const & jet) {
          return !multiplet.Overlap(jet);
        }));
        TwoBody<Multiplet_1, boca::Singlet>::SetMultiplet1(multiplet);
        TwoBody<Multiplet_1, boca::Singlet>::SetMultiplet2(global_observables_.Singlet());
    }

    Multiplet_1 Signature() const {
        return boca::TwoBody<Multiplet_1, boca::Singlet>::Multiplet1();
    }

    boca::Singlet Rest() const {
        return boca::TwoBody<Multiplet_1, boca::Singlet>::Multiplet2();
    }

    const boca::GlobalObservables& GlobalObservables() const {
        return global_observables_;
    }

private:

    boca::GlobalObservables global_observables_;

};

}



