# include "SextetEvent.hh"

SextetEvent::SextetEvent(const analysis::Sextet &sextet)
{
    sextet_ = sextet;
    SetBdt(sextet_.Bdt());
    SetTag(sextet_.Tag());
}

SextetEvent::SextetEvent(const analysis::Sextet& sextet, const EventStruct& event_struct)
{
    sextet_ = sextet;
    event_struct_ = event_struct;
    SetBdt(sextet_.Bdt());
    SetTag(sextet_.Tag());
}
