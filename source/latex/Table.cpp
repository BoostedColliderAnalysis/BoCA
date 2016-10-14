

#include <boost/units/io.hpp>

#include "boca/math/Math.hh"
#include "boca/latex/Table.hh"

// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

namespace latex
{

Table::Table(const std::string &header)
{
    INFO(header);
    stream_ << table_.Begin() << Command("centering") << tabular_.Begin(header) << "    " << Command("toprule");
}

Table::Table(latex::Table const& table) :
    stream_(table.stream_.str()),
    first_(table.first_),
    table_(table.table_),
    tabular_(table.tabular_)
{}

void Table::AddRow(const Row &row)
{
    INFO0;
    if (first_) {
        stream_ << "   ";
        first_ = false;
    }
    stream_ << row.str();
}

void Table::AddLine()
{
    INFO0;
    stream_ << " " << Command("midrule") << "   ";
}

void Table::AddCaption(const std::string &caption)
{
    INFO0;
    stream_ << " " << Command("bottomrule") << tabular_.End() << Caption(caption);
}

std::string Table::str() const
{
    INFO0;
    return stream_.str() + table_.End();
}


}

}
