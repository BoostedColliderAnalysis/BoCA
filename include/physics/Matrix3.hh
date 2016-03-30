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
#include "Vector3.hh"
#include "GradedVector.hh"
#include "Units.hh"
#include "Types.hh"
#include "Mutable.hh"
#include "TQuaternion.h"

namespace boca
{

enum class Matrix
{
    diagonal,
    symmetric,
    antisymmetric,
    row,
    column
};

template <typename Value_>
class Matrix3
// : boost::operators<Matrix3<Value_>>
{

public:

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

    // Default constructor.
    Matrix3() {}

    // Diagonal Matrix
    Matrix3(Value_ scalar) : x_( {scalar, Value_(0), Value_(0)}), y_( {Value_(0), scalar, Value_(0)}), z_( {Value_(0), Value_(0), scalar}) {}

//     // Protected constructor.
//     Matrix3(Value_ xx, Value_ xy, Value_ xz, Value_ yx, Value_ yy, Value_ yz, Value_ zx, Value_ zy, Value_ zz) : x_( {xx, xy, xz}), y_( {yx, yy, yz}), z_( {zx, zy, zz}) {}

    // Construct from three rows
    Matrix3(Vector3<Value_> const& x, Vector3<Value_> const& y, Vector3<Value_> const& z) : x_(x), y_(y), z_(z) {}

    // Construct from vector product
    Matrix3(Vector3<Value_> const& vector_1, Vector3<Value_> const& vector_2) : x_(vector_1.X()* vector_2), y_(vector_1.Y()* vector_2), z_(vector_1.Z()* vector_2) {}

    // Construct anti symetric matrix from vector
    Matrix3(Vector3<Value_> const& vector) : x_(Value_(0), vector.Z(), -vector.Y()), y_(-vector.Z(), Value_(0), vector.X()) , z_(vector.Y(), -vector.X(), Value_(0)) {};

    // Constructor for a rotation based on a Quaternion
    // if magnitude of quaternion is null, creates identity rotation
    // if quaternion is non-unit, creates rotation corresponding to the normalized(unit) quaternion
    Matrix3(TQuaternion const& quaternion) {
        double mag2 = quaternion.QMag2();
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
    Matrix3(Matrix3<Value_2> const& matrix) {
        x_ = matrix.X();
        y_ = matrix.Y();
        z_ = matrix.Z();
    }

    Vector3<Value_> const& X() const {
        return x_;
    }
    Vector3<Value_> const& Y() const {
        return y_;
    }
    Vector3<Value_> const& Z() const {
        return z_;
    }

    Vector3<Value_>& X() {
        return x_;
    }
    Vector3<Value_>& Y() {
        return y_;
    }
    Vector3<Value_>& Z() {
        return z_;
    }

// Returns true if the identity matrix(Geant4).
    bool IsIdentity() const {
        return x_ == Vector3<Value_>(1, 0, 0) && y_ == Vector3<Value_>(0, 1, 0) && z_ == Vector3<Value_>(0, 0, 1);
    }
// Returns the inverse.
    Matrix3 Transposed() const {
        return {ColumnX(), ColumnY(), ColumnZ()};
    }

// Inverts the Rotation matrix.
    Matrix3& Transpose() {
        return *this = Transposed();
    }

    Matrix3<ValueInverse> Inverse() {
        auto x = ColumnX();
        auto y = ColumnY();
        auto z = ColumnZ();
        auto det = Determinant();
        if (det = ValueCubed(0)) std::cout << "Matrix is not invertible" << std::endl;
        return Matrix3<ValueSquare>(y ^ z, z ^ x, x ^ y) / Determinant();
    }

// Rotation around the x-axis.
    Matrix3& RotateX(Angle phi) {
        //rotate around x
        double cos = boost::units::cos(phi);
        double sin = boost::units::sin(phi);
        Vector3<Value_> vector = y_;
        y_ = cos * vector - sin * z_;
        z_ = sin * vector + cos * z_;
        return *this;
    }

// Rotation around the y-axis.
    Matrix3& RotateY(Angle phi) {
        //rotate around y
        double cos = boost::units::cos(phi);
        double sin = boost::units::sin(phi);
        Vector3<Value_> vector = z_;
        z_ = cos * vector - sin * x_;
        x_ = sin * vector + cos * x_;
        return *this;
    }

// Rotation around the z-axis.
    Matrix3& RotateZ(Angle phi) {
        //rotate around z
        double cos = boost::units::cos(phi);
        double sin = boost::units::sin(phi);
        Vector3<Value_> vector = x_;
        x_ = cos * vector - sin * y_;
        y_ = sin * vector + cos * y_;
        return *this;
    }

// Rotation around a specified vector.
    //rotate along an axis
    Matrix3& Rotate(Angle phi, Vector3<Value_> const& axis) {
        if (phi == 0_rad)  return *this;
        double sin = boost::units::sin(phi);
        double cos = boost::units::cos(phi);
        Vector3<double> vector = axis.Unit();
        Transform(Matrix3(cos) + Matrix3(vector, vector) * (1 - cos) - Matrix3(vector * sin));
        return *this;
    }

// Rotation of local axes(Geant4).
    //rotate axes
    Matrix3& RotateAxes(Vector3<Value_> const& vector_x, Vector3<Value_> const& vector_y, Vector3<Value_> const& vector_z) {
        double epsilon = 0.001;
        Vector3<Value_> cross = vector_x.Cross(vector_y);
        if (std::abs(vector_z.X() - cross.X()) > epsilon || std::abs(vector_z.Y() - cross.Y()) > epsilon || std::abs(vector_z.Z() - cross.Z()) > epsilon || std::abs(vector_x.Mag2() - 1) > epsilon || std::abs(vector_y.Mag2() - 1) > epsilon || std::abs(vector_z.Mag2() - 1) > epsilon || std::abs(vector_x.Dot(vector_y)) > epsilon || std::abs(vector_y.Dot(vector_z)) > epsilon || std::abs(vector_z.Dot(vector_x)) > epsilon) {
            std::cout << "RotateAxes bad axis vectors" << std::endl;
            return *this;
        }
        return Transform(Matrix3(vector_x.X(), vector_y.X(), vector_z.X(), vector_x.Y(), vector_y.Y(), vector_z.Y(), vector_x.Z(), vector_y.Z(), vector_z.Z()));
    }

//return Phi
    Angle PhiX() const {
        return y_.X() == Value_(0) && x_.X() == Value_(0) ? 0_rad : boost::units::atan2(y_.X(), x_.X());
    }

//return Phi
    Angle PhiY() const {
        return y_.Y() == Value_(0) && x_.Y() == Value_(0) ? 0_rad : boost::units::atan2(y_.Y(), x_.Y());
    }

//return Phi
    Angle PhiZ() const {
        return y_.Z() == Value_(0) && x_.Z() == Value_(0) ? 0_rad : boost::units::atan2(y_.Z(), x_.Z());
    }

    //return Theta
    Angle ThetaX() const {
        return boost::units::acos(z_.X());
    }

//return Theta
    Angle ThetaY() const {
        return boost::units::acos(z_.Y());
    }
// Return angles(RADS) made by rotated axes against original axes(Geant4).
    Angle ThetaZ() const {
        //return Theta
        return boost::units::acos(z_.Z());
    }

// Returns the rotation angle and rotation axis(Geant4).
    //rotation defined by an angle and a vector
    void AngleAxis(Angle& angle, Vector3<Value_>& axis) const {
        Value_ cosa  = 0.5 * (x_.X() + y_.Y() + z_.Z() - 1);
        Value_ cosa1 = 1 - cosa;
        if (cosa1 <= Value_(0)) {
            angle = 0_rad;
            axis  = Vector3<Value_>(0, 0, 1);
        } else {
            double x = 0;
            double y = 0;
            double z = 0;
            if (x_.X() > cosa) x = std::sqrt((x_.X() - cosa) / cosa1);
            if (y_.Y() > cosa) y = std::sqrt((y_.Y() - cosa) / cosa1);
            if (z_.Z() > cosa) z = std::sqrt((z_.Z() - cosa) / cosa1);
            if (z_.Y() < y_.Z())  x = -x;
            if (x_.Z() < z_.X())  y = -y;
            if (y_.X() < x_.Y())  z = -z;
            angle = boost::units::acos(cosa);
            axis  = Vector3<Value_>(x, y, z);
        }
    }

// Set equal to the identity rotation.
    Matrix3& SetToIdentity() {
        x_ = Vector3<Value_>(1, 0, 0);
        y_ = Vector3<Value_>(0, 1, 0);
        z_ = Vector3<Value_>(0, 0, 1);
        return *this;
    }

    Matrix3& SetDiagonal(Value_ value) {
        x_ = Vector3<Value_>(value, 0, 0);
        y_ = Vector3<Value_>(0, value, 0);
        z_ = Vector3<Value_>(0, 0, value);
        return *this;
    }

    Matrix3& SetXEulerAngles(Angle phi, Angle theta, Angle psi) {
        // Rotate using the x-convention(Landau and Lifshitz, Goldstein, &c) by
        // doing the explicit rotations.  This is slightly less efficient than
        // directly applying the rotation, but makes the code much clearer.  My
        // presumption is that this code is not going to be a speed bottle neck.
        SetToIdentity();
        RotateZ(phi);
        RotateX(theta);
        RotateZ(psi);
        return *this;
    }

//set XPhi
    void SetXPhi(Angle phi) {
        SetXEulerAngles(phi, XTheta(), XPsi());
    }

    void SetXTheta(Angle theta) {
        //set XTheta
        SetXEulerAngles(XPhi(), theta, XPsi());
    }

    void SetXPsi(Angle psi) {
        //set XPsi
        SetXEulerAngles(XPhi(), XTheta(), psi);
    }

// Set the euler angles of the rotation.  The angles are defined using the
// y-convention which rotates around the Z axis, around the new X axis, and
// then around the new Z axis.  The x-convention is used Goldstein, Landau
// and Lifshitz, and other common physics texts.  Contrast this with
// SetYEulerAngles.

// Adds a rotation of the local axes defined by the Euler angle to the
// current rotation.  See SetXEulerAngles for a note about conventions.
    Matrix3& RotateXEulerAngles(Angle phi, Angle theta, Angle psi) {
        // Rotate using the x-convention.
        Matrix3 euler;
        euler.SetXEulerAngles(phi, theta, psi);
        return Transform(euler);
    }

    //return phi angle
    Angle XPhi() const {
        ValueSquare s2 =  ValueSquare(1) - z_.Z() * z_.Z();
        if (s2 < ValueSquare(0)) {
            std::cout << "Phi() |z_.Z()| > 1 " << std::endl;
            s2 = 0;
        }
        Value_ sinTheta = std::sqrt(s2);
        if (sinTheta != Value_(0)) {
            double cscTheta = 1 / sinTheta;
            double cosAbsPhi =  z_.Y() * cscTheta;
            if (std::abs(cosAbsPhi) > 1) {         // NaN-proofing
                std::cout << "Phi() finds | cos phi | > 1" << std::endl;
                cosAbsPhi = 1;
            }
            Angle absPhi = acos(cosAbsPhi);
            if (z_.X() > 0) return absPhi;
            if (z_.X() < 0) return -absPhi;
            if (z_.Y() > 0) return 0_rad;
            return Pi();
        } else {              // sinTheta == Value(0) so |Fzz| = 1
            Angle absPhi = .5 * boost::units::acos(x_.X());
            if (x_.Y() > 0) return -absPhi;
            if (x_.Y() < 0) return absPhi;
            if (x_.X() > 0) return 0_rad;
            return z_.Z() * Pi() / 2;
        }
    }

    //return XTheta
    double XTheta() const {
        return ThetaZ();
    }

// Return the euler angles of the rotation.  See SetYEulerAngles for a
// note about conventions.
    Angle XPsi() const {
        // psi angle
        double s2 =  1 - z_.Z() * z_.Z();
        if (s2 < 0) {
            std::cout << "Psi() |z_.Z()| > 1 " << std::endl;
            s2 = 0;
        }
        double sinTheta = std::sqrt(s2);
        if (sinTheta != 0) {
            double cscTheta = 1 / sinTheta;
            double cosAbsPsi =  - y_.Z() * cscTheta;
            if (std::abs(cosAbsPsi) > 1) {         // NaN-proofing
                std::cout << "Psi() | cos psi | > 1 " << std::endl;
                cosAbsPsi = 1;
            }
            double absPsi = acos(cosAbsPsi);
            if (x_.Z() > 0) return absPsi;
            if (x_.Z() < 0) return -absPsi;
            return (y_.Z() < 0) ? 0_rad : Pi();
        } else {              // sinTheta == Value(0) so |Fzz| = 1
            double absPsi = x_.X();
            if (std::abs(x_.X()) > 1) {         // NaN-proofing
                std::cout << "Psi() | x_.X() | > 1 " << std::endl;
                absPsi = 1;
            }
            absPsi = .5 * acos(absPsi);
            if (y_.X() > 0) return absPsi;
            if (y_.X() < 0) return -absPsi;
            return (x_.X() > 0) ? 0_rad : Pi() / 2.;

        }
    }

    // Rotate using the y-convention.
    Matrix3& SetYEulerAngles(Angle phi, Angle theta, Angle psi) {
        SetToIdentity();
        RotateZ(phi);
        RotateY(theta);
        RotateZ(psi);
        return *this;
    }

    //set YPhi
    void SetYPhi(Angle phi) {
        SetYEulerAngles(phi, YTheta(), YPsi());
    }

    //set YTheta
    void SetYTheta(Angle theta) {
        SetYEulerAngles(YPhi(), theta, YPsi());
    }

    //set YPsi
    void SetYPsi(Angle psi) {
        SetYEulerAngles(YPhi(), YTheta(), psi);
    }

    Value_ Trace()const {
        return x_.X() + y_.Y() + z_.Z();
    }

    ValueCubed Determinant()const {
        return x_.X() * y_.Y() * z_.Z() + x_.Y() * y_.Z() * z_.X() + x_.Z() * y_.X() * z_.Y() - x_.Z() * y_.Y() * z_.X() - x_.Y() * y_.X() * z_.Z() - x_.X() * y_.Z() * z_.Y();
    }

    Matrix3<ValueSquare> Square() const {
        return sqr(*this);
    }

    class Characteristic
    {
    public:
        Characteristic(Matrix3 const& matrix) {
            qudratic_ = - matrix.Trace();
            linear_ = (matrix.Square().Trace() - sqr(qudratic_)) / 2;
            constant_ = - matrix.Determinant();
        }
        Value_ Qudratic() const {
            return qudratic_;
        }
        ValueSquare Linear() const {
            return linear_;
        }
        ValueCubed Constant() const {
            return constant_;
        }
    private:
        Value_ qudratic_;
        ValueSquare linear_;
        ValueCubed constant_;
    };

    class Depressed
    {
    public:
        Depressed(Characteristic const& c) {
            auto quadratic = c.Qudratic() / 3;
            linear_ = c.Linear() - sqr(quadratic) * 3;
            constant_ = 2. * cube(quadratic) - quadratic * c.Linear() + c.Constant();
        }
        ValueSquare Linear() const {
            return linear_;
        }

        ValueCubed Constant() const {
            return constant_;
        }
    private:
        ValueSquare linear_;
        ValueCubed constant_;
    };

    class Eigen
    {
    public:
        Eigen() {}
        Eigen(Depressed const& d, Matrix3<Value_> const& matrix) {
            factor_ = 2. * sqrt(- d.Linear() / 3.);
            angle_ = acos(3. * d.Constant() / d.Linear() / factor_);
            if (4 * cube(d.Linear()) + 27 * sqr(d.Constant()) > 0) complex_ = true;
            matrix_ = &matrix;
        }
        template<typename Value_2_>
        using Array = std::array<Value_2_, 3>;
        Array<Value_> Values() const {
            return values_.Get([&]() {
                Array<Value_> values;
                if (complex_) {
                    for (auto & value : values) value = -1;
                    std::cerr << "Eigensystem has no real Eigenvalues!\n";
                    return values;
                }
                values.at(0) = Value(0);
                values.at(1) = Value(1);
                values.at(2) = Value(2);
                return boost::range::sort(values, [](Value_ i, Value_ j) {
                    return i > j;
                });
            });
        }
        Array<Vector3<Value_>> Vectors() const {
            return vectors_.Get([&]() {
                Array<Vector3<Value_>> vectors;
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

        Value_ Factor() const {
            return factor_;
        }

        boca::Angle Angle() const {
            return angle_;
        }

        Value_ Value(int index) const {
            return Factor() * boost::units::cos((Angle() - 2. * Pi() * double(index)) / 3.);
        }

        Vector3<Value_> Vector(int index) const {
            // set up matrix of system to be solved
            auto a11 = matrix_->X().X() - Values().at(index);
            auto a12 = matrix_->X().Y();
            auto a13 = matrix_->X().Z();
            auto a23 = matrix_->Y().Z();
            auto a33 = matrix_->Z().Z() - Values().at(index);
            // intermediate steps from gauss type algorithm
            auto b1 = a11 * a33 - sqr(a13);
            auto b2 = a12 * a33 - a13 * a23;
            auto b4 = a11 * a23 - a12 * a13;
            // vector
            Vector3<Value_> vector(b2, -b1, b4);
            return vector.Unit();
        }
        Value_ factor_;
        boca::Angle angle_;
        bool complex_ = false;
        Mutable<Array<Value_>> values_;
        Mutable<Array<Vector3<Value_>>> vectors_;
        Matrix3<Value_> const* matrix_;
    };

    Mutable<Eigen> eigen_;

    Eigen const& eigen() const {
        return eigen_.Get([&]() {
            return Eigen(Depressed(Characteristic(*this)), *this);
        });
    }


// Set the euler angles of the rotation.  The angles are defined using the
// y-convention which rotates around the Z axis, around the new Y axis, and
// then around the new Z axis.  The x-convention is used Goldstein, Landau
// and Lifshitz, and other common physics texts and is a rotation around the
// Z axis, around the new X axis, and then around the new Z axis.

// Adds a rotation of the local axes defined by the Euler angle to the
// current rotation.  See SetYEulerAngles for a note about conventions.
    // Rotate using the y-convention.
    Matrix3& RotateYEulerAngles(Angle phi, Angle theta, Angle psi) {
        Matrix3 euler;
        euler.SetYEulerAngles(phi, theta, psi);
        return Transform(euler);
    }

    //return YPhi
    Angle YPhi() const {
        return XPhi() + Pi() / 2.;
    }

    //return YTheta
    Angle YTheta() const {
        return ThetaZ();
    }

// Return the euler angles of the rotation.  See SetYEulerAngles for a
// note about conventions.
    //return YPsi
    Angle YPsi() const {
        return XPsi() - Pi() / 2.;
    }

    //set X axis
    Matrix3& SetXAxis(Vector3<Value_> const& axis) {
        Vector3<Value_> xyPlane(0, 1, 0);
        return SetXAxis(axis, xyPlane);
    }

    //set X axis
    Matrix3& SetXAxis(Vector3<Value_> const& axis, Vector3<Value_> const& xyPlane) {
        Matrix3 matrix = MakeBasis(xyPlane, axis);
        Matrix3 matrix2(matrix.Z(), matrix.X(), matrix.Y());
        x_ = matrix2.ColumnX();
        y_ = matrix2.ColumnY();
        z_ = matrix2.ColumnZ();
        return *this;
    }

    //set Y axis
    Matrix3& SetYAxis(Vector3<Value_> const& axis) {
        Vector3<Value_> yzPlane(0, 0, 1);
        return SetYAxis(axis, yzPlane);
    }

    //set Y axis
    Matrix3& SetYAxis(Vector3<Value_> const& axis, Vector3<Value_> const& yzPlane) {
        Matrix3 matrix = MakeBasis(yzPlane, axis);
        Matrix3 matrix2(matrix.Y(), matrix.Z(), matrix.X());
        x_ = matrix2.ColumnX();
        y_ = matrix2.ColumnY();
        z_ = matrix2.ColumnZ();
        return *this;
    }

    //set Z axis
    Matrix3& SetZAxis(Vector3<Value_> const& axis) {
        Vector3<Value_> zxPlane(1, 0, 0);
        return SetZAxis(axis, zxPlane);
    }

// Create a rotation with the axis vector parallel to the rotated coordinate
// systematrix.  If a second vector is provided it defines a plane passing
    //set Z axis
    Matrix3& SetZAxis(Vector3<Value_> const& axis, Vector3<Value_> const& zxPlane) {
        Matrix3 matrix = MakeBasis(zxPlane, axis);
        x_ = matrix.ColumnX();
        y_ = matrix.ColumnY();
        z_ = matrix.ColumnZ();
        return *this;
    }

// through the axis.

// Take two input vectors(in xAxis, and zAxis) and turn them into an
// orthogonal basis.  This is an internal helper function used to implement
// the Set?Axis functions, but is exposed because the functionality is
// often useful.
    Matrix3 MakeBasis(Vector3<Value_> const& xAxis, Vector3<Value_> const& zAxis) const {
        Matrix3 matrix;
        // Make the Z axis into a unit variable.
        double zmag = zAxis.Mag();
        if (zmag < 1E-6) std::cout << "MakeBasis(X,Y,Z) non-zero Z Axis is required" << std::endl;
        matrix.Z() = zAxis / zmag;
        double xmag = xAxis.Mag();
        if (xmag < 1E-6 * zmag) {
            matrix.X() = matrix.Z().Orthogonal();
            xmag = 1;
        } else matrix.X() = xAxis;
        // Find the Y axis
        matrix.Y() = matrix.Z().Cross(matrix.X()) * (1 / xmag);
        double ymag = matrix.Y().Mag();
        matrix.Y() = ymag < 1E-6 * zmag ? matrix.Z().Orthogonal() : matrix.Y() / ymag;
        matrix.X() = matrix.Y().Cross(matrix.Z());
        return matrix;
    }

    // Elements of the rotation matrix(Geant4).

    // Returns object of the helper class for C-style subscripting r[i][j]
    Vector3<Value_> const& operator()(int i) const {
        switch (i) {
        case 0 : return x_;
        case 1 : return y_;
        case 2 : return z_;
        }
        std::cout << "operator()(i) bad index " << i << std::endl;
    }

    Vector3<Value_> const& operator[](int i) const {
        return operator()(i);
    }

    // Returns object of the helper class for C-style subscripting r[i][j]
    Vector3<Value_> const& operator()(Dimension3 i) const {
        switch (i) {
        case Dimension3::x : return x_;
        case Dimension3::y : return y_;
        case Dimension3::z : return z_;
        }
    }

    Vector3<Value_> const& operator[](Dimension3 i) const {
        return operator()(i);
    }

    // Returns object of the helper class for C-style subscripting r[i][j]
    Vector3<Value_>& operator()(int i)  {
        switch (i) {
        case 0 : return x_;
        case 1 : return y_;
        case 2 : return z_;
        }
        std::cout << "operator()(i) bad index " << i << std::endl;
    }

    Vector3<Value_>& operator[](int i)  {
        return operator()(i);
    }

    // Returns object of the helper class for C-style subscripting r[i][j]
    Vector3<Value_>& operator()(Dimension3 i)  {
        switch (i) {
        case Dimension3::x : return x_;
        case Dimension3::y : return y_;
        case Dimension3::z : return z_;
        }
    }

    Vector3<Value_>& operator[](Dimension3 i)  {
        return operator()(i);
    }

    ConstIterator2<Matrix3, Vector3, Value_> begin() const {
        return {this, 0};
    }

    ConstIterator2<Matrix3, Vector3, Value_> end() const {
        return {this, 3};
    }

    Iterator2<Matrix3, Vector3, Value_> begin() {
        return {this, 0};
    }

    Iterator2<Matrix3, Vector3, Value_> end() {
        return {this, 3};
    }

    // Comparisons(Geant4).
    bool operator==(Matrix3 const& matrix) const {
        return x_ == matrix.x_ && y_ == matrix.y_ && z_ == matrix.z_;
    }
    bool operator!=(Matrix3 const& matrix) const {
        return x_ != matrix.x_ || y_ != matrix.y_ || z_ != matrix.z_;
    }

    // Addition.
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    Matrix3& operator+=(Matrix3<Value_2> const& matrix) {
        x_ += matrix.x_;
        y_ += matrix.y_;
        z_ += matrix.z_;
        return *this;
    }

    Vector3<Value_> ColumnX() const {
        return {x_.X(), y_.X(), z_.X()};
    }

    Vector3<Value_> ColumnY() const {
        return {x_.Y(), y_.Y(), z_.Y()};
    }

    Vector3<Value_> ColumnZ() const {
        return {x_.Z(), y_.Z(), z_.Z()};
    }

    template<typename Value_2_>
    Matrix3<ValueProduct<Value_2_>> Scaled(Value_2_ scalar) const {
        return {x_ * scalar, y_ * scalar, z_ * scalar};
    }

    template<typename Value_2_>
    Matrix3<ValueQuotient<Value_2_>> operator/(Value_2_ scalar) {
        return Scaled(1. / scalar);
    }

    // Multiplication with a Vector3<Value_>.
    template<typename Value_2_>
    Vector3<ValueProduct<Value_2_>> Multiply(Vector3<Value_2_> const& vector) const {
        return {x_ * vector, y_ * vector, z_ * vector};
    }

    // Multiplication with a Vector3<Value_>.
    template<typename Value_2_>
    Vector3<ValueProduct<Value_2_>> operator*(Vector3<Value_2_> const& vector) const {
        return Multiply(vector);
    }

    //multiplication operator
    template<typename Value_2_>
    Matrix3<ValueProduct<Value_2_>> Multiply(Matrix3<Value_2_> const& matrix) const {
        return {{x_ * matrix.ColumnX(), x_ * matrix.ColumnY(), x_ * matrix.ColumnZ()}, {y_ * matrix.ColumnX(), y_ * matrix.ColumnY(), y_ * matrix.ColumnZ()}, {z_ * matrix.ColumnX(), z_ * matrix.ColumnY(), z_ * matrix.ColumnZ()}};
    }

    //multiplication operator
    template<typename Value_2_>
    Matrix3<ValueProduct<Value_2_>> operator*(Matrix3<Value_2_> const& matrix) const {
        return Multiply(matrix);
    }

    // Matrix multiplication.
    template<typename Value_2_, typename = OnlyIfNotQuantity<Value_2_>>
    Matrix3& operator*=(Matrix3<Value_2_> const& matrix) {
        return *this = Multiply(matrix);
    }

private:

// The matrix rows
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
Matrix3 <ValueProduct<Value_, Value_2_>> operator*(Matrix3<Value_> const& matrix, Value_2_ scalar)
{
    return matrix.Scale(scalar);
}

template < class Value_, class Value_2_, typename = OnlyIfNotMatrix3<Value_2_> >
Matrix3 <ValueProduct<Value_, Value_2_>> operator*(Value_2_ scalar, Matrix3<Value_> const& matrix)
{
    return matrix.Scale(scalar);
}

template < class Value_, class Value_2_>
Vector3 <ValueProduct<Value_, Value_2_>> operator*(Matrix3<Value_> const& matrix, Vector3<Value_2_> const& vector)
{
    return matrix.Multiply(vector);
}

template < class Value_, class Value_2_>
Vector3 <ValueProduct<Value_, Value_2_>> operator*(Vector3<Value_2_> const& vector, Matrix3<Value_> const& matrix)
{
    return {vector.X()* matrix.ColumnX(), vector.Y()* matrix.ColumnY(), vector.Z()* matrix.ColumnZ()};
}

template<typename Value_1_, typename Value_2_>
Matrix3<ValueProduct<Value_1_, Value_2_>> MatrixProduct(Vector3<Value_1_> const& vector_1, Vector3<Value_2_> const& vector_2)
{
    return {vector_1.X()* vector_2, vector_1.Y()* vector_2, vector_1.Z()* vector_2};
}

}
