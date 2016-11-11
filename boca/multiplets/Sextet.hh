/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/multiplets/Quartet.hh"

namespace boca
{

/**
 * @ingroup Multiplets
 * @brief A Sextet consisting of two Triplet%s
 *
 */
class Sextet33 : public TwoBody<Triplet, Triplet>
{

public:

    using TwoBody<Triplet, Triplet>::TwoBody;

    Triplet const& Triplet1() const;

    Triplet const& Triplet2() const;

    Triplet & Triplet1();

    Triplet & Triplet2();

private:

    std::string Name() const override;

};

/**
 * @ingroup Multiplets
 * @brief A Sextet consisting of a Quartet and a Doublet
 *
 */
class Sextet42 : public TwoBody<Quartet22, boca::Doublet>
{

public:

    using TwoBody<Quartet22, boca::Doublet>::TwoBody;

    Quartet22 const& Quartet() const;

    boca::Doublet const& Doublet() const;

    Quartet22 & Quartet();

    boca::Doublet & Doublet();

private:

    std::string Name() const override;

};

}
