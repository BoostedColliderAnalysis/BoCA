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
    Matrix3() {}

    /**
    * @brief Diagonal Matrix
    */
    Matrix3(Value_ scalar, Matrix matrix = Matrix::diagonal)
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

    // Construct from three rows
    Matrix3(Vector3<Value_> const &x, Vector3<Value_> const &y, Vector3<Value_> const &z, Matrix matrix = Matrix::row)
    {
        switch (matrix) {
        case Matrix::row:
            SetRows(x, y, z);
            break;
        case Matrix::column :
            SetColumns(x, y, z);
            break;
        default :
            std::cout << "Maformed matrix constructor: " << Name(matrix) << std::endl;
        }
    }

    // Construct from vector product
    Matrix3(Vector3<Value_> const &vector_1, Vector3<Value_> const &vector_2, Matrix matrix = Matrix::symmetric)
    {
        switch (matrix) {
        case Matrix::symmetric:
            *this = MatrixProduct(vector_1, vector_2);
            break;
        default :
            std::cout << "Maformed matrix constructor: " << Name(matrix) << std::endl;
        }
    }

    // Construct anti symetric matrix from vector
    Matrix3(Vector3<Value_> const &vector, Matrix matrix = Matrix::antisymmetric)
    {
        switch (matrix) {
        case Matrix::antisymmetric:
            SetAntisymmetric(vector);
            break;
        default :
            std::cout << "Maformed matrix constructor: " << Name(matrix) << std::endl;
        }
    }

    // Constructor for a rotation based on a Quaternion
    // if magnitude of quaternion is null, creates identity rotation
    // if quaternion is non-unit, creates rotation corresponding to the normalized(unit) quaternion
    Matrix3(TQuaternion const &quaternion)
    {
        auto mag2 = quaternion.QMag2();
        if (mag2 <= 0) {
            // Identity
            *this = Matrix3(1.);
        } else {
            *this = 2 * (Matrix3(sqr(quaternion.fRealPart)) + Matrix3(Vector3<double>(quaternion.fVectorPart), Vector3<double>(quaternion.fVectorPart)) - Matrix3(Vector3<double>(quaternion.fVectorPart * quaternion.fRealPart)));
            // protect agains non-unit quaternion
            if (std::abs(mag2 - 1) > 1e-10) *this /= mag2;
            // diago : remove identity
            *this -= Matrix3(1.);
        }
    }

    // Constructor
    template<typename Value_2>
    Matrix3(Matrix3<Value_2> const &matrix)
    {
        x_ = matrix.X();
        y_ = matrix.Y();
        z_ = matrix.Z();
    }

    //@}

    /**
    * @name Setter
    * @{
    */

    /**
    * @brief Set diagonal
    */
    Matrix3 &SetDiagonal(Value_ value)
    {
        x_ = {value, Dim3::x};
        y_ = {value, Dim3::y};
        z_ = {value, Dim3::z};
        return *this;
    }

    // Set equal to the identity rotation.
    Matrix3 &SetToIdentity()
    {
        return SetDiagonal(1);
    }

    Matrix3 &SetUniform(Value_ value)
    {
        x_ = {value, value, value};
        y_ = {value, value, value};
        z_ = {value, value, value};
        return *this;
    }

    void SetRows(Vector3<Value_> const &x, Vector3<Value_> const &y, Vector3<Value_> const &z)
    {
        x_ = x;
        y_ = y;
        z_ = z;
    }

    void SetColumns(Vector3<Value_> const &x, Vector3<Value_> const &y, Vector3<Value_> const &z)
    {
        x_ = {x.X(), y.X(), z.X()};
        y_ = {x.Y(), y.Y(), z.Y()};
        z_ = {x.Z(), y.Z(), z.Z()};
    }

    void SetAntisymmetric(Vector3<Value_> const &vector)
    {
        x_ = {Value_(0), vector.Z(), -vector.Y()};
        y_ = { -vector.Z(), Value_(0), vector.X()};
        z_ = {vector.Y(), -vector.X(), Value_(0)};
    }

    // Rotate using the x-convention(Landau and Lifshitz, Goldstein, &c) by
    // doing the explicit rotations.  This is slightly less efficient than
    // directly applying the rotation, but makes the code much clearer.  My
    // presumption is that this code is not going to be a speed bottle neck.
    Matrix3 &SetXEulerAngles(Angle const &phi, Angle const &theta, Angle const &psi)
    {
        SetToIdentity();
        RotateZ(phi);
        RotateX(theta);
        RotateZ(psi);
        return *this;
    }

    //set XPhi
    void SetXPhi(Angle const &phi)
    {
        SetXEulerAngles(phi, XTheta(), XPsi());
    }

    //set XTheta
    void SetXTheta(Angle const &theta)
    {
        SetXEulerAngles(XPhi(), theta, XPsi());
    }

    //set XPsi
    void SetXPsi(Angle const &psi)
    {
        SetXEulerAngles(XPhi(), XTheta(), psi);
    }

    // Rotate using the y-convention.
    Matrix3 &SetYEulerAngles(Angle const &phi, Angle const &theta, Angle const &psi)
    {
        SetToIdentity();
        RotateZ(phi);
        RotateY(theta);
        RotateZ(psi);
        return *this;
    }

    //set YPhi
    void SetYPhi(Angle const &phi)
    {
        SetYEulerAngles(phi, YTheta(), YPsi());
    }

    //set YTheta
    void SetYTheta(Angle const &theta)
    {
        SetYEulerAngles(YPhi(), theta, YPsi());
    }

    //set YPsi
    void SetYPsi(Angle const &psi)
    {
        SetYEulerAngles(YPhi(), YTheta(), psi);
    }

    //set X axis
    Matrix3 &SetXAxis(Vector3<Value_> const &axis)
    {
        auto xyPlane = Vector3<Value_> {0, 1, 0};
        return SetXAxis(axis, xyPlane);
    }

    //set X axis
    Matrix3 &SetXAxis(Vector3<Value_> const &axis, Vector3<Value_> const &xyPlane)
    {
        auto matrix = MakeBasis(xyPlane, axis);
        auto matrix2 = Matrix3 {matrix.Z(), matrix.X(), matrix.Y()};
        x_ = matrix2.ColumnX();
        y_ = matrix2.ColumnY();
        z_ = matrix2.ColumnZ();
        return *this;
    }

    //set Y axis
    Matrix3 &SetYAxis(Vector3<Value_> const &axis)
    {
        auto yzPlane = Vector3<Value_> {0, 0, 1};
        return SetYAxis(axis, yzPlane);
    }

    //set Y axis
    Matrix3 &SetYAxis(Vector3<Value_> const &axis, Vector3<Value_> const &yzPlane)
    {
        auto matrix = MakeBasis(yzPlane, axis);
        auto matrix2 = Matrix3 {matrix.Y(), matrix.Z(), matrix.X()};
        x_ = matrix2.ColumnX();
        y_ = matrix2.ColumnY();
        z_ = matrix2.ColumnZ();
        return *this;
    }

    //set Z axis
    Matrix3 &SetZAxis(Vector3<Value_> const &axis)
    {
        auto zxPlane = Vector3<Value_> {1, 0, 0};
        return SetZAxis(axis, zxPlane);
    }

    // Create a rotation with the axis vector parallel to the rotated coordinate
    // systematrix.  If a second vector is provided it defines a plane passing
    //set Z axis
    Matrix3 &SetZAxis(Vector3<Value_> const &axis, Vector3<Value_> const &zxPlane)
    {
        auto matrix = MakeBasis(zxPlane, axis);
        x_ = matrix.ColumnX();
        y_ = matrix.ColumnY();
        z_ = matrix.ColumnZ();
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
    Vector3<Value_> X() const
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
    Vector3<Value_> Y() const
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

    Vector3<Value_> Z() const
    {
        return z_;
    }
    //@}

    //@}

    /**
    * @brief Check if this is the identity matrix
    */
    bool IsIdentity() const
    {
        return x_ == Vector3<Value_>(1, 0, 0) && y_ == Vector3<Value_>(0, 1, 0) && z_ == Vector3<Value_>(0, 0, 1);
    }

    /**
    * @name Accessor and getter
    * @{
    */

    /**
    * @brief x
    */

    /**
    * @brief transposed matrix
    */
    Matrix3 Transposed() const
    {
        return {ColumnX(), ColumnY(), ColumnZ()};
    }

    /**
    * @brief transpose this matrix
    */
    Matrix3 &Transpose()
    {
        return *this = Transposed();
    }

    /**
    * @brief vector of the diagonal
    */
    Vector3<Value_> Diagonal()
    {
        return {x_.X(), y_.Y(), z_.Z()};
    }

    /**
    * @brief vector of upper triangle
    */
    Vector3<Value_> UpperTriangle()
    {
        return {x_.Y(), x_.Z(), y_.Z()};
    }

    /**
    * @brief vector of lower triangle
    */
    Vector3<Value_> LowerTriangle()
    {
        return {y_.X(), z_.X(), z_.Y()};
    }

    Matrix Symmetry()
    {
        if (UpperTriangle() == LowerTriangle()) return Matrix::symmetric;
        if (UpperTriangle() == -LowerTriangle() && Diagonal() == Vector3<Value_> {0, 0, 0}) return Matrix::antisymmetric;
        return Matrix::none;
    }

    /**
    * @brief Inverse matrix
    *
    * return zero matrix if the determinant is zero
    */
    Matrix3<ValueInverse> Inverse()
    {
        auto det = Determinant();
        if (det == ValueCubed(0)) {
            std::cout << "Matrix is not invertible" << std::endl;
            return {};
        }
        auto x = ColumnX();
        auto y = ColumnY();
        auto z = ColumnZ();
        return Matrix3<ValueSquare>(y ^ z, z ^ x, x ^ y) / det;
    }

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
        return Vector2<Value_>(x_.X(), y_.X()).Phi();
    }

