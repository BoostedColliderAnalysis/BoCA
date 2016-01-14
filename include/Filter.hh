#pragma once
#include <string>
#include <map>

namespace boca
{
class Filter
{
public:
    void Set(std::string const& observable) {
        map_.emplace(observable, false);
    }
    bool Check(std::string const& observable) const {
        return IsSet(observable);
    }

    bool IsSet(std::string const& observable) const {
        return map_.find(observable) != map_.end();
    }

private:
    std::map<std::string, bool> map_;
};
}
