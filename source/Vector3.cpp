#include "Vector3.hh"
// #include "TRotation.h"
// #include "TMath.h"
// #include "TClass.h"
#include <cmath>
#include <iostream>
#include "TVector3.h"
// ClassImp(Vector3)

namespace analysis
{

//______________________________________________________________________________
Vector3::Vector3()
    : x_(0.0), y_(0.0), z_(0.0) {}

// Vector3::Vector3(const Vector3 &p) : // TObject(p),
//     x_(p.x_), y_(p.y_), z_(p.z_) {}

Vector3::Vector3(float xx, float yy, float zz)
    : x_(xx), y_(yy), z_(zz) {}

Vector3::Vector3(const float *x0)
    : x_(x0[0]), y_(x0[1]), z_(x0[2]) {}

// Vector3::Vector3(const float *x0)
//     : x_(x0[0]), y_(x0[1]), z_(x0[2]) {}

// Vector3::~Vector3() {}

//______________________________________________________________________________
float Vector3::operator()(int i) const
{
    //dereferencing operator const
    switch (i) {
    case 0:
        return x_;
    case 1:
        return y_;
    case 2:
        return z_;
    default:
//          Error("operator()(i)", "bad index (%d) returning 0",i);
      std::cout<< "Error" << std::endl;
    }
    return 0.;
}

//______________________________________________________________________________
float &Vector3::operator()(int i)
{
    //dereferencing operator
    switch (i) {
    case 0:
        return x_;
    case 1:
        return y_;
    case 2:
        return z_;
    default:
      //          Error("operator()(i)", "bad index (%d) returning &x_",i);
      std::cout<< "Error" << std::endl;
    }
    return x_;
}

//______________________________________________________________________________
// Vector3 &Vector3::operator *= (const TRotation &m)
// {
//     //multiplication operator
//     return *this = m * (*this);
// }

//______________________________________________________________________________
// Vector3 &Vector3::Transform(const TRotation &m)
// {
//     //transform this vector with a TRotation
//     return *this = m * (*this);
// }

//______________________________________________________________________________
float Vector3::Angle(const Vector3 &q) const
{
    // return the angle w.r.t. another 3-vector
    float ptot2 = Mag2() * q.Mag2();
    if (ptot2 <= 0) {
        return 0.0;
    } else {
        float arg = Dot(q) / std::sqrt(ptot2);
        if (arg >  1.0) arg =  1.0;
        if (arg < -1.0) arg = -1.0;
        return std::acos(arg);
    }
}

//______________________________________________________________________________
float Vector3::Mag() const
{
    // return the magnitude (rho in spherical coordinate system)

    return std::sqrt(Mag2());
}

//______________________________________________________________________________
float Vector3::Perp() const
{
    //return the transverse component  (R in cylindrical coordinate system)

    return std::sqrt(Perp2());
}


//______________________________________________________________________________
float Vector3::Perp(const Vector3 &p) const
{
    //return the transverse component (R in cylindrical coordinate system)

    return std::sqrt(Perp2(p));
}

//______________________________________________________________________________
float Vector3::Phi() const
{
    //return the  azimuth angle. returns phi from -pi to pi
    return x_ == 0.0 && y_ == 0.0 ? 0.0 : std::atan2(y_, x_);
}

//______________________________________________________________________________
float Vector3::Theta() const
{
    //return the polar angle
    return x_ == 0.0 && y_ == 0.0 && z_ == 0.0 ? 0.0 : std::atan2(Perp(), z_);
}

//______________________________________________________________________________
Vector3 Vector3::Unit() const
{
    // return unit vector parallel to this.
    float  tot2 = Mag2();
    float tot = (tot2 > 0) ?  1.0 / std::sqrt(tot2) : 1.0;
    Vector3 p(x_ * tot, y_ * tot, z_ * tot);
    return p;
}

//______________________________________________________________________________
void Vector3::RotateX(float angle)
{
    //rotate vector around X
    float s = std::sin(angle);
    float c = std::cos(angle);
    float yy = y_;
    y_ = c * yy - s * z_;
    z_ = s * yy + c * z_;
}

//______________________________________________________________________________
void Vector3::RotateY(float angle)
{
    //rotate vector around Y
    float s = std::sin(angle);
    float c = std::cos(angle);
    float zz = z_;
    z_ = c * zz - s * x_;
    x_ = s * zz + c * x_;
}

//______________________________________________________________________________
void Vector3::RotateZ(float angle)
{
    //rotate vector around Z
    float s = std::sin(angle);
    float c = std::cos(angle);
    float xx = x_;
    x_ = c * xx - s * y_;
    y_ = s * xx + c * y_;
}

//______________________________________________________________________________
// void Vector3::Rotate(float angle, const Vector3 &axis)
// {
//     //rotate vector
//     TRotation trans;
//     trans.Rotate(angle, axis);
//     operator*=(trans);
// }

//______________________________________________________________________________
void Vector3::RotateUz(const Vector3 &NewUzVector)
{
    // NewUzVector must be normalized !

    float u1 = NewUzVector.x_;
    float u2 = NewUzVector.y_;
    float u3 = NewUzVector.z_;
    float up = u1 * u1 + u2 * u2;

    if (up) {
        up = std::sqrt(up);
        float px = x_,  py = y_,  pz = z_;
        x_ = (u1 * u3 * px - u2 * py + u1 * up * pz) / up;
        y_ = (u2 * u3 * px + u1 * py + u2 * up * pz) / up;
        z_ = (u3 * u3 * px -    px + u3 * up * pz) / up;
    } else if (u3 < 0.) {
        x_ = -x_;    // phi=0  teta=pi
        z_ = -z_;
    } else {};
}

//______________________________________________________________________________
float Vector3::PseudoRapidity() const
{
    //float m = Mag();
    //return 0.5*log( (m+z_)/(m-z_) );
    // guard against Pt=0
    double cosTheta = CosTheta();
    if (cosTheta * cosTheta < 1) return -0.5 * std::log((1.0 - cosTheta) / (1.0 + cosTheta));
    if (z_ == 0) return 0;
//    Warning("PseudoRapidity","transvers momentum = 0! return +/- 10e10");
    if (z_ > 0) return 10e10;
    else        return -10e10;
}

//______________________________________________________________________________
void Vector3::SetPtEtaPhi(float pt, float eta, float phi)
{
    //set Pt, Eta and Phi
    float apt = std::abs(pt);
    SetXYZ(apt * std::cos(phi), apt * std::sin(phi), apt / std::tan(2.0 * std::atan(std::exp(-eta))));
}

//______________________________________________________________________________
void Vector3::SetPtThetaPhi(float pt, float theta, float phi)
{
    //set Pt, Theta and Phi
    x_ = pt * std::cos(phi);
    y_ = pt * std::sin(phi);
    float tanTheta = std::tan(theta);
    z_ = tanTheta ? pt / tanTheta : 0;
}

//______________________________________________________________________________
void Vector3::SetTheta(float th)
{
    // Set theta keeping mag and phi constant (BaBar).
    float ma   = Mag();
    float ph   = Phi();
    SetX(ma * std::sin(th)*std::cos(ph));
    SetY(ma * std::sin(th)*std::sin(ph));
    SetZ(ma * std::cos(th));
}

//______________________________________________________________________________
void Vector3::SetPhi(float ph)
{
    // Set phi keeping mag and theta constant (BaBar).
    float xy   = Perp();
    SetX(xy * std::cos(ph));
    SetY(xy * std::sin(ph));
}

//______________________________________________________________________________
float Vector3::DeltaR(const Vector3 &v) const
{
    //return deltaR with respect to v
    float deta = Eta() - v.Eta();
    float dphi = TVector2::Phi_mpi_pi(Phi() - v.Phi());
    return std::sqrt(deta * deta + dphi * dphi);
}

//______________________________________________________________________________
void Vector3::SetMagThetaPhi(float mag, float theta, float phi)
{
    //setter with mag, theta, phi
    float amag = std::abs(mag);
    x_ = amag * std::sin(theta) * std::cos(phi);
    y_ = amag * std::sin(theta) * std::sin(phi);
    z_ = amag * std::cos(theta);
}

//______________________________________________________________________________
// void Vector3::Streamer(TBuffer &R__b)
// {
//    // Stream an object of class Vector3.
//
//    if (R__b.IsReading()) {
//       UInt_t R__s, R__c;
//       Version_t R__v = R__b.ReadVersion(&R__s, &R__c);
//       if (R__v > 2) {
//          R__b.ReadClassBuffer(Vector3::Class(), this, R__v, R__s, R__c);
//          return;
//       }
//       //====process old versions before automatic schema evolution
//       if (R__v < 2) TObject::Streamer(R__b);
//       R__b >> x_;
//       R__b >> y_;
//       R__b >> z_;
//       R__b.CheckByteCount(R__s, R__c, Vector3::IsA());
//       //====end of old versions
//
//    } else {
//       R__b.WriteClassBuffer(Vector3::Class(),this);
//    }
// }

Vector3 operator + (const Vector3 &a, const Vector3 &b)
{
    return Vector3(a.X() + b.X(), a.Y() + b.Y(), a.Z() + b.Z());
}

Vector3 operator - (const Vector3 &a, const Vector3 &b)
{
    return Vector3(a.X() - b.X(), a.Y() - b.Y(), a.Z() - b.Z());
}

Vector3 operator * (const Vector3 &p, float a)
{
    return Vector3(a * p.X(), a * p.Y(), a * p.Z());
}

Vector3 operator * (float a, const Vector3 &p)
{
    return Vector3(a * p.X(), a * p.Y(), a * p.Z());
}

float operator * (const Vector3 &a, const Vector3 &b)
{
    return a.Dot(b);
}

Vector3 operator * (const TMatrix &m, const Vector3 &v)
{
    return Vector3(m(0, 0) * v.X() + m(0, 1) * v.Y() + m(0, 2) * v.Z(),
                   m(1, 0) * v.X() + m(1, 1) * v.Y() + m(1, 2) * v.Z(),
                   m(2, 0) * v.X() + m(2, 1) * v.Y() + m(2, 2) * v.Z());
}
void Vector3::operator=(const TVector3 &vector)
{
    x_ = vector.X();
    y_ = vector.Y();
    z_ = vector.Z();
}


//const Vector3 kXHat(1.0, 0.0, 0.0);
//const Vector3 kYHat(0.0, 1.0, 0.0);
//const Vector3 kZHat(0.0, 0.0, 1.0);

// void Vector3::Print(Option_t*)const
// {
//    //print vector parameters
//    Printf("%s %s (x,y,z)=(%f,%f,%f) (rho,theta,phi)=(%f,%f,%f)",GetName(),GetTitle(),X(),Y(),Z(),
//                                           Mag(),Theta()*TMath::RadToDeg(),Phi()*TMath::RadToDeg());
// }

}