//return Phi
    Angle PhiY() const
    {
        return Vector2<Value_>(x_.Y(), y_.Y()).Phi();
    }

//return Phi
    Angle PhiZ() const
    {
        return Vector2<Value_>(x_.Z(), y_.Z()).Phi();
    }

    //return Theta
    Angle ThetaX() const
    {
        return acos(z_.X());
    }

//return Theta
    Angle ThetaY() const
    {
        return acos(z_.Y());
    }
// Return angles(RADS) made by rotated axes against original axes(Geant4).
    Angle ThetaZ() const
    {
        //return Theta
        return acos(z_.Z());
    }

    //return phi angle
    Angle XPhi() const
    {
        auto s2 =  ValueSquare(1) - z_.Z() * z_.Z();
        if (s2 < ValueSquare(0)) {
            std::cout << "Phi() |z_.Z()| > 1 " << std::endl;
            s2 = 0;
        }
        auto sinTheta = std::sqrt(s2);
        if (sinTheta != Value_(0)) {
            auto cscTheta = 1 / sinTheta;
            auto cosAbsPhi =  z_.Y() * cscTheta;
            if (std::abs(cosAbsPhi) > 1) {         // NaN-proofing
                std::cout << "Phi() finds | cos phi | > 1" << std::endl;
                cosAbsPhi = 1;
            }
            auto absPhi = acos(cosAbsPhi);
            if (z_.X() > 0) return absPhi;
            if (z_.X() < 0) return -absPhi;
            if (z_.Y() > 0) return 0_rad;
            return Pi();
        } else {              // sinTheta == Value(0) so |Fzz| = 1
            auto absPhi = .5 * acos(x_.X());
            if (x_.Y() > 0) return -absPhi;
            if (x_.Y() < 0) return absPhi;
            if (x_.X() > 0) return 0_rad;
            return z_.Z() * Pi() / 2;
        }
    }

    //return XTheta
    double XTheta() const
    {
        return ThetaZ();
    }

