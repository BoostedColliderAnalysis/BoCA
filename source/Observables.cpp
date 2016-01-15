
#include <boost/range/algorithm_ext/erase.hpp>

#include "Observables.hh"
#include "Vector.hh"
namespace boca
{
// namespace
// {
// std::vector< Observable > Join(const std::vector< Observable >& vector_1, const std::vector< Observable >& vector_2)
// {
//     std::vector<Observable> joined;
//     joined.reserve(vector_1.size() + vector_2.size());
//     joined.insert(joined.end(), vector_1.begin(), vector_1.end());
//     joined.insert(joined.end(), vector_2.begin(), vector_2.end());
//     return joined;
// }
// }
Observables::Observables() {}
Observables::Observables(const Observable& obs)
{
    observables_ = {obs};
}
Observables::Observables(const std::vector< Observable >& obs)
{
    observables_ = obs;
}
void Observables::AddObservable(const Observable& observable)
{
    observables_.emplace_back(observable);
}
std::vector< Observable > Observables::Vector() const
{
    return ApplyFilter();
}
const Filter& Observables::Filt() const
{
    return filter_;
}
void Observables::AddFilter(const Filter& filter)
{
    filter_ = filter;
}
std::vector< Observable > Observables::ApplyFilter() const
{
    std::vector<Observable> observables = observables_;
    observables = boost::range::remove_erase_if(observables, [&](Observable const & observable) {
        return filter_.IsSet(observable.Name());
    });
    return observables;
}
Observables operator+(const Observables& observables_1, const Observables& observables_2)
{
    return Join(observables_1.Vector(), observables_2.Vector());
}
Observables operator+(Observables& observables, const Observable& observable)
{
    observables.AddObservable(observable);
    return observables;
}
Observables operator+(const Observable& observable_1, const Observable& observable_2)
{
    return Observables( {observable_1, observable_2});
}
}

