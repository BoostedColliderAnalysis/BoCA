# include "Identification.hh"

analysis::Identification::Identification()
{
    initial_value_ =  -11.1111111; // this must be identical to the initial value in the branch
    bdt_ = initial_value_;
    tag_ = 0;
    flag_ = false;
    degenerate_ = false;

}

void analysis::Identification::SetBdt(const float bdt)
{
    bdt_ = bdt;
}

void analysis::Identification::SetBdt(const float bdt_1, const float bdt_2)
{
    bdt_ = (bdt_1 + bdt_2) / 2;
}

float analysis::Identification::Bdt() const
{
    return bdt_;
}

void analysis::Identification::SetTag(const int tag)
{
    tag_ = tag;
}

void analysis::Identification::SetTag(const int tag_1, const int tag_2)
{
    tag_ = tag_1 * tag_2;
}

int analysis::Identification::Tag() const
{
    return tag_;
}


void analysis::Identification::SetFlag(const bool flag)
{
    flag_ = flag;
}

void analysis::Identification::SetFlag(const bool flag_1, const bool flag_2)
{
    flag_ = flag_1 & flag_2;
}

bool analysis::Identification::Flag() const
{
    return flag_;
}