// Return the euler angles of the rotation.  See SetYEulerAngles for a
// note about conventions.
    Angle XPsi() const
    {
        // psi angle
        auto s2 =  1 - z_.Z() * z_.Z();
        if (s2 < 0) {
            std::cout << "Psi() |z_.Z()| > 1 " << std::endl;
            s2 = 0;
        }
        auto sinTheta = std::sqrt(s2);
        if (sinTheta != 0) {
            auto cscTheta = 1 / sinTheta;
            auto cosAbsPsi =  - y_.Z() * cscTheta;
            if (std::abs(cosAbsPsi) > 1) {         // NaN-proofing
                std::cout << "Psi() | cos psi | > 1 " << std::endl;
                cosAbsPsi = 1;
            }
            auto absPsi = boca::acos(cosAbsPsi);
            if (x_.Z() > 0) return absPsi;
            if (x_.Z() < 0) return -absPsi;
            return (y_.Z() < 0) ? 0_rad : Pi();
        } else {              // sinTheta == Value(0) so |Fzz| = 1
            auto absPsi = x_.X();
            // NaN-proofing
            if (std::abs(x_.X()) > 1) {
                std::cout << "Psi() | x_.X() | > 1 " << std::endl;
                absPsi = 1;
            }
            auto absPsi2 = .5 * acos(absPsi);
            if (y_.X() > 0) return absPsi2;
            if (y_.X() < 0) return -absPsi2;
            return (x_.X() > 0) ? 0_rad : Pi() / 2.;

        }
    }

    //return YPhi
    Angle YPhi() const
    {
        return XPhi() + Pi() / 2.;
    }

    //return YTheta
    Angle YTheta() const
    {
        return ThetaZ();
    }

