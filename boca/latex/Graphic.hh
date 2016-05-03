#pragma once

#include <sstream>
#include <vector>

#include "boca/latex/String.hh"
#include "boca/latex/Command.hh"

namespace boca
{

namespace latex
{

class Graphic
{

public:

    Graphic();

    Graphic(std::string const& name, String const& caption = "", double width = 0.5);

    Graphic(const std::vector< std::string >& names, const String& caption, double width = 0.5);

    void Initialize();

    void AddGraphic(std::string const& name, double width = 0.5);

    void AddCaption(const String& caption);

    void AddGraphic(const std::vector< std::string >& names, const String& caption, double width = 0.5);

    std::string str() const;

private:

    std::stringstream graphic_;

    Environment environment_ = Environment("figure");

};

}

}
