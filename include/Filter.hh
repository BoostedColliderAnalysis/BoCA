#pragma once
#include <string>
#include <map>
#include <vector>

namespace boca
{
class Filter
{
public:
    Filter() {}
    Filter(std::string const& observable) {
        Add(observable);
    }
    void Add(std::string const& observable) {
        map_.emplace(observable, false);
    }
    void Add(std::vector<std::string> const& observables) {
        for (auto const & observable : observables) Add(observable);
    }
    bool IsSet(std::string const& observable) const {
        return map_.find(observable) != map_.end();
    }
private:
    std::map<std::string, bool> map_;
};
}
