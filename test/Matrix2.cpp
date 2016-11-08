#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Math
#include <boost/test/included/unit_test.hpp>
#include <boost/range/numeric.hpp>

#include "boca/generic/Vector.hh"
#include "boca/math/Matrix2.hh"
#include "boca/generic/DEBUG_MACROS.hh"


/**
* @test Test Matrix2
*
*/
BOOST_AUTO_TEST_SUITE(Matrix2)

using namespace boca;
boca::Matrix2<double> matrix({1, 2}, {3, 4});

BOOST_AUTO_TEST_CASE(Basics)
{
    ERROR(matrix);
    BOOST_CHECK_EQUAL(matrix[Dim2::x][Dim2::y], 2);
}

BOOST_AUTO_TEST_CASE(Sum)
{
    auto total = 10.;
    {
        auto sum = 0.;
        for (auto &row : matrix) for (auto const &cell : row) sum += cell;
        BOOST_CHECK_EQUAL(sum, total);
    }

    {
        auto vector = std::accumulate(matrix.begin(),  matrix.end(), Vector2<double> {});
        BOOST_CHECK_EQUAL(vector[Dim2::x], 4);
        BOOST_CHECK_EQUAL(std::accumulate(vector.begin(),  vector.end(), 0.), total);
    }

    BOOST_CHECK_EQUAL(boost::accumulate(boost::accumulate(matrix, Vector2<double> {}), 0.), total);
}

BOOST_AUTO_TEST_CASE(Scalar)
{
    BOOST_CHECK_EQUAL(matrix.Trace(), 5);
    BOOST_CHECK_EQUAL(matrix.Determinant(), -2);
}

BOOST_AUTO_TEST_CASE(EigenSystem)
{
    std::array<double, 2> test {{ -0.37228132326901431,  5.3722813232690143}};
    auto eigensystem = matrix.EigenSystem();
    for (auto const &graded : eigensystem)    {
        BOOST_CHECK_EQUAL(graded.Scalar(), test[Position(eigensystem, graded)]);
        auto product = graded.Product();
        auto vector = matrix * graded.Vector();
        for (auto dim : Dimensions2()) BOOST_CHECK_CLOSE(vector[dim], product[dim], 1E-10);
    }
}

BOOST_AUTO_TEST_SUITE_END()
