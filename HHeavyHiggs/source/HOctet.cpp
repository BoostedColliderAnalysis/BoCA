# include "HOctet.hh"

HOctet::HOctet(const hanalysis::HSextet &NewSextet, const fastjet::PseudoJet &NewJet1, const fastjet::PseudoJet &NewJet2)
{
    Sextet = NewSextet;
    Jet1 = NewJet1;
    Jet2 = NewJet2;
    if (Jet1.has_user_info<hanalysis::HJetInfo>() && Jet1.has_user_info<hanalysis::HJetInfo>()) {
      Bdt = Sextet.GetBdt() * Jet1.user_info<hanalysis::HJetInfo>().GetBdt() * Jet2.user_info<hanalysis::HJetInfo>().GetBdt();
      Tag = Sextet.GetTag() * Jet1.user_info<hanalysis::HJetInfo>().GetTag() * Jet2.user_info<hanalysis::HJetInfo>().GetTag();
    }
}
