#pragma once

#include <functional>

#include "boca/generic/Debug.hh"

namespace boca
{

template<typename Member_>
class Mutable
{
public:

    Member_ const& Get(std::function<Member_()> const& function) const {
        if (set_) return member_;
        member_ = function();
        set_ = true;
        return member_;
    }

private:

    mutable Member_ member_;

    mutable bool set_ = false;

};

}
