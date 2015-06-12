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
        analysis::Multiplet<Multiplet_1, analysis::Singlet>::multiplet_1_ = multiplet;
        global_observables_.SetEvent(event,jets);
        Jets unique_jets;
        for (const auto jet : jets) if (!analysis::Multiplet<Multiplet_1, analysis::Singlet>::Multiplet1().Overlap(jet)) unique_jets.push_back(jet);
        global_observables_.SetJets(unique_jets);
        analysis::Multiplet<Multiplet_1, analysis::Singlet>::multiplet_2_ = global_observables_.Singlet();
    }

    Multiplet_1 Multiplet() const {
      return analysis::Multiplet<Multiplet_1, analysis::Singlet>::multiplet_1_;
    }

    analysis::Singlet Singlet() const {
      return analysis::Multiplet<Multiplet_1, analysis::Singlet>::multiplet_2_;
    }

    const analysis::GlobalObservables & GlobalObservables() const{
      return global_observables_;
    }

protected:

    virtual inline std::string ClassName() const {
        return "MultipletEvent";
    }

private:

    analysis::GlobalObservables global_observables_;

};

}

