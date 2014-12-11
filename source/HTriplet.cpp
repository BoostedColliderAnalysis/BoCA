# include "HTriplet.hh"

hanalysis::HTriplet::HTriplet()
{
    Print(HInformation, "Constructor");
}

// hanalysis::HTriplet::HTriplet(const fastjet::PseudoJet &NewJet1, const fastjet::PseudoJet &NewJet2, const fastjet::PseudoJet &NewJet3)
// {
//
//   Print(HInformation, "Constructor");
//
//   Jet1 = NewJet1;
//   Jet2 = NewJet2;
//   Jet3 = NewJet3;
//   Bdt =1;
//   if(Jet1.has_user_info<HJetInfo>()) if(Jet1.user_info<HJetInfo>().GetBdt() != InitialValue) Bdt *= Jet1.user_info<HJetInfo>().GetBdt();
//   if(Jet2.has_user_info<HJetInfo>()) if(Jet2.user_info<HJetInfo>().GetBdt() != InitialValue) Bdt *= Jet2.user_info<HJetInfo>().GetBdt();
//   if(Jet3.has_user_info<HJetInfo>()) if(Jet3.user_info<HJetInfo>().GetBdt() != InitialValue) Bdt *= Jet3.user_info<HJetInfo>().GetBdt();
//
// }

// hanalysis::HTriplet::HTriplet(const fastjet::PseudoJet& NewJet, const hanalysis::HDoublet& Pair)
// {
//
//   Print(HInformation, "Constructor");
//
//   Jet1 = NewJet;
//   Jet2 = Pair.GetLepton();
//   Jet3 = Pair.GetJet();
//   Bdt = Pair.GetBdt();
//   Tag = Pair.GetTag();
//
// }

hanalysis::HTriplet::HTriplet(const HDoublet &NewDoublet, const fastjet::PseudoJet &NewJet)
{

    Print(HInformation, "Constructor");

    Jet = NewJet;
    Doublet = NewDoublet;
    Bdt = NewDoublet.GetBdt();
    Tag = NewDoublet.GetTag();

}

hanalysis::HTriplet::~HTriplet()
{

    Print(HInformation, "Destructor");

}
