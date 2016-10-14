#pragma once

#include <sstream>

#include "boca/latex/Command.hh"

namespace boca
{

namespace latex
{

class Row
{

public:

    Row();

    Row(std::string const& cell);

    Row(Row const& row) : row_(row.row_.str()),  first_(row.first_){}

    void Initialize();

    template <typename... Arguments>
    Row(Arguments... arguments) {
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

    std::string str() const;

private:

    template <typename Cell>
    void SetCell(Cell const& cell) {
        if (first_) {
            row_ << " " << cell << '\n';
            first_ = false;
        } else row_ << "  & " << cell << '\n';
    }

    void AddCells() {}

    std::stringstream row_;

    bool first_ = true;

};

}

}
