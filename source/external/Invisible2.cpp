/****************************************************************************/
/* Solve an event with two decay chains, each containing 2 visible particles*/
/* Translated from Jack Gunion's Fortran code */
/* Reference arXiv: 0707.0030 */
/* Maintained by Zhenyu Han */
/****************************************************************************/

/****************************************************************************

 USAGE

 The program solves for the momenta of the invisible particles in an event
 with two decay chains containing the same particles. Each decay chain
 has 2 visible particles, and an invisible particle at the end of decay chain.

 The visible momenta and the missing transverse momentum are stored in the
 structure:
 struct event22
 {
 double p3[4], p4[4], p5[4], p6[4];
 double pmiss[4];
 };

 The particles are labled such that particles 1,3,5 are in the same decay
 chain, with particle 1 denoting the invisible dark matter particle.
 Particles 3 and 5 are visible paritcles ordered from downstream to upstream
 (i.e., 3 is the one ajacent to the missing particle). Similarly, particles
 2,4,6 are in the other decay chain with particle 2 the other missing
 particle and so forth.

 One also need the masses of the unknown particles (mn < mx < my) to solve for
 the momenta of the missing particles. The syntax is

 void solvp2.E()2(event22 & evt, double mn, double mx, double my, int & nsols,
 double p1[4][4], double p2[4][4])

 The output is "nsols", the number of real solutions, not exceeding 4, and
 "p1[0..nsols-1][0..3], p2[0..nsols-1][0..3]", the solutions of the 4-momenta
 of the invisible particles.

 see examples/examplp2.E()2.cpp for an example.
********************************************************************************/

#include "Math/Polynomial.h"

#include "boca/external/Invisible2.hh"
#include "boca/generic/Types.hh"
#include "boca/multiplets/Quartet.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

