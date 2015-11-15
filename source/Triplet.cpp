/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Triplet.hh"

namespace boca
{

Doublet const& Triplet::Doublet() const
{
    return Multiplet1();
}

Doublet& Triplet::Doublet()
{
    return Multiplet1();
}

Singlet const& Triplet::Singlet() const
{
    return Multiplet2();
}

void Triplet::set_sub_jettiness(const SubJettiness& sub_jettiness)
{
  sub_jettiness_ = sub_jettiness;
}

float Triplet::pt() const
{
  return pt_;
}

void Triplet::set_pt(float pt)
{
  pt_ = pt;
}

}