// Return the euler angles of the rotation.  See SetYEulerAngles for a
// note about conventions.
    //return YPsi
    Angle YPsi() const
    {
        return XPsi() - Pi() / 2.;
    }

    //@}

    /**
    * @name Rotate
    * @{
    */

    /**
    * @brief Rotation around the x-axis.
    */
    Matrix3 &RotateX(Angle const &phi)
    {
        //rotate around x
        auto cos = boost::units::cos(phi);
        auto sin = boost::units::sin(phi);
        auto vector = y_;
        y_ = cos * vector - sin * z_;
        z_ = sin * vector + cos * z_;
        return *this;
    }

// Rotation around the y-axis.
    Matrix3 &RotateY(Angle const &phi)
    {
        //rotate around y
        auto cos = boost::units::cos(phi);
        auto sin = boost::units::sin(phi);
        auto vector = z_;
        z_ = cos * vector - sin * x_;
        x_ = sin * vector + cos * x_;
        return *this;
    }

// Rotation around the z-axis.
    Matrix3 &RotateZ(Angle const &phi)
    {
        //rotate around z
        auto cos = boost::units::cos(phi);
        auto sin = boost::units::sin(phi);
        auto vector = x_;
        x_ = cos * vector - sin * y_;
        y_ = sin * vector + cos * y_;
        return *this;
    }

// Rotation around a specified vector.
    //rotate along an axis
    Matrix3 &Rotate(Angle const &phi, Vector3<Value_> const &axis)
    {
        if (phi == 0_rad)  return *this;
        auto sin = boost::units::sin(phi);
        auto cos = boost::units::cos(phi);
        auto vector = axis.Unit();
        Transform(Matrix3(cos) + Matrix3(vector, vector) * (1 - cos) - Matrix3(vector * sin));
        return *this;
    }

