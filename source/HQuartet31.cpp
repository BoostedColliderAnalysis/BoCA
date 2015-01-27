# include "HQuartet31.hh"
# include "HTagPrivate.hh"

class hanalysis::HQuartet31Private : public HTagPrivate
{

public:

//     HQuartet31Private() {}

    void SetTriplet(const HTriplet &NewTriplet);

    void SetSinglet(const fastjet::PseudoJet &NewSinglet);

    HTriplet Triplet;

    fastjet::PseudoJet Singlet;

};

void hanalysis::HQuartet31Private::SetTriplet(const HTriplet &NewTriplet)
{
    Triplet = NewTriplet;
}

void hanalysis::HQuartet31Private::SetSinglet(const fastjet::PseudoJet &NewSinglet)
{
    Singlet = NewSinglet;
}

hanalysis::HQuartet31::HQuartet31(HQuartet31Private &NewQuartet31Private) : HTag(NewQuartet31Private)
{
    Print(HInformation, "Constructor");
}

hanalysis::HQuartet31::HQuartet31() : hanalysis::HTag(*new HQuartet31Private)
{
    Print(HInformation, "Constructor");
}

hanalysis::HQuartet31::HQuartet31(const HTriplet &NewTriplet, const fastjet::PseudoJet &NewSinglet) : hanalysis::HTag(*new HQuartet31Private)
{
    Print(HInformation, "Constructor");
    static_cast<HQuartet31Private *>(TagPrivate)->SetTriplet(NewTriplet);
    static_cast<HQuartet31Private *>(TagPrivate)->SetSinglet(NewSinglet);
    if (Singlet().has_user_info<HJetInfo>()) {
        TagPrivate->Bdt = (Triplet().Bdt() + Singlet().user_info<HJetInfo>().Bdt()) / 2;
        TagPrivate->Tag = Triplet().Tag() * Singlet().user_info<HJetInfo>().Tag();
    }
}

hanalysis::HQuartet31::~HQuartet31()
{
    Print(HInformation, "Destructor");
}

hanalysis::HTriplet hanalysis::HQuartet31::Triplet() const
{
    return static_cast<HQuartet31Private *>(TagPrivate)->Triplet;
}

fastjet::PseudoJet hanalysis::HQuartet31::Singlet()const
{
    return static_cast<HQuartet31Private *>(TagPrivate)->Singlet;
}
