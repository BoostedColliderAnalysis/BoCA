#pragma once

#include "boca/Matrix3.hh"
#include "boca/LorentzVector.hh"

namespace boca
{

/**
 * @ingroup Math
 * @brief Lorentz matrix
 */
template<typename Value_>
class LorentzMatrix
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


    // Default constructor
    LorentzMatrix() {}

    // Constructor for 3d rotations.
    LorentzMatrix(Matrix3<Value_> const& matrix, Vector3<Value_> const& vector, Value_ scalar, Matrix symmetry = Matrix::none) {
        if (symmetry == Matrix::none) symmetry == matrix.Symmetry();
        if (symmetry != Matrix::symmetric || symmetry != Matrix::antisymmetric) std::cout << "matrix symmetry not well defiend" << std::endl;
        SetMatrix(matrix);
        SetVector(vector, symmetry);
        SetScalar(scalar);
    }

    // Constructor for 3d rotations.
    LorentzMatrix(Matrix3<Value_> const& matrix) {
        SetMatrix(matrix);
        SetVector( {0, 0, 0}, Matrix::symmetric);
        SetScalar(Value_(1));
    }

    // Constructors giving a Lorenz-boost.
    LorentzMatrix(Vector3<double> const& vector) {
        SetBoost(vector);
    }

    // Construct from three rows
    LorentzMatrix(LorentzVector<Value_> const& x, LorentzVector<Value_> const& y, LorentzVector<Value_> const& z, LorentzVector<Value_> const& t, Matrix matrix = Matrix::row) {
        switch (matrix) {
        case Matrix::row: SetRows(x, y, z, t); break;
        case Matrix::column : SetColumns(x, y, z, t); break;
        default : std::cout << "Maformed matrix constructor: " << Name(matrix) << std::endl;
        }
    }

    void SetMatrix(Matrix3<Value_> const& matrix) {
        x_.SetVector(matrix.X());
        y_.SetVector(matrix.Y());
        z_.SetVector(matrix.Z());
    }

    void SetVector(Vector3<Value_> const& vector, Matrix symmetry) {
        x_.SetScalar(vector.X());
        y_.SetScalar(vector.Y());
        z_.SetScalar(vector.Z());
        switch (symmetry) {
        case Matrix::symmetric : t_.SetVector(vector); break;
        case Matrix::antisymmetric : t_.SetVector(-vector); break;
        default : std::cout << "matrix symmetry not well defiend" << std::endl;
        }
    }

    void SetScalar(Value_ scalar) {
        t_.SetScalar(scalar);
    }

    void SetRows(LorentzVector<Value_> const& x, LorentzVector<Value_> const& y, LorentzVector<Value_> const& z, LorentzVector<Value_> const& t) {
        x_ = x;
        y_ = y;
        z_ = z;
        t_ = t;
    }

    void SetColumns(LorentzVector<Value_> const& x, LorentzVector<Value_> const& y, LorentzVector<Value_> const& z, LorentzVector<Value_> const& t) {
        x_ = {x.X(), y.X(), z.X(), t.X()};
        y_ = {x.Y(), y.Y(), z.Y(), t.Y()};
        z_ = {x.Z(), y.Z(), z.Z(), t.Z()};
        t_ = {x.T(), y.T(), z.T(), t.T()};
    }

    // Elements of the matrix.
    LorentzVector<Value_> X() const {
        return x_;
    }
    LorentzVector<Value_> Y() const {
        return y_;
    }
    LorentzVector<Value_> Z() const {
        return z_;
    }
    LorentzVector<Value_> T() const {
        return t_;
    }
    LorentzVector<Value_>& X() {
        return x_;
    }
    LorentzVector<Value_>& Y() {
        return y_;
    }
    LorentzVector<Value_>& Z() {
        return z_;
    }
    LorentzVector<Value_>& T() {
        return t_;
    }

    Value4 Determinant()const {
        return  boost::accumulate(LorentzDimensions(), Value4(0), [&](Value4 & sum, LorentzDim dim) {
            return sum + Laplace(LorentzDim::x, dim);
        });
    }

    Value4 Laplace(LorentzDim dim_1, LorentzDim dim_2) const {
        return (*this)[dim_1][dim_2] * Cofactor(dim_1, dim_2);
    }

    ValueCubed Cofactor(LorentzDim dim_1, LorentzDim dim_2) const {
        return static_cast<double>(Sign(dim_1, dim_2)) * Minor(dim_1, dim_2);
    }

