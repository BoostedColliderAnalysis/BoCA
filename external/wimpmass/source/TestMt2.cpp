
#include <gtest/gtest.h>

#include "external/wimpmass/wimpmass/Mt2.hh"

namespace wimpmass
{

class TestMt2 :  public Mt2
{

public:

    using Mt2::SetMomenta;
    using Mt2::SetMass;
    using Mt2::GetMt2;

};

}

using namespace boca::units;

TEST(Wimpmass, Mt2)
{
    std::array<double, 3> pa {{ 0.106, 39.0, 12.0 }};
    std::array<double, 3> pb {{ 0.106, 119.0, -33.0 }};
    std::array<double, 3> pmiss {{ 0, -29.9, 35.9 }};
    double mn = 50.;
    double result = 107.12787909;

    wimpmass::TestMt2 mt2test;
    mt2test.SetMomenta(pa.data(), pb.data(), pmiss.data());
    mt2test.SetMass(mn);
    ASSERT_FLOAT_EQ(result, mt2test.GetMt2());


    boca::LorentzVector<Momentum> vectora(pa.at(1) * GeV, pa.at(2) * GeV, at_rest, at_rest);
    vectora.SetMag(pa.at(0) * GeV);
    boca::LorentzVector<Momentum> vectorb(pb.at(1) * GeV, pb.at(2) * GeV, at_rest, at_rest);
    vectorb.SetMag(pb.at(0) * GeV);
    boca::LorentzVector<Momentum> vectormiss(pmiss.at(1) * GeV, pmiss.at(2) * GeV, at_rest, at_rest);
    vectormiss.SetMag(pmiss.at(0) * GeV);                   ///< introduces an floating point error of 0.001

    wimpmass::Mt2 mt2(mn * GeV);
    ASSERT_NEAR(result, mt2.Get(vectora, vectorb, vectormiss), 0.001);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// int main()
// {

//pa, pb = {mass, px, py}
//pmiss = {NULL, pxmiss, pymiss}
//mn = invisible particle mass

// }

