# pragma once

#include <sstream>

namespace boca
{

class Options
{

public:

    Options() {}

    Options(std::string const& string) {
        Add(string);
    }

    template<typename Value>
    Options(std::string const& string, Value value) {
        Add(string, value);
    }

    template<typename Value>
    Options(std::string const& string, Value value, std::string const& unit) {
        Add(string, value, unit);
    }

    void Add(std::string const& string) {
        Separator();
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

private:

    void Separator() {
        if (!first_) options_ << ":";
        first_ = false;
    }

    std::stringstream options_;

    bool first_ = true;

};

}
