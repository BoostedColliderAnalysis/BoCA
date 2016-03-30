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

namespace boca {

template<typename Value_>
class LorentzMatrix {

public:

    // Default constructor. Gives a unit matrix.
    LorentzMatrix() {}

    // Constructor for 3d rotations.
    LorentzMatrix(Matrix3<Value_> const& matrix)
        : x_(matrix.X(), Value_(0)), y_(matrix.Y(), Value_(0)), z_(matrix.Z(), Value_(0)), t_(Value_(0), Value_(0), Value_(0), Value_(1)) {}

    //constructor
    LorentzMatrix(double bx, double by, double bz) {
        SetBoost(bx, by, bz);
    }
    // Constructors giving a Lorenz-boost.
    LorentzMatrix(Vector3<Value_> const& p) {
        //copy constructor
        SetBoost(p.X(), p.Y(), p.Z());
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
    LorentzVector<Value_> &X() {
        return x_;
    }
    LorentzVector<Value_> &Y() {
        return y_;
    }
    LorentzVector<Value_> &Z() {
        return z_;
    }
    LorentzVector<Value_> &T() {
        return t_;
    }

    // Returns object of the helper class for C-style subscripting r[i][j]
    LorentzVector<Value_> operator[] (int i) const {
        return (*this, i);
    }


    // Fortran-style subscriptimg: returns (i,j) element of the matrix.
    LorentzVector<Value_> operator() (int i) const {
        //derefencing operator
        switch(i) {
        case 0 :
            return x_;
        case 1 :
            return y_;
        case 2 :
            return z_;
        case 3 :
            return t_;
        }
        std::cout << "operator()(i), subscripting: bad index " << i << std::endl;
        return LorentzVector<Value_>;
    }

    // Fortran-style subscriptimg: returns (i,j) element of the matrix.
    LorentzVector<Value_> & operator() (int i) {
        //derefencing operator
        switch(i) {
        case 0 :
            return x_;
        case 1 :
            return y_;
        case 2 :
            return z_;
        case 3 :
            return t_;
        }
        std::cout << "operator()(i), subscripting: bad index " << i << std::endl;
        return x_;
    }


    // Assignment.
    x & LorentzMatrix::operator=(const Matrix3<Value_> & r) {
        x_.X() = r.XX();
        x_.Y() = r.XY();
        x_.Z() = r.XZ();
        x_.T() = 0.0;
        y_.X() = r.YX();
        y_.Y() = r.YY();
        y_.Z() = r.YZ();
        y_.T() = 0.0;
        z_.X() = r.ZX();
        z_.Y() = r.ZY();
        z_.Z() = r.ZZ();
        z_.T() = 0.0;
        t_.X() = 0.0;
        t_.Y() = 0.0;
        t_.Z() = 0.0;
        t_.T() = 1.0;
        return *this;
    }

    bool LorentzMatrix::operator==(LorentzMatrix const& matrix) const {
        return x_ == matrix.x_ && y_ == matrix.y_ && z_ == matrix.z_ && t_ == matrix.t_ ;
    }

    // Comparisons.
    bool LorentzMatrix::operator!=(LorentzMatrix const& matrix) const {
        return x_ != matrix.x_ || y_ != matrix.y_ || z_ != matrix.z_ || t_ != matrix.t_;
    }

    inline bool IsIdentity() const;
    // Returns true if the Identity matrix.

    inline LorentzVector<Value_> VectorMultiplication(const LorentzVector<Value_>&) const;

    inline LorentzVector<Value_> operator* (const LorentzVector<Value_> &) const;
    // Multiplication with a Lorentz vector.

    LorentzMatrix MatrixMultiplication(const LorentzMatrix &) const const {
        //multiply this vector by a matrix
        return {x_.X()*b.x_.X() + x_.Y()*b.y_.X() + x_.Z()*b.z_.X() + x_.T()*b.t_.X(),
                x_.X()*b.x_.Y() + x_.Y()*b.y_.Y() + x_.Z()*b.z_.Y() + x_.T()*b.t_.Y(),
                x_.X()*b.x_.Z() + x_.Y()*b.y_.Z() + x_.Z()*b.z_.Z() + x_.T()*b.t_.Z(),
                x_.X()*b.x_.T() + x_.Y()*b.y_.T() + x_.Z()*b.z_.T() + x_.T()*b.t_.T(),
                y_.X()*b.x_.X() + y_.Y()*b.y_.X() + y_.Z()*b.z_.X() + y_.T()*b.t_.X(),
                y_.X()*b.x_.Y() + y_.Y()*b.y_.Y() + y_.Z()*b.z_.Y() + y_.T()*b.t_.Y(),
                y_.X()*b.x_.Z() + y_.Y()*b.y_.Z() + y_.Z()*b.z_.Z() + y_.T()*b.t_.Z(),
                y_.X()*b.x_.T() + y_.Y()*b.y_.T() + y_.Z()*b.z_.T() + y_.T()*b.t_.T(),
                z_.X()*b.x_.X() + z_.Y()*b.y_.X() + z_.Z()*b.z_.X() + z_.T()*b.t_.X(),
                z_.X()*b.x_.Y() + z_.Y()*b.y_.Y() + z_.Z()*b.z_.Y() + z_.T()*b.t_.Y(),
                z_.X()*b.x_.Z() + z_.Y()*b.y_.Z() + z_.Z()*b.z_.Z() + z_.T()*b.t_.Z(),
                z_.X()*b.x_.T() + z_.Y()*b.y_.T() + z_.Z()*b.z_.T() + z_.T()*b.t_.T(),
                t_.X()*b.x_.X() + t_.Y()*b.y_.X() + t_.Z()*b.z_.X() + t_.T()*b.t_.X(),
                t_.X()*b.x_.Y() + t_.Y()*b.y_.Y() + t_.Z()*b.z_.Y() + t_.T()*b.t_.Y(),
                t_.X()*b.x_.Z() + t_.Y()*b.y_.Z() + t_.Z()*b.z_.Z() + t_.T()*b.t_.Z(),
                t_.X()*b.x_.T() + t_.Y()*b.y_.T() + t_.Z()*b.z_.T() + t_.T()*b.t_.T()
               };
    }

    inline LorentzMatrix operator* (const LorentzMatrix &) const;
    inline LorentzMatrix & operator*= (const LorentzMatrix &);
    inline LorentzMatrix & Transform(const LorentzMatrix &);
    inline LorentzMatrix & Transform(const Matrix3<Value_> &);
    // Matrix multiplication.
    // Note: a *= b; <=> a = a * b; while a.Transform(b); <=> a = b * a;

    inline LorentzMatrix Inverse() const;
    // Return the inverse.

    inline LorentzMatrix & Invert();
    // Inverts the LorentzRotation matrix.

    inline LorentzMatrix & Boost(double, double, double);
    inline LorentzMatrix & Boost(const Vector<Value_> &);
    // Lorenz boost.

    inline LorentzMatrix & RotateX(double);
    // Rotation around x-axis.

    inline LorentzMatrix & RotateY(double);
    // Rotation around y-axis.

    inline LorentzMatrix & RotateZ(double);
    // Rotation around z-axis.

    inline LorentzMatrix & Rotate(double, const Vector<Value_> &);
    inline LorentzMatrix & Rotate(double, const Vector<Value_> *);
    // Rotation around specified vector.

protected:

    LorentzVector<Value_> x_;
    LorentzVector<Value_> y_;
    LorentzVector<Value_> z_;
    LorentzVector<Value_> t_;
    // The matrix elements.

    // Set elements according to a boost vector.
    void SetBoost(Vector3<double> const& boost) {
        //boost this Lorentz vector
        double bp2 = boost.Mag2();
        double gamma = 1 / std::sqrt(1 - bp2);
        double bgamma = sqr(gamma) / (1 + gamma);
        auto matrix = MatrixMultiplication(boost, boost) + Matrix3<double>(1);
        auto vector = boost + Vector3<double>(gamma,gamma,gamma);

        *this = LorentzMatrix<double>(matrix, vector,vector,gamma);

        x_.X() = 1 + bgamma * bx * bx;
        x_.Y() = bgamma * bx * by;
        x_.Z() = bgamma * bx * bz;
        x_.T() = gamma * bx;

        y_.X() = bgamma * bx * by;
        y_.Y() = 1 + bgamma * by * by;
        y_.Z() = bgamma * by * bz;
        y_.T() = gamma * by;

        z_.Z() = 1 + bgamma * bz * bz;
        z_.X() = bgamma * bx * bz;
        z_.Y() = bgamma * by * bz;
        z_.T() = gamma * bz;

        t_.X() = gamma * bx;
        t_.Y() = gamma * by;
        t_.Z() = gamma * bz;
        t_.T() = gamma;
    }


};


//inline LorentzMatrix &
//LorentzMatrix::operator= (const Matrix3<Value_> & r) {
//  mxx = r.xx(); mxy = r.xy(); mxz = r.xz(); mxt = 0.0;
//  myx = r.yx(); myy = r.yy(); myz = r.yz(); myt = 0.0;
//  mzx = r.zx(); mzy = r.zy(); mzz = r.zz(); mzt = 0.0;
//  mtx = 0.0;    mty = 0.0;    mtz = 0.0;    mtt = 1.0;
//  return *this;
//}


//inline bool
//LorentzMatrix::operator== (const LorentzMatrix & r) const {
//  return (mxx == r.xx() && mxy == r.xy() && mxz == r.xz() && mxt == r.xt() &&
//          myx == r.yx() && myy == r.yy() && myz == r.yz() && myt == r.yt() &&
//          mzx == r.zx() && mzy == r.zy() && mzz == r.zz() && mzt == r.zt() &&
//          mtx == r.tx() && mty == r.ty() && mtz == r.tz() && mtt == r.tt())
//  ? kTRUE : kFALSE;
//}



//inline bool
//LorentzMatrix::operator!= (const LorentzMatrix & r) const {
//  return (mxx != r.xx() || mxy != r.xy() || mxz != r.xz() || mxt != r.xt() ||
//          myx != r.yx() || myy != r.yy() || myz != r.yz() || myt != r.yt() ||
//          mzx != r.zx() || mzy != r.zy() || mzz != r.zz() || mzt != r.zt() ||
//          mtx != r.tx() || mty != r.ty() || mtz != r.tz() || mtt != r.tt())
//  ? kTRUE : kFALSE;
//}



inline bool LorentzMatrix::IsIdentity() const {
    return x_.X() == 1.0 && x_.Y() == 0.0 && x_.Z() == 0.0 && x_.T() == 0.0 &&
            y_.X() == 0.0 && y_.Y() == 1.0 && y_.Z() == 0.0 && y_.T() == 0.0 &&
            z_.X() == 0.0 && z_.Y() == 0.0 && z_.Z() == 1.0 && z_.T() == 0.0 &&
            t_.X() == 0.0 && t_.Y() == 0.0 && t_.Z() == 0.0 && t_.T() == 1.0;
}


inline LorentzVector<Value_> LorentzMatrix::VectorMultiplication(const LorentzVector<Value_> & p) const {
    return {x_.X()*p.X()+x_.Y()*p.Y()+x_.Z()*p.Z()+x_.T()*p.T(),
            y_.X()*p.X()+y_.Y()*p.Y()+y_.Z()*p.Z()+y_.T()*p.T(),
            z_.X()*p.X()+z_.Y()*p.Y()+z_.Z()*p.Z()+z_.T()*p.T(),
            t_.X()*p.X()+t_.Y()*p.Y()+t_.Z()*p.Z()+t_.T()*p.T()
           };
}

inline LorentzVector<Value_> LorentzMatrix::operator* (const LorentzVector<Value_> & p) const {
    return VectorMultiplication(p);
}

inline LorentzMatrix LorentzMatrix::operator* (const LorentzMatrix & m) const {
    return MatrixMultiplication(m);
}

inline LorentzMatrix & LorentzMatrix::operator*= (const LorentzMatrix & m) {
    return *this = MatrixMultiplication(m);
}

inline LorentzMatrix & LorentzMatrix::Transform(const LorentzMatrix & m) {
    return *this = m.MatrixMultiplication(*this);
}

inline LorentzMatrix & LorentzMatrix::Transform(const Matrix3<Value_> & m) {
    return Transform(LorentzMatrix(m));
}

inline LorentzMatrix LorentzMatrix::Inverse() const {
    return LorentzMatrix( x_.X(),  y_.X(),  z_.X(), -t_.X(),
                          x_.Y(),  y_.Y(),  z_.Y(), -t_.Y(),
                          x_.Z(),  y_.Z(),  z_.Z(), -t_.Z(),
                          -x_.T(), -y_.T(), -z_.T(),  t_.T());
}

inline LorentzMatrix & LorentzMatrix::Invert() {
    return *this = Inverse();
}

inline LorentzMatrix & LorentzMatrix::Boost(double bx, double by, double bz) {
    return Transform(LorentzMatrix(bx, by, bz));
}

inline LorentzMatrix & LorentzMatrix::Boost(const Vector<Value_> & b) {
    return Transform(LorentzMatrix(b));
}

inline LorentzMatrix & LorentzMatrix::RotateX(double angle) {
    return Transform(Matrix3<Value_>().RotateX(angle));
}

inline LorentzMatrix & LorentzMatrix::RotateY(double angle) {
    return Transform(Matrix3<Value_>().RotateY(angle));
}

inline LorentzMatrix & LorentzMatrix::RotateZ(double angle) {
    return Transform(Matrix3<Value_>().RotateZ(angle));
}

inline LorentzMatrix & LorentzMatrix::Rotate(double angle, const Vector<Value_> & axis) {
    return Transform(Matrix3<Value_>().Rotate(angle, axis));
}

inline LorentzMatrix & LorentzMatrix::Rotate(double angle, const Vector<Value_> * axis) {
    return Transform(Matrix3<Value_>().Rotate(angle, axis));
}

}