    ValueCubed Minor(LorentzDim delete_1, LorentzDim delete_2) const {
        return SubMatrix(delete_1, delete_2).Determinant();
    }

    Matrix3<Value_> SubMatrix(LorentzDim delete_1, LorentzDim delete_2) const {
//       std::cout << "delete " << Name(delete_1) <<  " " << Name(delete_2) << std::endl;
        auto dim3_1 = EnumIterator<Dim3>{Dim3::x};
        auto dim3_2 = EnumIterator<Dim3>{Dim3::x};
        auto matrix = Matrix3<Value_>{};
        for (auto dim4_1 : LorentzDimensions()) {
            if (dim4_1 == delete_1) continue;
            for (auto dim4_2 : LorentzDimensions()) {
                if (dim4_2 == delete_2) continue;
//               std::cout << "insert " << Name(dim4_1) <<  " " << Name(dim4_2) << " into "<< Name(*dim3_1) <<  " " << Name(*dim3_2) << std::endl;
                matrix(*dim3_1, *dim3_2) = (*this)(dim4_1, dim4_2);
                ++dim3_2;
            }
            ++dim3_1;
            dim3_2.Set(Dim3::x);
        }
        return matrix;
    }

    Value4 ReducedDeterminant(LorentzDim dim_1, LorentzDim dim_2) const {
        return Determinant() - (*this)[dim_1][dim_2] * Cofactor(dim_1, dim_2);
    }

    Value4 ReducedLaplace(LorentzDim dim_1, LorentzDim dim_2, Dim3 dim_3, Dim3 dim_4) {
        return (*this)[dim_1][dim_2] * SubMatrix(dim_1, dim_2).ReducedDeterminant(dim_3, dim_4);
    }

    int Sign(LorentzDim i, LorentzDim j) const {
        return (static_cast<int>(i) + static_cast<int>(j)) % 2 ? -1 : 1;
    }

    Value_ const& operator()(LorentzDim i, LorentzDim j) const {
        return operator()(i)(j);
    }

    Value_& operator()(LorentzDim i, LorentzDim j) {
        return operator()(i)(j);
    }

    // Returns object of the helper class for C-style subscripting r[i][j]
    LorentzVector<Value_> const& operator[](LorentzDim i) const {
        return operator()(i);
    }

    // Returns object of the helper class for C-style subscripting r[i][j]
    LorentzVector<Value_>& operator[](LorentzDim i) {
        return operator()(i);
    }

    // Fortran-style subscriptimg: returns (i,j) element of the matrix.
    LorentzVector<Value_> const& operator()(LorentzDim i) const {
        //derefencing operator
        switch (i) {
        case LorentzDim::x : return x_;
        case LorentzDim::y : return y_;
        case LorentzDim::z : return z_;
        case LorentzDim::t : return t_;
        }
        std::cout << "operator()(i), subscripting: bad index " << Name(i) << std::endl;
        return x_;
    }

    // Fortran-style subscriptimg: returns (i,j) element of the matrix.
    LorentzVector<Value_>& operator()(LorentzDim i) {
        //derefencing operator
        switch (i) {
        case LorentzDim::x : return x_;
        case LorentzDim::y : return y_;
        case LorentzDim::z : return z_;
        case LorentzDim::t : return t_;
        }
        std::cout << "operator()(i), subscripting: bad index " << Name(i) << std::endl;
        return x_;
    }


    // Assignment.
    LorentzMatrix<Value_>& operator=(const Matrix3<Value_>& matrix) {
        SetMatrix(matrix);
        SetVector( {0, 0, 0}, Matrix::symmetric);
        SetScalar(Value_(1));
        return *this;
    }

    bool operator==(LorentzMatrix const& matrix) const {
        return x_ == matrix.x_ && y_ == matrix.y_ && z_ == matrix.z_ && t_ == matrix.t_ ;
    }

    // Comparisons.
    bool operator!=(LorentzMatrix const& matrix) const {
        return x_ != matrix.x_ || y_ != matrix.y_ || z_ != matrix.z_ || t_ != matrix.t_;
    }

    // Returns true if the Identity matrix.
    bool IsIdentity() const {
        return *this == LorentzMatrix(1, Matrix::diagonal);
    }


    LorentzVector<Value_> ColumnX() const {
        return {x_.X(), y_.X(), z_.X(), t_.X()};
    }

