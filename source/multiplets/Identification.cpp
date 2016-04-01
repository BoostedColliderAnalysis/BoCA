/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "multiplets/Identification.hh"
#include "Branches.hh"
#include "generic/DEBUG.hh"

namespace boca
{

std::string Name(Tag tag)
{
    switch (tag) {
    case Tag::signal : return "Signal";
    case Tag::background : return "Background";
    DEFAULT("tag","");
    }
}

Identification::Identification()
{
    bdt_ = InitialValue();
    tag_ = boca::Tag::background;
}

void Identification::SetBdt(double bdt)
{
    bdt_ = bdt;
}

void Identification::SetBdt(double bdt_1, double bdt_2)
{
    bdt_ = (bdt_1 + bdt_2) / 2;
}

double Identification::Bdt() const
{
    return bdt_;
}

void Identification::SetTag(boca::Tag tag)
{
    tag_ = tag;
}

void Identification::SetTag(boca::Tag tag_1, boca::Tag tag_2)
{
    tag_ = tag_1 == boca::Tag::signal || tag_2 == boca::Tag::signal ? boca::Tag::signal : boca::Tag::background;
}

boca::Tag Identification::Tag() const
{
    return tag_;
}

double Identification::InitialValue()
{
    return BaseBranch::InitialValue();
}

bool Identification::operator<(Identification const& multiplet) const
{
    return Bdt() > multiplet.Bdt();
}

}
