/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "TFile.h"

#include "File.hh"
#include "Phase.hh"

namespace boca
{

class Files
{
public:
    Files(boca::Phase& phase, File& file, TFile& export_file);
    boca::Phase Phase() const;
    File const& Import() const;
    TFile& Export();
private:
    boca::Phase phase_;
    File& import_file_;
    TFile& export_file_;
};

}
