# include "HSextetEvent.hh"
// # include "HTagPrivate.hh"

HSextetevent::HSextetevent(const hanalysis::HSextet &NewSextet)
{
    SextetM = NewSextet;
    SetBdt(SextetM.Bdt());
    SetTag(SextetM.Tag());
}

HSextetevent::HSextetevent(const hanalysis::HSextet &NewSextet, const EventStruct &NeweventStruct)
{
    SextetM = NewSextet;
    eventM = NeweventStruct;
    SetBdt(SextetM.Bdt());
    SetTag(SextetM.Tag());
}
