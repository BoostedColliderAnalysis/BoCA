// @(#)root/physics:$Id$
// Author: Peter Malzacher   19/06/99

/*************************************************************************
 * Copyright(C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/
#pragma once

// #include "boost/operators.hpp"
#include "boost/range/algorithm/sort.hpp"
#include "Vector2.hh"
#include "GradedVector.hh"
#include "Units.hh"
#include "Types.hh"
#include "Mutable.hh"

namespace boca
{

template <typename Value_>
class Matrix2
// : boost::operators<Matrix2<Value_>>
{

public:

    template<typename Value_2_>
    using ValueProduct = ValueProduct<Value_, Value_2_>;
    using ValueSquare = boca::ValueSquare<Value_>;
    template<typename Value_2>
    using ValueQuotient = ValueQuotient<Value_, Value_2>;
    using ValueInverse = boost::units::divide_typeof_helper<double, Value_>;
    template<typename Value_2>
    using OnlyIfNotOrSameQuantity = typename std::enable_if < !IsQuantity<Value_2>::value || std::is_same<Value_, Value_2>::value >::type;
    template<typename Value_2>
    using OnlyIfNotQuantity = typename std::enable_if < !IsQuantity<Value_2>::value >::type;

    // Default constructor.
    Matrix2() {}

    // Diagonal Matrix
    Matrix2(Value_ scalar) : x_( {scalar, Value_(0)}), y_( {Value_(0), scalar}) {}

    // Construct from three rows
    Matrix2(Vector2<Value_> const& x, Vector2<Value_> const& y) : x_(x), y_(y) {}

    // Construct from vector product
    Matrix2(Vector2<Value_> const& vector_1, Vector2<Value_> const& vector_2) : x_(vector_1.X()* vector_2), y_(vector_1.Y()* vector_2) {}

    // Constructor
    template<typename Value_2>
    Matrix2(Matrix2<Value_2> const& matrix) {
        x_ = matrix.X();
        y_ = matrix.Y();
    }

    Vector2<Value_> const& X() const {
        return x_;
    }
    Vector2<Value_> const& Y() const {
        return y_;
    }

    Vector2<Value_>& X() {
        return x_;
    }
    Vector2<Value_>& Y() {
        return y_;
    }

// Returns true if the identity matrix(Geant4).
    bool IsIdentity() const {
        return x_ == Vector2<Value_>(1, 0) && y_ == Vector2<Value_>(0, 1);
    }
// Returns the inverse.
    Matrix2 Transposed() const {
        return {ColumnX(), ColumnY()};
    }

// Inverts the Rotation matrix.
    Matrix2& Transpose() {
        return *this = Transposed();
    }

    Matrix2<ValueInverse> Inverse() {
      auto det = Determinant();
      if (det = ValueSquare(0)) std::cout << "Matrix is not invertible" << std::endl;
      return (Matrix2(Trace()) - *this) / det;
    }


//return Phi
    Angle PhiX() const {
        return y_.X() == Value_(0) && x_.X() == Value_(0) ? 0_rad : boost::units::atan2(y_.X(), x_.X());
    }

//return Phi
    Angle PhiY() const {
        return y_.Y() == Value_(0) && x_.Y() == Value_(0) ? 0_rad : boost::units::atan2(y_.Y(), x_.Y());
    }

// Set equal to the identity rotation.
    Matrix2& SetToIdentity() {
        x_ = Vector2<Value_>(1, 0);
        y_ = Vector2<Value_>(0, 1);
        return *this;
    }

    Matrix2& SetDiagonal(Value_ value) {
        x_ = Vector2<Value_>(value, 0);
        y_ = Vector2<Value_>(0, value);
        return *this;
    }


    Value_ Trace()const {
        return x_.X() + y_.Y();
    }

    ValueSquare Determinant()const {
        return x_.X() * y_.Y() - x_.Y() * y_.X();
    }

    Matrix2<ValueSquare> Square() const {
        return sqr(*this);
    }

    class Eigen
    {
    public:
        Eigen() {}
        Eigen(Matrix2<Value_> const& matrix) {
            trace_ = matrix.Trace();
            auto radicant = sqr(trace_) - 4 * matrix.Determinant();
            if (radicant < 0) complex_ = true;
            sqrt_ = sqrt(radicant) / 2;
            matrix_ = &matrix;
        }
        template<typename Value_2_>
        using Array = std::array<Value_2_, 2>;
        Array<Value_> Values() const {
            return values_.Get([&]() {
                Array<Value_> values;
                if (error_) {
                    for (auto & value : values) value = -1;
                    std::cerr << "Eigensystem has no real Eigenvalues!\n";
                    return values;
                }
                values.at(0) = Value1();
                values.at(1) = Value2();
            });
        }
        Array<Vector2<Value_>> Vectors() const {
            return vectors_.Get([&]() {
                Array<Vector2<Value_>> vectors;
                for (auto index : IntegerRange(vectors.size())) vectors.at(index) = Vector(index);
                return vectors;
            });
        }
        Array<GradedVector3<Value_>> System() const {
            Array<GradedVector3<Value_>> system;
            for (auto index : IntegerRange(system.size())) system.at(index) = GradedVector3<Value_>(Vectors().at(index), Values().at(index));
            return system;
        }

    private:

        Value_ Sqrt() const {
            return sqrt_;
        }

        boca::Angle Trace() const {
            return trace_;
        }

        Value_ Value1() const {
            return (Trace() + Sqrt()) / 2;
        }

        Value_ Value2() const {
            return (Trace() - Sqrt()) / 2;
        }

        Vector2<Value_> Vector(int index) const {
            // set up matrix of system to be solved
            auto a11 = matrix_->X().X() - Values().at(index);
            auto a12 = matrix_->X().Y();
            // FIXME this is simply wrong
            auto b1 = a11;
            auto b2 = a11 - a12;
            // vector
            Vector2<Value_> vector(b2, -b1);
            return vector.Unit();
        }
        Value_ sqrt_;
        boca::Angle trace_;
        bool complex_ = false;
        Mutable<Array<Value_>> values_;
        Mutable<Array<Vector2<Value_>>> vectors_;
        Matrix2<Value_> const* matrix_;
    };

    Mutable<Eigen> eigen_;

    Eigen const& eigen() const {
        return eigen_.Get([&]() {
            return Eigen(*this);
        });
    }


    //set X axis
    Matrix2& SetXAxis(Vector2<Value_> const& axis) {
        Vector2<Value_> xyPlane(0, 1, 0);
        return SetXAxis(axis, xyPlane);
    }



    //set Y axis
    Matrix2& SetYAxis(Vector2<Value_> const& axis) {
        Vector2<Value_> yzPlane(0, 0, 1);
        return SetYAxis(axis, yzPlane);
    }



    // Elements of the rotation matrix(Geant4).

    // Returns object of the helper class for C-style subscripting r[i][j]
    Vector2<Value_> const& operator()(int i) const {
        switch (i) {
        case 0 : return x_;
        case 1 : return y_;
        }
        std::cout << "operator()(i) bad index " << i << std::endl;
    }

    Vector2<Value_> const& operator[](int i) const {
        return operator()(i);
    }

    // Returns object of the helper class for C-style subscripting r[i][j]
    Vector2<Value_> const& operator()(Dimension2 i) const {
        switch (i) {
        case Dimension2::x : return x_;
        case Dimension2::y : return y_;
        }
    }

    Vector2<Value_> const& operator[](Dimension2 i) const {
        return operator()(i);
    }

    // Returns object of the helper class for C-style subscripting r[i][j]
    Vector2<Value_>& operator()(int i)  {
        switch (i) {
        case 0 : return x_;
        case 1 : return y_;
        }
        std::cout << "operator()(i) bad index " << i << std::endl;
    }

    Vector2<Value_>& operator[](int i)  {
        return operator()(i);
    }

    // Returns object of the helper class for C-style subscripting r[i][j]
    Vector2<Value_>& operator()(Dimension2 i)  {
        switch (i) {
        case Dimension2::x : return x_;
        case Dimension2::y : return y_;
        }
    }

    Vector2<Value_>& operator[](Dimension2 i)  {
        return operator()(i);
    }

    ConstIterator2<Matrix2, Vector2, Value_> begin() const {
        return {this, 0};
    }

    ConstIterator2<Matrix2, Vector2, Value_> end() const {
        return {this, 2};
    }

    Iterator2<Matrix2, Vector2, Value_> begin() {
        return {this, 0};
    }

    Iterator2<Matrix2, Vector2, Value_> end() {
        return {this, 2};
    }

    // Comparisons(Geant4).
    bool operator==(Matrix2 const& matrix) const {
        return x_ == matrix.x_ && y_ == matrix.y_;
    }
    bool operator!=(Matrix2 const& matrix) const {
        return x_ != matrix.x_ || y_ != matrix.y_;
    }

    // Addition.
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    Matrix2& operator+=(Matrix2<Value_2> const& matrix) {
        x_ += matrix.x_;
        y_ += matrix.y_;
        return *this;
    }

    Vector2<Value_> ColumnX() const {
        return {x_.X(), y_.X()};
    }

    Vector2<Value_> ColumnY() const {
        return {x_.Y(), y_.Y()};
    }

    template<typename Value_2_>
    Matrix2<ValueProduct<Value_2_>> Scaled(Value_2_ scalar) const {
        return {x_ * scalar, y_ * scalar};
    }

    template<typename Value_2_>
    Matrix2<ValueQuotient<Value_2_>> operator/(Value_2_ scalar) {
        return Scaled(1. / scalar);
    }

    // Multiplication with a Vector2<Value_>.
    template<typename Value_2_>
    Vector2<ValueProduct<Value_2_>> Multiply(Vector2<Value_2_> const& vector) const {
        return {x_ * vector, y_ * vector};
    }

    // Multiplication with a Vector2<Value_>.
    template<typename Value_2_>
    Vector2<ValueProduct<Value_2_>> operator*(Vector2<Value_2_> const& vector) const {
        return Multiply(vector);
    }

    //multiplication operator
    template<typename Value_2_>
    Matrix2<ValueProduct<Value_2_>> Multiply(Matrix2<Value_2_> const& matrix) const {
        return {Vector2<ValueProduct<Value_2_>>(x_ * matrix.ColumnX(), x_ * matrix.ColumnY()), Vector2<ValueProduct<Value_2_>>(y_ * matrix.ColumnX(), y_ * matrix.ColumnY())};
    }

    //multiplication operator
    template<typename Value_2_>
    Matrix2<ValueProduct<Value_2_>> operator*(Matrix2<Value_2_> const& matrix) const {
        return Multiply(matrix);
    }

    // Matrix multiplication.
    template<typename Value_2_, typename = OnlyIfNotQuantity<Value_2_>>
    Matrix2& operator*=(Matrix2<Value_2_> const& matrix) {
        return *this = Multiply(matrix);
    }

private:

// The matrix rows
    Vector2<Value_> x_;
    Vector2<Value_> y_;

};

template <typename>
struct IsMatrix2 : std::false_type { };

template <typename Value>
struct IsMatrix2<Matrix2<Value>> : std::true_type { };

template<typename Value>
using OnlyIfNotMatrix2 = typename std::enable_if < !IsMatrix2<Value>::value >::type;

template < class Value_, class Value_2_, typename = OnlyIfNotMatrix2<Value_2_> >
Matrix2 <ValueProduct<Value_, Value_2_>> operator*(Matrix2<Value_> const& matrix, Value_2_ scalar)
{
    return matrix.Scale(scalar);
}

template < class Value_, class Value_2_, typename = OnlyIfNotMatrix2<Value_2_> >
Matrix2 <ValueProduct<Value_, Value_2_>> operator*(Value_2_ scalar, Matrix2<Value_> const& matrix)
{
    return matrix.Scale(scalar);
}

template < class Value_, class Value_2_>
Vector2 <ValueProduct<Value_, Value_2_>> operator*(Matrix2<Value_> const& matrix, Vector2<Value_2_> const& vector)
{
    return matrix.Multiply(vector);
}

template < class Value_, class Value_2_>
Vector2 <ValueProduct<Value_, Value_2_>> operator*(Vector2<Value_2_> const& vector, Matrix2<Value_> const& matrix)
{
    return {vector.X()* matrix.ColumnX(), vector.Y()* matrix.ColumnY()};
}

template<typename Value_1_, typename Value_2_>
Matrix2<ValueProduct<Value_1_, Value_2_>> MatrixProduct(Vector2<Value_1_> const& vector_1, Vector2<Value_2_> const& vector_2)
{
    return {vector_1.X()* vector_2, vector_1.Y()* vector_2};
}

}
