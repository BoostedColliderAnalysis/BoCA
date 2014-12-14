# include "HTriplet.hh"

hanalysis::HTriplet::HTriplet()
{
    Print(HInformation, "Constructor");
}

hanalysis::HTriplet::HTriplet(const HDoublet &NewDoublet, const fastjet::PseudoJet &NewJet)
{

    Print(HInformation, "Constructor");

    Jet = NewJet;
    Doublet = NewDoublet;
    if(Jet.has_user_info<HJetInfo>()) if(Jet.user_info<HJetInfo>().GetBdt() != InitialValue) Bdt = Jet.user_info<HJetInfo>().GetBdt() * Doublet.GetBdt();
}

hanalysis::HTriplet::~HTriplet()
{

    Print(HInformation, "Destructor");

}
