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
    constexpr Matrix2() {}

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
            std::cout << "Maformed matrix constructor: " << Name(matrix) << '\n';
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
            std::cout << "Maformed matrix constructor: " << Name(matrix) << '\n';
        }
    }

    /**
    * @brief Constructor with type conversion
    */
    template<typename Value_2>
    constexpr Matrix2(Matrix2<Value_2> const &matrix) : x_(matrix.X()), y_(matrix.Y()) {}

    //@}

    /**
    * @name Setter
    * @{
    */

    /**
    * @brief Set equal to the identity rotation.
    */
    constexpr Matrix2 &SetToIdentity()
    {
        return SetDiagonal(1);
    }

    /**
    * @brief Set diagonal
    */
    constexpr Matrix2 &SetDiagonal(Value_ value)
    {
        x_ = {value, Value_(0)};
        y_ = {Value_(0), value};
        return *this;
    }

    /**
    * @brief Set uniform
    */
    constexpr Matrix2 &SetUniform(Value_ value)
    {
        x_ = {value, value};
        y_ = {value, value};
        return *this;
    }

    /**
    * @brief Set rows
    */
    constexpr void SetRows(Vector2<Value_> const &x, Vector2<Value_> const &y)
    {
        x_ = x;
        y_ = y;
    }

    /**
    * @brief Set columns
    */
    constexpr void SetColumns(Vector2<Value_> const &x, Vector2<Value_> const &y)
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
    constexpr Vector2<Value_> X() const
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
    constexpr Vector2<Value_> Y() const
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

    /**
    * @name Scalars
    * @{
    */

    /**
    * @brief Trace
    */
    constexpr Value_ Trace()const
    {
        return x_.X() + y_.Y();
    }

    /**
    * @brief Determinant
    */
    constexpr ValueSquare Determinant()const
    {
        return x_.X() * y_.Y() - x_.Y() * y_.X();
    }

    /**
    * @brief Minor
    */
    constexpr Value_ Minor(Dim2 delete_1, Dim2 delete_2) const
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
    constexpr Vector2<Value_> ColumnX() const
    {
        return {x_.X(), y_.X()};
    }

    /**
    * @brief y column
    */
    constexpr Vector2<Value_> ColumnY() const
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
    constexpr Matrix2 Transposed() const
    {
        return {ColumnX(), ColumnY()};
    }

    /**
    * @brief transpose this matrix
    */
    constexpr Matrix2 &Transpose()
    {
        return *this = Transposed();
    }

    /**
    * @brief inverse of this matrix
    */
    constexpr Matrix2<ValueInverse> Inverse()
    {
        auto const det = Determinant();
        return det == ValueSquare(0) ? Matrix2<ValueInverse>{} : (Matrix2(Trace()) - *this) / det;
    }

    /**
    * @brief Rotation
    */
    Matrix2 &Rotate(Angle const &phi)
    {
        auto const cos = boost::units::cos(phi);
        auto const sin = boost::units::sin(phi);
        auto const vector = x_;
        x_ = cos * vector - sin * y_;
        y_ = sin * vector + cos * y_;
        return *this;
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
    constexpr Matrix2<ValueProduct<Value_2_>> Scaled(Value_2_ scalar) const
    {
        return {x_ * scalar, y_ * scalar};
    }

    /**
    * @brief multiply with a matrix
    */
    template<typename Value_2_>
    constexpr Matrix2<ValueProduct<Value_2_>> Multiply(Matrix2<Value_2_> const &matrix) const
    {
        return {Vector2<ValueProduct<Value_2_>>(x_ * matrix.ColumnX(), x_ * matrix.ColumnY()), Vector2<ValueProduct<Value_2_>>(y_ * matrix.ColumnX(), y_ * matrix.ColumnY())};
    }

    /**
    * @brief multiply with a vector
    */
    template<typename Value_2_>
    constexpr Vector2<ValueProduct<Value_2_>> Multiply(Vector2<Value_2_> const &vector) const
    {
        return {x_ * vector, y_ * vector};
    }

    /**
    * @brief Square
    */
    constexpr Matrix2<ValueSquare> Square() const
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
    constexpr bool operator<(Matrix2 const &matrix) const
    {
        return abs(Determinant()) < abs(matrix.Determinant());
    }

    /**
    * @brief Equality comnparison
    */
    constexpr bool operator==(Matrix2 const &matrix) const
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
    constexpr Matrix2<ValueQuotient<Value_2_>> operator/(Value_2_ scalar)
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
    constexpr Matrix2<ValueProduct<Value_2_>> operator*(Matrix2<Value_2_> const &matrix) const
    {
        return Multiply(matrix);
    }

    /**
    * @brief Multiplication with a Vector
    */
    template<typename Value_2_>
    constexpr Vector2<ValueProduct<Value_2_>> operator*(Vector2<Value_2_> const &vector) const
    {
        return Multiply(vector);
    }

    /**
    * @brief rows
    */
    constexpr Vector2<Value_> const &operator()(Dim2 dim) const
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
    constexpr Value_ const &operator()(Dim2 i, Dim2 j) const
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
    constexpr Vector2<Value_> const &operator[](Dim2 i) const
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
    constexpr ConstSubIterator<boca::Matrix2, Vector2, Value_, Dim2> begin() const
    {
        return {this, Dim2::x};
    }

    /**
    * @brief end
    */
    constexpr ConstSubIterator<boca::Matrix2, Vector2, Value_, Dim2> end() const
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
    constexpr Array2<Value_> EigenValues() const
    {
        return Eigen().Values();
    }

    /**
    * @brief Eigen vectors
    */
    constexpr Array2<Vector2<Value_>> EigenVectors() const
    {
        return Eigen().Vectors();
    }

    /**
    * @brief Eigen system
    */
    constexpr Array2<GradedVector2<Value_>> EigenSystem() const
    {
        return Eigen().System();
    }

    //@}

private:

    class Eigen_
    {

    public:

        constexpr Eigen_() {}

        Eigen_(Matrix2<Value_> const &matrix)
        {
            trace_ = matrix.Trace();
            auto const radicant = sqr(trace_) - 4 * matrix.Determinant();
            complex_ = radicant < 0;
            sqrt_ = sqrt(radicant) / 2;
            matrix_ = &matrix;
        }

        constexpr Array2<Value_> Values() const
        {
            return values_.Get([&]() {
                Array2<Value_> values;
                if (complex_) {
                    for (auto &value : values) value = -1;
                    std::cerr << "Eigensystem has no real Eigenvalues!\n";
                    return values;
                }
                for (auto const index : IntegerRange(values.size())) values.at(index) = Value(index);
                return values;
            });
        }

        constexpr Array2<Vector2<Value_>> Vectors() const
        {
            return vectors_.Get([&]() {
                auto vectors = Array2<Vector2<Value_>> {};
                for (auto const index : IntegerRange(vectors.size())) vectors.at(index) = Vector(index);
                return vectors;
            });
        }

        constexpr Array2<GradedVector2<Value_>> System() const
        {
            auto system = Array2<GradedVector2<Value_>> {};
            for (auto const index : IntegerRange(system.size())) system.at(index) = {Vectors().at(index), Values().at(index)};
            return system;
        }

    private:

        constexpr Value_ Sqrt() const
        {
            return sqrt_;
        }

        constexpr Value_ Trace() const
        {
            return trace_;
        }

        constexpr Value_ Value(int i) const
        {
            switch (i) {
            case 0 :
                return (Trace() - Sqrt()) / 2;
            case 1 :
                return (Trace() + Sqrt()) / 2;
            }
        }

        constexpr Vector2<Value_> Vector(int index) const
        {
            auto const matrix = *matrix_ - Matrix2<Value_>(Values().at(index));
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

    constexpr Eigen_ const &Eigen() const
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
constexpr auto operator*(Matrix2<Value_> const &matrix, Value_2_ scalar)
{
    return matrix.Scale(scalar);
}

template < class Value_, class Value_2_, typename = OnlyIfNotMatrix2<Value_2_> >
constexpr auto operator*(Value_2_ scalar, Matrix2<Value_> const &matrix)
{
    return matrix.Scale(scalar);
}

template < class Value_, class Value_2_>
constexpr auto operator*(Matrix2<Value_> const &matrix, Vector2<Value_2_> const &vector)
{
    return matrix.Multiply(vector);
}

template < class Value_, class Value_2_>
constexpr Matrix2<ValueProduct<Value_, Value_2_>> operator*(Vector2<Value_2_> const &vector, Matrix2<Value_> const &matrix)
{
    return {vector.X() *matrix.ColumnX(), vector.Y() *matrix.ColumnY()};
}

template<typename Value_1_, typename Value_2_>
constexpr Matrix2<ValueProduct<Value_1_, Value_2_>> MatrixProduct(Vector2<Value_1_> const &vector_1, Vector2<Value_2_> const &vector_2)
{
    return {vector_1.X() *vector_2, vector_1.Y() *vector_2};
}

}
