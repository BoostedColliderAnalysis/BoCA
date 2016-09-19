/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/multiplets/Sextet.hh"
#include "boca/multiplets/Quintet.hh"
#include "boca/multiplets/Quartet.hh"
#include "boca/multiplets/ThreeBody.hh"

namespace boca
{

/**
 * @brief An octet composed of a sextet an a doublet
 *
 */
class Octet62 : public TwoBody<::boca::Sextet33, ::boca::Doublet>
{

public:

    using TwoBody<::boca::Sextet33, ::boca::Doublet>::TwoBody;

    const boca::Sextet33& Sextet33() const;

    boca::Doublet const& Doublet() const;

};

/**
 * @brief An octet composed of two quartets
 *
 */
class Octet44 : public boca::TwoBody<boca::Quartet31, boca::Quartet31>
{

public:

    using boca::TwoBody<boca::Quartet31, boca::Quartet31>::TwoBody;

    const boca::Quartet31& Quartet1() const;

    const boca::Quartet31& Quartet2() const;

};

/**
 * @brief An octet composed of two quartets
 *
 */
class Octet53 : public boca::TwoBody<boca::Quintet, boca::Triplet>
{

public:

    using boca::TwoBody<boca::Quintet, boca::Triplet>::TwoBody;

    const boca::Quintet& Quintet() const;

    boca::Triplet const& Triplet() const;

};

/**
 * @brief Octet consisting of two triplets and one doublet
 *
 */
class Octet332 : public boca::ThreeBody<boca::Triplet, boca::Triplet, boca::Doublet>
{

public:

    using boca::ThreeBody<boca::Triplet, boca::Triplet, boca::Doublet>::ThreeBody;

    boca::Triplet const& Triplet1() const;

    boca::Triplet const& Triplet2() const;

    boca::Doublet const& Doublet() const;

};

}
