/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <fstream>
#include "boca/physics/Units.hh"

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

    void IncludeGraphic(const std::string& file_name, const std::string& caption);

    void IncludeGraphic(std::vector<std::string>  const& file_names, std::string  const& caption);

    void Table(std::string const& header, std::string const& content, std::string const& caption);

    void Mass(const boca::Mass& mass);

    std::ofstream latex_file_;
};

}
