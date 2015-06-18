# include "Quartet31.hh"

namespace analysis
{

Triplet Quartet31::Triplet() const
{
    return Multiplet1();
}

fastjet::PseudoJet Quartet31::SingletJet()const
{
    return Multiplet2().Jet();
}

Singlet Quartet31::Singlet()const
{
    return Multiplet2();
}

}
