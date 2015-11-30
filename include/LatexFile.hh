/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <fstream>
#include "physics/Units.hh"

namespace boca
{

class LatexFile
{
public:
    LatexFile(std::string const& name);

    virtual ~LatexFile();

    void operator<<(std::string const& string);

//     void operator+(std::string const& string) {
//         latex_file_ << string;
//     }

    void IncludeGraphic(std::string file_name, std::string caption);

    void Table(std::string const& header, std::string const& content, std::string caption);

    void Mass(boca::Mass mass);

    std::ofstream latex_file_;
};

}
