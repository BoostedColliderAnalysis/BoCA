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

// bool analysis::Triplet::Overlap() const
// {
//   if(Doublet().Overlap(SingletJet())) return true;
//   return false;
// }
//
//
// bool analysis::Triplet::Overlap(const fastjet::PseudoJet &jet) const
// {
//   if(Doublet().Overlap(jet)) return true;
//   if(Singlet().Overlap(jet)) return true;
//   return false;
// }
