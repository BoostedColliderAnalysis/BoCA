/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <string>

namespace boca {

class Observable {

public:

    Observable(float& value, std::string const& expression, std::string const& title, std::string const& unit);

    float& Value() const;

    std::string Expression() const;

    std::string Title() const;

    std::string Unit() const;

    char Type() const;

private:

    std::string expression_;

    std::string title_;

    std::string unit_;

    char type_;

    float* value_;

};

}
