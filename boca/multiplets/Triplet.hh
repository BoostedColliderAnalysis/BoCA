/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/multiplets/Doublet.hh"
#include "boca/multiplets/ThreeBody.hh"

namespace boca
{

/**
* @ingroup Multiplets
* @brief A %Triplet consisting of a Singlet and a Doublet
*
*/
class Triplet : public TwoBody<boca::Doublet, boca::Singlet>
{

public:

    using TwoBody<boca::Doublet, boca::Singlet>::TwoBody;

    boca::Doublet const &Doublet() const;

    boca::Doublet &Doublet();

    boca::Singlet const &Singlet() const;

private:

};

/**
* @ingroup Multiplets
* @brief A %Triplet consisting of three Singlet%s
*
*/
class Triplet111 : public ThreeBody<boca::Singlet, boca::Singlet,  boca::Singlet>
{

public:

    using ThreeBody<boca::Singlet, boca::Singlet,  boca::Singlet>::ThreeBody;

    boca::Singlet const &Singlet1() const;

    boca::Singlet const &Singlet2() const;

    boca::Singlet const &Singlet3() const;

private:

};

}
