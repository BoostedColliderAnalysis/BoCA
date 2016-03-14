/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "Identification.hh"
#include "Branches.hh"
#include "DEBUG.hh"

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

void Identification::SetBdt(float bdt)
{
    bdt_ = bdt;
}

void Identification::SetBdt(float bdt_1, float bdt_2)
{
    bdt_ = (bdt_1 + bdt_2) / 2;
}

float Identification::Bdt() const
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

float Identification::InitialValue()
{
    return BaseBranch::InitialValue();
}

bool Identification::operator<(Identification const& multiplet) const
{
    return Bdt() > multiplet.Bdt();
}

}
