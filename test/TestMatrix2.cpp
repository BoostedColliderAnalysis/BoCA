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

    boca::Vector2<double> add = std::accumulate(matrix.begin(),  matrix.end(), boca::Vector2<double>{});
    BOOST_CHECK_EQUAL(add[boca::Dim2::x], 4);

    sum = boost::accumulate(boost::accumulate(matrix, boca::Vector2<double>{}), 0.);
    BOOST_CHECK_EQUAL(sum, 10);
}
