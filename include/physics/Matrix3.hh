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
#include "Vector3.hh"
#include "Units.hh"
#include "TQuaternion.h"

namespace boca
{

template <typename Value_>
class Matrix3
// : boost::operators<Matrix3<Value_>>
{

public:

    template<typename Value_2_>
    using ValueProduct = ValueProduct<Value_, Value_2_>;
    using ValueSquare = boca::ValueSquare<Value_>;
    template<typename Value_2_, typename Value_3>
    using ValueCubed = boca::ValueProduct<ValueProduct<Value_2_>, Value_3>;
    template<typename Value_2>
    using ValueQuotient = ValueQuotient<Value_, Value_2>;
    using ValueInverse = boost::units::divide_typeof_helper<double, Value_>;
    template<typename Value_2>
    using OnlyIfNotOrSameQuantity = typename std::enable_if < !IsQuantity<Value_2>::value || std::is_same<Value_, Value_2>::value >::type;

    // Helper class for implemention of C-style subscripting r[i][j]
    template<typename Dimension_>
    class Row
    {
    public:
        Row(Matrix3 const& matrix, Dimension_ index) : matrix_(&matrix), index_(index) {}
        Value_ operator[](Dimension_ index) const {
            return matrix_->operator()(index_, index);
        }
    private:
        Matrix3 const* matrix_;
        Dimension_ index_;
    };

    // Default constructor.
    Matrix3() {}

    // Protected constructor.
    Matrix3(Value_ xx, Value_ xy, Value_ xz, Value_ yx, Value_ yy, Value_ yz, Value_ zx, Value_ zy, Value_ zz) : xx_(xx), xy_(xy), xz_(xz), yx_(yx), yy_(yy), yz_(yz), zx_(zx), zy_(zy), zz_(zz) {}

    // Constructor for a rotation based on a Quaternion
    // if magnitude of quaternion is null, creates identity rotation
    // if quaternion is non-unit, creates rotation corresponding to the normalized(unit) quaternion
    Matrix3(TQuaternion const& quaternion) {
        double two_r2 = 2 * quaternion.fRealPart * quaternion.fRealPart;
        double two_x2 = 2 * quaternion.fVectorPart.X() * quaternion.fVectorPart.X();
        double two_y2 = 2 * quaternion.fVectorPart.Y() * quaternion.fVectorPart.Y();
        double two_z2 = 2 * quaternion.fVectorPart.Z() * quaternion.fVectorPart.Z();
        double two_xy = 2 * quaternion.fVectorPart.X() * quaternion.fVectorPart.Y();
        double two_xz = 2 * quaternion.fVectorPart.X() * quaternion.fVectorPart.Z();
        double two_xr = 2 * quaternion.fVectorPart.X() * quaternion.fRealPart;
        double two_yz = 2 * quaternion.fVectorPart.Y() * quaternion.fVectorPart.Z();
        double two_yr = 2 * quaternion.fVectorPart.Y() * quaternion.fRealPart;
        double two_zr = 2 * quaternion.fVectorPart.Z() * quaternion.fRealPart;

        // protect agains zero quaternion
        double mag2 = quaternion.QMag2();
        if (mag2 > 0) {
            // diago + identity
            xx_ = two_r2 + two_x2;
            yy_ = two_r2 + two_y2;
            zz_ = two_r2 + two_z2;
            //        line 0 column 1 and conjugate
            xy_ = two_xy - two_zr;
            yx_ = two_xy + two_zr;
            //        line 0 column 2 and conjugate
            xz_ = two_xz + two_yr;
            zx_ = two_xz - two_yr;
            //        line 1 column 2 and conjugate
            yz_ = two_yz - two_xr;
            zy_ = two_yz + two_xr;
            // protect agains non-unit quaternion
            if (std::abs(mag2 - 1) > 1e-10) {
                xx_ /= mag2;
                yy_ /= mag2;
                zz_ /= mag2;
                xy_ /= mag2;
                yx_ /= mag2;
                xz_ /= mag2;
                zx_ /= mag2;
                yz_ /= mag2;
                zy_ /= mag2;
            }
            // diago : remove identity
            xx_ -= 1;
            yy_ -= 1;
            zz_ -= 1;
        } else {
            // Identity
            xx_ = yy_ = zz_ = 1;
            xy_ = yx_ = xz_ = zx_ = yz_ = zy_ = 0;
        }
    }

    // Constructor
    template<typename Value_2>
    Matrix3(Matrix3<Value_2> const& matrix) {
        xx_ = Value_(matrix.XX());
        xy_ = Value_(matrix.XY());
        xz_ = Value_(matrix.XZ());
        yx_ = Value_(matrix.YX());
        yy_ = Value_(matrix.YY());
        yz_ = Value_(matrix.YZ());
        zx_ = Value_(matrix.ZX());
        zy_ = Value_(matrix.ZY());
        zz_ = Value_(matrix.ZZ());
    }

    Value_ XX() const {
        return xx_;
    }

    Value_ XY() const {
        return xy_;
    }

    Value_ XZ() const {
        return xz_;
    }
    Value_ YX() const {
        return yx_;
    }
    Value_ YY() const {
        return yy_;
    }
    Value_ YZ() const {
        return yz_;
    }
    Value_ ZX() const {
        return zx_;
    }
    Value_ ZY() const {
        return zy_;
    }
    Value_ ZZ() const {
        return zz_;
    }


// Returns true if the identity matrix(Geant4).
    bool IsIdentity() const {
        return xx_ == Value_(1) && xy_ == Value_(0) && xz_ == Value_(0) && yx_ == Value_(0) && yy_ == Value_(1) && yz_ == Value_(0) && zx_ == Value_(0) && zy_ == Value_(0) && zz_ == Value_(1) ? true : false;
    }
// Returns the inverse.
    Matrix3 Inverse() const {
        return {xx_, yx_, zx_, xy_, yy_, zy_, xz_, yz_, zz_};
    }

// Inverts the Rotation matrix.
    Matrix3& Invert() {
        return *this = Inverse();
    }

// Rotation around the x-axis.
    Matrix3& RotateX(Angle phi) {
        //rotate around x
        double c = boost::units::cos(phi);
        double s = boost::units::sin(phi);
        Value_ x = yx_;
        Value_ y = yy_;
        Value_ z = yz_;
        yx_ = c * x - s * zx_;
        yy_ = c * y - s * zy_;
        yz_ = c * z - s * zz_;
        zx_ = s * x + c * zx_;
        zy_ = s * y + c * zy_;
        zz_ = s * z + c * zz_;
        return *this;
    }

// Rotation around the y-axis.
    Matrix3& RotateY(Angle phi) {
        //rotate around y
        double c = boost::units::cos(phi);
        double s = boost::units::sin(phi);
        Value_ x = zx_;
        Value_ y = zy_;
        Value_ z = zz_;
        zx_ = c * x - s * xx_;
        zy_ = c * y - s * xy_;
        zz_ = c * z - s * xz_;
        xx_ = s * x + c * xx_;
        xy_ = s * y + c * xy_;
        xz_ = s * z + c * xz_;
        return *this;
    }

// Rotation around the z-axis.
    Matrix3& RotateZ(Angle phi) {
        //rotate around z
        double c = boost::units::cos(phi);
        double s = boost::units::sin(phi);
        Value_ x = xx_;
        Value_ y = xy_;
        Value_ z = xz_;
        xx_ = c * x - s * yx_;
        xy_ = c * y - s * yy_;
        xz_ = c * z - s * yz_;
        yx_ = s * x + c * yx_;
        yy_ = s * y + c * yy_;
        yz_ = s * z + c * yz_;
        return *this;
    }

// Rotation around a specified vector.
    Matrix3& Rotate(Angle phi, Vector3<Value_> const& axis) {
        //rotate along an axis
        if (phi == Value_(0))  return *this;
        Value_ ll = axis.Mag();
        if (ll == Value_(0)) {
            std::cout << "Rotate(angle,axis) zero axis" << std::endl;
            return *this;
        }
        double sa = boost::units::sin(phi);
        double ca = boost::units::cos(phi);
        double dx = axis.X() / ll, dy = axis.Y() / ll, dz = axis.Z() / ll;
        Matrix3 matrix(
            ca + (1 - ca)*dx * dx, (1 - ca)*dx * dy - sa * dz, (1 - ca)*dx * dz + sa * dy,
            (1 - ca)*dy * dx + sa * dz, ca + (1 - ca)*dy * dy, (1 - ca)*dy * dz - sa * dx,
            (1 - ca)*dz * dx - sa * dy, (1 - ca)*dz * dy + sa * dx, ca + (1 - ca)*dz * dz);
        Transform(matrix);
        return *this;
    }

// Rotation of local axes(Geant4).
    Matrix3& RotateAxes(Vector3<Value_> const& newX, Vector3<Value_> const& newY, Vector3<Value_> const& newZ) {
        //rotate axes
        double del = 0.01;
        Vector3<Value_> w = newX.Cross(newY);

        if (std::abs(newZ.X() - w.X()) > del || std::abs(newZ.Y() - w.Y()) > del || std::abs(newZ.Z() - w.Z()) > del || std::abs(newX.Mag2() - 1) > del || std::abs(newY.Mag2() - 1) > del || std::abs(newZ.Mag2() - 1) > del || std::abs(newX.Dot(newY)) > del || std::abs(newY.Dot(newZ)) > del || std::abs(newZ.Dot(newX)) > del) {
            std::cout << "RotateAxes bad axis vectors" << std::endl;
            return *this;
        }
        return Transform(Matrix3(newX.X(), newY.X(), newZ.X(), newX.Y(), newY.Y(), newZ.Y(), newX.Z(), newY.Z(), newZ.Z()));
    }

//return Phi
    Angle PhiX() const {
        return yx_ == Value_(0) && xx_ == Value_(0) ? 0_rad : boost::units::atan2(yx_, xx_);
    }

//return Phi
    Angle PhiY() const {
        return yy_ == Value_(0) && xy_ == Value_(0) ? 0_rad : boost::units::atan2(yy_, xy_);
    }

//return Phi
    Angle PhiZ() const {
        return yz_ == Value_(0) && xz_ == Value_(0) ? 0_rad : boost::units::atan2(yz_, xz_);
    }

//return Phi
    Angle ThetaX() const {
        return boost::units::acos(zx_);
    }

//return Theta
    Angle ThetaY() const {
        return boost::units::acos(zy_);
    }
// Return angles(RADS) made by rotated axes against original axes(Geant4).
    Angle ThetaZ() const {
        //return Theta
        return boost::units::acos(zz_);
    }

// Returns the rotation angle and rotation axis(Geant4).
    void AngleAxis(Angle& angle, Vector3<Value_>& axis) const {
        //rotation defined by an angle and a vector
        Value_ cosa  = 0.5 * (xx_ + yy_ + zz_ - 1);
        Value_ cosa1 = 1 - cosa;
        if (cosa1 <= Value_(0)) {
            angle = 0_rad;
            axis  = Vector3<Value_>(0, 0, 1);
        } else {
            double x = 0;
            double y = 0;
            double z = 0;
            if (xx_ > cosa) x = std::sqrt((xx_ - cosa) / cosa1);
            if (yy_ > cosa) y = std::sqrt((yy_ - cosa) / cosa1);
            if (zz_ > cosa) z = std::sqrt((zz_ - cosa) / cosa1);
            if (zy_ < yz_)  x = -x;
            if (xz_ < zx_)  y = -y;
            if (yx_ < xy_)  z = -z;
            angle = boost::units::acos(cosa);
            axis  = Vector3<Value_>(x, y, z);
        }
    }

// Set equal to the identity rotation.
    Matrix3& SetToIdentity() {
        xx_ = yy_ = zz_ = Value_(1);
        xy_ = xz_ = yx_ = yz_ = zx_ = zy_ = Value_(0);
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
        ValueSquare s2 =  ValueSquare(1) - zz_ * zz_;
        if (s2 < ValueSquare(0)) {
            std::cout << "Phi() |zz_| > 1 " << std::endl;
            s2 = 0;
        }
        Value_ sinTheta = std::sqrt(s2);
        if (sinTheta != Value_(0)) {
            double cscTheta = 1 / sinTheta;
            double cosAbsPhi =  zy_ * cscTheta;
            if (std::abs(cosAbsPhi) > 1) {         // NaN-proofing
                std::cout << "Phi() finds | cos phi | > 1" << std::endl;
                cosAbsPhi = 1;
            }
            Angle absPhi = acos(cosAbsPhi);
            if (zx_ > 0) return absPhi;
            if (zx_ < 0) return -absPhi;
            if (zy_ > 0) return 0_rad;
            return Pi();
        } else {              // sinTheta == Value(0) so |Fzz| = 1
            Angle absPhi = .5 * boost::units::acos(xx_);
            if (xy_ > 0) return -absPhi;
            if (xy_ < 0) return absPhi;
            if (xx_ > 0) return 0_rad;
            return zz_ * Pi() / 2;
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
        double s2 =  1 - zz_ * zz_;
        if (s2 < 0) {
            std::cout << "Psi() |zz_| > 1 " << std::endl;
            s2 = 0;
        }
        double sinTheta = std::sqrt(s2);
        if (sinTheta != 0) {
            double cscTheta = 1 / sinTheta;
            double cosAbsPsi =  - yz_ * cscTheta;
            if (std::abs(cosAbsPsi) > 1) {         // NaN-proofing
                std::cout << "Psi() | cos psi | > 1 " << std::endl;
                cosAbsPsi = 1;
            }
            double absPsi = acos(cosAbsPsi);
            if (xz_ > 0) return absPsi;
            if (xz_ < 0) return -absPsi;
            return (yz_ < 0) ? 0_rad : Pi();
        } else {              // sinTheta == Value(0) so |Fzz| = 1
            double absPsi = xx_;
            if (std::abs(xx_) > 1) {         // NaN-proofing
                std::cout << "Psi() | xx_ | > 1 " << std::endl;
                absPsi = 1;
            }
            absPsi = .5 * acos(absPsi);
            if (yx_ > 0) return absPsi;
            if (yx_ < 0) return -absPsi;
            return (xx_ > 0) ? 0_rad : Pi() / 2.;

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
        Vector3<Value_> xAxis(xyPlane);
        Vector3<Value_> yAxis;
        Vector3<Value_> zAxis(axis);
        MakeBasis(xAxis, yAxis, zAxis);
        xx_ = zAxis.X();  yx_ = zAxis.Y();  zx_ = zAxis.Z();
        xy_ = xAxis.X();  yy_ = xAxis.Y();  zy_ = xAxis.Z();
        xz_ = yAxis.X();  yz_ = yAxis.Y();  zz_ = yAxis.Z();
        return *this;
    }

    //set Y axis
    Matrix3& SetYAxis(Vector3<Value_> const& axis) {
        Vector3<Value_> yzPlane(0, 0, 1);
        return SetYAxis(axis, yzPlane);
    }

    //set Y axis
    Matrix3& SetYAxis(Vector3<Value_> const& axis, Vector3<Value_> const& yzPlane) {
        Vector3<Value_> xAxis(yzPlane);
        Vector3<Value_> yAxis;
        Vector3<Value_> zAxis(axis);
        MakeBasis(xAxis, yAxis, zAxis);
        xx_ = yAxis.X();  yx_ = yAxis.Y();  zx_ = yAxis.Z();
        xy_ = zAxis.X();  yy_ = zAxis.Y();  zy_ = zAxis.Z();
        xz_ = xAxis.X();  yz_ = xAxis.Y();  zz_ = xAxis.Z();
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
        Vector3<Value_> xAxis(zxPlane);
        Vector3<Value_> yAxis;
        Vector3<Value_> zAxis(axis);
        MakeBasis(xAxis, yAxis, zAxis);
        xx_ = xAxis.X();  yx_ = xAxis.Y();  zx_ = xAxis.Z();
        xy_ = yAxis.X();  yy_ = yAxis.Y();  zy_ = yAxis.Z();
        xz_ = zAxis.X();  yz_ = zAxis.Y();  zz_ = zAxis.Z();
        return *this;
    }

// through the axis.

// Take two input vectors(in xAxis, and zAxis) and turn them into an
// orthogonal basis.  This is an internal helper function used to implement
// the Set?Axis functions, but is exposed because the functionality is
// often useful.
    void MakeBasis(Vector3<Value_>& xAxis, Vector3<Value_>& yAxis, Vector3<Value_>& zAxis) const {
        // Make the Z axis into a unit variable.
        double zmag = zAxis.Mag();
        if (zmag < 1E-6) std::cout << "MakeBasis(X,Y,Z) non-zero Z Axis is required" << std::endl;
        zAxis *= (1 / zmag);
        double xmag = xAxis.Mag();
        if (xmag < 1E-6 * zmag) {
            xAxis = zAxis.Orthogonal();
            xmag = 1;
        }
        // Find the Y axis
        yAxis = zAxis.Cross(xAxis) * (1 / xmag);
        double ymag = yAxis.Mag();
        if (ymag < 1E-6 * zmag) yAxis = zAxis.Orthogonal();
        else yAxis *= (1 / ymag);
        xAxis = yAxis.Cross(zAxis);
    }

    // Elements of the rotation matrix(Geant4).

    // Returns object of the helper class for C-style subscripting r[i][j]
    Row<int> operator[](int i) const {
        return Row<int>(*this, i);
    }

    // Fortran-style subscripting: returns(i,j) element of the rotation matrix.
    Value_ operator()(int i, int j) const {
        //dereferencing operatorconst
        switch (i) {
        case 0 : switch (j) {
            case 0 : return xx_;
            case 1 : return xy_;
            case 2 : return xz_;
        } case 1 : switch (j) {
            case 0 : return yx_;
            case 1 : return yy_;
            case 2 : return yz_;
        } case 2 : switch (j) {
            case 0 : return zx_;
            case 1 : return zy_;
            case 2 : return zz_;
            }
        }
        std::cout << "operator()(i,j) bad indices " << i << " " << j << std::endl;
        return Value_(0);
    }

    // Returns object of the helper class for C-style subscripting r[i][j]
    Row<Dimension3> operator[](Dimension3 i) const {
        return Row<Dimension3>(*this, i);
    }

    // Fortran-style subscripting: returns(i,j) element of the rotation matrix.
    Value_ operator()(Dimension3 i, Dimension3 j) const {
        //dereferencing operatorconst
        switch (i) {
        case Dimension3::x : switch (j) {
            case Dimension3::x : return xx_;
            case Dimension3::y : return xy_;
            case Dimension3::z : return xz_;
        } case Dimension3::y : switch (j) {
            case Dimension3::x : return yx_;
            case Dimension3::y : return yy_;
            case Dimension3::z : return yz_;
        } case Dimension3::z : switch (j) {
            case Dimension3::x : return zx_;
            case Dimension3::y : return zy_;
            case Dimension3::z : return zz_;
            }
        }
        std::cout << "operator()(i,j) bad indices " << Name(i) << " " << Name(j) << std::endl;
        return Value_(0);
    }

    // Fortran-style subscripting: returns(i,j) element of the rotation matrix.
    Value_& operator()(int i, int j) {
        //dereferencing operatorconst
        switch (i) {
        case 0 : switch (j) {
            case 0 : return xx_;
            case 1 : return xy_;
            case 2 : return xz_;
        } case 1 : switch (j) {
            case 0 : return yx_;
            case 1 : return yy_;
            case 2 : return yz_;
        } case 2 : switch (j) {
            case 0 : return zx_;
            case 1 : return zy_;
            case 2 : return zz_;
            }
        }
        std::cout << "operator()(i,j) bad indices " << i << " " << j << std::endl;
        return xx_;
    }

    // Fortran-style subscripting: returns(i,j) element of the rotation matrix.
    Value_& operator()(Dimension3 i, Dimension3 j) {
        //dereferencing operatorconst
        switch (i) {
        case Dimension3::x : switch (j) {
            case Dimension3::x : return xx_;
            case Dimension3::y : return xy_;
            case Dimension3::z : return xz_;
        } case Dimension3::y : switch (j) {
            case Dimension3::x : return yx_;
            case Dimension3::y : return yy_;
            case Dimension3::z : return yz_;
        } case Dimension3::z : switch (j) {
            case Dimension3::x : return zx_;
            case Dimension3::y : return zy_;
            case Dimension3::z : return zz_;
            }
        }
        std::cout << "operator()(i,j) bad indices " << Name(i) << " " << Name(j) << std::endl;
        return xx_;
    }

    // Comparisons(Geant4).
    bool operator==(Matrix3 const& matrix) const {
        return xx_ == matrix.xx_ && xy_ == matrix.xy_ && xz_ == matrix.xz_ && yx_ == matrix.yx_ && yy_ == matrix.yy_ && yz_ == matrix.yz_ && zx_ == matrix.zx_ && zy_ == matrix.zy_ && zz_ == matrix.zz_ ? true : false;
    }
    bool operator!=(Matrix3 const& matrix) const {
        return xx_ != matrix.xx_ || xy_ != matrix.xy_ || xz_ != matrix.xz_ || yx_ != matrix.yx_ || yy_ != matrix.yy_ || yz_ != matrix.yz_ || zx_ != matrix.zx_ || zy_ != matrix.zy_ || zz_ != matrix.zz_ ? true : false;
    }
    // Addition.
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    Matrix3& operator+=(Matrix3<Value_2> const& matrix) {
        xx_ += matrix.xx_;
        xy_ += matrix.xy_;
        xz_ += matrix.xz_;
        yx_ += matrix.yx_;
        yy_ += matrix.yy_;
        yz_ += matrix.yz_;
        zx_ += matrix.zx_;
        zy_ += matrix.zy_;
        zz_ += matrix.zz_;
        return *this;
    }

    //multiplication operator
    Matrix3 operator*(Matrix3 const& matrix) const {
        return {xx_* matrix.xx_ + xy_* matrix.yx_ + xz_ * matrix.zx_,
                xx_* matrix.xy_ + xy_* matrix.yy_ + xz_ * matrix.zy_,
                xx_* matrix.xz_ + xy_* matrix.yz_ + xz_ * matrix.zz_,
                yx_* matrix.xx_ + yy_* matrix.yx_ + yz_ * matrix.zx_,
                yx_* matrix.xy_ + yy_* matrix.yy_ + yz_ * matrix.zy_,
                yx_* matrix.xz_ + yy_* matrix.yz_ + yz_ * matrix.zz_,
                zx_* matrix.xx_ + zy_* matrix.yx_ + zz_ * matrix.zx_,
                zx_* matrix.xy_ + zy_* matrix.yy_ + zz_ * matrix.zy_,
                zx_* matrix.xz_ + zy_* matrix.yz_ + zz_* matrix.zz_};
    }

    // Multiplication with a Vector3<Value>.
    Vector3<Value_> operator*(Vector3<Value_> const& vector) const {
        return {xx_ * vector.X() + xy_ * vector.Y() + xz_ * vector.Z(),
                yx_ * vector.X() + yy_ * vector.Y() + yz_ * vector.Z(),
                zx_ * vector.X() + zy_ * vector.Y() + zz_ * vector.Z()};
    }

    // Matrix multiplication.
    Matrix3& operator*=(Matrix3 const& matrix) {
        return *this = operator*(matrix);
    }
    // Note a *= b; <=> a = a * b; while a.transform(b); <=> a = b * a;
    Matrix3& Transform(Matrix3 const& matrix) {
        return *this = matrix.operator * (*this);
    }

    template<typename Value_2_>
    Matrix3<ValueProduct<Value_2_>> Scale(Value_2_ scalar) const {
        return {xx_ * scalar, xy_ * scalar, xz_ * scalar, yx_ * scalar, yy_ * scalar, yz_ * scalar, zx_ * scalar, zy_ * scalar, zz_ * scalar};
    }

    template<typename Value_2_>
    Matrix3<ValueProduct<Value_2_>> operator*(Value_2_ scalar) {
        return Scale(scalar);
    }

    template<typename Value_2_>
    Matrix3<ValueQuotient<Value_2_>> operator/(Value_2_ scalar) {
        return Scale(1. / scalar);
    }

private:

// The matrix elements.
    Value_ xx_ = Value_(0);
    Value_ xy_ = Value_(0);
    Value_ xz_ = Value_(0);
    Value_ yx_ = Value_(0);
    Value_ yy_ = Value_(0);
    Value_ yz_ = Value_(0);
    Value_ zx_ = Value_(0);
    Value_ zy_ = Value_(0);
    Value_ zz_ = Value_(0);

};

template<typename Value_1_, typename Value_2_>
Matrix3<ValueProduct<Value_1_, Value_2_>> MatrixProduct(Vector3<Value_1_> const& vector_1, Vector3<Value_2_> const& vector_2)
{
    return {vector_1.X()* vector_2.X(), vector_1.X()* vector_2.Y(), vector_1.X()* vector_2.Z(), vector_1.Y()* vector_2.X(), vector_1.Y()* vector_2.Y(), vector_1.Y()* vector_2.Z(), vector_1.Z()* vector_2.X(), vector_1.Z()* vector_2.Y(), vector_1.Z()* vector_2.Z()};
}

}
