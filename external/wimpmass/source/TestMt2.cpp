
#include <gtest/gtest.h>
#include "wimpmass/Mt2.hh"

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

TEST(Mt2Test, Mt2)
{
    double pa[3] = { 0.106, 39.0, 12.0 };
    double pb[3] = { 0.106, 119.0, -33.0 };
    double pmiss[3] = { 0, -29.9, 35.9 };
    double mn = 50.;

    wimpmass::TestMt2 mt2;

    mt2.SetMomenta(pa, pb, pmiss);
    mt2.SetMass(mn);
    ASSERT_EQ(20, mt2.GetMt2());
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

