// @(#)root/physics:$Id$
// Author: Peter Malzacher   19/06/99

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#pragma once
#include "Matrix3.hh"
#include "LorentzVector.hh"

namespace boca
{

template<typename Value_>
class LorentzMatrix
{

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
        default std::cout << "matrix symmetry not well defiend" << std::endl;
        }
    }

    void SetScalar(Value_ scalar) {
        t_.SetScalar(scalar);
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

    // Returns object of the helper class for C-style subscripting r[i][j]
    LorentzVector<Value_> operator[](int i) const {
        return (*this, i);
    }


    // Fortran-style subscriptimg: returns (i,j) element of the matrix.
    LorentzVector<Value_> operator()(int i) const {
        //derefencing operator
        switch (i) {
        case 0 : return x_;
        case 1 : return y_;
        case 2 : return z_;
        case 3 : return t_;
        }
        std::cout << "operator()(i), subscripting: bad index " << i << std::endl;
        return LorentzVector<Value_>;
    }

    // Fortran-style subscriptimg: returns (i,j) element of the matrix.
    LorentzVector<Value_>& operator()(int i) {
        //derefencing operator
        switch (i) {
        case 0 : return x_;
        case 1 : return y_;
        case 2 : return z_;
        case 3 : return t_;
        }
        std::cout << "operator()(i), subscripting: bad index " << i << std::endl;
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
    LorentzMatrix Multiply(const LorentzMatrix& matrix) const const {
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
    LorentzMatrix& Boost(const Vector<Value_>& b) {
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
    LorentzMatrix& Rotate(double angle, const Vector<Value_>& axis) {
        return Transform(Matrix3<Value_>().Rotate(angle, axis));
    }
    LorentzMatrix& Rotate(double angle, const Vector<Value_>* axis) {
        return Transform(Matrix3<Value_>().Rotate(angle, axis));
    }

protected:

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
