# include "Triplet.hh"

void analysis::Triplet::SetSinglet(const fastjet::PseudoJet &singlet)
{
  singlet_ = singlet;
}

void analysis::Triplet::Setdoublet(const analysis::Doublet &doublet)
{
  doublet_ = doublet;
}

analysis::Triplet::Triplet()
{
    Print(kInformation, "Constructor");
}

fastjet::PseudoJet analysis::Triplet::singlet() const
{
    return singlet_;
}

analysis::Doublet analysis::Triplet::doublet() const
{
    return doublet_;
}

analysis::Triplet::Triplet(const analysis::Doublet &doublet, const fastjet::PseudoJet &singlet)
{
    Print(kInformation, "Constructor");
    SetSinglet(singlet);
    Setdoublet(doublet);
    if (singlet.has_user_info<JetInfo>() && singlet.user_info<JetInfo>().Bdt() != initial_value()) SetBdt(singlet.user_info<JetInfo>().Bdt(),doublet.Bdt());
    SetFlag(doublet.Flag());
}

analysis::Triplet::Triplet(const fastjet::PseudoJet &singlet)
{
    Print(kInformation, "Constructor");
    SetSinglet(singlet / 2);
    Setdoublet(Doublet(singlet / 2));
    SetDegenerate();
    if (singlet.has_user_info<JetInfo>() && singlet.user_info<JetInfo>().Bdt() != initial_value()) SetBdt(singlet.user_info<JetInfo>().Bdt());
    else SetBdt(0);
}
