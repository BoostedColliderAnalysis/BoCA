# include "HSextetEvent.hh"
// # include "HTagPrivate.hh"

HSextetEvent::HSextetEvent(const hanalysis::HSextet &NewSextet)
{
    SextetM = NewSextet;
    SetBdt(SextetM.Bdt());
    SetTag(SextetM.Tag());
}

HSextetEvent::HSextetEvent(const hanalysis::HSextet &NewSextet, const HEventStruct &NewEventStruct)
{
    SextetM = NewSextet;
    EventM = NewEventStruct;
    SetBdt(SextetM.Bdt());
    SetTag(SextetM.Tag());
}