// Rotation of local axes(Geant4).
    //rotate axes
    Matrix3 &RotateAxes(Vector3<Value_> const &vector_x, Vector3<Value_> const &vector_y, Vector3<Value_> const &vector_z)
    {
        auto epsilon = 0.001;
        auto cross = vector_x.Cross(vector_y);
        if (std::abs(vector_z.X() - cross.X()) > epsilon || std::abs(vector_z.Y() - cross.Y()) > epsilon || std::abs(vector_z.Z() - cross.Z()) > epsilon || std::abs(vector_x.Mag2() - 1) > epsilon || std::abs(vector_y.Mag2() - 1) > epsilon || std::abs(vector_z.Mag2() - 1) > epsilon || std::abs(vector_x.Dot(vector_y)) > epsilon || std::abs(vector_y.Dot(vector_z)) > epsilon || std::abs(vector_z.Dot(vector_x)) > epsilon) {
            std::cout << "RotateAxes bad axis vectors" << std::endl;
            return *this;
        }
        return Transform(Matrix3(vector_x.X(), vector_y.X(), vector_z.X(), vector_x.Y(), vector_y.Y(), vector_z.Y(), vector_x.Z(), vector_y.Z(), vector_z.Z()));
    }

// Set the euler angles of the rotation.  The angles are defined using the
// y-convention which rotates around the Z axis, around the new X axis, and
// then around the new Z axis.  The x-convention is used Goldstein, Landau
// and Lifshitz, and other common physics texts.  Contrast this with
// SetYEulerAngles.

// Adds a rotation of the local axes defined by the Euler angle to the
// current rotation.  See SetXEulerAngles for a note about conventions.
    Matrix3 &RotateXEulerAngles(Angle const &phi, Angle const &theta, Angle const &psi)
    {
        // Rotate using the x-convention.
        auto euler = Matrix3 {};
        euler.SetXEulerAngles(phi, theta, psi);
        return Transform(euler);
    }

// Returns the rotation angle and rotation axis(Geant4).
    //rotation defined by an angle and a vector
    void AngleAxis(Angle &angle, Vector3<Value_> &axis) const
    {
        auto cosa  = 0.5 * (x_.X() + y_.Y() + z_.Z() - 1);
        auto cosa1 = 1 - cosa;
        if (cosa1 <= Value_(0)) {
            angle = 0_rad;
            axis  = Vector3<Value_>(0, 0, 1);
        } else {
            auto x = 0.;
            auto y = 0.;
            auto z = 0.;
            if (x_.X() > cosa) x = std::sqrt((x_.X() - cosa) / cosa1);
            if (y_.Y() > cosa) y = std::sqrt((y_.Y() - cosa) / cosa1);
            if (z_.Z() > cosa) z = std::sqrt((z_.Z() - cosa) / cosa1);
            if (z_.Y() < y_.Z())  x = -x;
            if (x_.Z() < z_.X())  y = -y;
            if (y_.X() < x_.Y())  z = -z;
            angle = acos(cosa);
            axis  = Vector3<Value_>(x, y, z);
        }
    }

// Set the euler angles of the rotation.  The angles are defined using the
// y-convention which rotates around the Z axis, around the new Y axis, and
// then around the new Z axis.  The x-convention is used Goldstein, Landau
// and Lifshitz, and other common physics texts and is a rotation around the
// Z axis, around the new X axis, and then around the new Z axis.

