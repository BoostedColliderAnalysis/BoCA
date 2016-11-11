/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/multiplets/Triplet.hh"
#include "boca/multiplets/ThreeBody.hh"

namespace boca
{

/**
* @ingroup Multiplets
* @defgroup Quartet Quartet
* @brief Quartets consisting of four Singlet%s
* @{
*/

/**
* @brief A Quartet consisting of two Doublet%s
*
*/
class Quartet22 : public TwoBody<Doublet, Doublet>
{

public:

    using TwoBody<Doublet, Doublet>::TwoBody;

    Doublet const &Doublet1() const;

    Doublet const &Doublet2() const;

    Doublet &Doublet1();

    Doublet &Doublet2();

private:

    std::string Name() const override;

};

/**
* @brief A Quartet consisting of a Triplet and a Singlet
*
*/
class Quartet31 : public TwoBody<boca::Triplet, boca::Singlet>
{

public:

    using TwoBody<boca::Triplet, boca::Singlet>::TwoBody;

    boca::Triplet const &Triplet() const;

    boca::Singlet const &Singlet() const;

private:

    std::string Name() const override;

};

/**
* @brief A Quartet consisting of a Doublet and two Singlet%s
*
*/
class Quartet211 : public ThreeBody<boca::Doublet, boca::Singlet, boca::Singlet>
{

public:

    using ThreeBody<boca::Doublet, boca::Singlet, boca::Singlet>::ThreeBody;

    boca::Doublet const &Doublet() const;

    boca::Singlet const &Singlet1() const;

    boca::Singlet const &Singlet2() const;

private:

    std::string Name() const override;

};

/*
 * @}
 */

}
