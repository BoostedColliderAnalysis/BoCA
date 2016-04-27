#pragma once

#include <sstream>
// #include <boost/units/is_dimensionless.hpp>

namespace boca
{

class LatexRow
{

public:

    LatexRow();

    LatexRow(std::string const& cell);

    void Initialize();

    template <typename... Arguments>
    LatexRow(Arguments... arguments) {
        this->AddCells(arguments ...);
    }


    template <typename Cell, typename... Arguments>
    void AddCells(Cell const& cell, Arguments... arguments) {
        AddCell(cell);
        AddCells(arguments...);
    }

    template <typename Cell>
    void AddCell(Cell const& cell) {
        SetCell(cell);
    }
/*
    void AddCell(double cell);

    template<typename Dimensionless>
    void AddCell(Dimensionless const& dimensionless) {
      BOOST_MPL_ASSERT((boost::units::is_dimensionless<boost::units::quantity<Dimensionless>>));
      AddCell(double(dimensionless));
    };*/

    std::string Row() const;

private:

    template <typename Cell>
    void SetCell(Cell const& cell) {
        if (first_) {
            row_ << " " << cell << "\n";
            first_ = false;
        } else row_ << "  & " << cell << "\n";
    }

    void AddCells() {}

    std::stringstream row_;

    bool first_ = true;

};

class LatexTable
{

public:

    LatexTable(std::string const& header);

    template <typename ... Arguments>
    void AddRow(Arguments ... arguments) {
        AddRow(LatexRow(arguments ...));
    }

    void AddRow(LatexRow const& row);

    void AddLine();

    void AddCaption(std::string const& caption);

    std::string Table() const;

private:

    std::stringstream table_;

    bool first_ = true;

};

}
