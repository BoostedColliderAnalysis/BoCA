#include "LorentzVector.hh"
#include "TLorentzVector.h"
#include <iostream>

namespace analysis
{

LorentzVector::LorentzVector() : p_(), e_(0.0) {}

LorentzVector::LorentzVector(float x, float y, float z, float t) : p_(x, y, z), e_(t) {}

LorentzVector::LorentzVector(const float *x0) : p_(x0), e_(x0[3]) {}

LorentzVector::LorentzVector(const Vector3 &p, float e) : p_(p), e_(e) {}

float LorentzVector::operator()(int i) const
{
//dereferencing operator const
    switch (i) {
    case kX:
    case kY:
    case kZ:
        return p_(i);
    case kT:
        return e_;
    default:
// Error("operator()()", "bad index (%d) returning 0", i);
        std::cout << "Error" << std::endl;
    }
    return 0.;
}

float &LorentzVector::operator()(int i)
{
//dereferencing operator
    switch (i) {
    case kX:
    case kY:
    case kZ:
        return p_(i);
    case kT:
        return e_;
    default:
// Error("operator()()", "bad index (%d) returning &e_", i);
        std::cout << "Error" << std::endl;
    }
    return e_;
}

void LorentzVector::Boost(float bx, float by, float bz)
{
//Boost this Lorentz vector
    float b2 = bx * bx + by * by + bz * bz;
    float gamma = 1.0 / std::sqrt(1.0 - b2);
    float bp = bx * X() + by * Y() + bz * Z();
    float gamma2 = b2 > 0 ? (gamma - 1.0) / b2 : 0.0;

    SetX(X() + gamma2 * bp * bx + gamma * bx * T());
    SetY(Y() + gamma2 * bp * by + gamma * by * T());
    SetZ(Z() + gamma2 * bp * bz + gamma * bz * T());
    SetT(gamma * (T() + bp));
}

float LorentzVector::Rapidity() const
{
//return rapidity
    return 0.5 * log((E() + Pz()) / (E() - Pz()));
}
void LorentzVector::operator=(const TLorentzVector &lorentzvector)
{
    p_ = lorentzvector.Vect();
    e_ = lorentzvector.T();
}
void LorentzVector::SetXYZM(float x, float y, float z, float m)
{
    if (m >= 0) SetXYZT(x, y, z, std::sqrt(x * x + y * y + z * z + m * m));
    else SetXYZT(x, y, z, std::sqrt(std::max((x * x + y * y + z * z - m * m), float(0))));
}
void LorentzVector::SetPtEtaPhiM(float pt, float eta, float phi, float m)
{
    pt = std::abs(pt);
    SetXYZM(pt * std::cos(phi), pt * std::sin(phi), pt * sinh(eta) , m);
}
void LorentzVector::SetPtEtaPhiE(float pt, float eta, float phi, float e)
{
    pt = std::abs(pt);
    SetXYZT(pt * std::cos(phi), pt * std::sin(phi), pt * sinh(eta) , e);
}
void LorentzVector::GetXYZT(float *carray) const
{
    p_.GetXYZ(carray);
    carray[3] = e_;
}
float LorentzVector::Et() const
{
    float etet = Et2();
    return E() < 0.0 ? -std::sqrt(etet) : std::sqrt(etet);
}
float LorentzVector::Et2(const Vector3 &v) const
{
    float pt2 = p_.Perp2(v);
    float pv = p_.Dot(v.Unit());
    return pt2 == 0 ? 0 : E() * E() * pt2 / (pt2 + pv * pv);
}
float LorentzVector::Et(const Vector3 &v) const
{
    float etet = Et2(v);
    return E() < 0.0 ? -std::sqrt(etet) : std::sqrt(etet);
}
float LorentzVector::DeltaR(const LorentzVector &v) const
{
    float deta = Eta() - v.Eta();
    float dphi = Vector2::Phi_mpi_pi(Phi() - v.Phi());
    return std::sqrt(deta * deta + dphi * dphi);
}
float LorentzVector::Mag() const
{
    float mm = Mag2();
    return mm < 0.0 ? -std::sqrt(-mm) : std::sqrt(mm);
}
float LorentzVector::Mt() const
{
    float mm = Mt2();
    return mm < 0.0 ? -std::sqrt(-mm) : std::sqrt(mm);
}
float LorentzVector::Gamma() const
{
    float b = Beta();
    return 1.0 / std::sqrt(1 - b * b);
}
float LorentzVector::X() const
{
    return p_.X();
}
float LorentzVector::Y() const
{
    return p_.Y();
}
float LorentzVector::Z() const
{
    return p_.Z();
}
float LorentzVector::T() const
{
    return e_;
}

void LorentzVector::SetX(float a)
{
    p_.SetX(a);
}
void LorentzVector::SetY(float a)
{
    p_.SetY(a);
}
void LorentzVector::SetZ(float a)
{
    p_.SetZ(a);
}
void LorentzVector::SetT(float a)
{
    e_ = a;
}

float LorentzVector::Px() const
{
    return X();
}
float LorentzVector::Py() const
{
    return Y();
}
float LorentzVector::Pz() const
{
    return Z();
}
float LorentzVector::P() const
{
    return p_.Mag();
}
float LorentzVector::E() const
{
    return T();
}
float LorentzVector::Energy() const
{
    return T();
}

void LorentzVector::SetPx(float a)
{
    SetX(a);
}
void LorentzVector::SetPy(float a)
{
    SetY(a);
}
void LorentzVector::SetPz(float a)
{
    SetZ(a);
}
void LorentzVector::SetE(float a)
{
    SetT(a);
}

Vector3 LorentzVector::Vect() const
{
    return p_;
}

void LorentzVector::SetVect(const Vector3 &p)
{
    p_ = p;
}

float LorentzVector::Phi() const
{
    return p_.Phi();
}

float LorentzVector::Theta() const
{
    return p_.Theta();
}

float LorentzVector::CosTheta() const
{
    return p_.CosTheta();
}


float LorentzVector::Rho() const
{
    return p_.Mag();
}

void LorentzVector::SetTheta(float th)
{
    p_.SetTheta(th);
}

void LorentzVector::SetPhi(float phi)
{
    p_.SetPhi(phi);
}

void LorentzVector::SetRho(float rho)
{
    p_.SetMag(rho);
}

void LorentzVector::SetXYZT(float x, float y, float z, float t)
{
    p_.SetXYZ(x, y, z);
    SetT(t);
}

void LorentzVector::SetPxPyPzE(float px, float py, float pz, float e)
{
    SetXYZT(px, py, pz, e);
}

float &LorentzVector::operator [](int i)
{
    return (*this)(i);
}
float LorentzVector::operator [](int i) const
{
    return (*this)(i);
}

LorentzVector LorentzVector::operator + (const LorentzVector &q) const
{
    return LorentzVector(p_ + q.Vect(), e_ + q.T());
}

LorentzVector &LorentzVector::operator += (const LorentzVector &q)
{
    p_ += q.Vect();
    e_ += q.T();
    return *this;
}

LorentzVector LorentzVector::operator - (const LorentzVector &q) const
{
    return LorentzVector(p_ - q.Vect(), e_ - q.T());
}

LorentzVector &LorentzVector::operator -= (const LorentzVector &q)
{
    p_ -= q.Vect();
    e_ -= q.T();
    return *this;
}

LorentzVector LorentzVector::operator - () const
{
    return LorentzVector(-X(), -Y(), -Z(), -T());
}

LorentzVector &LorentzVector::operator *= (float a)
{
    p_ *= a;
    e_ *= a;
    return *this;
}

LorentzVector LorentzVector::operator * (float a) const
{
    return LorentzVector(a * X(), a * Y(), a * Z(), a * T());
}

bool LorentzVector::operator == (const LorentzVector &q) const
{
    return (Vect() == q.Vect() && T() == q.T());
}

bool LorentzVector::operator != (const LorentzVector &q) const
{
    return (Vect() != q.Vect() || T() != q.T());
}

float LorentzVector::Perp2() const
{
    return p_.Perp2();
}

float LorentzVector::Perp() const
{
    return p_.Perp();
}

float LorentzVector::Pt() const
{
    return Perp();
}

void LorentzVector::SetPerp(float r)
{
    p_.SetPerp(r);
}

float LorentzVector::Perp2(const Vector3 &v) const
{
    return p_.Perp2(v);
}

float LorentzVector::Perp(const Vector3 &v) const
{
    return p_.Perp(v);
}

float LorentzVector::Pt(const Vector3 &v) const
{
    return Perp(v);
}

float LorentzVector::Et2() const
{
    float pt2 = p_.Perp2();
    return pt2 == 0 ? 0 : E() * E() * pt2 / (pt2 + Z() * Z());
}

float LorentzVector::DeltaPhi(const LorentzVector &v) const
{
    return Vector2::Phi_mpi_pi(Phi() - v.Phi());
}

float LorentzVector::Eta() const
{
    return PseudoRapidity();
}

float LorentzVector::DrEtaPhi(const LorentzVector &v) const
{
    return DeltaR(v);
}

Vector2 LorentzVector::EtaPhiVector()
{
    return Vector2(Eta(), Phi());
}


float LorentzVector::Angle(const Vector3 &v) const
{
    return p_.Angle(v);
}

float LorentzVector::Mag2() const
{
    return T() * T() - p_.Mag2();
}

// float LorentzVector::Mag() const;

float LorentzVector::M2() const
{
    return Mag2();
}
float LorentzVector::M() const
{
    return Mag();
}

float LorentzVector::Mt2() const
{
    return E() * E() - Z() * Z();
}

float LorentzVector::Beta() const
{
    return p_.Mag() / e_;
}

void LorentzVector::SetVectMag(const Vector3 &spatial, float magnitude)
{
    SetXYZM(spatial.X(), spatial.Y(), spatial.Z(), magnitude);
}

void LorentzVector::SetVectM(const Vector3 &spatial, float mass)
{
    SetVectMag(spatial, mass);
}

float LorentzVector::Dot(const LorentzVector &q) const
{
    return T() * q.T() - Z() * q.Z() - Y() * q.Y() - X() * q.X();
}

float LorentzVector::operator * (const LorentzVector &q) const
{
    return Dot(q);
}

//Member functions Plus() and Minus() return the positive and negative
//light-cone components:
//
// float pcone = v.Plus();
// float mcone = v.Minus();
//
//CAVEAT: The values returned are T{+,-}Z. It is known that some authors
//find it easier to define these components as (T{+,-}Z)/sqrt(2). Thus
//check what definition is used in the physics you're working in and adapt
//your code accordingly.

float LorentzVector::Plus() const
{
    return T() + Z();
}

float LorentzVector::Minus() const
{
    return T() - Z();
}

Vector3 LorentzVector::BoostVector() const
{
    return Vector3(X() / T(), Y() / T(), Z() / T());
}

void LorentzVector::Boost(const Vector3 &b)
{
    Boost(b.X(), b.Y(), b.Z());
}

float LorentzVector::PseudoRapidity() const
{
    return p_.PseudoRapidity();
}

void LorentzVector::RotateX(float angle)
{
    p_.RotateX(angle);
}

void LorentzVector::RotateY(float angle)
{
    p_.RotateY(angle);
}

void LorentzVector::RotateZ(float angle)
{
    p_.RotateZ(angle);
}

void LorentzVector::RotateUz(Vector3 &newUzVector)
{
    p_.RotateUz(newUzVector);
}

LorentzVector operator * (float a, const LorentzVector &p)
{
    return LorentzVector(a * p.X(), a * p.Y(), a * p.Z(), a * p.T());
}

}
