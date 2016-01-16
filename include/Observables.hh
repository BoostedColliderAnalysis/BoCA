#pragma once

#include "Observable.hh"
#include "Filter.hh"

namespace boca
{

class Observables
{

public:
    Observables();
    Observables(Observable const& obs);
    Observables(std::vector<Observable> const& obs);
    void AddObservable(Observable const& observable);

    std::vector<Observable> Vector() const;

    Filter const& Filt() const;

    void AddFilter(Filter const& filter);
    friend Observables operator+(Observables const& observables_1, Observables const& observables_2);
    friend Observables operator+(Observables& observables, Observable const& observable);
private:
    std::vector<Observable> ApplyFilter() const;
    std::vector<Observable> observables_;
    Filter filter_;
};

Observables operator+(Observable const& observable_1, Observable const& observable_2);

}
