# pragma once

#include <sstream>

class TString;

namespace boca
{

class Options
{

public:

    Options();

    Options(std::string const& string, bool do_it = true);

    template<typename Value>
    Options(std::string const& string, Value value) {
        Add(string, value);
    }

    template<typename Value>
    Options(std::string const& string, Value value, std::string const& unit) {
        Add(string, value, unit);
    }

    void Add(std::string const& string, bool do_it = true);

    template<typename Value>
    void Add(std::string const& string, Value value) {
        Separator();
        options_ << string << "=" << value;
    }

    template<typename Value>
    void Add(std::string const& string, Value value, std::string const& unit) {
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
