/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Sextet.hh"
#include "Quintet.hh"
#include "Quartet.hh"
#include "ThreeBody.hh"

namespace boca {

/**
 * @brief An octet composed of a sextet an a doublet
 *
 */
class Octet62 : public TwoBody<::boca::Sextet, ::boca::Doublet> {

public:

    using TwoBody<::boca::Sextet, ::boca::Doublet>::TwoBody;

    const boca::Sextet& Sextet() const;

    boca::Doublet const& Doublet() const;

//     float BottomBdt() const {
//         return (Doublet().Singlet1().Bdt() + Doublet().Singlet2().Bdt() + Sextet().Triplet1().Singlet().Bdt() + Sextet().Triplet2().Singlet().Bdt()) / 4;
//     }
//
//     float PairBottomBdt() const {
//         return (Doublet().Singlet1().Bdt() + Doublet().Singlet2().Bdt()) / 2;
//     }

};

/**
 * @brief An octet composed of two quartets
 *
 */
class Octet44 : public boca::TwoBody<boca::Quartet31, boca::Quartet31> {

public:

  using boca::TwoBody<boca::Quartet31, boca::Quartet31>::TwoBody;

  const boca::Quartet31& Quartet1() const;

  const boca::Quartet31& Quartet2() const;

};

/**
 * @brief An octet composed of two quartets
 *
 */
class Octet53 : public boca::TwoBody<boca::Quintet, boca::Triplet> {

public:

  using boca::TwoBody<boca::Quintet, boca::Triplet>::TwoBody;

  const boca::Quintet& Quintet() const;

  boca::Triplet const& Triplet() const;

};

class Octet332 : public boca::ThreeBody<boca::Triplet,boca::Triplet,boca::Doublet>{

public:

  using boca::ThreeBody<boca::Triplet,boca::Triplet,boca::Doublet>::ThreeBody;

  boca::Triplet const& Triplet1() const{return Multiplet1();};

  boca::Triplet const& Triplet2() const{return Multiplet2();};

  boca::Doublet const& Doublet() const{return Multiplet3();};

};

}