    LorentzVector<Value_> ColumnY() const {
        return {x_.Y(), y_.Y(), z_.Y(), t_.Y()};
    }

    LorentzVector<Value_> ColumnZ() const {
        return {x_.Z(), y_.Z(), z_.Z(), t_.Z()};
    }

    LorentzVector<Value_> ColumnT() const {
        return {x_.T(), y_.T(), z_.T(), t_.T()};
    }


    LorentzVector<Value_> Multiply(const LorentzVector<Value_>& p) const {
        return {x_ * p, y_ * p, z_ * p, t_ * p};
    }

    // Multiplication with a Lorentz vector.
    LorentzVector<Value_> operator* (const LorentzVector<Value_>& p) const {
        return Multiply(p);
    }

    //multiply this vector by a matrix
    LorentzMatrix Multiply(const LorentzMatrix& matrix) const {
        return {{x_ * matrix.ColumnX(), x_ * matrix.ColumnY(), x_ * matrix.ColumnZ(), x_ * matrix.ColumnT()}, {y_ * matrix.ColumnX(), y_ * matrix.ColumnY(), y_ * matrix.ColumnZ(), y_ * matrix.ColumnT()}, {z_ * matrix.ColumnX(), z_ * matrix.ColumnY(), z_ * matrix.ColumnZ(), z_ * matrix.ColumnT()}, {t_ * matrix.ColumnX(), t_ * matrix.ColumnY(), t_ * matrix.ColumnZ(), t_ * matrix.ColumnT()}};
    }

    LorentzMatrix operator* (const LorentzMatrix& m) const {
        return Multiply(m);
    }

    LorentzMatrix& operator*= (const LorentzMatrix& m) {
        return *this = Multiply(m);
    }


    LorentzMatrix& Transform(const LorentzMatrix& m) {
        return *this = m.Multiply(*this);
    }

    // Matrix multiplication.
    // Note: a *= b; <=> a = a * b; while a.Transform(b); <=> a = b * a;
    LorentzMatrix& Transform(const Matrix3<Value_>& m) {
        return Transform(LorentzMatrix(m));
    }

    // Return the inverse.
    LorentzMatrix Inverse() const {
        return {x_.X(),  y_.X(),  z_.X(), -t_.X(),
                x_.Y(),  y_.Y(),  z_.Y(), -t_.Y(),
                x_.Z(),  y_.Z(),  z_.Z(), -t_.Z(),
                -x_.T(), -y_.T(), -z_.T(),  t_.T()
               };
    }

    // Inverts the LorentzRotation matrix.
    LorentzMatrix& Invert() {
        return *this = Inverse();
    }

    // Lorenz boost.
    LorentzMatrix& Boost(const Vector3<Value_>& b) {
        return Transform(LorentzMatrix(b));
    }

    // Rotation around x-axis.
    LorentzMatrix& RotateX(double angle) {
        return Transform(Matrix3<Value_>().RotateX(angle));
    }

    // Rotation around y-axis.
    LorentzMatrix& RotateY(double angle) {
        return Transform(Matrix3<Value_>().RotateY(angle));
    }

    // Rotation around z-axis.
    LorentzMatrix& RotateZ(double angle) {
        return Transform(Matrix3<Value_>().RotateZ(angle));
    }

    // Rotation around specified vector.
    LorentzMatrix& Rotate(double angle, const Vector3<Value_>& axis) {
        return Transform(Matrix3<Value_>().Rotate(angle, axis));
    }
    LorentzMatrix& Rotate(double angle, const Vector3<Value_>* axis) {
        return Transform(Matrix3<Value_>().Rotate(angle, axis));
    }

private:

    // The matrix elements.
    LorentzVector<Value_> x_;
    LorentzVector<Value_> y_;
    LorentzVector<Value_> z_;
    LorentzVector<Value_> t_;

    // Set elements according to a boost vector.
    //boost this Lorentz vector
    void SetBoost(Vector3<double> const& boost) {
        auto bp2 = boost.Mag2();
        auto gamma = 1 / std::sqrt(1 - bp2);
        auto bgamma = sqr(gamma) / (1 + gamma);
        auto matrix = Matrix3<double>(bgamma, Matrix::uniform) + Multiply(boost, boost) + Matrix3<double>(1);
        auto vector = boost + Vector3<double>(gamma, gamma, gamma);
        *this = LorentzMatrix<double>(matrix, vector, gamma);
    }


};

}
