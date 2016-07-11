

#include <boost/units/io.hpp>

#include "boca/math/Math.hh"
#include "boca/latex/Table.hh"

// #define INFORMATION
#include "boca/generic/DEBUG.hh"

namespace boca
{

namespace latex
{

Row::Row()
{
    INFO0;
    Initialize();
}

Row::Row(const std::string& cell)
{
    INFO(cell);
    Initialize();
    AddCell(cell);
}

void Row::Initialize()
{
    INFO0;
    row_ << boost::units::engineering_prefix;
}

std::string Row::str() const
{
    INFO0;
    std::stringstream row;
    row << row_.str() << " \\\\";
    return row.str();
}

}

}
