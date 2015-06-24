# include "Identification.hh"

namespace analysis {

Identification::Identification()
{
    bdt_ = initial_value();
    tag_ = 0;
    flag_ = false;
    degenerate_ = false;

}

void Identification::SetBdt(const float bdt)
{
    bdt_ = bdt;
}

void Identification::SetBdt(const float bdt_1, const float bdt_2)
{
    bdt_ = (bdt_1 + bdt_2) / 2;
}

float Identification::Bdt() const
{
    return bdt_;
}

void Identification::SetTag(const int tag)
{
    tag_ = tag;
}

void Identification::SetTag(const int tag_1, const int tag_2)
{
    tag_ = tag_1 * tag_2;
}

int Identification::Tag() const
{
    return tag_;
}


void Identification::SetFlag(const bool flag)
{
    flag_ = flag;
}

void Identification::SetFlag(const bool flag_1, const bool flag_2)
{
    flag_ = flag_1 & flag_2;
}

bool Identification::Flag() const
{
    return flag_;
}

}