// Adds a rotation of the local axes defined by the Euler angle to the
// current rotation.  See SetYEulerAngles for a note about conventions.
    // Rotate using the y-convention.
    Matrix3 &RotateYEulerAngles(Angle const &phi, Angle const &theta, Angle const &psi)
    {
        auto euler = Matrix3 {};
        euler.SetYEulerAngles(phi, theta, psi);
        return Transform(euler);
    }

    //@}

    /**
    * @name Scalar
    * @{
    */

    auto Sign(Dim3 i, Dim3 j) const
    {
        return (static_cast<int>(i) + static_cast<int>(j)) % 2 ? -1 : 1;
    }

    /**
    * @brief Trace
    */
    auto Trace()const
    {
        return x_.X() + y_.Y() + z_.Z();
    }

    template<typename Value_2_>
    auto ProductTrace(Matrix3<Value_2_> const &matrix) const
    {
        return x_ * matrix.ColumnX() + y_ * matrix.ColumnY() + z_ * matrix.ColumnZ();
    }

    /**
    * @brief Determinant
    */
    auto Determinant()const
    {
        return  boost::accumulate(Dimensions3(), ValueCubed(0), [&](ValueCubed & sum, Dim3 dim) {
            return sum + Laplace(Dim3::x, dim);
        });
    }

    /**
    * @brief Laplace
    */
    auto Laplace(Dim3 dim_1, Dim3 dim_2) const
    {
        return (*this)[dim_1][dim_2] * Cofactor(dim_1, dim_2);
    }

    auto Cofactor(Dim3 dim_1, Dim3 dim_2) const
    {
        return static_cast<double>(Sign(dim_1, dim_2)) * Minor(dim_1, dim_2);
    }

    auto Minor(Dim3 delete_1, Dim3 delete_2) const
    {
        return SubMatrix(delete_1, delete_2).Determinant();
    }

    auto ReducedDeterminant(Dim3 dim_1, Dim3 dim_2) const
    {
        return Determinant() - Laplace(dim_1, dim_2);
    }

    //@}

    /**
    * @name Matrix
    * @{
    */

    /**
    * @brief Sub matrix
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

    //@}



// through the axis.

// Take two input vectors(in xAxis, and zAxis) and turn them into an
// orthogonal basis.  This is an internal helper function used to implement
// the Set?Axis functions, but is exposed because the functionality is
// often useful.
    Matrix3 MakeBasis(Vector3<Value_> const &xAxis, Vector3<Value_> const &zAxis) const
    {
        auto matrix = Matrix3 {};
        // Make the Z axis into a unit variable.
        auto zmag = zAxis.Mag();
        if (zmag < 1E-6) std::cout << "MakeBasis(X,Y,Z) non-zero Z Axis is required" << std::endl;
        matrix.Z() = zAxis / zmag;
        auto xmag = xAxis.Mag();
        if (xmag < 1E-6 * zmag) {
            matrix.X() = matrix.Z().Orthogonal();
            xmag = 1;
        } else matrix.X() = xAxis;
        // Find the Y axis
        matrix.Y() = matrix.Z().Cross(matrix.X()) * (1 / xmag);
        auto ymag = matrix.Y().Mag();
        matrix.Y() = ymag < 1E-6 * zmag ? matrix.Z().Orthogonal() : matrix.Y() / ymag;
        matrix.X() = matrix.Y().Cross(matrix.Z());
        return matrix;
    }

    /**
     * @name Columns
     * @{
     */

    /**
    * @brief x-column
    */
    Vector3<Value_> ColumnX() const
    {
        return {x_.X(), y_.X(), z_.X()};
    }

    /**
    * @brief y-column
    */
    Vector3<Value_> ColumnY() const
    {
        return {x_.Y(), y_.Y(), z_.Y()};
    }

    /**
    * @brief z-column
    */
    Vector3<Value_> ColumnZ() const
    {
        return {x_.Z(), y_.Z(), z_.Z()};
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
    Matrix3<ValueProduct<Value_2_>> Multiply(Matrix3<Value_2_> const &matrix) const
    {
        return {{x_ * matrix.ColumnX(), x_ * matrix.ColumnY(), x_ * matrix.ColumnZ()}, {y_ * matrix.ColumnX(), y_ * matrix.ColumnY(), y_ * matrix.ColumnZ()}, {z_ * matrix.ColumnX(), z_ * matrix.ColumnY(), z_ * matrix.ColumnZ()}};
    }

    /**
    * @brief Multiplication with a Vector
    */
    template<typename Value_2_>
    Vector3<ValueProduct<Value_2_>> Multiply(Vector3<Value_2_> const &vector) const
    {
        return {x_ * vector, y_ * vector, z_ * vector};
    }

    /**
    * @brief Scale by scalar
    */
    template<typename Value_2_>
    Matrix3<ValueProduct<Value_2_>> Scaled(Value_2_ scalar) const
    {
        return {x_ * scalar, y_ * scalar, z_ * scalar};
    }

    //@}

    /**
     * @name Operator
     * @{
     */

    /**
    * @brief Less than comparison according to determinans
    */
    bool operator<(Matrix3 const &matrix) const
    {
        return abs(Determinant()) < abs(matrix.Determinant());
    }

    /**
    * @brief Equality comnparison
    */
    bool operator==(Matrix3 const &matrix) const
    {
        return x_ == matrix.x_ && y_ == matrix.y_ && z_ == matrix.z_;
    }

    /**
    * @brief Addition
    */
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    Matrix3 &operator+=(Matrix3<Value_2> const &matrix)
    {
        x_ += matrix.x_;
        y_ += matrix.y_;
        z_ += matrix.z_;
        return *this;
    }

    /**
    * @brief Substraction
    */
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    Matrix3 &operator-=(Matrix3<Value_2> const &matrix)
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
    Matrix3 &operator*=(Matrix3<Value_2_> const &matrix)
    {
        return *this = Multiply(matrix);
    }

    /**
    * @brief Multiplication with a matrix
    */
    template<typename Value_2_>
    Matrix3<ValueProduct<Value_2_>> operator*(Matrix3<Value_2_> const &matrix) const
    {
        return Multiply(matrix);
    }

    /**
    * @brief Multiplication with a Vector
    */
    template<typename Value_2_>
    Vector3<ValueProduct<Value_2_>> operator*(Vector3<Value_2_> const &vector) const
    {
        return Multiply(vector);
    }

    /**
    * @brief Division by scalar
    */
    template<typename Value_2_, typename = OnlyIfNotOrSameQuantity<Value_2_>>
    Matrix3<ValueQuotient<Value_2_>> operator/=(Value_2_ scalar)
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
    Matrix3<ValueQuotient<Value_2_>> operator/(Value_2_ scalar) const
    {
        return Scaled(1. / scalar);
    }

    /**
    * @brief Components by index
    */
    Vector3<Value_> const &operator()(Dim3 dim) const
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
    Value_ const &operator()(Dim3 i, Dim3 j) const
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
    Vector3<Value_> const &operator[](Dim3 i) const
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
    ConstSubIterator<boca::Matrix3, Vector3, Value_, Dim3> begin() const
    {
        return {this, Dim3::x};
    }

    /**
    * @brief Const end
    */
    ConstSubIterator<boca::Matrix3, Vector3, Value_, Dim3> end() const
    {
        return {this, Dim3::last};
    }

    /**
    * @brief Begin
    */
    SubIterator<boca::Matrix3, Vector3, Value_, Dim3> begin()
    {
        return {this, Dim3::x};
    }

    /**
    * @brief End
    */
    SubIterator<boca::Matrix3, Vector3, Value_, Dim3> end()
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
    Array3<Value_> EigenValues() const
    {
        return Eigen().Values();
    }

    /**
    * @brief Eigen vectors
    */
    Array3<Vector3<Value_>> EigenVectors() const
    {
        return Eigen().Vectors();
    }

    /**
    * @brief Eigen system
    */
    Array3<GradedVector3<Value_>> EigenSystem() const
    {
        return Eigen().System();
    }

    //@}

private:

    class Characteristic_
    {
    public:
        Characteristic_(Matrix3 const &matrix)
        {
            qudratic_ = - matrix.Trace();
            linear_ = - (matrix.ProductTrace(matrix) - sqr(qudratic_)) / 2;
            constant_ = - matrix.Determinant();
        }
        Value_ Qudratic() const
        {
            return qudratic_;
        }
        ValueSquare Linear() const
        {
            return linear_;
        }
        ValueCubed Constant() const
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
        Depressed_(Characteristic_ const &c)
        {
            auto quadratic = c.Qudratic() / 3;
            linear_ = c.Linear() - sqr(quadratic) * 3;
            constant_ = 2. * cube(quadratic) - quadratic * c.Linear() + c.Constant();
        }
        ValueSquare Linear() const
        {
            return linear_;
        }

        ValueCubed Constant() const
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
        Eigen_() {}
        Eigen_(Depressed_ const &d, Matrix3<Value_> const &matrix)
        {
            factor_ = 2. * sqrt(- d.Linear() / 3.);
            angle_ = acos(3. * d.Constant() / d.Linear() / factor_);
            complex_ = 4 * cube(d.Linear()) > - 27 * sqr(d.Constant());
            matrix_ = &matrix;
        }
        Array3<Value_> Values() const
        {
            return values_.Get([&]() {
                auto values = Array3<Value_> {};
                if (complex_) {
                    for (auto &value : values) value = -1;
                    std::cerr << "Eigensystem has no real Eigenvalues!\n";
                    return values;
                }
                for (auto index : IntegerRange(values.size())) values.at(index) = Value(index);
                return boost::range::sort(values, [](Value_ i, Value_ j) {
                    return abs(i) > abs(j);
                });
            });
        }
        Array3<Vector3<Value_>> Vectors() const
        {
            return vectors_.Get([&]() {
                auto vectors = Array3<Vector3<Value_>> {};
                for (auto index : IntegerRange(vectors.size())) vectors.at(index) = Vector(index);
                return vectors;
            });
        }
        Array3<GradedVector3<Value_>> System() const
        {
            auto system = Array3<GradedVector3<Value_>> {};
            for (auto index : IntegerRange(system.size())) system.at(index) = {Vectors().at(index), Values().at(index)};
            return system;
        }

    private:

        Value_ Factor() const
        {
            return factor_;
        }

        boca::Angle Angle() const
        {
            return angle_;
        }

        Value_ Value(int index) const
        {
            return Factor() * cos((Angle() - TwoPi() * static_cast<double>(index)) / 3.) + matrix_->Trace() / 3;
        }

        Vector3<Value_> Vector(int index) const
        {
            auto matrix = *matrix_ - Matrix3<Value_>(Values().at(index));
            return Vector3<Value_>(matrix.Cofactor(Dim3::x, Dim3::x), matrix.Cofactor(Dim3::x, Dim3::y), matrix.Cofactor(Dim3::x, Dim3::z)).Unit();
        }
        Value_ factor_;
        boca::Angle angle_;
        bool complex_;
        Mutable<Array3<Value_>> values_;
        Mutable<Array3<Vector3<Value_>>> vectors_;
        Matrix3<Value_> const *matrix_;
    };

    Eigen_ const &Eigen() const
    {
        return eigen_.Get([&]() {
            return Eigen_(Depressed_(Characteristic_(*this)), *this);
        });
    }

    Mutable<Eigen_> eigen_;

    Vector3<Value_> x_;

    Vector3<Value_> y_;

    Vector3<Value_> z_;

};

