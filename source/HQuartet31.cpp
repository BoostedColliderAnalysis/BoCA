# include "HQuartet31.hh"

hanalysis::HQuartet31::HQuartet31(const HTriplet &NewTriplet, const fastjet::PseudoJet &NewSinglet)
{
    Print(HInformation, "Constructor");
    Triplet = NewTriplet;
    Singlet = NewSinglet;
    if(Singlet.has_user_info<HJetInfo>()) {
        Bdt = Triplet.GetBdt() * Singlet.user_info<HJetInfo>().GetBdt();
        Tag = Triplet.GetTag() * Singlet.user_info<HJetInfo>().GetTag();
    }
}

hanalysis::HQuartet31::~HQuartet31()
{

}
