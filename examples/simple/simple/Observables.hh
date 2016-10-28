#pragma once

// include the Identification base class
#include "boca/fastjet/Particle.hh"
// include the Event class
#include "boca/Event.hh"

namespace simple
{


/**
* @brief Simple collection of Observables
*/
// Each Observable is calculated by a function of this class
// Additionally the Tag and the BDT response has to be saved, which is done in the Identification base class
class Observables : public boca::Identification
{

public:

    // The constructor takes the complete event
    Observables(boca::Event const &event);

    // The number of leptons
    int LeptonNumber() const;

    // The number of jets
    int JetNumber() const;

    // The number of bottom jets
    int BottomNumber() const;

    // The sclar sum of the transvers momenta
    boca::Momentum ScalarHt() const;

    // The transverse momentum of the n'th jet
    boca::Momentum JetPt(unsigned number) const;

    // The transverse momentum of the n'th lepton
    boca::Momentum LeptonPt(unsigned number) const;

    // The missing transvser energy
    boca::Energy MissingEt() const;

private:

    // storage for the jets
    std::vector<boca::Jet> jets_;

    // storage for the leptons
    std::vector<boca::Lepton> leptons_;

    // storage for the scalar ht
    boca::Momentum scalar_ht_;

    // storage for the missing et
    boca::Energy missing_et_;

};

}
