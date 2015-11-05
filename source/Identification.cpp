/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Identification.hh"
#include "Branches.hh"
#include "Debug.hh"

namespace boca
{

std::string Name(Tag tag)
{
    switch (tag) {
    case Tag::signal : return "Signal";
    case Tag::background : return "Background";
    Default("tag","");
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

void Identification::SetTag(enum Tag tag)
{
    tag_ = tag;
}

void Identification::SetTag(enum Tag tag_1, enum Tag tag_2)
{
    if (tag_1 == boca::Tag::signal || tag_2 == boca::Tag::signal) tag_ = boca::Tag::signal;
    else tag_ = boca::Tag::background;
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
