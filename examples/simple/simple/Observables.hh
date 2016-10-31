#pragma once

// include the Identification base class
#include "boca/fastjet/Particle.hh"
// include the Event class
#include "boca/Event.hh"

namespace simple
{

// use members of boca::units without prefix
using namespace boca::units;


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
    Momentum ScalarHt() const;

    // The transverse momentum of the n'th jet
    Momentum JetPt(unsigned number) const;

    // The transverse momentum of the n'th lepton
    Momentum LeptonPt(unsigned number) const;

    // The missing transvser energy
    Energy MissingEt() const;

private:

    // storage for the jets
    std::vector<boca::Jet> jets_;

    // storage for the leptons
    std::vector<boca::Lepton> leptons_;

    // storage for the scalar ht
    Momentum scalar_ht_;

    // storage for the missing et
    Energy missing_et_;

};

}
