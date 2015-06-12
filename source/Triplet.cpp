# include "Triplet.hh"

namespace analysis {

Doublet Triplet::Doublet() const
{
    return multiplet_1_;
}

Singlet Triplet::Singlet() const
{
  return multiplet_2_;
}

fastjet::PseudoJet Triplet::SingletJet() const
{
    return multiplet_2_.Jet();
}

}
