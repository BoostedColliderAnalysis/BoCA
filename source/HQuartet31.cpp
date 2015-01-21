# include "HQuartet31.hh"
# include "HTagPrivate.hh"

hanalysis::HQuartet31::HQuartet31(const HTriplet &NewTriplet, const fastjet::PseudoJet &NewSinglet)
{
    Print(HInformation, "Constructor");
    Triplet = NewTriplet;
    Singlet = NewSinglet;
    if (Singlet.has_user_info<HJetInfo>()) {
      TagPrivate->Bdt = (Triplet.Bdt() + Singlet.user_info<HJetInfo>().Bdt()) / 2;
      TagPrivate->Tag = Triplet.Tag() * Singlet.user_info<HJetInfo>().Tag();
    }
}

hanalysis::HQuartet31::~HQuartet31()
{

}
