# include "Triplet.hh"

namespace analysis
{

Doublet Triplet::Doublet() const
{
    return Multiplet1();
}

Singlet Triplet::Singlet() const
{
    return Multiplet2();
}

fastjet::PseudoJet Triplet::SingletJet() const
{
    return Multiplet2().Jet();
}

}
