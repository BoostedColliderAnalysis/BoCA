/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Sextet.hh"
#include "Quintet.hh"
#include "Quartet.hh"
#include "ThreeBody.hh"

namespace analysis {

/**
 * @brief An octet composed of a sextet an a doublet
 *
 */
class Octet62 : public TwoBody<::analysis::Sextet, ::analysis::Doublet> {

public:

    using TwoBody<::analysis::Sextet, ::analysis::Doublet>::TwoBody;

    const analysis::Sextet& Sextet() const;

    analysis::Doublet const& Doublet() const;

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
class Octet44 : public analysis::TwoBody<analysis::Quartet31, analysis::Quartet31> {

public:

  using analysis::TwoBody<analysis::Quartet31, analysis::Quartet31>::TwoBody;

  const analysis::Quartet31& Quartet1() const;

  const analysis::Quartet31& Quartet2() const;

};

/**
 * @brief An octet composed of two quartets
 *
 */
class Octet53 : public analysis::TwoBody<analysis::Quintet, analysis::Triplet> {

public:

  using analysis::TwoBody<analysis::Quintet, analysis::Triplet>::TwoBody;

  const analysis::Quintet& Quintet() const;

  analysis::Triplet const& Triplet() const;

};

class Octet332 : public analysis::ThreeBody<analysis::Triplet,analysis::Triplet,analysis::Doublet>{

public:

  using analysis::ThreeBody<analysis::Triplet,analysis::Triplet,analysis::Doublet>::ThreeBody;

  analysis::Triplet const& Triplet1() const{return Multiplet1();};

  analysis::Triplet const& Triplet2() const{return Multiplet2();};

  analysis::Doublet const& Doublet() const{return Multiplet3();};

};

}
