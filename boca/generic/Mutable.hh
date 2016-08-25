#pragma once

#include <functional>

#include "boca/generic/Debug.hh"

namespace boca
{

/**
* @ingroup Generic
* @brief Lazy caching of variables
*
* Variables stored in the Mutable class will only be evaluated when need (lazy evaluation) and the result will be cached.
*/
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

    void Reset() {
        set_ = false;
    }

private:

    mutable Member_ member_;

    mutable bool set_ = false;

};

}