namespace wimpmass
{

Invisible22::Invisible22() {}

Invisible22::Invisible22(LorentzVector< Momentum > const& missing) :
    missing_(missing) {}

Invisible22::Invisible22(Quartet22 const& quartet, LorentzVector< Momentum > const& missing) :
    missing_(missing)
{
    Set(quartet);
}

void Invisible22::SetMissingMomentum(LorentzVector< Momentum > const& missing)
{
    missing_ = missing;
}

void Invisible22::Set(Quartet22 const& quartet)
{
    SetFirstChain(quartet.Doublet1());
    SetSecondChain(quartet.Doublet2());
}

void Invisible22::SetFirstChain(const Doublet& doublet)
{
    p3_ = doublet.Singlet2().Vector();
    p5_ = doublet.Singlet1().Vector();
}

void Invisible22::SetSecondChain(const Doublet& doublet)
{
    p4_ = doublet.Singlet2().Vector();
    p6_ = doublet.Singlet1().Vector();
}

void Invisible22::SetFirstChain(LorentzVector< Momentum > const& first, LorentzVector< Momentum > const& second)
{
    p3_ = first;
    p5_ = second;
}

void Invisible22::SetSecondChain(LorentzVector< Momentum > const& first, LorentzVector< Momentum > const& second)
{
    p4_ = first;
    p6_ = second;
}

void Invisible22::solve22(event22& evt, double mn, double mx, double my, int& nsols, double p1[][4], double p2[][4])
{
    SetVector(evt.p3, p3_);
    SetVector(evt.p4, p4_);
    SetVector(evt.p5, p5_);
    SetVector(evt.p6, p6_);
    SetVector(evt.pmiss, missing_);
    auto sols = Solve(my * GeV, mx * GeV, mn * GeV);
    nsols = sols.size();
    for (auto sol : IntegerRange(sols.size())) {
        SetMomentum(p1[sol], sols[sol].first);
        SetMomentum(p2[sol], sols[sol].second);
    }
}

void Invisible22::SetVector(double momentum[4], LorentzVector<Momentum>& jet)
{
    jet.E() = momentum[0] * GeV;
    jet.Px() = momentum[1] * GeV;
    jet.Py() = momentum[2] * GeV;
    jet.Pz() = momentum[3] * GeV;
}

void Invisible22::SetMomentum(double momentum[4], const LorentzVector<Momentum>& jet)
{
    momentum[0] = jet.E() / GeV;
    momentum[1] = jet.Px() / GeV;
    momentum[2] = jet.Py() / GeV;
    momentum[3] = jet.Pz() / GeV;
}

std::vector<std::pair<LorentzVector<Momentum>, LorentzVector<Momentum>>> Invisible22::Solve(Mass const& heavy, Mass const& light, Mass const& invisible)
{
    heavy_square_ = sqr(heavy);
    light_square_ = sqr(light);
    invisible_square_ = sqr(invisible);
    missing_.Pz() = 0_GeV;
    missing_.E() = 0_GeV;

    auto coefficients = Coefficients();
    if (coefficients.at(4) == 0.) {
        ERROR("Not a Quartic Equation");
        return {};
    }
    ROOT::Math::Polynomial polynomial(coefficients.size() - 1);
    polynomial.SetParameters(coefficients.data());

    std::vector<std::pair<LorentzVector<Momentum>, LorentzVector<Momentum>>> solutions;
    for (auto const & root : polynomial.FindRealRoots()) if (auto solution = Solution(root * GeV)) solutions.emplace_back(*solution);
    return solutions;
}

std::array< double, 5 > Invisible22::Coefficients()
{
    std::array< double, 5 > coefficients;

    auto factor_1 = VectorA().X() * MatrixB().X().X() - MatrixA().X().X() * VectorB().X();
    auto factor_2 = MatrixA().X().X() * ScalarB() - ScalarA() * MatrixB().X().X();

    coefficients.at(0) = (MatrixA().X().X() * sqr(factor_2) + VectorA().X() * factor_2 * factor_1 + ScalarA() * sqr(factor_1)) / GeV / GeV / GeV / GeV;

    coefficients.at(1) = (- sqr(MatrixA().X().X()) * MatrixA().X().Y() * ScalarB() * VectorB().X()
                          + sqr(MatrixA().X().X()) * VectorA().Y() * sqr(VectorB().X())
                          + 2. * VectorA().X() * MatrixA().X().X() * MatrixA().X().Y() * ScalarB() * MatrixB().X().X()
                          - 2. * sqr(MatrixA().X().X()) * VectorA().Y() * ScalarB() * MatrixB().X().X()
                          - ScalarA() * MatrixA().X().X() * MatrixA().X().Y() * VectorB().X() * MatrixB().X().X()
                          - VectorA().X() * MatrixA().X().X() * VectorA().Y() * VectorB().X() * MatrixB().X().X()
                          + 2. * ScalarA() * MatrixA().X().X() * VectorA().Y() * sqr(MatrixB().X().X())
                          - VectorA().X() * sqr(MatrixA().X().X()) * ScalarB() * MatrixB().X().Y()
                          + 2. * ScalarA() * sqr(MatrixA().X().X()) * VectorB().X() * MatrixB().X().Y()
                          - ScalarA() * VectorA().X() * MatrixA().X().X() * MatrixB().X().X() * MatrixB().X().Y()
                          + 2. * sqr(MatrixA().X().X()) * MatrixA().X().X() * ScalarB() * VectorB().Y()
                          - VectorA().X() * sqr(MatrixA().X().X()) * VectorB().X() * VectorB().Y()
                          + VectorA().X() * VectorA().X() * MatrixA().X().X() * MatrixB().X().X() * VectorB().Y()
                          - 2. * ScalarA() * sqr(MatrixA().X().X()) * MatrixB().X().X() * VectorB().Y()) / GeV / GeV / GeV;

    coefficients.at(2) = (sqr(MatrixA().X().X()) * MatrixA().Y().Y() * sqr(VectorB().X())
                          + MatrixA().X().X() * MatrixA().X().Y() * MatrixA().X().Y() * ScalarB() * MatrixB().X().X()
                          - 2. * sqr(MatrixA().X().X()) * MatrixA().Y().Y() * ScalarB() * MatrixB().X().X()
                          - MatrixA().X().X() * MatrixA().X().Y() * VectorA().Y() * VectorB().X() * MatrixB().X().X()
                          - VectorA().X() * MatrixA().X().X() * MatrixA().Y().Y() * VectorB().X() * MatrixB().X().X()
                          + MatrixA().X().X() * VectorA().Y() * VectorA().Y() * sqr(MatrixB().X().X())
                          + 2. * ScalarA() * MatrixA().X().X() * MatrixA().Y().Y() * sqr(MatrixB().X().X())
                          - sqr(MatrixA().X().X()) * MatrixA().X().Y() * ScalarB() * MatrixB().X().Y()
                          + 2. * sqr(MatrixA().X().X()) * VectorA().Y() * VectorB().X() * MatrixB().X().Y()
                          - ScalarA() * MatrixA().X().X() * MatrixA().X().Y() * MatrixB().X().X() * MatrixB().X().Y()
                          - VectorA().X() * MatrixA().X().X() * VectorA().Y() * MatrixB().X().X() * MatrixB().X().Y()
                          + ScalarA() * sqr(MatrixA().X().X()) * MatrixB().X().Y() * MatrixB().X().Y()
                          - sqr(MatrixA().X().X()) * MatrixA().X().Y() * VectorB().X() * VectorB().Y()
                          + 2. * VectorA().X() * MatrixA().X().X() * MatrixA().X().Y() * MatrixB().X().X() * VectorB().Y()
                          - 2. * sqr(MatrixA().X().X()) * VectorA().Y() * MatrixB().X().X() * VectorB().Y()
                          - VectorA().X() * sqr(MatrixA().X().X()) * MatrixB().X().Y() * VectorB().Y()
                          + sqr(MatrixA().X().X()) * MatrixA().X().X() * sqr(VectorB().Y())
                          + 2. * sqr(MatrixA().X().X()) * MatrixA().X().X() * ScalarB() * MatrixB().Y().Y()
                          - VectorA().X() * sqr(MatrixA().X().X()) * VectorB().X() * MatrixB().Y().Y()
                          + VectorA().X() * VectorA().X() * MatrixA().X().X() * MatrixB().X().X() * MatrixB().Y().Y()
                          - 2. * ScalarA() * sqr(MatrixA().X().X()) * MatrixB().X().X() * MatrixB().Y().Y()) / GeV / GeV;

    coefficients.at(3) = (- MatrixA().X().X() * MatrixA().X().Y() * MatrixA().Y().Y() * VectorB().X() * MatrixB().X().X()
                          + 2. * MatrixA().X().X() * VectorA().Y() * MatrixA().Y().Y() * sqr(MatrixB().X().X())
                          + 2. * sqr(MatrixA().X().X()) * MatrixA().Y().Y() * VectorB().X() * MatrixB().X().Y()
                          - MatrixA().X().X() * MatrixA().X().Y() * VectorA().Y() * MatrixB().X().X() * MatrixB().X().Y()
                          - VectorA().X() * MatrixA().X().X() * MatrixA().Y().Y() * MatrixB().X().X() * MatrixB().X().Y()
                          + sqr(MatrixA().X().X()) * VectorA().Y() * MatrixB().X().Y() * MatrixB().X().Y()
                          + MatrixA().X().X() * MatrixA().X().Y() * MatrixA().X().Y() * MatrixB().X().X() * VectorB().Y()
                          - 2. * sqr(MatrixA().X().X()) * MatrixA().Y().Y() * MatrixB().X().X() * VectorB().Y()
                          - sqr(MatrixA().X().X()) * MatrixA().X().Y() * MatrixB().X().Y() * VectorB().Y()
                          - sqr(MatrixA().X().X()) * MatrixA().X().Y() * VectorB().X() * MatrixB().Y().Y()
                          + 2. * VectorA().X() * MatrixA().X().X() * MatrixA().X().Y() * MatrixB().X().X() * MatrixB().Y().Y()
                          - 2. * sqr(MatrixA().X().X()) * VectorA().Y() * MatrixB().X().X() * MatrixB().Y().Y()
                          - VectorA().X() * sqr(MatrixA().X().X()) * MatrixB().X().Y() * MatrixB().Y().Y()
                          + 2. * sqr(MatrixA().X().X()) * MatrixA().X().X() * VectorB().Y() * MatrixB().Y().Y()) / GeV;

    coefficients.at(4) = MatrixA().X().X() * sqr(MatrixA().Y().Y()) * sqr(MatrixB().X().X())
                         - MatrixA().X().X() * MatrixA().X().Y() * MatrixA().Y().Y() * MatrixB().X().X() * MatrixB().X().Y()
                         + sqr(MatrixA().X().X()) * MatrixA().Y().Y() * MatrixB().X().Y() * MatrixB().X().Y()
                         + MatrixA().X().X() * MatrixA().X().Y() * MatrixA().X().Y() * MatrixB().X().X() * MatrixB().Y().Y()
                         - 2. * sqr(MatrixA().X().X()) * MatrixA().Y().Y() * MatrixB().X().X() * MatrixB().Y().Y()
                         - sqr(MatrixA().X().X()) * MatrixA().X().Y() * MatrixB().X().Y() * MatrixB().Y().Y()
                         + sqr(MatrixA().X().X()) * MatrixA().X().X() * MatrixB().Y().Y() * MatrixB().Y().Y();

    return coefficients;
}

Matrix2<double> Invisible22::MatrixA()
{
    return matrix_a_.Get([&]() {
        Matrix2<double> matrix;
        matrix.X().X() = sqr(CoefficientVector1().Vector()) - 1.;
        matrix.Y().Y() = sqr(CoefficientVector2().Vector());
        matrix.X().Y() = 2. * CoefficientVector1().Vector() * CoefficientVector2().Vector();
        return matrix;
    });
}

Matrix2<double> Invisible22::MatrixB()
{
    return matrix_b_.Get([&]() {
        Matrix2<double> matrix;
        matrix.X().X() = CoefficientVector1().Euclidean(CoefficientVector1()) - 2. * CoefficientVector1().Z() * CoefficientVector1().T();
        matrix.Y().Y() = -1. + CoefficientVector2().Euclidean(CoefficientVector2()) - 2. * CoefficientVector2().Z() * CoefficientVector2().T();
        matrix.X().Y() = 2. * (CoefficientVector1().Euclidean(CoefficientVector2()) - CoefficientVector2().Z() * CoefficientVector1().T() - CoefficientVector1().Z() * CoefficientVector2().T());
        return matrix;
    });
}

Vector2< Momentum > Invisible22::VectorA()
{
    return vector_a_.Get([&]() {
        Vector2<Momentum> vector;
        vector.X() = 2. * CoefficientVector().Vector() * CoefficientVector1().Vector();
        vector.Y() = 2. * CoefficientVector().Vector() * CoefficientVector2().Vector();
        return vector;
    });
}

Vector2< Momentum > Invisible22::VectorB()
{
    return vector_b_.Get([&]() {
        Vector2<Momentum> vector;
        vector.X() = 2. * (CoefficientVector().Euclidean(CoefficientVector1()) - CoefficientVector1().Z() * CoefficientVector().T() - CoefficientVector().Z() * CoefficientVector1().T() + CoefficientVector1() * missing_);
        vector.Y() = 2. * (CoefficientVector().Euclidean(CoefficientVector2()) - CoefficientVector2().Z() * CoefficientVector().T() - CoefficientVector().Z() * CoefficientVector2().T() + CoefficientVector2() * missing_);
        return vector;
    });
}

MomentumSquare Invisible22::ScalarA()
{
    return scalar_a_.Get([&]() {
        return sqr(CoefficientVector().Vector()) + invisible_square_;
    });
}

MomentumSquare Invisible22::ScalarB()
{
    return scalar_b_.Get([&]() {
        return CoefficientVector().Euclidean(CoefficientVector()) + invisible_square_ - sqr(missing_) - 2. * CoefficientVector().Z() * CoefficientVector().T() + 2. * (CoefficientVector() * missing_);
    });
}

LorentzVector< double > Invisible22::CoefficientVector1() const
{
    return coefficient_vector_1_.Get([&]() {
        Matrix2<Momentum> matrix_35( {p3_.Z(), p3_.E()}, {p5_.Z(), p5_.E()});
        Matrix3<Momentum> matrix_345(p3_.Vector(), p4_.Vector(), p5_.Vector());
        Matrix3<Momentum> matrix_356(p3_.Vector(), p5_.Vector(), p6_.Vector());
        Matrix3<Momentum> matrix_346(p3_.Vector(), p4_.Vector(), p6_.Vector());
        Matrix3<Momentum> matrix_456(p4_.Vector(), p5_.Vector(), p6_.Vector());
        auto red_det_3 = matrix_456.ReducedDeterminant(Dim3::y, Dim3::z);
        auto red_det_4 = matrix_356.ReducedDeterminant(Dim3::z, Dim3::z);
        auto red_det_5 = matrix_346.ReducedDeterminant(Dim3::x, Dim3::z);
        auto red_det_6 = matrix_345.ReducedDeterminant(Dim3::y, Dim3::z);
        auto denominator = p5_.Pz() * red_det_5 + p3_.Pz() * red_det_3;

        LorentzVector<double> vector;
        vector.X() = matrix_35.Determinant() * matrix_456.Cofactor(Dim3::y, Dim3::x) / (p4_.Z() * red_det_4 + p6_.Z() * red_det_6);
        vector.Y() = matrix_35.Determinant() * matrix_456.Cofactor(Dim3::y, Dim3::y) / denominator;
        vector.Z() = (p5_.E() * red_det_5 + p3_.E() * red_det_3) / denominator;
        vector.T() = (p5_.E() * matrix_346.Determinant() + p3_.E() * matrix_456.Determinant()) / denominator;
        return vector;
    });
}

LorentzVector< double > Invisible22::CoefficientVector2() const
{
    return coefficient_vector_2_.Get([&]() {
        Matrix2<Momentum> matrix_46( {p4_.Z(), p4_.E()}, {p6_.Z(), p6_.E()});
        Matrix3<Momentum> matrix_345(p3_.Vector(), p4_.Vector(), p5_.Vector());
        Matrix3<Momentum> matrix_356(p3_.Vector(), p5_.Vector(), p6_.Vector());
        Matrix3<Momentum> matrix_346(p3_.Vector(), p4_.Vector(), p6_.Vector());
        Matrix3<Momentum> matrix_456(p4_.Vector(), p5_.Vector(), p6_.Vector());
        auto red_det_3 = matrix_456.ReducedDeterminant(Dim3::y, Dim3::z);
        auto red_det_4 = matrix_356.ReducedDeterminant(Dim3::z, Dim3::z);
        auto red_det_5 = matrix_346.ReducedDeterminant(Dim3::x, Dim3::z);
        auto red_det_6 = matrix_345.ReducedDeterminant(Dim3::y, Dim3::z);
        auto denominator = p5_.Pz() * red_det_5 + p3_.Pz() * red_det_3;

        LorentzVector<double> vector;
        vector.X() = matrix_46.Determinant() * matrix_345.Cofactor(Dim3::y, Dim3::x) / (p4_.Z() * red_det_4 + p6_.Z() * red_det_6);
        vector.Y() = matrix_46.Determinant() * matrix_345.Cofactor(Dim3::y, Dim3::y) / denominator;
        vector.Z() = matrix_46.Determinant() * matrix_345.Cofactor(Dim3::y, Dim3::z) / denominator;
        vector.T() = (p6_.E() * matrix_345.Determinant() + p4_.E() * matrix_356.Determinant()) / denominator;
        return vector;
    });
}

using Momentum5 = typename boost::units::power_typeof_helper<Momentum, boost::units::static_rational<5>>::type;

LorentzVector< Momentum > Invisible22::CoefficientVector() const
{
    return coefficient_vector_.Get([&]() {
        auto mass_4 = light_square_ - invisible_square_ - sqr(p4_);
        auto mass_3 = light_square_ - invisible_square_ - sqr(p3_);
        auto mass_46 = heavy_square_ - light_square_ - sqr(p4_ + p6_) + sqr(p4_);
        auto mass_35 = heavy_square_ - light_square_ - sqr(p3_ + p5_) + sqr(p3_);

        Matrix3<Momentum> matrix_345(p3_.Vector(), p4_.Vector(), p5_.Vector());
        Matrix3<Momentum> matrix_356(p3_.Vector(), p5_.Vector(), p6_.Vector());
        Matrix3<Momentum> matrix_346(p3_.Vector(), p4_.Vector(), p6_.Vector());
        Matrix3<Momentum> matrix_456(p4_.Vector(), p5_.Vector(), p6_.Vector());
        auto red_det_3 = matrix_456.ReducedDeterminant(Dim3::y, Dim3::z);
        auto red_det_5 = matrix_346.ReducedDeterminant(Dim3::x, Dim3::z);

        auto missing3 = 2. * (missing_ * p3_);
        auto missing4 = 2. * (missing_ * p4_);
        auto missing5 = 2. * (missing_ * p5_);
        auto missing6 = 2. * (missing_ * p6_);

        auto factor_35 = p6_.Pz() * (mass_4 - missing4) - p4_.Pz() * (mass_46 - missing6);
        auto factor_46 = p5_.Pz() * mass_3 - p3_.Pz() * mass_35;

        LorentzVector<Momentum5> vector;
        vector.X() = factor_46 * matrix_456.Cofactor(Dim3::y, Dim3::x) + factor_35 * matrix_345.Cofactor(Dim3::y, Dim3::x);
        vector.Y() = factor_46 * matrix_456.Cofactor(Dim3::y, Dim3::y) + factor_35 * matrix_345.Cofactor(Dim3::y, Dim3::y);
        vector.Z() = factor_35 * matrix_345.Cofactor(Dim3::y, Dim3::z) - mass_3 * red_det_3 - mass_35 * red_det_5;
        vector.T() =  - mass_46 * matrix_345.Determinant()
                      - mass_4 * matrix_356.Determinant()
                      - mass_35 * matrix_346.Determinant()
                      - mass_3 * matrix_456.Determinant()
                      - (p6_.Pz() * missing4 - p4_.Pz() * missing6) * matrix_345.Cofactor(Dim3::y, Dim3::z)
                      - (p3_.Pz() * missing5 - p5_.Pz() * missing3) * matrix_456.Cofactor(Dim3::y, Dim3::z);
        auto denominator = 2. * (p5_.Pz() * red_det_5 + p3_.Pz() * red_det_3);
        return vector / denominator;
    });
}

boost::optional<std::pair<LorentzVector<Momentum>, LorentzVector<Momentum>>> Invisible22::Solution(const Momentum& root)
{
    LorentzVector<Momentum> vector_2;
    vector_2.E() = root;
    LorentzVector<Momentum> vector_1;
    vector_1.E() = Energy1(vector_2.E());
    if (vector_1.E() <= 0_eV || vector_2.E() <= 0_eV) return boost::none;
    vector_1.Vector() = CoefficientVector1().Vector() * vector_1.E() + CoefficientVector2().Vector() * vector_2.E() + CoefficientVector().Vector();
    vector_2.Vector() = missing_.Vector() - vector_1.Vector();
    vector_2.Z() += CoefficientVector1().T() * vector_1.E() + CoefficientVector2().T() * vector_2.E() + CoefficientVector().T();
    return std::make_pair(vector_1, vector_2);
}

Energy Invisible22::Energy1(Energy const& energy_2)
{
    // substitute p2.E() solution into general p1.E() solution in terms of p2.E()
    return (
               MatrixA().X().X() * ScalarB()
               - ScalarA() * MatrixB().X().X()
               - VectorA().Y() * MatrixB().X().X() * energy_2
               + MatrixA().X().X() * VectorB().Y() * energy_2
               - MatrixA().Y().Y() * MatrixB().X().X() * sqr(energy_2)
               + MatrixA().X().X() * MatrixB().Y().Y() * sqr(energy_2)
           ) / (
               - MatrixA().X().X() * VectorB().X()
               + VectorA().X() * MatrixB().X().X()
               + MatrixA().X().Y() * MatrixB().X().X() * energy_2
               - MatrixA().X().X() * MatrixB().X().Y() * energy_2
           );
}

}

}

