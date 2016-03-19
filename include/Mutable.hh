#pragma once
#include <functional>
#include <iostream>

namespace boca
{

template<typename Member_>
class Mutable
{
public:

    Mutable() {};

    Mutable(std::function<Member_()> const& function) :
        function_(function)
    {}

    void SetFunction(std::function<Member_()> const& function) const {
        function_ = function;
    }

    Member_ const& Get(std::function<Member_()> const& function) const {
        if (!function_) SetFunction(function);
        if (!set_) Set();
        return member_;
    }

    Member_ const& Get()const {
      if (!set_) Set();
      return member_;
    }

    void Set() const {
        if (!function_) std::cout << "defining function of mutable class got lost" << std::endl;
        member_ = function_();
        set_ = true;
    }

    Member_ const* operator->() const {
        return &Get();
    }

    Member_ const& operator*() const {
        return Get();
    }

private:
    mutable Member_ member_;
    mutable bool set_ = false;
    mutable std::function<Member_()> function_;
};


template<typename Member_>
Mutable<Member_> MakeMutable(std::function<Member_()> const& function)
{
    return Mutable<Member_>(function);
}

}
