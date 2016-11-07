#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Math
#include <boost/test/included/unit_test.hpp>
#include <boost/range/numeric.hpp>

#include "boca/math/Vector2.hh"

/**
* @test Test Vector2
*
*/
BOOST_AUTO_TEST_CASE(Vector2)
{
    boca::Vector2<double> vector(5, 6);
    double result = 11;
    BOOST_CHECK_EQUAL(vector[boca::Dim2::y], 6);
    double sum = 0;
    for(auto & cell : vector) sum += cell;
    BOOST_CHECK_EQUAL(sum, result);

    sum = 0;
    for(auto const& cell : vector) sum += cell;
    BOOST_CHECK_EQUAL(sum, result);

    sum = 0;
    for(auto cell : vector) sum += cell;
    BOOST_CHECK_EQUAL(sum, result);

    sum = std::accumulate(vector.begin(),  vector.end(), 0.);
    BOOST_CHECK_EQUAL(sum, result);

    sum = boost::accumulate(vector, 0.);
    BOOST_CHECK_EQUAL(sum, result);
}
