#pragma once

#include "boost/range/numeric.hpp"

#include "TQuaternion.h"

#include "boca/math/GradedVector3.hh"
#include "boca/math/Matrix2.hh"

namespace boca
{

template<typename Value_>
using Array3 = std::array<Value_, 3>;

/**
 * @ingroup Math
 * @brief Three dimensional matrix
 */
template <typename Value_>
class Matrix3 : public boost::totally_ordered<Matrix3<Value_>>
            , boost::additive<Matrix3<Value_>>
{

    template<typename Value_2_>
    using ValueProduct = ValueProduct<Value_, Value_2_>;
    using ValueSquare = boca::ValueSquare<Value_>;
    using ValueCubed = boca::ValueCubed<Value_>;
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
    constexpr Matrix3() {}

    /**
    * @brief Constructor accepting a scalar
    */
    constexpr Matrix3(Value_ scalar, Matrix matrix = Matrix::diagonal)
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
    * @brief Constructor accepting three vectors
    */
    constexpr Matrix3(Vector3<Value_> const &x, Vector3<Value_> const &y, Vector3<Value_> const &z, Matrix matrix = Matrix::row)
    {
        switch (matrix) {
        case Matrix::row:
            SetRows(x, y, z);
            break;
        case Matrix::column :
            SetColumns(x, y, z);
            break;
        default :
            std::cout << "Maformed matrix constructor: " << Name(matrix) << '\n';
        }
    }

    /**
    * @brief Constructor accepting two vectors
    */
    constexpr Matrix3(Vector3<Value_> const &vector_1, Vector3<Value_> const &vector_2, Matrix matrix = Matrix::symmetric)
    {
        switch (matrix) {
        case Matrix::symmetric:
            *this = MatrixProduct(vector_1, vector_2);
            break;
        default :
            std::cout << "Maformed matrix constructor: " << Name(matrix) << '\n';
        }
    }

    /**
    * @brief Constructor accepting one vector
    */
    constexpr Matrix3(Vector3<Value_> const &vector, Matrix matrix = Matrix::antisymmetric)
    {
        switch (matrix) {
        case Matrix::antisymmetric:
            SetAntisymmetric(vector);
            break;
        case Matrix::diagonal:
            SetDiagonal(vector);
            break;
        default :
            std::cout << "Maformed matrix constructor: " << Name(matrix) << '\n';
        }
    }

    /**
    * @brief Constructor accepting one vector and its direction
    */
    constexpr Matrix3(Vector3<Value_> const &vector, Dim3 dim, Matrix matrix = Matrix::row)
    {
        switch (matrix) {
        case Matrix::row:
            SetRow(vector, dim);
            break;
        case Matrix::column:
            SetColumn(vector, dim);
            break;
        default :
            std::cout << "Maformed matrix constructor: " << Name(matrix) << '\n';
        }
    }



    /**
    * @brief Constructor accepting a root::TQuaternion
    *
    * Constructor for a rotation based on a Quaternion if magnitude of quaternion is null, creates identity rotation if quaternion is non-unit, creates rotation corresponding to the normalized(unit) quaternion.
    */
    constexpr Matrix3(TQuaternion const &quaternion)
    {
        auto const mag2 = quaternion.QMag2();
        if (mag2 <= 0) *this = Matrix3(1.);
        else {
            *this = 2 * (Matrix3(sqr(quaternion.fRealPart)) + Matrix3(Vector3<double>(quaternion.fVectorPart), Vector3<double>(quaternion.fVectorPart)) - Matrix3(Vector3<double>(quaternion.fVectorPart * quaternion.fRealPart)));
            // protect agains non-unit quaternion
            if (std::abs(mag2 - 1) > 1e-10) *this /= mag2;
            // diago : remove identity
            *this -= Matrix3(1);
        }
    }

    /**
    * @brief Copy construct with casting
    */
    template<typename Value_2>
    constexpr Matrix3(Matrix3<Value_2> const &matrix) :
        x_(matrix.X()),
        y_(matrix.Y()),
        z_(matrix.Z())
    {}

    //@}

    /**
    * @name Setter
    * @{
    */

    /**
    * @brief Set the diagonal to uniform value
    */
    constexpr Matrix3 &SetDiagonal(Value_ value)
    {
        x_ = {value, Dim3::x};
        y_ = {value, Dim3::y};
        z_ = {value, Dim3::z};
        return *this;
    }

    /**
    * @brief Set the diagonal to given vector
    */
    constexpr Matrix3 &SetDiagonal(Vector3<Value_> vector)
    {
        x_ = {vector.X(), Dim3::x};
        y_ = {vector.Y(), Dim3::y};
        z_ = {vector.Z(), Dim3::z};
        return *this;
    }

    /**
    * @brief vector of upper triangle
    */
    constexpr Matrix3 &SetUpperTriangle(Vector3<Value_> vector)
    {
        x_.Y() = vector.X();
        x_.Z() = vector.Y();
        y_.Z() = vector.Z();
        return *this;
    }

    /**
    * @brief vector of lower triangle
    */
    constexpr Matrix3 &SetLowerTriangle(Vector3<Value_> vector)
    {
        y_.X() = vector.X();
        z_.X() = vector.Y();
        z_.Y() = vector.Z();
        return *this;
    }

    /**
    * @brief Set to the diagonal to identiy
    */
    constexpr Matrix3 &SetToIdentity()
    {
        SetUpperTriangle({0});
        SetLowerTriangle({0});
        return SetDiagonal(1);
    }

    /**
    * @brief Set the matrix to uniform value
    */
    constexpr Matrix3 &SetUniform(Value_ value)
    {
        x_ = {value, value, value};
        y_ = {value, value, value};
        z_ = {value, value, value};
        return *this;
    }

    /**
    * @brief Set the rows according to given vectors
    */
    constexpr void SetRows(Vector3<Value_> const &x, Vector3<Value_> const &y, Vector3<Value_> const &z)
    {
        x_ = x;
        y_ = y;
        z_ = z;
    }

    /**
    * @brief Set a row according to vector and direction
    */
    constexpr void SetRow(Vector3<Value_> const &vector, Dim3 dim)
    {
        switch (dim) {
        case Dim3::x :
            x_ = vector;
            break;
        case Dim3::y :
            y_ = vector;
            break;
        case Dim3::z :
            z_ = vector;
            break;
        default :
            ;
        }
    }

    /**
    * @brief Set columns according to given vectors
    */
    constexpr void SetColumns(Vector3<Value_> const &x, Vector3<Value_> const &y, Vector3<Value_> const &z)
    {
        x_ = {x.X(), y.X(), z.X()};
        y_ = {x.Y(), y.Y(), z.Y()};
        z_ = {x.Z(), y.Z(), z.Z()};
    }

    /**
    * @brief Set a column according to vector and its direction
    */
    constexpr void SetColumn(Vector3<Value_> const &vector, Dim3 dim)
    {
        x_ = {vector.X(), dim};
        y_ = {vector.Y(), dim};
        z_ = {vector.Z(), dim};
    }

    /**
    * @brief Fill the matrix antisymmetrically with the values of the vector
    */
    constexpr void SetAntisymmetric(Vector3<Value_> const &vector)
    {
        x_ = {Value_(0), vector.Z(), -vector.Y()};
        y_ = { -vector.Z(), Value_(0), vector.X()};
        z_ = {vector.Y(), -vector.X(), Value_(0)};
    }

    /**
    * @brief Set the Euler angles
    *
    * Dim2 defines the type of Euler rotation
    */
    constexpr Matrix3 &SetEulerAngles(Angle const &phi, Angle const &theta, Angle const &psi, Dim2 dim = Dim2::x)
    {
        SetToIdentity();
        Rotate(phi, Dim3::z);
        switch (dim) {
        case Dim2::x :
            Rotate(theta, Dim3::x);
            break;
        case Dim2::y :
            Rotate(theta, Dim3::y);
            break;
        default :
            ;
        }
        Rotate(psi, Dim3::z);
        return *this;
    }

    /**
    * @brief Set phi
    *
    */
    constexpr void SetPhi(Angle const &phi, Dim2 dim = Dim2::x)
    {
        SetEulerAngles(phi, Theta(dim), Psi(dim), dim);
    }

    /**
    * @brief Set theta
    */
    constexpr void SetTheta(Angle const &theta, Dim2 dim = Dim2::x)
    {
        SetEulerAngles(Phi(dim), theta, Psi(dim), dim);
    }

    /**
    * @brief Set psi
    */
    constexpr void SetPsi(Angle const &psi, Dim2 dim = Dim2::x)
    {
        SetEulerAngles(Phi(), Theta(dim), psi, dim);
    }

    /**
    * @brief Set axis
    *
    */
    constexpr Matrix3 &SetAxis(Vector3<Value_> const &axis, Dim3 dim)
    {
        return SetAxis(axis, {axis.Mag(), Next(dim)});
    }

    /**
    * @brief Set axis
    *
    */
    constexpr Matrix3 &SetAxis(Vector3<Value_> const &axis, Vector3<Value_> const &plane, Dim3 dim)
    {
        *this = MakeBasis(plane, axis).MoveTo(dim, Dim3::x).Transpose();
        return *this;
    }

    //@}

    /**
    * @name Accessor and getter
    * @{
    */

    /**
    * @brief x-row
    * @{
    */
    constexpr Vector3<Value_> X() const
    {
        return x_;
    }

    Vector3<Value_> &X()
    {
        return x_;
    }
    //@}

    /**
    * @brief y-row
    * @{
    */
    constexpr Vector3<Value_> Y() const
    {
        return y_;
    }

    Vector3<Value_> &Y()
    {
        return y_;
    }
    //@}

    /**
    * @brief z-row
    * @{
    */
    Vector3<Value_> &Z()
    {
        return z_;
    }

    constexpr Vector3<Value_> Z() const
    {
        return z_;
    }
    //@}

    //@}

    constexpr Matrix Symmetry()
    {
        if (UpperTriangle() == LowerTriangle()) return Matrix::symmetric;
        if (UpperTriangle() == -LowerTriangle() && Diagonal() == Vector3<Value_> {0, 0, 0}) return Matrix::antisymmetric;
        return Matrix::none;
    }

    /**
    * @name Vectors
    * @{
    */

    /**
    * @brief x-column
    */
    constexpr Vector3<Value_> ColumnX() const
    {
        return {x_.X(), y_.X(), z_.X()};
    }

    /**
    * @brief y-column
    */
    constexpr Vector3<Value_> ColumnY() const
    {
        return {x_.Y(), y_.Y(), z_.Y()};
    }

    /**
    * @brief z-column
    */
    constexpr Vector3<Value_> ColumnZ() const
    {
        return {x_.Z(), y_.Z(), z_.Z()};
    }

    /**
    * @brief vector of the diagonal
    */
    constexpr Vector3<Value_> Diagonal()
    {
        return {x_.X(), y_.Y(), z_.Z()};
    }

    /**
    * @brief vector of upper triangle
    */
    constexpr Vector3<Value_> UpperTriangle()
    {
        return {x_.Y(), x_.Z(), y_.Z()};
    }

    /**
    * @brief vector of lower triangle
    */
    constexpr Vector3<Value_> LowerTriangle()
    {
        return {y_.X(), z_.X(), z_.Y()};
    }

    //@}

    /**
    * @name Scalar
    * @{
    */

    /**
    * @brief Sign of a given element \f$(-1)^{i+j}\f$
    */
    constexpr auto Sign(Dim3 i, Dim3 j) const
    {
        return (static_cast<int>(i) + static_cast<int>(j)) % 2 ? -1 : 1;
    }

    /**
    * @brief Trace \f$\text{tr} A = A_{x, x} + A_{y, y} + A_{z, z}\f$
    */
    constexpr auto Trace()const
    {
        return x_.X() + y_.Y() + z_.Z();
    }

    /**
    * @brief Trace of the product of two matrices \f$\text{tr}(A B)\f$
    */
    template<typename Value_2_>
    constexpr auto ProductTrace(Matrix3<Value_2_> const &matrix) const
    {
        return x_ * matrix.ColumnX() + y_ * matrix.ColumnY() + z_ * matrix.ColumnZ();
    }

    /**
    * @brief Determinant \f$\det A = \sum_{i=1}^n A_{i, j} C_{i, j}\f$
    */
    constexpr auto Determinant()const
    {
        return  boost::accumulate(Dimensions3(), ValueCubed(0), [&](ValueCubed & sum, Dim3 dim) {
            return sum + Laplace(Dim3::x, dim);
        });
    }

    /**
    * @brief Laplace \f$A_{i, j} C_{i, j}\f$
    */
    constexpr auto Laplace(Dim3 dim_1, Dim3 dim_2) const
    {
        return (*this)[dim_1][dim_2] * Cofactor(dim_1, dim_2);
    }

    /**
    * @brief Cofactor \f$C_{i, j} = (-1)^{i+j} M_{i, j}\f$
    */
    constexpr auto Cofactor(Dim3 dim_1, Dim3 dim_2) const
    {
        return static_cast<double>(Sign(dim_1, dim_2)) * Minor(dim_1, dim_2);
    }

    /**
    * @brief Minor \f$M_{i, j} = \det ((A_{p, q})_{p\neq i, q\neq j})\f$
    */
    constexpr auto Minor(Dim3 delete_1, Dim3 delete_2) const
    {
        return SubMatrix(delete_1, delete_2).Determinant();
    }

    /**
    * @brief Reduced determinant \f$\det_{i, j} A = \det A - A_{i, j} C_{i, j}\f$
    */
    constexpr auto ReducedDeterminant(Dim3 dim_1, Dim3 dim_2) const
    {
        return Determinant() - Laplace(dim_1, dim_2);
    }

    /**
    * @name Angles
    * @{
    */

    /**
    * @brief Phi
    */
    Angle Phi(Dim3 dim) const
    {
        return Vector2<Value_>(x_(dim), y_(dim)).Phi();
    }

    /**
    * @brief Theta
    */
    Angle Theta(Dim3 dim) const
    {
        return acos(z_(dim));
    }

    /**
    * @brief Phi
    */
    Angle Phi(Dim2 dim) const
    {
        switch (dim) {
        case Dim2::x :
            return XPhi();
        case Dim2::y :
            return XPhi() + Pi() / 2.;
        default :
            return XPhi();
        }
    }

    /**
    * @brief Theta
    */
    Angle Theta(Dim2 = Dim2::x) const
    {
        return Theta(Dim3::z);
    }

    /**
    * @brief Psi
    */
    Angle Psi(Dim2 dim) const
    {
        switch (dim) {
        case Dim2::x :
            return XPsi();
        case Dim2::y :
            return XPsi() - Pi() / 2.;
        default :
            return XPhi();
        }
    }

    //@}

    //@}

    /**
    * @name Matrix
    * @{
    */

    /**
    * @brief transposed matrix
    */
    constexpr Matrix3 Transposed() const
    {
        return {ColumnX(), ColumnY(), ColumnZ()};
    }

    /**
    * @brief transpose this matrix
    */
    constexpr Matrix3 &Transpose()
    {
        return *this = Transposed();
    }

    /**
    * @brief Inverse matrix
    *
    * return zero matrix if the determinant is zero
    */
    constexpr Matrix3<ValueInverse> Inverse()
    {
        auto const det = Determinant();
        if (det == ValueCubed(0)) return {};
        auto const x = ColumnX();
        auto const y = ColumnY();
        auto const z = ColumnZ();
        return Matrix3<ValueSquare>(y ^ z, z ^ x, x ^ y) / det;
    }

    /**
    * @brief Sub matrix \f$(A_{p, q})_{p\neq i, q\neq j}\f$
    */
    auto SubMatrix(Dim3 delete_1, Dim3 delete_2) const
    {
        auto dim2_1 = EnumIterator<Dim2> {Dim2::x};
        auto dim2_2 = EnumIterator<Dim2> {Dim2::x};
        auto matrix = Matrix2<Value_> {};
        for (auto dim3_1 : Dimensions3()) {
            if (dim3_1 == delete_1) continue;
            for (auto dim3_2 : Dimensions3()) {
                if (dim3_2 == delete_2) continue;
                matrix(*dim2_1, *dim2_2) = (*this)(dim3_1, dim3_2);
                ++dim2_2;
            }
            ++dim2_1;
            dim2_2.Set(Dim2::x);
        }
        return matrix;
    }

    /**
    * @brief Move row cyclic from dim1 to dim 2
    */
    constexpr Matrix3 &MoveTo(Dim3 dim_1, Dim3 dim_2)
    {
        std::swap((*this)(dim_1), (*this)(dim_2));
        std::swap((*this)(dim_1),  (*this)(Third(dim_1, dim_2)));
        return *this;
    }

    //@}

    /**
    * @name Rotate
    * @{
    */

    /**
    * @brief Rotate by phi in (dim_1,  dim_2) plain
    */
    Matrix3 &Rotate(Angle const &phi, Dim3 dim_1,  Dim3 dim_2)
    {
        if (phi == 0_rad)  return *this;
        auto const cos = boost::units::cos(phi);
        auto const sin = boost::units::sin(phi);
        auto const row = (*this)(dim_1);
        (*this)(dim_1) = cos * row - sin * (*this)(dim_2);
        (*this)(dim_2) = sin * row + cos * (*this)(dim_2);
        return *this;
    }

    /**
    * @brief Rotate by phi around axis dim
    */
    constexpr Matrix3 &Rotate(Angle const &phi, Dim3 dim)
    {
        switch (dim) {
        case Dim3::x :
            return Rotate(phi, Dim3::y, Dim3::z);
        case Dim3::y :
            return Rotate(phi, Dim3::z, Dim3::x);
        case Dim3::z :
            return Rotate(phi, Dim3::x, Dim3::y);
        default :
            ;
        }
    }

    /**
    * @brief Rotation by phi around axis
    */
    Matrix3 &Rotate(Angle const &phi, Vector3<Value_> const &axis)
    {
        if (phi == 0_rad)  return *this;
        auto const sin = boost::units::sin(phi);
        auto const cos = boost::units::cos(phi);
        auto const unit = axis.Unit();
        return Transform(Matrix3(cos) + Matrix3(unit, unit) * (1 - cos) - Matrix3(unit * sin));
    }

    /**
    * @brief Rotation of local axes
    */
    constexpr Matrix3 &RotateAxes(Vector3<Value_> const &vector_x, Vector3<Value_> const &vector_y, Vector3<Value_> const &vector_z)
    {
        auto const epsilon = 0.001;
        auto const cross = vector_x.Cross(vector_y);
        if (std::abs(vector_z.X() - cross.X()) > epsilon || std::abs(vector_z.Y() - cross.Y()) > epsilon || std::abs(vector_z.Z() - cross.Z()) > epsilon || std::abs(vector_x.Mag2() - 1) > epsilon || std::abs(vector_y.Mag2() - 1) > epsilon || std::abs(vector_z.Mag2() - 1) > epsilon || std::abs(vector_x.Dot(vector_y)) > epsilon || std::abs(vector_y.Dot(vector_z)) > epsilon || std::abs(vector_z.Dot(vector_x)) > epsilon) {
            std::cout << "RotateAxes bad axis vectors" << '\n';
            return *this;
        }
        return Transform(Matrix3(vector_x.X(), vector_y.X(), vector_z.X(), vector_x.Y(), vector_y.Y(), vector_z.Y(), vector_x.Z(), vector_y.Z(), vector_z.Z()));
    }


    /**
    * @brief Set the euler angles of the rotation.
    */
    constexpr Matrix3 &RotateEulerAngles(Angle const &phi, Angle const &theta, Angle const &psi, Dim2 dim = Dim2::x)
    {
        auto euler = Matrix3 {};
        euler.SetEulerAngles(phi, theta, psi, dim);
        return Transform(euler);
    }

    /**
    * @brief rotation defined by an angle and a vector
    */
    std::pair<Vector3<Value_>, Angle> AngleAxis() const
    {
        auto const cosa  = 0.5 * (x_.X() + y_.Y() + z_.Z() - 1);
        auto const cosa1 = 1 - cosa;
        if (cosa1 <= Value_(0)) return std::make_pair<Vector3<Value_>, Angle>({0, 0, 1},  0_rad);
        auto x = x_.X() > cosa ? sqrt((x_.X() - cosa) / cosa1) : 0;
        auto y = y_.Y() > cosa ? sqrt((y_.Y() - cosa) / cosa1) : 0;
        auto z = z_.Z() > cosa ? sqrt((z_.Z() - cosa) / cosa1) : 0;
        if (z_.Y() < y_.Z()) x = -x;
        if (x_.Z() < z_.X()) y = -y;
        if (y_.X() < x_.Y()) z = -z;
        return std::make_pair<Vector3<Value_>, Angle>({x, y, z},  acos(cosa));
    }

    //@}

    /**
     * @name Products
     * @{
     */

    /**
    * @brief Multiplication with a matrix
    */
    template<typename Value_2_>
    constexpr Matrix3<ValueProduct<Value_2_>> Multiply(Matrix3<Value_2_> const &matrix) const
    {
        return {{x_ * matrix.ColumnX(), x_ * matrix.ColumnY(), x_ * matrix.ColumnZ()}, {y_ * matrix.ColumnX(), y_ * matrix.ColumnY(), y_ * matrix.ColumnZ()}, {z_ * matrix.ColumnX(), z_ * matrix.ColumnY(), z_ * matrix.ColumnZ()}};
    }

    /**
    * @brief Multiplication with a Vector
    */
    template<typename Value_2_>
    constexpr Vector3<ValueProduct<Value_2_>> Multiply(Vector3<Value_2_> const &vector) const
    {
        return {x_ * vector, y_ * vector, z_ * vector};
    }

    /**
    * @brief Scale by scalar
    */
    template<typename Value_2_>
    constexpr Matrix3<ValueProduct<Value_2_>> Scaled(Value_2_ scalar) const
    {
        return {x_ * scalar, y_ * scalar, z_ * scalar};
    }

    /**
    * @brief Transform this matrix by another
    */
    template<typename Value_2_, typename = OnlyIfNotOrSameQuantity<Value_2_>>
    constexpr Matrix3<ValueProduct<Value_2_>> &Transform(Matrix3<Value_2_> const &matrix)
    {
        return *this = matrix * (*this);
    }

    /**
    * @brief Transform this matrix by another
    */
    template<typename Value_2_>
    constexpr Matrix3<ValueProduct<Value_2_>> &Transformed(Matrix3<Value_2_> const &matrix)
    {
        return matrix * (*this);
    }


    //@}

    /**
     * @name Operator
     * @{
     */

    /**
    * @brief Less than comparison according to determinans
    */
    constexpr bool operator<(Matrix3 const &matrix) const
    {
        return abs(Determinant()) < abs(matrix.Determinant());
    }

    /**
    * @brief Equality comnparison
    */
    constexpr bool operator==(Matrix3 const &matrix) const
    {
        return x_ == matrix.x_ && y_ == matrix.y_ && z_ == matrix.z_;
    }

    /**
    * @brief Addition
    */
    template <typename Value_2_, typename = OnlyIfNotOrSameQuantity<Value_2_>>
    constexpr Matrix3 &operator+=(Matrix3<Value_2_> const &matrix)
    {
        x_ += matrix.x_;
        y_ += matrix.y_;
        z_ += matrix.z_;
        return *this;
    }

    /**
    * @brief Substraction
    */
    template <typename Value_2_, typename = OnlyIfNotOrSameQuantity<Value_2_>>
    constexpr Matrix3 &operator-=(Matrix3<Value_2_> const &matrix)
    {
        x_ -= matrix.x_;
        y_ -= matrix.y_;
        z_ -= matrix.z_;
        return *this;
    }

    /**
    * @brief Multiplication with a matrix
    */
    template<typename Value_2_, typename = OnlyIfNotQuantity<Value_2_>>
    constexpr Matrix3 &operator*=(Matrix3<Value_2_> const &matrix)
    {
        return *this = Multiply(matrix);
    }

    /**
    * @brief Multiplication with a matrix
    */
    template<typename Value_2_>
    constexpr Matrix3<ValueProduct<Value_2_>> operator*(Matrix3<Value_2_> const &matrix) const
    {
        return Multiply(matrix);
    }

    /**
    * @brief Multiplication with a Vector
    */
    template<typename Value_2_>
    constexpr Vector3<ValueProduct<Value_2_>> operator*(Vector3<Value_2_> const &vector) const
    {
        return Multiply(vector);
    }

    /**
    * @brief Division by scalar
    */
    template<typename Value_2_, typename = OnlyIfNotOrSameQuantity<Value_2_>>
    constexpr Matrix3<ValueQuotient<Value_2_>> operator/=(Value_2_ scalar)
    {
        x_ /= scalar;
        y_ /= scalar;
        z_ /= scalar;
        return *this;
    }

    /**
    * @brief Division by scalar
    */
    template<typename Value_2_>
    constexpr Matrix3<ValueQuotient<Value_2_>> operator/(Value_2_ scalar) const
    {
        return Scaled(1. / scalar);
    }

    /**
    * @brief Components by index
    */
    constexpr Vector3<Value_> const &operator()(Dim3 dim) const
    {
        switch (dim) {
        case Dim3::x :
            return x_;
        case Dim3::y :
            return y_;
        case Dim3::z :
            return z_;
        default :
            Default("Matrix3", to_int(dim));
            return x_;
        }
    }

    /**
    * @brief Components by index
    */
    Vector3<Value_> &operator()(Dim3 dim)
    {
        switch (dim) {
        case Dim3::x :
            return x_;
        case Dim3::y :
            return y_;
        case Dim3::z :
            return z_;
        default :
            Default("Matrix3", to_int(dim));
            return x_;
        }
    }

    /**
    * @brief Components by index
    */
    constexpr Value_ const &operator()(Dim3 i, Dim3 j) const
    {
        return operator()(i)(j);
    }

    /**
    * @brief Components by index
    */
    Value_ &operator()(Dim3 i, Dim3 j)
    {
        return operator()(i)(j);
    }

    /**
    * @brief Components by index
    */
    constexpr Vector3<Value_> const &operator[](Dim3 i) const
    {
        return operator()(i);
    }

    /**
    * @brief Components by index
    */
    Vector3<Value_> &operator[](Dim3 i)
    {
        return operator()(i);
    }

    //@}

    /**
     * @name Iterator
     * @{
     */

    /**
    * @brief Const begin
    */
    constexpr ConstSubIterator<boca::Matrix3, Vector3, Value_, Dim3> begin() const
    {
        return {this, Dim3::x};
    }

    /**
    * @brief Const end
    */
    constexpr ConstSubIterator<boca::Matrix3, Vector3, Value_, Dim3> end() const
    {
        return {this, Dim3::last};
    }

    /**
    * @brief Begin
    */
    constexpr SubIterator<boca::Matrix3, Vector3, Value_, Dim3> begin()
    {
        return {this, Dim3::x};
    }

    /**
    * @brief End
    */
    constexpr SubIterator<boca::Matrix3, Vector3, Value_, Dim3> end()
    {
        return {this, Dim3::last};
    }

    //@}

    /**
     * @name Eigen system
     * @{
     */

    /**
    * @brief Eigen values
    */
    constexpr Array3<Value_> EigenValues() const
    {
        return Eigen().Values();
    }

    /**
    * @brief Eigen vectors
    */
    constexpr Array3<Vector3<Value_>> EigenVectors() const
    {
        return Eigen().Vectors();
    }

    /**
    * @brief Eigen system
    */
    constexpr Array3<GradedVector3<Value_>> EigenSystem() const
    {
        return Eigen().System();
    }

    //@}

private:

    class Characteristic_
    {

    public:

        constexpr Characteristic_(Matrix3 const &matrix)
        {
            qudratic_ = - matrix.Trace();
            linear_ = - (matrix.ProductTrace(matrix) - sqr(qudratic_)) / 2;
            constant_ = - matrix.Determinant();
        }

        constexpr Value_ Qudratic() const
        {
            return qudratic_;
        }

        constexpr ValueSquare Linear() const
        {
            return linear_;
        }

        constexpr ValueCubed Constant() const
        {
            return constant_;
        }

    private:

        Value_ qudratic_;

        ValueSquare linear_;

        ValueCubed constant_;

    };

    class Depressed_
    {

    public:

        constexpr Depressed_(Characteristic_ const &c)
        {
            auto const quadratic = c.Qudratic() / 3;
            linear_ = c.Linear() - sqr(quadratic) * 3;
            constant_ = 2. * cube(quadratic) - quadratic * c.Linear() + c.Constant();
        }

        constexpr ValueSquare Linear() const
        {
            return linear_;
        }

        constexpr ValueCubed Constant() const
        {
            return constant_;
        }

    private:

        ValueSquare linear_;

        ValueCubed constant_;

    };

    class Eigen_
    {

    public:

        constexpr Eigen_() {}

        constexpr Eigen_(Depressed_ const &d, Matrix3<Value_> const &matrix)
        {
            factor_ = 2. * sqrt(- d.Linear() / 3.);
            angle_ = acos(3. * d.Constant() / d.Linear() / factor_);
            complex_ = 4 * cube(d.Linear()) > - 27 * sqr(d.Constant());
            matrix_ = &matrix;
        }

        constexpr Array3<Value_> Values() const
        {
            return values_.Get([&]() {
                auto values = Array3<Value_> {};
                if (complex_) {
                    for (auto &value : values) value = -1;
                    std::cerr << "Eigensystem has no real Eigenvalues!\n";
                    return values;
                }
                for (auto const index : IntegerRange(values.size())) values.at(index) = Value(index);
                return boost::range::sort(values, [](Value_ i, Value_ j) {
                    return abs(i) > abs(j);
                });
            });
        }

        constexpr Array3<Vector3<Value_>> Vectors() const
        {
            return vectors_.Get([&]() {
                auto vectors = Array3<Vector3<Value_>> {};
                for (auto const index : IntegerRange(vectors.size())) vectors.at(index) = Vector(index);
                return vectors;
            });
        }

        constexpr Array3<GradedVector3<Value_>> System() const
        {
            auto system = Array3<GradedVector3<Value_>> {};
            for (auto const index : IntegerRange(system.size())) system.at(index) = {Vectors().at(index), Values().at(index)};
            return system;
        }

    private:

        constexpr Value_ Factor() const
        {
            return factor_;
        }

        boca::Angle Angle() const
        {
            return angle_;
        }

        constexpr Value_ Value(int index) const
        {
            return Factor() * cos((Angle() - TwoPi() * static_cast<double>(index)) / 3.) + matrix_->Trace() / 3;
        }

        constexpr Vector3<Value_> Vector(int index) const
        {
            auto const matrix = *matrix_ - Matrix3<Value_>(Values().at(index));
            return Vector3<Value_>(matrix.Cofactor(Dim3::x, Dim3::x), matrix.Cofactor(Dim3::x, Dim3::y), matrix.Cofactor(Dim3::x, Dim3::z)).Unit();
        }

        Value_ factor_;

        boca::Angle angle_;

        bool complex_;

        Mutable<Array3<Value_>> values_;

        Mutable<Array3<Vector3<Value_>>> vectors_;

        Matrix3<Value_> const *matrix_;

    };

    constexpr Eigen_ const &Eigen() const
    {
        return eigen_.Get([&]() {
            return Eigen_(Depressed_(Characteristic_(*this)), *this);
        });
    }

    Mutable<Eigen_> eigen_;

    Vector3<Value_> x_;

    Vector3<Value_> y_;

    Vector3<Value_> z_;

    /**
    * @brief Phi
    */
    Angle XPhi() const
    {
        auto s2 =  ValueSquare(1) - z_.Z() * z_.Z();
        if (s2 < ValueSquare(0)) {
            std::cout << "Phi() |z_.Z()| > 1 " << '\n';
            s2 = 0;
        }
        auto const sinTheta = std::sqrt(s2);
        if (sinTheta != Value_(0)) {
            auto const cscTheta = 1 / sinTheta;
            auto const cosAbsPhi =  z_.Y() * cscTheta;
            if (std::abs(cosAbsPhi) > 1) {         // NaN-proofing
                std::cout << "Phi() finds | cos phi | > 1" << '\n';
                cosAbsPhi = 1;
            }
            auto const absPhi = acos(cosAbsPhi);
            if (z_.X() > 0) return absPhi;
            if (z_.X() < 0) return -absPhi;
            if (z_.Y() > 0) return 0_rad;
            return Pi();
        } else {              // sinTheta == Value(0) so |Fzz| = 1
            auto const absPhi = .5 * acos(x_.X());
            if (x_.Y() > 0) return -absPhi;
            if (x_.Y() < 0) return absPhi;
            if (x_.X() > 0) return 0_rad;
            return z_.Z() * Pi() / 2;
        }
    }

// Return the euler angles of the rotation.  See SetYEulerAngles for a
// note about conventions.
    Angle XPsi() const
    {
        // psi angle
        auto s2 =  1 - sqr(z_.Z());
        if (s2 < 0) {
            std::cout << "Psi() |z_.Z()| > 1 " << '\n';
            s2 = 0;
        }
        auto const sinTheta = std::sqrt(s2);
        if (sinTheta != 0) {
            auto const cscTheta = 1 / sinTheta;
            auto const cosAbsPsi =  - y_.Z() * cscTheta;
            if (std::abs(cosAbsPsi) > 1) {         // NaN-proofing
                std::cout << "Psi() | cos psi | > 1 " << '\n';
                cosAbsPsi = 1;
            }
            auto const absPsi = boca::acos(cosAbsPsi);
            if (x_.Z() > 0) return absPsi;
            if (x_.Z() < 0) return -absPsi;
            return (y_.Z() < 0) ? 0_rad : Pi();
        } else {              // sinTheta == Value(0) so |Fzz| = 1
            auto absPsi = x_.X();
            // NaN-proofing
            if (std::abs(x_.X()) > 1) {
                std::cout << "Psi() | x_.X() | > 1 " << '\n';
                absPsi = 1;
            }
            auto const absPsi2 = .5 * acos(absPsi);
            if (y_.X() > 0) return absPsi2;
            if (y_.X() < 0) return -absPsi2;
            return (x_.X() > 0) ? 0_rad : Pi() / 2.;
        }
    }

    /**
    * @brief Take two input vectors and turn them into an orthogonal basis.
    */
    Matrix3<double> MakeBasis(Vector3<Value_> const &plane, Vector3<Value_> const &axis) const
    {
        auto const mag_z = axis.Mag();
        if (mag_z == Value_(0)) {
            if (plane.Mag() != Value_(0)) return MakeBasis(axis, plane);
            return {};
        }
        auto matrix = Matrix3<double> {axis / mag_z, Dim3::z};

        auto mag_x = plane.Mag();
        if (mag_x == Value_(0)) {
            matrix.X() = matrix.Z().Orthogonal();
            mag_x = 1;
        } else matrix.X() = plane;

        matrix.Y() = matrix.Z().Cross(matrix.X()) / mag_x;
        auto const mag_y = matrix.Y().Mag();
        matrix.Y() = mag_y == Value_(0) ? matrix.Z().Orthogonal() : matrix.Y() / mag_y;
        matrix.X() = matrix.Y().Cross(matrix.Z());
        return matrix;
    }

};

template <typename>
struct IsMatrix3 : std::false_type { };

template <typename Value>
struct IsMatrix3<Matrix3<Value>> : std::true_type { };

template<typename Value>
using OnlyIfNotMatrix3 = typename std::enable_if < !IsMatrix3<Value>::value >::type;

/**
* @brief Multiplication with a scalar
*/
template < class Value_, class Value_2_, typename = OnlyIfNotMatrix3<Value_2_> >
constexpr auto operator*(Matrix3<Value_> const &matrix, Value_2_ scalar)
{
    return matrix.Scale(scalar);
}

/**
* @brief Multiplication with a scalar
*/
template < class Value_, class Value_2_, typename = OnlyIfNotMatrix3<Value_2_> >
constexpr auto operator*(Value_2_ scalar, Matrix3<Value_> const &matrix)
{
    return matrix.Scale(scalar);
}

/**
* @brief Multiplication with a vector
*/
template < class Value_, class Value_2_>
constexpr auto operator*(Matrix3<Value_> const &matrix, Vector3<Value_2_> const &vector)
{
    return matrix.Multiply(vector);
}

/**
* @brief Multiplication with a vector
*/
template < class Value_, class Value_2_>
constexpr Matrix3<ValueProduct<Value_,  Value_2_>> operator*(Vector3<Value_2_> const &vector, Matrix3<Value_> const &matrix)
{
    return {vector.X() *matrix.ColumnX(), vector.Y() *matrix.ColumnY(), vector.Z() *matrix.ColumnZ()};
}

/**
* @brief Multiplication with a matrix
*/
template<typename Value_1_, typename Value_2_>
constexpr Matrix3<ValueProduct<Value_1_,  Value_2_>> MatrixProduct(Vector3<Value_1_> const &vector_1, Vector3<Value_2_> const &vector_2)
{
    return {vector_1.X() *vector_2, vector_1.Y() *vector_2, vector_1.Z() *vector_2};
}


/**
* @brief Rotates around the axis specified by another vector
*/

template<typename Value_1_>
template<typename Value_2_>
auto &Vector3<Value_1_>::Rotate(boca::Angle angle, Vector3<Value_2_> const &axis)
{
    Matrix3<double> matrix;
    matrix.Rotate(angle, axis);
    operator*=(matrix);
}

/**
* @brief Transformation with a Rotation matrix.
*/
template<typename Value_1_>
template<typename Value_2_>
auto &Vector3<Value_1_>::Transform(Matrix3<Value_2_> const &matrix)
{
    return *this = matrix * (*this);
}

/**
* @brief Multiplication with a matrix
*/
template<typename Value_1_>
template<typename Value_2_>
auto &Vector3<Value_1_>::operator*=(Matrix3<Value_2_> const &matrix)
{
    return *this = matrix * (*this);
}

}
