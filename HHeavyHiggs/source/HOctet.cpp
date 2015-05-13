# include "HOctet.hh"
// # include "HTagPrivate.hh"

HOctet::HOctet(const hanalysis::HSextet &NewSextet, const hanalysis::Doublet &Newdoublet)
{
    SextetM = NewSextet;
    doubletM = Newdoublet;
    SetBdt(SextetM.Bdt(),doubletM.Bdt());
    SetTag(SextetM.Tag(),doubletM.Tag());
}

// HOctet::HOctet(const hanalysis::HSextet &NewSextet, const hanalysis::Doublet &Newdoublet, const EventStruct &NeweventStruct)
// {
//     SextetM = NewSextet;
//     doubletM = Newdoublet;
//     eventStructM = NeweventStruct;
//     SetBdt(SextetM.Bdt(),doubletM.Bdt());
//     SetTag(SextetM.Tag(),doubletM.Tag());
// }
