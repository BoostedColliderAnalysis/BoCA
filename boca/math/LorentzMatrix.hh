#pragma once

#include "boca/math/Matrix3.hh"
#include "boca/math/LorentzVector.hh"

namespace boca
{

/**
 * @ingroup Math
 * @brief Lorentz matrix
 */
template<typename Value_>
class LorentzMatrix : public boost::totally_ordered<LorentzMatrix<Value_>>
            , boost::additive<LorentzMatrix<Value_>>
{

    template<typename Value_2_>
    using ValueProduct = ValueProduct<Value_, Value_2_>;
    using ValueSquare = boca::ValueSquare<Value_>;
    using ValueCubed = boca::ValueCubed<Value_>;
    using Value4 = boca::Value4<Value_>;
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
    LorentzMatrix() {}

    /**
    * @brief Constructor accepting one three dimensional matrix,  vector and scalar
    */
    LorentzMatrix(Matrix3<Value_> const &matrix, Vector3<Value_> const &vector, Value_ scalar, Matrix symmetry = Matrix::none)
    {
        if (symmetry == Matrix::none) symmetry == matrix.Symmetry();
        if (symmetry != Matrix::symmetric || symmetry != Matrix::antisymmetric) std::cout << "matrix symmetry not well defiend" << '\n';
        SetMatrix(matrix);
        SetVector(vector, symmetry);
        SetScalar(scalar);
    }

    /**
    * @brief Constructor accepting one three dimensional matrix
    */
    LorentzMatrix(Matrix3<Value_> const &matrix)
    {
        SetMatrix(matrix);
        SetVector({0, 0, 0}, Matrix::symmetric);
        SetScalar(Value_(1));
    }

    /**
    * @brief Constructor accepting one three dimensional vector as a Lorenz-boost.
    */
    LorentzMatrix(Vector3<double> const &vector)
    {
        SetBoost(vector);
    }

    /**
    * @brief Constructor accepting three Lorentz vectors
    */
    LorentzMatrix(LorentzVector<Value_> const &x, LorentzVector<Value_> const &y, LorentzVector<Value_> const &z, LorentzVector<Value_> const &t, Matrix matrix = Matrix::row)
    {
        switch (matrix) {
        case Matrix::row:
            SetRows(x, y, z, t);
            break;
        case Matrix::column :
            SetColumns(x, y, z, t);
            break;
        default :
            std::cout << "Maformed matrix constructor: " << Name(matrix) << '\n';
        }
    }

    //@}

    /**
    * @name Setter
    * @{
    */

    /**
    * @brief Set the three dimension matrix
    */
    void SetMatrix(Matrix3<Value_> const &matrix)
    {
        x_.SetVector(matrix.X());
        y_.SetVector(matrix.Y());
        z_.SetVector(matrix.Z());
    }

    /**
    * @brief Set the three dimensional vectors
    */
    void SetVector(Vector3<Value_> const &vector, Matrix symmetry)
    {
        x_.SetScalar(vector.X());
        y_.SetScalar(vector.Y());
        z_.SetScalar(vector.Z());
        switch (symmetry) {
        case Matrix::symmetric :
            t_.SetVector(vector);
            break;
        case Matrix::antisymmetric :
            t_.SetVector(-vector);
            break;
        default :
            std::cout << "matrix symmetry not well defiend" << '\n';
        }
    }

    /**
    * @brief Set the three dimensional scalar
    */
    void SetScalar(Value_ scalar)
    {
        t_.SetScalar(scalar);
    }

    /**
    * @brief Set the rows
    */
    void SetRows(LorentzVector<Value_> const &x, LorentzVector<Value_> const &y, LorentzVector<Value_> const &z, LorentzVector<Value_> const &t)
    {
        x_ = x;
        y_ = y;
        z_ = z;
        t_ = t;
    }

    /**
    * @brief Set the columns
    */
    void SetColumns(LorentzVector<Value_> const &x, LorentzVector<Value_> const &y, LorentzVector<Value_> const &z, LorentzVector<Value_> const &t)
    {
        x_ = {x.X(), y.X(), z.X(), t.X()};
        y_ = {x.Y(), y.Y(), z.Y(), t.Y()};
        z_ = {x.Z(), y.Z(), z.Z(), t.Z()};
        t_ = {x.T(), y.T(), z.T(), t.T()};
    }

    /**
    * @name Accessor and getter
    * @{
    */

    /**
    * @brief x-row
    * @{
    */
    LorentzVector<Value_> X() const
    {
        return x_;
    }

    LorentzVector<Value_> &X()
    {
        return x_;
    }
    //@}

    /**
    * @brief y-row
    * @{
    */
    LorentzVector<Value_> Y() const
    {
        return y_;
    }

    LorentzVector<Value_> &Y()
    {
        return y_;
    }
    //@}

    /**
    * @brief z-row
    * @{
    */
    LorentzVector<Value_> Z() const
    {
        return z_;
    }

    LorentzVector<Value_> &Z()
    {
        return z_;
    }
    //@}

    /**
    * @brief t-row
    * @{
    */
    LorentzVector<Value_> T() const
    {
        return t_;
    }

    LorentzVector<Value_> &T()
    {
        return t_;
    }
    //@}

    //@}

    /**
    * @name Scalar
    * @{
    */

    /**
    * @brief Determinant \f$\det A = \sum_{i=1}^n A_{i, j} C_{i, j}\f$
    */
    Value4 Determinant()const
    {
        return  boost::accumulate(LorentzDimensions(), Value4(0), [&](Value4 & sum, LorentzDim dim) {
            return sum + Laplace(LorentzDim::x, dim);
        });
    }

    /**
    * @brief Laplace \f$A_{i, j} C_{i, j}\f$
    */
    Value4 Laplace(LorentzDim dim_1, LorentzDim dim_2) const
    {
        return (*this)[dim_1][dim_2] * Cofactor(dim_1, dim_2);
    }

    /**
    * @brief Cofactor \f$C_{i, j} = (-1)^{i+j} M_{i, j}\f$
    */
    ValueCubed Cofactor(LorentzDim dim_1, LorentzDim dim_2) const
    {
        return static_cast<double>(Sign(dim_1, dim_2)) * Minor(dim_1, dim_2);
    }

    /**
    * @brief Minor \f$M_{i, j} = \det ((A_{p, q})_{p\neq i, q\neq j})\f$
    */
    ValueCubed Minor(LorentzDim delete_1, LorentzDim delete_2) const
    {
        return SubMatrix(delete_1, delete_2).Determinant();
    }

    /**
    * @brief Reduced determinant  \f$\det_{i, j} = \det - A_{i, j} C_{i, j}\f$
    */
    Value4 ReducedDeterminant(LorentzDim dim_1, LorentzDim dim_2) const
    {
        return Determinant() - (*this)[dim_1][dim_2] * Cofactor(dim_1, dim_2);
    }

    /**
    * @brief Reduced Laplace \f$\det_{i, j} = A_{i, j} (\det - M_{i, j} C_{i, j})\f$
    */
    Value4 ReducedLaplace(LorentzDim dim_1, LorentzDim dim_2, Dim3 dim_3, Dim3 dim_4)
    {
        return (*this)[dim_1][dim_2] * SubMatrix(dim_1, dim_2).ReducedDeterminant(dim_3, dim_4);
    }

    /**
    * @brief Sign of a given element \f$(-1)^{i+j}\f$
    */
    int Sign(LorentzDim i, LorentzDim j) const
    {
        return (static_cast<int>(i) + static_cast<int>(j)) % 2 ? -1 : 1;
    }

    //@}

    /**
    * @name Matrix
    * @{
    */

    /**
    * @brief Sub matrix \f$(A_{p, q})_{p\neq i, q\neq j}\f$
    */
    Matrix3<Value_> SubMatrix(LorentzDim delete_1, LorentzDim delete_2) const
    {
        auto dim3_1 = EnumIterator<Dim3> {Dim3::x};
        auto dim3_2 = EnumIterator<Dim3> {Dim3::x};
        auto matrix = Matrix3<Value_> {};
        for (auto dim4_1 : LorentzDimensions()) {
            if (dim4_1 == delete_1) continue;
            for (auto dim4_2 : LorentzDimensions()) {
                if (dim4_2 == delete_2) continue;
                matrix(*dim3_1, *dim3_2) = (*this)(dim4_1, dim4_2);
                ++dim3_2;
            }
            ++dim3_1;
            dim3_2.Set(Dim3::x);
        }
        return matrix;
    }

    //@}

    /**
    * @name Matrix
    * @{
    */

    /**
    * @brief x column
    */
    LorentzVector<Value_> ColumnX() const
    {
        return {x_.X(), y_.X(), z_.X(), t_.X()};
    }

    /**
    * @brief y column
    */
    LorentzVector<Value_> ColumnY() const
    {
        return {x_.Y(), y_.Y(), z_.Y(), t_.Y()};
    }

    /**
    * @brief z column
    */
    LorentzVector<Value_> ColumnZ() const
    {
        return {x_.Z(), y_.Z(), z_.Z(), t_.Z()};
    }

    /**
    * @brief t column
    */
    LorentzVector<Value_> ColumnT() const
    {
        return {x_.T(), y_.T(), z_.T(), t_.T()};
    }

    //@}

    /**
    * @name Multiplication
    * @{
    */

    /**
    * @brief Multiply with a vector
    */
    template<typename Value_2_>
    auto Multiply(const LorentzVector<Value_2_> &vector) const
    {
        return {x_ * vector, y_ * vector, z_ * vector, t_ * vector};
    }

    /**
    * @brief Multiply with a matrix
    */
    template<typename Value_2_>
    LorentzMatrix Multiply(const LorentzMatrix<Value_2_> &matrix) const
    {
        return {{x_ * matrix.ColumnX(), x_ * matrix.ColumnY(), x_ * matrix.ColumnZ(), x_ * matrix.ColumnT()},
            {y_ * matrix.ColumnX(), y_ * matrix.ColumnY(), y_ * matrix.ColumnZ(), y_ * matrix.ColumnT()},
            {z_ * matrix.ColumnX(), z_ * matrix.ColumnY(), z_ * matrix.ColumnZ(), z_ * matrix.ColumnT()},
            {t_ * matrix.ColumnX(), t_ * matrix.ColumnY(), t_ * matrix.ColumnZ(), t_ * matrix.ColumnT()}
        };
    }

    /**
    * @brief Transform this matrix
    */
    template<typename Value_2_>
    LorentzMatrix &Transform(const LorentzMatrix<Value_2_> &matrix)
    {
        return *this = matrix.Multiply(*this);
    }

    /**
    * @brief Transform this matrix with a three dimensional matrix
    *
    * a *= b; <=> a = a * b; while a.Transform(b); <=> a = b * a;
    */
    template<typename Value_2_>
    auto &Transform(const Matrix3<Value_2_> &matrix)
    {
        return Transform(LorentzMatrix(matrix));
    }

    /**
    * @brief Transposed
    */
    auto Transposed() const
    {
        return {ColumnX(), ColumnY(), ColumnZ(),ColumnT()};
    }

    /**
    * @brief Transpose
    */
    auto &Transpose()
    {
        return *this = Transposed();
    }

    /**
    * @brief Boost
    */
    template<typename Value_2_>
    auto &Boost(const Vector3<Value_> &boost)
    {
        return Transform(LorentzMatrix(boost));
    }

    /**
    * @brief Rotate
    */
    template<typename Value_2_>
    auto &Rotate(Angle angle, Dim3 dim)
    {
        return Transform(Matrix3<double>().Rotate(angle,  dim));
    }

    /**
    * @brief Rotation around specified vector.
    */
    template<typename Value_2_>
    auto &Rotate(Angle angle, const Vector3<Value_> &axis)
    {
        return Transform(Matrix3<double>().Rotate(angle, axis));
    }

    //@}

    /**
    * @name Operator
    * @{
    */

    /**
    * @brief Less than comparison
    */
    bool operator<(LorentzMatrix const &matrix) const
    {
        return abs(Determinant()) < abs(matrix.Determinant());
    }

    /**
    * @brief Equallity comparison
    */
    bool operator==(LorentzMatrix const &matrix) const
    {
        return x_ == matrix.x_ && y_ == matrix.y_ && z_ == matrix.z_ && t_ == matrix.t_ ;
    }

    /**
    * @brief Multiply with a vector
    */
    template<typename Value_2_>
    auto operator*(const LorentzVector<Value_2_> &vector) const
    {
        return Multiply(vector);
    }

    /**
    * @brief Multiply with a matrix
    */
    template<typename Value_2_>
    auto operator*(const LorentzMatrix<Value_2_> &matrix) const
    {
        return Multiply(matrix);
    }

    /**
    * @brief Multiply with a matrix
    */
    auto &operator*= (const LorentzMatrix<Value_2_> &matrix)
    {
        return *this = Multiply(matrix);
    }

    /**
    * @brief Element by indices
    */
    Value_ const &operator()(LorentzDim i, LorentzDim j) const
    {
        return operator()(i)(j);
    }

    /**
    * @brief Element by indices
    */
    Value_ &operator()(LorentzDim i, LorentzDim j)
    {
        return operator()(i)(j);
    }

    /**
    * @brief Row by index
    */
    LorentzVector<Value_> const &operator[](LorentzDim i) const
    {
        return operator()(i);
    }

    /**
    * @brief Row by index
    */
    LorentzVector<Value_> &operator[](LorentzDim i)
    {
        return operator()(i);
    }

    /**
    * @brief Row by index
    */
    LorentzVector<Value_> const &operator()(LorentzDim i) const
    {
        //derefencing operator
        switch (i) {
        case LorentzDim::x :
            return x_;
        case LorentzDim::y :
            return y_;
        case LorentzDim::z :
            return z_;
        case LorentzDim::t :
            return t_;
        }
        std::cout << "operator()(i), subscripting: bad index " << Name(i) << '\n';
        return x_;
    }

    /**
    * @brief Row by index
    */
    LorentzVector<Value_> &operator()(LorentzDim i)
    {
        //derefencing operator
        switch (i) {
        case LorentzDim::x :
            return x_;
        case LorentzDim::y :
            return y_;
        case LorentzDim::z :
            return z_;
        case LorentzDim::t :
            return t_;
        }
        std::cout << "operator()(i), subscripting: bad index " << Name(i) << '\n';
        return x_;
    }

    /**
     * @brief Output stream operator
     */
    friend auto &operator<<(std::ostream &stream, LorentzMatrix<Value_> const &matrix)
    {
        for(auto const& vector : matrix) stream << vector;
        return stream;
    }

    //@}

private:

    LorentzVector<Value_> x_;

    LorentzVector<Value_> y_;

    LorentzVector<Value_> z_;

    LorentzVector<Value_> t_;

    // Set elements according to a boost vector.
    //boost this Lorentz vector
    void SetBoost(Vector3<double> const &boost)
    {
        auto bp2 = boost.Mag2();
        auto gamma = 1 / std::sqrt(1 - bp2);
        auto bgamma = sqr(gamma) / (1 + gamma);
        auto matrix = Matrix3<double>(bgamma, Matrix::uniform) + Multiply(boost, boost) + Matrix3<double>(1);
        auto vector = boost + Vector3<double>(gamma, gamma, gamma);
        *this = LorentzMatrix<double>(matrix, vector, gamma);
    }


    // Assignment.
//     LorentzMatrix<Value_> &operator=(const Matrix3<Value_> &matrix)
//     {
//         SetMatrix(matrix);
//         SetVector({0, 0, 0}, Matrix::symmetric);
//         SetScalar(Value_(1));
//         return *this;
//     }


};

}
