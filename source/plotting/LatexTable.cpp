

#include <boost/units/io.hpp>

#include "boca/math/Math.hh"
#include "boca/plotting/LatexTable.hh"

// #define INFORMATION
#include "boca/generic/DEBUG.hh"

namespace boca
{

LatexRow::LatexRow()
{
    INFO0;
    Initialize();
}

LatexRow::LatexRow(const std::string& cell)
{
    INFO(cell);
    Initialize();
    AddCell(cell);
}

void LatexRow::Initialize()
{
    INFO0;
    row_ << boost::units::engineering_prefix;
}

// void LatexRow::AddCell(double cell)
// {
//     INFO(cell);
//     SetCell(RoundToDigits(cell));
// }

std::string LatexRow::Row() const
{
    INFO0;
    std::stringstream row;
    row << row_.str() << " \\\\";
    return row.str();
}

LatexTable::LatexTable(const std::string& header)
{
    INFO(header);
    table_ << "\n\\begin{table}\n\\centering\n\\begin{tabular}{" << header << "}\n    \\toprule\n";
}

void LatexTable::AddRow(const LatexRow& row)
{
    INFO0;
    if (first_) {
        table_ << "   ";
        first_ = false;
    }
    table_ << row.Row();
}

void LatexTable::AddLine()
{
    INFO0;
    table_ << " \\midrule\n   ";
}

void LatexTable::AddCaption(const std::string& caption)
{
    INFO0;
    table_ << " \\bottomrule\n\\end{tabular}\n\\caption{" << caption << ".}\n";
}

std::string LatexTable::Table() const
{
    INFO0;
    std::stringstream table;
    table << table_.str() << "\\end{table}\n";
    return table.str();
}

}