template <typename>
struct IsMatrix3 : std::false_type { };

template <typename Value>
struct IsMatrix3<Matrix3<Value>> : std::true_type { };

template<typename Value>
using OnlyIfNotMatrix3 = typename std::enable_if < !IsMatrix3<Value>::value >::type;

template < class Value_, class Value_2_, typename = OnlyIfNotMatrix3<Value_2_> >
auto operator*(Matrix3<Value_> const &matrix, Value_2_ scalar)
{
    return matrix.Scale(scalar);
}

template < class Value_, class Value_2_, typename = OnlyIfNotMatrix3<Value_2_> >
auto operator*(Value_2_ scalar, Matrix3<Value_> const &matrix)
{
    return matrix.Scale(scalar);
}

template < class Value_, class Value_2_>
auto operator*(Matrix3<Value_> const &matrix, Vector3<Value_2_> const &vector)
{
    return matrix.Multiply(vector);
}

template < class Value_, class Value_2_>
Matrix3<ValueProduct<Value_,  Value_2_>> operator*(Vector3<Value_2_> const &vector, Matrix3<Value_> const &matrix)
{
    return {vector.X() *matrix.ColumnX(), vector.Y() *matrix.ColumnY(), vector.Z() *matrix.ColumnZ()};
}

template<typename Value_1_, typename Value_2_>
Matrix3<ValueProduct<Value_1_,  Value_2_>> MatrixProduct(Vector3<Value_1_> const &vector_1, Vector3<Value_2_> const &vector_2)
{
    return {vector_1.X() *vector_2, vector_1.Y() *vector_2, vector_1.Z() *vector_2};
}

}
