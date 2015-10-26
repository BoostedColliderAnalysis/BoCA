# pragma once

#include <sstream>

namespace boca
{

class Options
{

public:

    Options() {}

    Options(std::string const& string, bool do_it = true) {
        Add(string, do_it);
    }

    template<typename Value>
    Options(std::string const& string, Value value) {
        Add(string, value);
    }

    template<typename Value>
    Options(std::string const& string, Value value, std::string const& unit) {
        Add(string, value, unit);
    }

    void Add(std::string const& string, bool do_it = true) {
        Separator();
        if (!do_it) options_ << "!";
        options_ << string;
    }

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

    std::string str() const {
        return options_.str();
    }

    operator std::string() const {
        return str();
    }

    operator TString() const {
        return str();
    }

private:

    void Separator() {
        if (!first_) options_ << ":";
        first_ = false;
    }

    std::stringstream options_;

    bool first_ = true;

};

}
