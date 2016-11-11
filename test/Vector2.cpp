#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Math
#include <boost/test/included/unit_test.hpp>
#include <boost/range/numeric.hpp>

#include "boca/math/Vector2.hh"
#include "boca/generic/DEBUG_MACROS.hh"

/**
* @test Test Vector2
*
*/
BOOST_AUTO_TEST_SUITE(Vector2)

using namespace boca;

boca::Vector2<Energy> vector(5_GeV, 6_GeV);

BOOST_AUTO_TEST_CASE(Basics)
{
    ERROR(vector);
    BOOST_CHECK_EQUAL(vector[Dim2::x], 5_GeV);
}

BOOST_AUTO_TEST_CASE(Sum)
{
    auto result = 11_GeV;

    auto sum = at_rest;
    for (auto &cell : vector) sum += cell;
    BOOST_CHECK_EQUAL(sum, result);

    sum = 0;
    for (auto const &cell : vector) sum += cell;
    BOOST_CHECK_EQUAL(sum, result);

    sum = 0;
    for (auto cell : vector) sum += cell;
    BOOST_CHECK_EQUAL(sum, result);

    BOOST_CHECK_EQUAL(std::accumulate(vector.begin(),  vector.end(), at_rest), result);

    BOOST_CHECK_EQUAL(boost::accumulate(vector, at_rest), result);

}

BOOST_AUTO_TEST_CASE(Scalar)
{
    BOOST_CHECK_EQUAL(sqr(vector), 61_GeV * GeV);
    auto copy = vector;
    auto mag = 10_GeV;
    copy.SetMag(mag);
    BOOST_CHECK_EQUAL(copy.Mag(), mag);
    BOOST_CHECK_EQUAL(copy.Phi(), vector.Phi());
}

BOOST_AUTO_TEST_CASE(Angle)
{
    auto copy = vector;
    auto phi = 1_rad;
    copy.SetPhi(phi);
    BOOST_CHECK_EQUAL(sqr(copy), 61_GeV * GeV);
    BOOST_CHECK_EQUAL(copy.Phi(), phi);
}

BOOST_AUTO_TEST_CASE(Unit)
{
    auto unit = vector.Unit();
    BOOST_CHECK_EQUAL(unit.Mag(), 1.);
    BOOST_CHECK_EQUAL(unit.Phi(), vector.Phi());
}

BOOST_AUTO_TEST_CASE(Projection)
{
    boca::Vector2<Length> relative(2_m, -3_m);
    boca::Vector2<Energy> proj = vector.Project(relative);
    BOOST_CHECK(proj.Phi() - relative.Phi() == 0_rad || proj.Phi() - relative.Phi() == PiRad());
    BOOST_CHECK_EQUAL(proj.Mag(), vector.Mag() * static_cast<double>(abs(cos(vector.DeltaPhiTo(relative)))));

}

BOOST_AUTO_TEST_SUITE_END()
