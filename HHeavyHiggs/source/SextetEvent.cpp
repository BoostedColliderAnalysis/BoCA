# include "SextetEvent.hh"

SextetEvent::SextetEvent(const analysis::Sextet &sextet)
{
    sextet_ = sextet;
    SetBdt(sextet_.Bdt());
    SetTag(sextet_.Tag());
}

SextetEvent::SextetEvent(const analysis::Sextet& sextet, const GlobalObservables& global_observables)
{
    sextet_ = sextet;
    global_observables_ = global_observables;
    SetBdt(sextet_.Bdt());
    SetTag(sextet_.Tag());
}
