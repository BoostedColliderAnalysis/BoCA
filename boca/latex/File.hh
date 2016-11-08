/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <fstream>

#include "boca/units/Units.hh"
#include "boca/latex/Table.hh"
#include "boca/latex/Graphic.hh"
#include "boca/latex/Command.hh"

namespace boca
{

namespace latex
{

class File
{

public:

    File(std::string const& name);

    virtual ~File();

    void operator<<(std::string const& string);

    void AddTable(Table const& table);

    void AddGraphic(Graphic const& graphic);

    void AddTitle(const Mass& mass);

private:

    std::ofstream latex_file_;

    Environment environment_;

};

}

}
