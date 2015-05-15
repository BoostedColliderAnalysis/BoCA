# include "Triplet.hh"

void hanalysis::Triplet::SetSinglet(const fastjet::PseudoJet &singlet)
{
  singlet_ = singlet;
}

void hanalysis::Triplet::Setdoublet(const hanalysis::Doublet &doublet)
{
  doublet_ = doublet;
}

hanalysis::Triplet::Triplet()
{
    Print(kInformation, "Constructor");
}

fastjet::PseudoJet hanalysis::Triplet::singlet() const
{
    return singlet_;
}

hanalysis::Doublet hanalysis::Triplet::doublet() const
{
    return doublet_;
}

hanalysis::Triplet::Triplet(const hanalysis::Doublet &doublet, const fastjet::PseudoJet &singlet)
{
    Print(kInformation, "Constructor");
    SetSinglet(singlet);
    Setdoublet(doublet);
    if (singlet.has_user_info<JetInfo>() && singlet.user_info<JetInfo>().Bdt() != initial_value()) SetBdt(singlet.user_info<JetInfo>().Bdt(),doublet.Bdt());
    SetFlag(doublet.Flag());
}

hanalysis::Triplet::Triplet(const fastjet::PseudoJet &singlet)
{
    Print(kInformation, "Constructor");
    SetSinglet(singlet / 2);
    Setdoublet(Doublet(singlet / 2));
    SetDegenerate();
    if (singlet.has_user_info<JetInfo>() && singlet.user_info<JetInfo>().Bdt() != initial_value()) SetBdt(singlet.user_info<JetInfo>().Bdt());
    else SetBdt(0);
}
