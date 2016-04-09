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
#include "external/Invisible2.hh"
#include "generic/Types.hh"
#include "multiplets/Quartet.hh"
#include "generic/DEBUG.hh"

namespace boca
{

namespace wimpmass
{

Invisible22::Invisible22() {}

Invisible22::Invisible22(const LorentzVector< Momentum >& missing) :
    missing_(missing) {}

Invisible22::Invisible22(const Quartet22& quartet, const LorentzVector< Momentum >& missing) :
    missing_(missing)
{
//     Set(quartet);
}

void Invisible22::SetMissingMomentum(const LorentzVector< Momentum >& missing)
{
    missing_ = missing;
}

// void Invisible22::Set(const Quartet22& quartet)
// {
//     SetFirstChain(quartet.Doublet1());
//     SetSecondChain(quartet.Doublet2());
// }

// void Invisible22::SetFirstChain(const Doublet& doublet)
// {
//     p3_ = doublet.Singlet2().Vector();
//     p5_ = doublet.Singlet1().Vector();
// }
//
// void Invisible22::SetSecondChain(const Doublet& doublet)
// {
//     p4_ = doublet.Singlet2().Vector();
//     p6_ = doublet.Singlet1().Vector();
// }

void Invisible22::SetFirstChain(const LorentzVector< Momentum >& first, const LorentzVector< Momentum >& second)
{
    p3_ = first;
    p5_ = second;
}

void Invisible22::SetSecondChain(const LorentzVector< Momentum >& first, const LorentzVector< Momentum >& second)
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
    for (auto const & sol : IntegerRange(sols.size())) {
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

std::vector<std::pair<LorentzVector<Momentum>, LorentzVector<Momentum>>> Invisible22::Solve(Mass heavy, Mass light, Mass invisible)
{
    missing_ = - missing_;
    missing_.Pz() = 0;

    auto coefficient_vector_1 = CoefficientVector1();
    auto coefficient_vector_2 = CoefficientVector2();
    auto coefficient_vector = CoefficientVector(heavy, light, invisible);

    auto matrix_a = MatrixA(coefficient_vector_1, coefficient_vector_2);
    auto matrix_b = MatrixB(coefficient_vector_1, coefficient_vector_2);

    auto vector_a = VectorA(coefficient_vector, coefficient_vector_1, coefficient_vector_2);
    auto vector_b = VectorB(coefficient_vector, coefficient_vector_1, coefficient_vector_2);

    auto scalar_a = ScalarA(coefficient_vector, invisible);
    auto scalar_b = ScalarB(coefficient_vector, invisible);

    auto coefficients = Coefficients(matrix_a, matrix_b, vector_a, vector_b, scalar_a, scalar_b);
    if (coefficients.at(4) == 0) {
        ERROR("Not a Quartic Equation");
        return {};
    }
    ROOT::Math::Polynomial polynomial(coefficients.size() - 1);
    polynomial.SetParameters(coefficients.data());

    std::vector<std::pair<LorentzVector<Momentum>, LorentzVector<Momentum>>> solutions;
    for (auto const & root : polynomial.FindRealRoots()) {
        LorentzVector<Momentum> vector_2;
        vector_2.E() = root * GeV;
        LorentzVector<Momentum> vector_1;
        vector_1.E() = Energy1(matrix_a, matrix_b, vector_a, vector_b, scalar_a, scalar_b, vector_2.E());

        if (vector_1.E() <= 0_eV || vector_2.E() <= 0_eV) continue;

        vector_1.Vector() = coefficient_vector_1.Vector() * vector_1.E() + coefficient_vector_2.Vector() * vector_2.E() + coefficient_vector.Vector();

        auto pz_tot = coefficient_vector_1.T() * vector_1.E() + coefficient_vector_2.T() * vector_2.E() + coefficient_vector.T();

        vector_2.Vector() = - missing_.Vector() - vector_1.Vector();
        vector_2.Z() += pz_tot ;

        solutions.emplace_back(std::make_pair(vector_1, vector_2));
    }
    return solutions;

}

LorentzVector< double > Invisible22::CoefficientVector1() const
{
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
    vector.X() = matrix_35.Determinant() * matrix_456.SignedMinor(Dim3::y, Dim3::x) / (p4_.Z() * red_det_4 + p6_.Z() * red_det_6);
    vector.Y() = matrix_35.Determinant() * matrix_456.SignedMinor(Dim3::y, Dim3::y) / denominator;
    vector.Z() = (p5_.E() * red_det_5 + p3_.E() * red_det_3) / denominator;
    vector.T() = (p5_.E() * matrix_346.Determinant() + p3_.E() * matrix_456.Determinant()) / denominator;
    return vector;
}

LorentzVector< double > Invisible22::CoefficientVector2() const
{
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
    vector.X() = matrix_46.Determinant() * matrix_345.SignedMinor(Dim3::y, Dim3::x) / (p4_.Z() * red_det_4 + p6_.Z() * red_det_6);
    vector.Y() = matrix_46.Determinant() * matrix_345.SignedMinor(Dim3::y, Dim3::y) / denominator;
    vector.Z() = matrix_46.Determinant() * matrix_345.SignedMinor(Dim3::y, Dim3::z) / denominator;
    vector.T() = (p6_.E() * matrix_345.Determinant() + p4_.E() * matrix_356.Determinant()) / denominator;
    return vector;
}

LorentzVector< Momentum > Invisible22::CoefficientVector(Mass heavy, Mass light, Mass invisible) const
{
    auto m531sq = sqr(heavy);
    auto m642sq = m531sq;
    auto m31sq = sqr(light);
    auto m42sq = m31sq;
    auto m1sq = sqr(invisible);
    auto m2sq = m1sq;

    auto m3sq = sqr(p3_);
    if (m3sq < 0_eV * eV) m3sq = 0_eV * eV;

    auto m4sq = sqr(p4_);
    if (m4sq < 0_eV * eV) m4sq = 0_eV * eV;

    auto m5sq = sqr(p5_);
    if (m5sq < 0_eV * eV) m5sq = 0_eV * eV;

    auto m6sq = sqr(p6_);
    if (m6sq < 0_eV * eV) m6sq = 0_eV * eV;

    auto p3dp5 = p3_ * p5_;
    auto p4dp6 = p4_ * p6_;

    auto del2b = m3sq + m1sq - m31sq + m42sq - m2sq - m4sq;
    auto del3b = m31sq + m5sq - m531sq + m642sq - m42sq - m6sq + 2.*p3dp5 - 2.*p4dp6;
    auto del31 = m31sq - m1sq - m3sq;
    auto del531 = m531sq - m31sq - m5sq - 2.0 * p3dp5;



    Matrix2<Momentum> matrix_46( {p4_.Z(), p4_.E()}, {p6_.Z(), p6_.E()});
    Matrix3<Momentum> matrix_345(p3_.Vector(), p4_.Vector(), p5_.Vector());
    Matrix3<Momentum> matrix_356(p3_.Vector(), p5_.Vector(), p6_.Vector());
    Matrix3<Momentum> matrix_346(p3_.Vector(), p4_.Vector(), p6_.Vector());
    Matrix3<Momentum> matrix_456(p4_.Vector(), p5_.Vector(), p6_.Vector());
    auto red_det_3 = matrix_456.ReducedDeterminant(Dim3::y, Dim3::z);
    auto red_det_4 = matrix_356.ReducedDeterminant(Dim3::z, Dim3::z);
    auto red_det_5 = matrix_346.ReducedDeterminant(Dim3::x, Dim3::z);
    auto red_det_6 = matrix_345.ReducedDeterminant(Dim3::y, Dim3::z);
    auto denominator = 2. * (p5_.Pz() * red_det_5 + p3_.Pz() * red_det_3);

    Matrix2<Momentum> matrix_35( {p3_.Y(), p3_.Z()}, {p5_.Y(), p5_.Z()});
    Matrix2<Momentum> matrix_46_( {p4_.Y(), p4_.Z()}, {p6_.Y(), p6_.Z()});

    LorentzVector<Momentum> vector;


    vector.X() = (
                     + p3_.Pz() * del531 * matrix_346.SignedMinor(Dim3::x, Dim3::x)
                     - p4_.Pz() * (del3b + del531) * matrix_345.SignedMinor(Dim3::y, Dim3::x)
                     + p5_.Pz() * del31 * matrix_456.SignedMinor(Dim3::y, Dim3::x)
                     + p6_.Pz() * (del2b + del31) * matrix_345.SignedMinor(Dim3::y, Dim3::x)
                     + 2. * p6_.Pz() * matrix_356.SignedMinor(Dim3::z, Dim3::x) * missing_.Vector() * p4_.Vector()
                     + 2. * p4_.Pz() * matrix_345.SignedMinor(Dim3::y, Dim3::x) * missing_.Vector() * p6_.Vector()
                 ) / denominator;

    vector.Y() = (
                     + p3_.Pz() * del531 * matrix_346.SignedMinor(Dim3::x, Dim3::y)
                     - p4_.Pz() * (del3b + del531) * matrix_345.SignedMinor(Dim3::y, Dim3::y)
                     + p5_.Pz() * del31 * matrix_456.SignedMinor(Dim3::y, Dim3::y)
                     + p6_.Pz() * (del31 + del2b) * matrix_345.SignedMinor(Dim3::y, Dim3::y)

                     + 2. * p6_.Pz() * matrix_356.SignedMinor(Dim3::z, Dim3::y) * missing_.Vector() * p4_.Vector()
                     + 2. * p4_.Pz() * matrix_345.SignedMinor(Dim3::y, Dim3::y) * missing_.Vector() * p6_.Vector()
                 ) / denominator;


    vector.Z() = - ((
                        + p4_.Pz() * (del3b + del531) * matrix_345.SignedMinor(Dim3::y, Dim3::z)
                        - p6_.Pz() * (del2b + del31) * matrix_345.SignedMinor(Dim3::y, Dim3::z)
                        + del31 * matrix_456.ReducedDeterminant(Dim3::y, Dim3::z)
                        + del531 * matrix_346.ReducedDeterminant(Dim3::x, Dim3::z)
                        - 2. * p6_.Pz() * matrix_356.SignedMinor(Dim3::z, Dim3::z) * missing_.Vector() * p4_.Vector()
                        - 2. * p4_.Pz() * matrix_345.SignedMinor(Dim3::y, Dim3::z) * missing_.Vector() * p6_.Vector()
                    ) / denominator);

    vector.T() = (
                     - (del3b + del531) * matrix_345.Determinant()
                     - del531 * matrix_346.Determinant()
                     - del31 * matrix_456.Determinant()
                     - (del2b + del31) * matrix_356.Determinant()

                     - 2. * p3_.Pz() * p4_.Py() * p5_.Px() * p6_.Px() * missing_.Px()
                     + 2. * p3_.Py() * p4_.Pz() * p5_.Px() * p6_.Px() * missing_.Px()
                     - 2. * p3_.Px() * p4_.Pz() * p5_.Py() * p6_.Px() * missing_.Px()
                     + 2. * p3_.Px() * p4_.Py() * p5_.Pz() * p6_.Px() * missing_.Px()
                     + 2. * p3_.Pz() * p4_.Px() * p5_.Px() * p6_.Py() * missing_.Px()
                     - 2. * p3_.Px() * p4_.Px() * p5_.Pz() * p6_.Py() * missing_.Px()
                     - 2. * p3_.Py() * p4_.Px() * p5_.Px() * p6_.Pz() * missing_.Px()
                     + 2. * p3_.Px() * p4_.Px() * p5_.Py() * p6_.Pz() * missing_.Px()
                     - 2. * p3_.Pz() * p4_.Py() * p5_.Py() * p6_.Px() * missing_.Py()
                     + 2. * p3_.Py() * p4_.Py() * p5_.Pz() * p6_.Px() * missing_.Py()
                     + 2. * p3_.Py() * p4_.Pz() * p5_.Px() * p6_.Py() * missing_.Py()
                     + 2. * p3_.Pz() * p4_.Px() * p5_.Py() * p6_.Py() * missing_.Py()
                     - 2. * p3_.Px() * p4_.Pz() * p5_.Py() * p6_.Py() * missing_.Py()
                     - 2. * p3_.Py() * p4_.Px() * p5_.Pz() * p6_.Py() * missing_.Py()
                     - 2. * p3_.Py() * p4_.Py() * p5_.Px() * p6_.Pz() * missing_.Py()
                     + 2. * p3_.Px() * p4_.Py() * p5_.Py() * p6_.Pz() * missing_.Py()
                     - 2. * p3_.Pz() * p4_.Pz() * p5_.Py() * p6_.Px() * missing_.Pz()
                     + 2. * p3_.Py() * p4_.Pz() * p5_.Pz() * p6_.Px() * missing_.Pz()
                     + 2. * p3_.Pz() * p4_.Pz() * p5_.Px() * p6_.Py() * missing_.Pz()
                     - 2. * p3_.Px() * p4_.Pz() * p5_.Pz() * p6_.Py() * missing_.Pz()
                     - 2. * p3_.Pz() * p4_.Py() * p5_.Px() * p6_.Pz() * missing_.Pz()
                     + 2. * p3_.Pz() * p4_.Px() * p5_.Py() * p6_.Pz() * missing_.Pz()
                     - 2. * p3_.Py() * p4_.Px() * p5_.Pz() * p6_.Pz() * missing_.Pz()
                     + 2. * p3_.Px() * p4_.Py() * p5_.Pz() * p6_.Pz() * missing_.Pz()
                 ) / denominator;




                 auto test1 =

//                  - 2. * p3_.Py() * p4_.Px() * p5_.Px() * p6_.Pz() * missing_.Px()
//                  + 2. * p3_.Px() * p4_.Px() * p5_.Py() * p6_.Pz() * missing_.Px()
//                  - 2. * p3_.Py() * p4_.Py() * p5_.Px() * p6_.Pz() * missing_.Py()
//                  + 2. * p3_.Px() * p4_.Py() * p5_.Py() * p6_.Pz() * missing_.Py()

                 + 2. * p3_.Py() * p4_.Pz() * p5_.Px() * p6_.Px() * missing_.Px()
                 - 2. * p3_.Px() * p4_.Pz() * p5_.Py() * p6_.Px() * missing_.Px()
                 + 2. * p3_.Py() * p4_.Pz() * p5_.Px() * p6_.Py() * missing_.Py()
                 - 2. * p3_.Px() * p4_.Pz() * p5_.Py() * p6_.Py() * missing_.Py()


//                  + 2. * p3_.Pz() * p4_.Px() * p5_.Px() * p6_.Py() * missing_.Px()
//                  - 2. * p3_.Px() * p4_.Px() * p5_.Pz() * p6_.Py() * missing_.Px()
//                  - 2. * p3_.Pz() * p4_.Py() * p5_.Py() * p6_.Px() * missing_.Py()
//                  + 2. * p3_.Py() * p4_.Py() * p5_.Pz() * p6_.Px() * missing_.Py()

//                  - 2. * p3_.Pz() * p4_.Py() * p5_.Px() * p6_.Px() * missing_.Px()
//                  + 2. * p3_.Px() * p4_.Py() * p5_.Pz() * p6_.Px() * missing_.Px()
//
//                  + 2. * p3_.Pz() * p4_.Px() * p5_.Py() * p6_.Py() * missing_.Py()
//                  - 2. * p3_.Py() * p4_.Px() * p5_.Pz() * p6_.Py() * missing_.Py()

//                  - 2. * p3_.Pz() * p4_.Pz() * p5_.Py() * p6_.Px() * missing_.Pz()
//                  + 2. * p3_.Py() * p4_.Pz() * p5_.Pz() * p6_.Px() * missing_.Pz()
//                  + 2. * p3_.Pz() * p4_.Pz() * p5_.Px() * p6_.Py() * missing_.Pz()
//                  - 2. * p3_.Px() * p4_.Pz() * p5_.Pz() * p6_.Py() * missing_.Pz()
//
//                  - 2. * p3_.Pz() * p4_.Py() * p5_.Px() * p6_.Pz() * missing_.Pz()
//                  + 2. * p3_.Pz() * p4_.Px() * p5_.Py() * p6_.Pz() * missing_.Pz()
//                  - 2. * p3_.Py() * p4_.Px() * p5_.Pz() * p6_.Pz() * missing_.Pz()
//                  + 2. * p3_.Px() * p4_.Py() * p5_.Pz() * p6_.Pz() * missing_.Pz()
        ;

    auto test2 =
//          2. * p6_.Pz() * matrix_356.SignedMinor(Dim3::z, Dim3::z) * missing_.Vector() * p4_.Vector()
        + 2. * p4_.Pz() * matrix_345.SignedMinor(Dim3::y, Dim3::z) * missing_.Vector() * p6_.Vector()

        ;
    ERROR(test1, test2);


    return vector;
}


Matrix2<double> Invisible22::MatrixA(LorentzVector<double> const& ce1, LorentzVector<double> const& ce2)
{
    Matrix2<double> matrix;
    matrix.X().X() = sqr(ce1.Vector()) - 1.;
    matrix.Y().Y() = sqr(ce2.Vector());
    matrix.X().Y() = 2. * ce1.Vector() * ce2.Vector();
    return matrix;
}

Matrix2<double> Invisible22::MatrixB(LorentzVector<double> const& ce1, LorentzVector<double> const& ce2)
{
    Matrix2<double> matrix;
    matrix.X().X() = sqr(ce1.Vector()) - 2. * ce1.Z() * ce1.T() + ce1.T() * ce1.T();
    matrix.Y().Y() = -1. + sqr(ce2.Vector()) - 2. * ce2.Z() * ce2.T() + ce2.T() * ce2.T();
    matrix.X().Y() = 2. * ce1.Vector() * ce2.Vector() - 2. * ce2.Z() * ce1.T() - 2. * ce1.Z() * ce2.T() + 2. * ce1.T() * ce2.T();
    return matrix;
}

Vector2< Momentum > Invisible22::VectorA(const LorentzVector< Momentum >& c, const LorentzVector< double >& ce1, const LorentzVector< double >& ce2)
{
    Vector2<Momentum> vector;
    vector.X() = 2. * c.Vector() * ce1.Vector();
    vector.Y() = 2. * c.Vector() * ce2.Vector();
    return vector;
}

Vector2< Momentum > Invisible22::VectorB(const LorentzVector< Momentum >& c, const LorentzVector< double >& ce1, const LorentzVector< double >& ce2)
{
    Vector2<Momentum> vector;
    vector.X() = 2. * c.Vector() * ce1.Vector()
                 - 2. * ce1.Z() * c.T()
                 - 2. * c.Z() * ce1.T()
                 + 2. * c.T() * ce1.T()
                 + 2. * ce1.Vector() * missing_.Vector()
                 - 2. * ce1.T() * missing_.Pz();
    vector.Y() = 2. * c.Vector() * ce2.Vector()
                 - 2. * ce2.Z() * c.T()
                 - 2. * c.Z() * ce2.T()
                 + 2. * c.T() * ce2.T()
                 + 2. * ce2.Vector() * missing_.Vector()
                 - 2. * ce2.T() * missing_.Pz();
    return vector;
}

MomentumSquare Invisible22::ScalarA(const LorentzVector< Momentum >& c, Mass invisible)
{
    return sqr(c.Vector()) + sqr(invisible);
}

MomentumSquare Invisible22::ScalarB(const LorentzVector< Momentum >& c, Mass invisible)
{
    return sqr(c.Vector())
           - 2. * c.Z() * c.T()
           + c.T() * c.T()
           + sqr(invisible)
           + sqr(missing_.Vector())
           + 2. * c.Vector() * missing_.Vector()
           - 2. * c.T() * missing_.Pz() ;
}

std::array< double, 5 > Invisible22::Coefficients(Matrix2<double> const& ma, Matrix2<double> const& mb, Vector2<Momentum> const& va, Vector2<Momentum> const& vb, MomentumSquare a, MomentumSquare b)
{
    std::array< double, 5 > coefficients;

    coefficients.at(0) = (ma.X().X() * (ma.X().X() * b - a * mb.X().X()) * (ma.X().X() * b - a * mb.X().X())
                          + va.X() * (ma.X().X() * b - a * mb.X().X()) * (-(ma.X().X() * vb.X()) + va.X() * mb.X().X())
                          + a * (-(ma.X().X() * vb.X()) + va.X() * mb.X().X()) * (-(ma.X().X() * vb.X()) + va.X() * mb.X().X())) / GeV / GeV / GeV / GeV;

    coefficients.at(1) = (-(sqr(ma.X().X()) * ma.X().Y() * b * vb.X())
                          + sqr(ma.X().X()) * va.Y() * vb.X() * vb.X()
                          + 2. * va.X() * ma.X().X() * ma.X().Y() * b * mb.X().X()
                          - 2. * sqr(ma.X().X()) * va.Y() * b * mb.X().X()
                          - a * ma.X().X() * ma.X().Y() * vb.X() * mb.X().X()
                          - va.X() * ma.X().X() * va.Y() * vb.X() * mb.X().X()
                          + 2. * a * ma.X().X() * va.Y() * sqr(mb.X().X())
                          - va.X() * sqr(ma.X().X()) * b * mb.X().Y()
                          + 2. * a * sqr(ma.X().X()) * vb.X() * mb.X().Y()
                          - a * va.X() * ma.X().X() * mb.X().X() * mb.X().Y()
                          + 2. * sqr(ma.X().X()) * ma.X().X() * b * vb.Y()
                          - va.X() * sqr(ma.X().X()) * vb.X() * vb.Y()
                          + va.X() * va.X() * ma.X().X() * mb.X().X() * vb.Y()
                          - 2. * a * sqr(ma.X().X()) * mb.X().X() * vb.Y()) / GeV / GeV / GeV;

    coefficients.at(2) = (sqr(ma.X().X()) * ma.Y().Y() * vb.X() * vb.X()
                          + ma.X().X() * ma.X().Y() * ma.X().Y() * b * mb.X().X()
                          - 2. * sqr(ma.X().X()) * ma.Y().Y() * b * mb.X().X()
                          - ma.X().X() * ma.X().Y() * va.Y() * vb.X() * mb.X().X()
                          - va.X() * ma.X().X() * ma.Y().Y() * vb.X() * mb.X().X()
                          + ma.X().X() * va.Y() * va.Y() * sqr(mb.X().X())
                          + 2. * a * ma.X().X() * ma.Y().Y() * sqr(mb.X().X())
                          - sqr(ma.X().X()) * ma.X().Y() * b * mb.X().Y()
                          + 2. * sqr(ma.X().X()) * va.Y() * vb.X() * mb.X().Y()
                          - a * ma.X().X() * ma.X().Y() * mb.X().X() * mb.X().Y()
                          - va.X() * ma.X().X() * va.Y() * mb.X().X() * mb.X().Y()
                          + a * sqr(ma.X().X()) * mb.X().Y() * mb.X().Y()
                          - sqr(ma.X().X()) * ma.X().Y() * vb.X() * vb.Y()
                          + 2. * va.X() * ma.X().X() * ma.X().Y() * mb.X().X() * vb.Y()
                          - 2. * sqr(ma.X().X()) * va.Y() * mb.X().X() * vb.Y()
                          - va.X() * sqr(ma.X().X()) * mb.X().Y() * vb.Y()
                          + sqr(ma.X().X()) * ma.X().X() * vb.Y() * vb.Y()
                          + 2. * sqr(ma.X().X()) * ma.X().X() * b * mb.Y().Y()
                          - va.X() * sqr(ma.X().X()) * vb.X() * mb.Y().Y()
                          + va.X() * va.X() * ma.X().X() * mb.X().X() * mb.Y().Y()
                          - 2. * a * sqr(ma.X().X()) * mb.X().X() * mb.Y().Y()) / GeV / GeV;

    coefficients.at(3) = (-(ma.X().X() * ma.X().Y() * ma.Y().Y() * vb.X() * mb.X().X())
                          + 2. * ma.X().X() * va.Y() * ma.Y().Y() * sqr(mb.X().X())
                          + 2. * sqr(ma.X().X()) * ma.Y().Y() * vb.X() * mb.X().Y()
                          - ma.X().X() * ma.X().Y() * va.Y() * mb.X().X() * mb.X().Y()
                          - va.X() * ma.X().X() * ma.Y().Y() * mb.X().X() * mb.X().Y()
                          + sqr(ma.X().X()) * va.Y() * mb.X().Y() * mb.X().Y()
                          + ma.X().X() * ma.X().Y() * ma.X().Y() * mb.X().X() * vb.Y()
                          - 2. * sqr(ma.X().X()) * ma.Y().Y() * mb.X().X() * vb.Y()
                          - sqr(ma.X().X()) * ma.X().Y() * mb.X().Y() * vb.Y()
                          - sqr(ma.X().X()) * ma.X().Y() * vb.X() * mb.Y().Y()
                          + 2. * va.X() * ma.X().X() * ma.X().Y() * mb.X().X() * mb.Y().Y()
                          - 2. * sqr(ma.X().X()) * va.Y() * mb.X().X() * mb.Y().Y()
                          - va.X() * sqr(ma.X().X()) * mb.X().Y() * mb.Y().Y()
                          + 2. * sqr(ma.X().X()) * ma.X().X() * vb.Y() * mb.Y().Y()) / GeV;

    coefficients.at(4) = ma.X().X() * ma.Y().Y() * ma.Y().Y() * sqr(mb.X().X())
                         - ma.X().X() * ma.X().Y() * ma.Y().Y() * mb.X().X() * mb.X().Y()
                         + sqr(ma.X().X()) * ma.Y().Y() * mb.X().Y() * mb.X().Y()
                         + ma.X().X() * ma.X().Y() * ma.X().Y() * mb.X().X() * mb.Y().Y()
                         - 2. * sqr(ma.X().X()) * ma.Y().Y() * mb.X().X() * mb.Y().Y()
                         - sqr(ma.X().X()) * ma.X().Y() * mb.X().Y() * mb.Y().Y()
                         + sqr(ma.X().X()) * ma.X().X() * mb.Y().Y() * mb.Y().Y();

    return coefficients;
}
Energy Invisible22::Energy1(const Matrix2< double >& ma, const Matrix2< double >& mb, const Vector2< Momentum >& va, const Vector2< Momentum >& vb, MomentumSquare a, MomentumSquare b, Energy energy_2)
{
    // substitute p2.E() solution into general p1.E() solution in terms of p2.E()
    return (ma.X().X() * b - a * mb.X().X() - va.Y() * mb.X().X() * energy_2 + ma.X().X() * vb.Y() * energy_2 - ma.Y().Y() * mb.X().X() * sqr(energy_2) + ma.X().X() * mb.Y().Y() * sqr(energy_2)) / (-(ma.X().X() * vb.X()) + va.X() * mb.X().X() + ma.X().Y() * mb.X().X() * energy_2 - ma.X().X() * mb.X().Y() * energy_2);
}

}

}


