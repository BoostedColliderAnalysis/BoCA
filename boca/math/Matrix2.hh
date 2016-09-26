#pragma once

#include <array>

#include "boost/range/algorithm/sort.hpp"

#include "boca/generic/Types.hh"
#include "boca/generic/Mutable.hh"
#include "boca/math/GradedVector2.hh"

namespace boca
{

/**
 * @ingroup Math
 * @brief Matrix types
 */
enum class Matrix
{
    none,
    diagonal,
    symmetric,
    antisymmetric,
    row,
    column,
    uniform
};

std::string Name(Matrix matrix);

template<typename Value_2_>
using Array2 = std::array<Value_2_, 2>;

/**
 * @ingroup Math
 * @brief Two dimensional matrix
 */
template <typename Value_>
class Matrix2 : boost::totally_ordered<Matrix2<Value_>>
            , boost::additive<Matrix2<Value_>>
{

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

public:

    /**
    * @name Constructor
    * @{
    */

    /**
    * @brief Default constructor
    */
    Matrix2() {}

    /**
    * @brief Diagonal Matrix
    */
    Matrix2(Value_ scalar, Matrix matrix = Matrix::diagonal)
    {
        switch (matrix) {
        case Matrix::diagonal :
            SetDiagonal(scalar);
            break;
        case Matrix::uniform :
            SetUniform(scalar);
            break;
        default :
            std::cout << "Maformed matrix constructor: " << Name(matrix) << std::endl;
        }
    }

    /**
    * @brief Constructor accepting two vectors
    */
    Matrix2(Vector2<Value_> const &vector_1, Vector2<Value_> const &vector_2, Matrix matrix = Matrix::row)
    {
        switch (matrix) {
        case Matrix::row:
            SetRows(vector_1, vector_2);
            break;
        case Matrix::column :
            SetColumns(vector_1, vector_2);
            break;
//         case Matrix::symmetric:
//             *this = MatrixProduct(vector_1, vector_2);
//             break;
        default :
            std::cout << "Maformed matrix constructor: " << Name(matrix) << std::endl;
        }
    }

    /**
    * @brief Constructor with type conversion
    */
    template<typename Value_2>
    Matrix2(Matrix2<Value_2> const &matrix) : x_(matrix.X()), y_(matrix.Y()) {}

    //@}

    /**
    * @name Setter
    * @{
    */

    /**
    * @brief Set equal to the identity rotation.
    */
    Matrix2 &SetToIdentity()
    {
        return SetDiagonal(1);
    }

    /**
    * @brief Set diagonal
    */
    Matrix2 &SetDiagonal(Value_ value)
    {
        x_ = {value, Value_(0)};
        y_ = {Value_(0), value};
        return *this;
    }

    /**
    * @brief Set uniform
    */
    Matrix2 &SetUniform(Value_ value)
    {
        x_ = {value, value};
        y_ = {value, value};
        return *this;
    }

    /**
    * @brief Set rows
    */
    void SetRows(Vector2<Value_> const &x, Vector2<Value_> const &y)
    {
        x_ = x;
        y_ = y;
    }

    /**
    * @brief Set columns
    */
    void SetColumns(Vector2<Value_> const &x, Vector2<Value_> const &y)
    {
        x_ = {x.X(), y.X()};
        y_ = {x.Y(), y.Y()};
    }


    //@}

    /**
    * @name Accessor and getter
    * @{
    */

    /**
    * @brief x
    * @{
    */
    Vector2<Value_> X() const
    {
        return x_;
    }

    Vector2<Value_> &X()
    {
        return x_;
    }
    //@}

    /**
    * @brief y
    */
    Vector2<Value_> Y() const
    {
        return y_;
    }

    Vector2<Value_> &Y()
    {
        return y_;
    }

    //@}

    //@}

    /**
    * @name Angles
    * @{
    */

    /**
    * @brief Phi x
    */
    Angle PhiX() const
    {
        return ColumnX().Phi();
    }

    /**
    * @brief Phi y
    */
    Angle PhiY() const
    {
        return ColumnY().Phi();
    }

    //@}

// Returns true if the identity matrix(Geant4).
    bool IsIdentity() const
    {
        return x_ == Vector2<Value_>(1, 0) && y_ == Vector2<Value_>(0, 1);
    }

    /**
    * @name Scalars
    * @{
    */

    /**
    * @brief Trace
    */
    Value_ Trace()const
    {
        return x_.X() + y_.Y();
    }

    /**
    * @brief Determinant
    */
    ValueSquare Determinant()const
    {
        return x_.X() * y_.Y() - x_.Y() * y_.X();
    }

    /**
    * @brief Minor
    */
    Value_ Minor(Dim2 delete_1, Dim2 delete_2) const
    {
        for (auto const &x : Dimensions2()) {
            if (x == delete_1) continue;
            for (auto const &y : Dimensions2()) {
                if (y == delete_2) continue;
                return (*this)[x][y];
            }
        }
    }

    //@}

    /**
    * @name Vectors
    * @{
    */

    /**
    * @brief x column
    */
    Vector2<Value_> ColumnX() const
    {
        return {x_.X(), y_.X()};
    }

    /**
    * @brief y column
    */
    Vector2<Value_> ColumnY() const
    {
        return {x_.Y(), y_.Y()};
    }

    //@}

    /**
    * @name Matrices
    * @{
    */

    /**
    * @brief transposed
    */
    Matrix2 Transposed() const
    {
        return {ColumnX(), ColumnY()};
    }

    /**
    * @brief transpose this matrix
    */
    Matrix2 &Transpose()
    {
        return *this = Transposed();
    }

    /**
    * @brief inverse of this matrix
    */
    Matrix2<ValueInverse> Inverse()
    {
        auto det = Determinant();
        if (det == ValueSquare(0)) std::cout << "Matrix is not invertible" << std::endl;
        return (Matrix2(Trace()) - *this) / det;
    }

    //@}

    /**
     * @name Products
     * @{
     */

    /**
    * @brief scale with a scalar
    */
    template<typename Value_2_>
    Matrix2<ValueProduct<Value_2_>> Scaled(Value_2_ scalar) const
    {
        return {x_ * scalar, y_ * scalar};
    }

    /**
    * @brief multiply with a matrix
    */
    template<typename Value_2_>
    Matrix2<ValueProduct<Value_2_>> Multiply(Matrix2<Value_2_> const &matrix) const
    {
        return {Vector2<ValueProduct<Value_2_>>(x_ * matrix.ColumnX(), x_ * matrix.ColumnY()), Vector2<ValueProduct<Value_2_>>(y_ * matrix.ColumnX(), y_ * matrix.ColumnY())};
    }

    /**
    * @brief multiply with a vector
    */
    template<typename Value_2_>
    Vector2<ValueProduct<Value_2_>> Multiply(Vector2<Value_2_> const &vector) const
    {
        return {x_ * vector, y_ * vector};
    }

    /**
    * @brief Square
    */
    Matrix2<ValueSquare> Square() const
    {
        return sqr(*this);
    }

    //@}

    /**
     * @name Operators
     * @{
     */

    /**
    * @brief Less than comparison according to determinans
    */
    bool operator<(Matrix2 const &matrix) const
    {
        return abs(Determinant()) < abs(matrix.Determinant());
    }

    /**
    * @brief Equality comnparison
    */
    bool operator==(Matrix2 const &matrix) const
    {
        return x_ == matrix.x_ && y_ == matrix.y_;
    }

    /**
    * @brief Addition
    */
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    Matrix2 &operator+=(Matrix2<Value_2> const &matrix)
    {
        x_ += matrix.x_;
        y_ += matrix.y_;
        return *this;
    }

    /**
    * @brief Substraction
    */
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    Matrix2 &operator-=(Matrix2<Value_2> const &matrix)
    {
        x_ -= matrix.x_;
        y_ -= matrix.y_;
        return *this;
    }

    /**
    * @brief Division by scalar
    */
    template<typename Value_2_, typename = OnlyIfNotOrSameQuantity<Value_2_>>
    Matrix2<ValueQuotient<Value_2_>> operator/=(Value_2_ scalar)
    {
        x_ /= scalar;
        y_ /= scalar;
        return *this;
    }

    /**
    * @brief Division by scalar
    */
    template<typename Value_2_>
    Matrix2<ValueQuotient<Value_2_>> operator/(Value_2_ scalar)
    {
        return Scaled(1. / scalar);
    }

    /**
    * @brief Multiplication with a matrix
    */
    template<typename Value_2_, typename = OnlyIfNotQuantity<Value_2_>>
    Matrix2 &operator*=(Matrix2<Value_2_> const &matrix)
    {
        return *this = Multiply(matrix);
    }

    /**
    * @brief Multiplication with a matrix
    */
    template<typename Value_2_>
    Matrix2<ValueProduct<Value_2_>> operator*(Matrix2<Value_2_> const &matrix) const
    {
        return Multiply(matrix);
    }

    /**
    * @brief Multiplication with a Vector
    */
    template<typename Value_2_>
    Vector2<ValueProduct<Value_2_>> operator*(Vector2<Value_2_> const &vector) const
    {
        return Multiply(vector);
    }

    /**
    * @brief rows
    */
    Vector2<Value_> const &operator()(Dim2 dim) const
    {
        switch (dim) {
        case Dim2::x :
            return x_;
        case Dim2::y :
            return y_;
        default :
            Default("Matrix2", to_int(dim));
            return x_;
        }
    }

    /**
    * @brief rows
    */
    Vector2<Value_> &operator()(Dim2 dim)
    {
        switch (dim) {
        case Dim2::x :
            return x_;
        case Dim2::y :
            return y_;
        default :
            Default("Matrix2", to_int(dim));
            return x_;
        }
    }

    /**
    * @brief rows
    */
    Value_ const &operator()(Dim2 i, Dim2 j) const
    {
        return operator()(i)(j);
    }

    /**
    * @brief rows
    */
    Value_ &operator()(Dim2 i, Dim2 j)
    {
        return operator()(i)(j);
    }

    /**
    * @brief rows
    */
    Vector2<Value_> const &operator[](Dim2 i) const
    {
        return operator()(i);
    }

    /**
    * @brief rows
    */
    Vector2<Value_> &operator[](Dim2 i)
    {
        return operator()(i);
    }

    //@}

    /**
     * @name Iterators
     * @{
     */

    /**
    * @brief begin
    */
    ConstSubIterator<boca::Matrix2, Vector2, Value_, Dim2> begin() const
    {
        return {this, Dim2::x};
    }

    /**
    * @brief end
    */
    ConstSubIterator<boca::Matrix2, Vector2, Value_, Dim2> end() const
    {
        return {this, Dim2::last};
    }

    /**
    * @brief const begin
    */
    SubIterator<boca::Matrix2, Vector2, Value_, Dim2> begin()
    {
        return {this, Dim2::x};
    }

    /**
    * @brief const end
    */
    SubIterator<boca::Matrix2, Vector2, Value_, Dim2> end()
    {
        return {this, Dim2::last};
    }

    //@}

    /**
     * @name Eigen system
     * @{
     */

    /**
    * @brief Eigen values
    */
    Array2<Value_> EigenValues() const
    {
        return Eigen().Values();
    }

    /**
    * @brief Eigen vectors
    */
    Array2<Vector2<Value_>> EigenVectors() const
    {
        return Eigen().Vectors();
    }

    /**
    * @brief Eigen system
    */
    Array2<GradedVector2<Value_>> EigenSystem() const
    {
        return Eigen().System();
    }

    //@}

private:

    class Eigen_
    {
    public:
        Eigen_() {}
        Eigen_(Matrix2<Value_> const &matrix)
        {
            trace_ = matrix.Trace();
            auto radicant = sqr(trace_) - 4 * matrix.Determinant();
            complex_ = radicant < 0;
            sqrt_ = sqrt(radicant) / 2;
            matrix_ = &matrix;
        }
        Array2<Value_> Values() const
        {
            return values_.Get([&]() {
                Array2<Value_> values;
                if (complex_) {
                    for (auto &value : values) value = -1;
                    std::cerr << "Eigensystem has no real Eigenvalues!\n";
                    return values;
                }
                for (auto index : IntegerRange(values.size())) values.at(index) = Value(index);
                return values;
            });
        }
        Array2<Vector2<Value_>> Vectors() const
        {
            return vectors_.Get([&]() {
                auto vectors = Array2<Vector2<Value_>> {};
                for (auto index : IntegerRange(vectors.size())) vectors.at(index) = Vector(index);
                return vectors;
            });
        }
        Array2<GradedVector2<Value_>> System() const
        {
            auto system = Array2<GradedVector2<Value_>> {};
            for (auto index : IntegerRange(system.size())) system.at(index) = {Vectors().at(index), Values().at(index)};
            return system;
        }

    private:

        Value_ Sqrt() const
        {
            return sqrt_;
        }

        Value_ Trace() const
        {
            return trace_;
        }

        Value_ Value(int i) const
        {
            switch (i) {
            case 0 :
                return (Trace() - Sqrt()) / 2;
            case 1 :
                return (Trace() + Sqrt()) / 2;
            }
        }

        Vector2<Value_> Vector(int index) const
        {
            auto matrix = *matrix_ - Matrix2<Value_>(Values().at(index));
            return Vector2<Value_>(matrix.X().Y(), -matrix.X().X()).Unit();
        }
        Value_ sqrt_;
        Value_ trace_;
        bool complex_ = false;
        Mutable<Array2<Value_>> values_;
        Mutable<Array2<Vector2<Value_>>> vectors_;
        Matrix2<Value_> const *matrix_;
    };

    Mutable<Eigen_> eigen_;

    Eigen_ const &Eigen() const
    {
        return eigen_.Get([&]() {
            return Eigen_(*this);
        });
    }

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
auto operator*(Matrix2<Value_> const &matrix, Value_2_ scalar)
{
    return matrix.Scale(scalar);
}

template < class Value_, class Value_2_, typename = OnlyIfNotMatrix2<Value_2_> >
auto operator*(Value_2_ scalar, Matrix2<Value_> const &matrix)
{
    return matrix.Scale(scalar);
}

template < class Value_, class Value_2_>
auto operator*(Matrix2<Value_> const &matrix, Vector2<Value_2_> const &vector)
{
    return matrix.Multiply(vector);
}

template < class Value_, class Value_2_>
Matrix2<ValueProduct<Value_, Value_2_>> operator*(Vector2<Value_2_> const &vector, Matrix2<Value_> const &matrix)
{
    return {vector.X() *matrix.ColumnX(), vector.Y() *matrix.ColumnY()};
}

template<typename Value_1_, typename Value_2_>
Matrix2<ValueProduct<Value_1_, Value_2_>> MatrixProduct(Vector2<Value_1_> const &vector_1, Vector2<Value_2_> const &vector_2)
{
    return {vector_1.X() *vector_2, vector_1.Y() *vector_2};
}

}
