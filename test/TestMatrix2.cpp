#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Math
#include <boost/test/included/unit_test.hpp>
#include <boost/range/numeric.hpp>

#include "boca/math/Matrix2.hh"

/**
* @test Test Matrix2
*
*/
BOOST_AUTO_TEST_CASE(Matrix2)
{
    boca::Matrix2<double> matrix({1, 2}, {3, 4});
    BOOST_CHECK_EQUAL(matrix[boca::Dim2::x][boca::Dim2::y], 2);
    double sum = 0;
    for(auto & row : matrix) for(auto const& cell : row) sum += cell;
    BOOST_CHECK_EQUAL(sum, 10);

    sum = boost::accumulate(matrix, 0.);
    BOOST_CHECK_EQUAL(sum, 10);
}
