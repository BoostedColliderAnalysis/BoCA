# include "Quartet31.hh"

namespace analysis {

Triplet Quartet31::Triplet() const
{
    return multiplet_1_;
}

fastjet::PseudoJet Quartet31::SingletJet()const
{
    return multiplet_2_.Jet();
}

Singlet Quartet31::Singlet()const
{
    return multiplet_2_;
}

}
