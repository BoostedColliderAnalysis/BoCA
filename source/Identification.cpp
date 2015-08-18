/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Identification.hh"

namespace analysis {

std::string Name(Tag tag)
{
    switch (tag) {
    case  Tag::signal:
        return "Signal";
    case  Tag::background:
        return "Background";
    }
}

Identification::Identification()
{
    bdt_ = initial_value();
    tag_ = analysis::Tag::background;
    flag_ = false;
    degenerate_ = false;
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
    if (tag_1 == analysis::Tag::signal || tag_2 == analysis::Tag::signal)
        tag_ = analysis::Tag::signal;
    else
        tag_ = analysis::Tag::background;
}

analysis::Tag Identification::Tag() const
{
    return tag_;
}


void Identification::SetFlag(bool flag)
{
    flag_ = flag;
}

void Identification::SetFlag(bool flag_1, bool flag_2)
{
    flag_ = flag_1 && flag_2;
}

bool Identification::Flag() const
{
    return flag_;
}

}
