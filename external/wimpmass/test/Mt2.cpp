#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Wimpmass
#include <boost/test/included/unit_test.hpp>

#include "external/wimpmass/wimpmass/Mt2.hh"

/**
* @test Test Mt2
*/
BOOST_AUTO_TEST_SUITE(Mt2)

std::array<double, 3> pa {{ 0.106, 39.0, 12.0 }};
std::array<double, 3> pb {{ 0.106, 119.0, -33.0 }};
std::array<double, 3> pmiss {{ 0, -29.9, 35.9 }};
auto mn = 50.;
auto result = 107.12787909;

BOOST_AUTO_TEST_CASE(Original)
{

    class TestMt2 : public wimpmass::Mt2
    {
    public:
        using wimpmass::Mt2::SetMomenta;
        using wimpmass::Mt2::SetMass;
        using wimpmass::Mt2::GetMt2;
    };

    TestMt2 mt2test;
    mt2test.SetMomenta(pa.data(), pb.data(), pmiss.data());
    mt2test.SetMass(mn);
    BOOST_CHECK_CLOSE(mt2test.GetMt2(), result, 10E-6);
}

BOOST_AUTO_TEST_CASE(Boca)
{
    using namespace boca::units;
    boca::LorentzVector<Momentum> vectora(pa.at(1) * GeV, pa.at(2) * GeV, at_rest, at_rest);
    vectora.SetMag(pa.at(0) * GeV);
    boca::LorentzVector<Momentum> vectorb(pb.at(1) * GeV, pb.at(2) * GeV, at_rest, at_rest);
    vectorb.SetMag(pb.at(0) * GeV);
    boca::LorentzVector<Momentum> vectormiss(pmiss.at(1) * GeV, pmiss.at(2) * GeV, at_rest, at_rest);
    vectormiss.SetMag(pmiss.at(0) * GeV);                   ///< introduces an floating point error of 0.001
    wimpmass::Mt2 mt2(mn * GeV);
    BOOST_CHECK_CLOSE(static_cast<double>(mt2.Get(vectora, vectorb, vectormiss) / GeV), result, 0.001);
}

BOOST_AUTO_TEST_SUITE_END()

// int main()
// {

//pa, pb = {mass, px, py}
//pmiss = {NULL, pxmiss, pymiss}
//mn = invisible particle mass

// }

