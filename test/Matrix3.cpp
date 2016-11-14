#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Math
#include <boost/test/included/unit_test.hpp>
#include <boost/range/numeric.hpp>

#include "boca/generic/Vector.hh"
#include "boca/math/Matrix3.hh"
#include "boca/generic/DEBUG_MACROS.hh"


/**
* @test Matrix3
*
*/
BOOST_AUTO_TEST_SUITE(Matrix3)

using namespace boca;
boca::Matrix3<double> matrix({1, 2, 3}, {4, 5, 6}, {7, 8, -9});

BOOST_AUTO_TEST_CASE(Basics)
{
    ERROR(matrix);
    BOOST_CHECK_EQUAL(matrix[Dim3::x][Dim3::y], 2);
}

BOOST_AUTO_TEST_CASE(Sum)
{
    auto total = 27.;
    {
        auto sum = 0.;
        for (auto &row : matrix) for (auto const &cell : row) sum += cell;
        BOOST_CHECK_EQUAL(sum, total);
    }
    {
        auto vector = std::accumulate(matrix.begin(),  matrix.end(), Vector3<double> {});
        BOOST_CHECK_EQUAL(vector[Dim3::x], 12);
        BOOST_CHECK_EQUAL(std::accumulate(vector.begin(),  vector.end(), 0.), total);
    }
    BOOST_CHECK_EQUAL(boost::accumulate(boost::accumulate(matrix, Vector3<double> {}), 0.), total);
}

BOOST_AUTO_TEST_CASE(Scalar)
{
    BOOST_CHECK_EQUAL(matrix.Trace(), -3);
    BOOST_CHECK_EQUAL(matrix.Determinant(), 54);
}

BOOST_AUTO_TEST_CASE(EigenSystem)
{
    std::array<double, 3> test {{ -12.6344, 10.0593, -0.424882}};
    auto eigensystem = matrix.EigenSystem();
    for (auto const &graded : eigensystem) {
        BOOST_CHECK_CLOSE(graded.Scalar(), test[Position(eigensystem, graded)], 1E-3);
        auto product = graded.Product();
        auto vector = matrix * graded.Vector();
        for (auto dim : Dimensions3()) BOOST_CHECK_CLOSE(vector[dim], product[dim], 1E-10);
    }
}

BOOST_AUTO_TEST_SUITE_END()
