# pragma once

# include "Multiplet.hh"
# include "GlobalObservables.hh"

namespace analysis
{

/**
 * @brief An evnt composed of a multiplet an a singlet made up from the remaining jets
 *
 */
template <typename Multiplet_1>
class MultipletEvent : public analysis::Multiplet<Multiplet_1, analysis::Singlet>
{

public:

    MultipletEvent(const Multiplet_1 &multiplet, Event &event, Jets &jets) {
        analysis::Multiplet<Multiplet_1, analysis::Singlet>::SetMultiplet1(multiplet);
        global_observables_.SetEvent(event,jets);
        Jets unique_jets;
        for (const auto jet : jets) if (!analysis::Multiplet<Multiplet_1, analysis::Singlet>::Multiplet1().Overlap(jet)) unique_jets.emplace_back(jet);
        global_observables_.SetJets(unique_jets);
        analysis::Multiplet<Multiplet_1, analysis::Singlet>::SetMultiplet2(global_observables_.Singlet());
    }

    Multiplet_1 Multiplet() const {
      return analysis::Multiplet<Multiplet_1, analysis::Singlet>::Multiplet1();
    }

    analysis::Singlet Singlet() const {
      return analysis::Multiplet<Multiplet_1, analysis::Singlet>::Multiplet2();
    }

    const analysis::GlobalObservables & GlobalObservables() const{
      return global_observables_;
    }

protected:

    virtual  std::string ClassName() const {
        return "MultipletEvent";
    }

private:

    analysis::GlobalObservables global_observables_;

};

}

