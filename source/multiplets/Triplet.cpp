/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/multiplets/Triplet.hh"

namespace boca
{

Doublet const &Triplet::Doublet() const
{
    return Multiplet1();
}

Doublet &Triplet::Doublet()
{
    return Multiplet1();
}

Singlet const &Triplet::Singlet() const
{
    return Multiplet2();
}

boca::Singlet const &Triplet111::Singlet1() const
{
    return Multiplet1();
}

boca::Singlet const &Triplet111::Singlet2() const
{
    return Multiplet2();
}

boca::Singlet const &Triplet111::Singlet3() const
{
    return Multiplet3();
}

}
