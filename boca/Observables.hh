/**
 * Copyright (C) 2016 Jan Hajer
 */
#pragma once

#include "boca/Observable.hh"

namespace boca
{

class Filter;

/**
 * @brief Container for Observable
 *
 */
class Observables
{
public:
    Observables();
    Observables(Observable const& obs);
    Observables(std::vector<Observable> const& obs);
    void AddObservable(Observable const& observable);
    std::vector<Observable> Vector() const;
    void AddFilter(Filter const& filter);
    friend Observables operator+(Observables const& observables_1, Observables const& observables_2);
    friend Observables operator+(Observables& observables, Observable const& observable);
private:
    std::vector<Observable> observables_;
};

Observables operator+(Observable const& observable_1, Observable const& observable_2);

}
