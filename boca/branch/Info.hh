/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/physics/Prefixes.hh"

#include "boca/branch/Base.hh"
#include "boca/Names.hh"

namespace boca
{

class File;

namespace branch
{

/**
 * @brief %Info tree branch
 *
 */
class Info : public Base
{

public:

    Info();

    Info(File const& file);

    boca::Crosssection Crosssection() const;

    boca::Crosssection CrosssectionError() const;

    boca::Mass Mass() const;

    int EventNumber() const;

    std::string Name() const;

    boca::Names Names() const;

    latex::String LatexName() const;

    void SetCrosssection(const boca::Crosssection& crosssection_);

    void SetCrosssectionError(const boca::Crosssection& crosssection_error_);

    void SetMass(const boca::Mass& mass_);

    void SetEventNumber(int event_number);

    void SetNames(boca::Names const& names);

private:

    float crosssection;

    float crosssection_error;

    float mass;

    int event_number;

    boca::Names names;

    ClassDef(Info, 1)

};

}

}
