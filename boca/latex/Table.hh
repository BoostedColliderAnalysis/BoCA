#pragma once

#include <sstream>

#include "boca/latex/Command.hh"
#include "boca/latex/Row.hh"

namespace boca
{

namespace latex
{

class Table
{

public:

    Table(std::string const &header);

    Table(Table const &table);

    template <typename ... Arguments>
    void AddRow(Arguments ... arguments)
    {
        AddRow(Row(arguments ...));
    }

    void AddRow(Row const &row);

    void AddLine();

    void AddCaption(std::string const &caption);

    std::string str() const;

private:

    std::stringstream stream_;

    bool first_ = true;

    Environment table_ = Environment("table");

    Environment tabular_ = Environment("tabular", false);

};

}

}
