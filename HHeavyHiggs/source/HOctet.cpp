# include "HOctet.hh"
// # include "HTagPrivate.hh"

HOctet::HOctet(const hanalysis::HSextet &NewSextet, const hanalysis::Doublet &Newdoublet)
{
    SextetM = NewSextet;
    doubletM = Newdoublet;
    SetBdt(SextetM.Bdt(),doubletM.Bdt());
    SetTag(SextetM.Tag(),doubletM.Tag());
}

// HOctet::HOctet(const hanalysis::HSextet &NewSextet, const hanalysis::Doublet &Newdoublet, const HEventStruct &NewEventStruct)
// {
//     SextetM = NewSextet;
//     doubletM = Newdoublet;
//     EventStructM = NewEventStruct;
//     SetBdt(SextetM.Bdt(),doubletM.Bdt());
//     SetTag(SextetM.Tag(),doubletM.Tag());
// }
