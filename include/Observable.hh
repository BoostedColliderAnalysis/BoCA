#pragma once

#include <string>

namespace analysis {

class Observable {

public:

    Observable(float& value, std::string const& expression, std::string const& title, std::string const& unit);

    float& value() const;

    std::string expression() const;

    std::string title() const;

    std::string unit() const;

    char type() const;

private:

    std::string expression_;

    std::string title_;

    std::string unit_;

    char type_;

    float& value_;

};

}
