/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/branch/Info.hh"
#include "boca/File.hh"
// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

namespace branch
{

Info::Info()
{
    INFO0;
    crosssection = InitialValue();
    crosssection_error = InitialValue();
    mass = InitialValue();
    event_number = 0;
}

Info::Info(File const& file)
{
    INFO0;
    SetCrosssection(file.Crosssection());
    SetCrosssectionError(file.CrosssectionError());
    SetMass(file.Mass());
    SetNames(file.Names());
    event_number = 0;
}

boca::Crosssection Info::Crosssection() const
{
    INFO0;
    return static_cast<double>(crosssection) * fb;
}

boca::Crosssection Info::CrosssectionError() const
{
    INFO0;
    return static_cast<double>(crosssection_error) * fb;
}

int Info::EventNumber() const
{
    INFO0;
    return event_number;
}

boca::Mass Info::Mass() const
{
    INFO0;
    return static_cast<double>(mass) * GeV;
}

std::string Info::Name() const
{
    INFO0;
    return names.Name();
}

boca::Names Info::Names() const
{
    INFO0;
    return names;
}

latex::String Info::LatexName() const
{
    INFO0;
    return names.LatexName();
}

void Info::SetCrosssection(boca::Crosssection const& crosssection_)
{
    INFO0;
    crosssection = crosssection_ / fb;
}

void Info::SetCrosssectionError(boca::Crosssection const& crosssection_error_)
{
    INFO0;
    crosssection_error = crosssection_error_ / fb;
}

void Info::SetEventNumber(int event_number_)
{
    INFO0;
    event_number = event_number_;
}

void Info::SetMass(boca::Mass const& mass_)
{
    INFO0;
    mass = mass_ / GeV;
}

void Info::SetNames(boca::Names const& names_)
{
    INFO0;
    names = names_;
}

}

}
