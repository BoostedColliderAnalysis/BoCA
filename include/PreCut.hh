/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <map>
#include "physics/Particles.hh"

namespace boca
{

template<typename Value>
class PreCut
{

public:

    void Set(Id id, Value value) {
        pre_cut_.emplace(id, value);
    }

    bool TooLarge(Id id, Value value) const {
      return IsSet(id) && Get(id) < value;
    }

    bool TooSmall(Id id, Value value) const {
      return IsSet(id) && Get(id) > value;
    }

    bool IsSet(Id id) const {
        return pre_cut_.find(id) != pre_cut_.end();
    }

    Value Get(Id id) const {
        return pre_cut_.at(id);
    }

private:

    std::map<Id, Value> pre_cut_;

};

}
