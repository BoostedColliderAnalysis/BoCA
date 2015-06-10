# include "Triplet.hh"

analysis::Doublet analysis::Triplet::Doublet() const
{
    return multiplet_1_;
}

analysis::Singlet analysis::Triplet::Singlet() const
{
  return multiplet_2_;
}

fastjet::PseudoJet analysis::Triplet::SingletJet() const
{
    return multiplet_2_.Jet();
}
