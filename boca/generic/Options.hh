# pragma once

#include <sstream>

class TString;

namespace boca
{

namespace detail
{

template <typename>
struct IsBool : std::false_type {};

template <>
struct IsBool<bool> : std::true_type {};

template<typename Value_>
using OnlyIfNotBool = typename std::enable_if < !IsBool<Value_>::value >::type;

}

/**
* @ingroup Generic
* @brief Key-value-pair options
*
*/
class Options
{

public:

    Options();

    Options(std::string const &string, bool do_it = true);

    template<typename Value_>
    Options(std::string const &string, Value_ value)
    {
        Add(string, value);
    }

    template<typename Value_, typename = detail::OnlyIfNotBool<Value_>>
    Options(std::string const &string, Value_ value, std::string const &unit)
    {
        Add(string, value, unit);
    }

    void Add(std::string const &string, bool do_it = true);

    template<typename Value_>
    void Add(std::string const &string, Value_ value)
    {
        Separator();
        options_ << string << "=" << value;
    }

    template<typename Value_>
    void Add(std::string const &string, Value_ value, std::string const &unit)
    {
        Separator();
        options_ << string << "=" << value << unit;
    }

    std::string str() const;

    operator std::string() const;

    operator TString() const;

private:

    void Separator();

    std::stringstream options_;

    bool first_ = true;

};

}
