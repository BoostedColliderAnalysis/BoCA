#pragma once

#include <boost/optional.hpp>
#include "boca/math/LorentzVector.hh"
#include "boca/math/Matrix2.hh"

// *********************************************************************************
// WIMPMASS
// version 1.00
//
// Authors: Hsin-Chia Cheng, John Gunion, Zhenyu Han, Bob McElrath, Dalit Engelhardt
//
// *********************************************************************************
// This package contains two C++ subroutines useful for event
// reconstruction in events with missing particles. The references
// are arXiv: 0707.0030 and arXiv: 0802.4290.
//
// The two functions are given in "topology22.cpp" and "topology33.cpp"
// in the "src/" directory. See the header of the source file for usage.
// "ROOT" (http://root.cern.ch/drupal/) is required for compiling
// topology33.cpp. The directory "examples/" contains a couple of examples
// calling these subroutines. You need to modify the Makefile in the "src"
// directory and "examples" directory to point to the correct ROOT location.

namespace boca
{
class Doublet;
class Quartet22;
}

namespace wimpmass
{

class Invisible22
{

public:

    Invisible22(boca::Mass const &heavy, boca::Mass const &light, boca::Mass const &invisible);

    std::vector<std::pair<boca::LorentzVector<boca::Momentum>, boca::LorentzVector<boca::Momentum>>> Solve(boca::LorentzVector<boca::Momentum> const &first, boca::LorentzVector<boca::Momentum> const &second, boca::LorentzVector<boca::Momentum> const &third, boca::LorentzVector<boca::Momentum> const &fourth, boca::LorentzVector<boca::Momentum> const &missing);

    std::vector<std::pair<boca::LorentzVector<boca::Momentum>, boca::LorentzVector<boca::Momentum>>> Solve(boca::Doublet const &doublet_1, boca::Doublet const &doublet_2, boca::LorentzVector<boca::Momentum> const &missing);

    std::vector<std::pair<boca::LorentzVector<boca::Momentum>, boca::LorentzVector<boca::Momentum>>> Solve(boca::Quartet22 const &quartet, boca::LorentzVector<boca::Momentum> const &missing);

protected:

    void SetMasses(boca::Mass const &heavy, boca::Mass const &light, boca::Mass const &invisible);

    std::vector<std::pair<boca::LorentzVector<boca::Momentum>, boca::LorentzVector<boca::Momentum>>> Solve();

    void SetFirstChain(boca::LorentzVector<boca::Momentum> const &first, boca::LorentzVector<boca::Momentum> const &second);

    void SetSecondChain(boca::LorentzVector<boca::Momentum> const &first, boca::LorentzVector<boca::Momentum> const &second);

    void SetMissingMomentum(boca::LorentzVector<boca::Momentum> const &missing);

private:

    void Set(boca::Quartet22 const &quartet);

    void SetFirstChain(boca::Doublet const &doublet);

    void SetSecondChain(boca::Doublet const &doublet);

    std::array<double, 5> Coefficients();

    boca::Matrix2<double> MatrixA();

    boca::Matrix2<double> MatrixB();

    boca::Vector2<boca::Momentum> VectorA();

    boca::Vector2<boca::Momentum> VectorB();

    boca::MomentumSquare ScalarA();

    boca::MomentumSquare ScalarB();

    boca::LorentzVector<double> CoefficientVector1() const;

    boca::LorentzVector<double> CoefficientVector2() const;

    boca::LorentzVector<boca::Momentum> CoefficientVector() const;

    boost::optional<std::pair<boca::LorentzVector<boca::Momentum>, boca::LorentzVector<boca::Momentum>>> Solution(boca::Momentum const &root);

    boca::Energy Energy1(boca::Energy const &energy_2);

    boca::Mutable<boca::LorentzVector<boca::Momentum>> coefficient_vector_;

    boca::Mutable<boca::LorentzVector<double>> coefficient_vector_1_;

    boca::Mutable<boca::LorentzVector<double>> coefficient_vector_2_;

    boca::Mutable<boca::Matrix2<double>> matrix_a_;

    boca::Mutable<boca::Matrix2<double>> matrix_b_;

    boca::Mutable<boca::Vector2<boca::Momentum>> vector_a_;

    boca::Mutable<boca::Vector2<boca::Momentum>> vector_b_;

    boca::Mutable<boca::MomentumSquare> scalar_a_;

    boca::Mutable<boca::MomentumSquare> scalar_b_;

    boca::LorentzVector<boca::Momentum> p3_;

    boca::LorentzVector<boca::Momentum> p4_;

    boca::LorentzVector<boca::Momentum> p5_;

    boca::LorentzVector<boca::Momentum> p6_;

    boca::LorentzVector<boca::Momentum> missing_;

    boca::MassSquare heavy_square_;

    boca::MassSquare light_square_;

    boca::MassSquare invisible_square_;

};

}
