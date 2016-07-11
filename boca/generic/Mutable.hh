#pragma once

#include <functional>

#include "boca/generic/Debug.hh"

namespace boca
{

template<typename Member_>
class Mutable
{
public:

    void SetFunction(std::function<Member_()> const& function) const {
        if (!function_) function_ = function;
    }

    Member_ const& Get(std::function<Member_()> const& function) const {
        SetFunction(function);
        Set();
        return member_;
    }

//     Member_ const& Get()const {
//       if (!set_) Set();
//       return member_;
//     }

    void Set() const {
        if (set_) return;
        if (!function_) Error("defining function of mutable class got lost");
        member_ = function_();
        set_ = true;
    }

//     Member_ const* operator->() const {
//         return &Get();
//     }

//     Member_ const& operator*() const {
//         return Get();
//     }

private:

    mutable Member_ member_;

    mutable bool set_ = false;

    mutable std::function<Member_()> function_;

};

}
