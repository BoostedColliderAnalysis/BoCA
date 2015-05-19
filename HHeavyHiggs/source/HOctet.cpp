# include "HOctet.hh"
// # include "HTagPrivate.hh"

HOctet::HOctet(const analysis::Sextet &Newsextet, const analysis::Doublet &Newdoublet)
{
    sextetM = Newsextet;
    doubletM = Newdoublet;
    SetBdt(sextetM.Bdt(),doubletM.Bdt());
    SetTag(sextetM.Tag(),doubletM.Tag());
}

// HOctet::HOctet(const analysis::Hsextet &Newsextet, const analysis::Doublet &Newdoublet, const EventStruct &Newevent_struct)
// {
//     sextetM = Newsextet;
//     doubletM = Newdoublet;
//     event_structM = Newevent_struct;
//     SetBdt(sextetM.Bdt(),doubletM.Bdt());
//     SetTag(sextetM.Tag(),doubletM.Tag());
// }
