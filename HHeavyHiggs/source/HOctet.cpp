# include "HOctet.hh"
// # include "HTagPrivate.hh"

HOctet::HOctet(const hanalysis::HSextet &NewSextet, const hanalysis::HDoublet &NewDoublet)
{
    SextetM = NewSextet;
    DoubletM = NewDoublet;
    SetBdt(SextetM.Bdt(),DoubletM.Bdt());
    SetTag(SextetM.Tag(),DoubletM.Tag());
}

HOctet::HOctet(const hanalysis::HSextet &NewSextet, const hanalysis::HDoublet &NewDoublet, const HEventStruct &NewEventStruct)
{
    SextetM = NewSextet;
    DoubletM = NewDoublet;
    EventStructM = NewEventStruct;
    SetBdt(SextetM.Bdt(),DoubletM.Bdt());
    SetTag(SextetM.Tag(),DoubletM.Tag());
}
