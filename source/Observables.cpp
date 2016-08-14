
#include <boost/range/algorithm_ext/erase.hpp>

#include "boca/generic/Vector.hh"
#include "boca/Observables.hh"
#include "boca/Filter.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

Observables::Observables() {}

Observables::Observables(Observable const& obs)
{
    observables_ = {obs};
}

Observables::Observables(std::vector<Observable> const& obs)
{
    observables_ = obs;
}

void Observables::AddObservable(Observable const& observable)
{
    observables_.emplace_back(observable);
}

std::vector< Observable > Observables::Vector() const
{
    return observables_;
}

void Observables::AddFilter(const Filter& filter)
{
    observables_ = boost::range::remove_erase_if(observables_, [&](Observable const & observable) {
        return filter.IsSet(observable.Name());
    });
}

Observables operator+(Observables const& observables_1, Observables const& observables_2)
{
    return Combine(observables_1.Vector(), observables_2.Vector());
}

Observables operator+(Observables& observables, Observable const& observable)
{
    observables.AddObservable(observable);
    return observables;
}

Observables operator+(Observable const& observable_1, Observable const& observable_2)
{
    return Observables( {observable_1, observable_2});
}

}

