# include "HOctet.hh"
# include "HTagPrivate.hh"

HOctet::HOctet(const hanalysis::HSextet &NewSextet, const hanalysis::HDoublet &NewDoublet)
{
    SextetM = NewSextet;
    DoubletM = NewDoublet;
    TagPrivate->Bdt = (SextetM.Bdt() + DoubletM.Bdt()) / 2;
    TagPrivate->Tag = SextetM.Tag() * DoubletM.Tag();
}

HOctet::HOctet(const hanalysis::HSextet &NewSextet, const hanalysis::HDoublet &NewDoublet, const HEventStruct &NewEventStruct)
{
    SextetM = NewSextet;
    DoubletM = NewDoublet;
    EventStructM = NewEventStruct;
    TagPrivate->Bdt = (SextetM.Bdt() + DoubletM.Bdt()) / 2;
    TagPrivate->Tag = SextetM.Tag() * DoubletM.Tag();
}
