#pragma once
#include "Vector2.hh"

typedef float Float_t;
class TVector3;
template<class Element> class TMatrixT;
typedef TMatrixT<Float_t> TMatrix;

namespace analysis{

class Vector3  {

public:

      void operator=(const TVector3 &vector);

   typedef float Scalar;   // to be able to use it with the ROOT::Math::VectorUtil functions

   Vector3();

   Vector3(float x, float y, float z);
   // The constructor.

   Vector3(const float *);
//    Vector3(const float *);
   // Constructors from an array

//    Vector3(const Vector3 &);
   // The copy constructor.

//    virtual ~Vector3();
   // Destructor

   float operator () (int) const;
   inline float operator [] (int) const;
   // Get components by index (Geant4).

   float & operator () (int);
   inline float & operator [] (int);
   // Set components by index.

   inline float x()  const;
   inline float y()  const;
   inline float z()  const;
   inline float X()  const;
   inline float Y()  const;
   inline float Z()  const;
   inline float Px() const;
   inline float Py() const;
   inline float Pz() const;
   // The components in cartesian coordinate system.

   inline void SetX(float);
   inline void SetY(float);
   inline void SetZ(float);
   inline void SetXYZ(float x, float y, float z);
   void        SetPtEtaPhi(float pt, float eta, float phi);
   void        SetPtThetaPhi(float pt, float theta, float phi);

   inline void GetXYZ(float *carray) const;
//    inline void GetXYZ(float *carray) const;
   // Get the components into an array
   // not checked!

   float Phi() const;
   // The azimuth angle. returns phi from -pi to pi

   float Theta() const;
   // The polar angle.

   inline float CosTheta() const;
   // Cosine of the polar angle.

   inline float Mag2() const;
   // The magnitude squared (rho^2 in spherical coordinate system).

   float Mag() const;
   // The magnitude (rho in spherical coordinate system).

   void SetPhi(float);
   // Set phi keeping mag and theta constant (BaBar).

   void SetTheta(float);
   // Set theta keeping mag and phi constant (BaBar).

   inline void SetMag(float);
   // Set magnitude keeping theta and phi constant (BaBar).

   inline float Perp2() const;
   // The transverse component squared (R^2 in cylindrical coordinate system).

   inline float Pt() const;
   float Perp() const;
   // The transverse component (R in cylindrical coordinate system).

   inline void SetPerp(float);
   // Set the transverse component keeping phi and z constant.

   inline float Perp2(const Vector3 &) const;
   // The transverse component w.r.t. given axis squared.

   inline float Pt(const Vector3 &) const;
   float Perp(const Vector3 &) const;
   // The transverse component w.r.t. given axis.

   inline float DeltaPhi(const Vector3 &) const;
   float DeltaR(const Vector3 &) const;
   inline float DrEtaPhi(const Vector3 &) const;
   inline Vector2 EtaPhiVector() const;
   void SetMagThetaPhi(float mag, float theta, float phi);

   inline Vector3 & operator = (const Vector3 &);
   // Assignment.

   inline bool operator == (const Vector3 &) const;
   inline bool operator != (const Vector3 &) const;
   // Comparisons (Geant4).

   inline Vector3 & operator += (const Vector3 &);
   // Addition.

   inline Vector3 & operator -= (const Vector3 &);
   // Subtraction.

   inline Vector3 operator - () const;
   // Unary minus.

   inline Vector3 & operator *= (float);
   // Scaling with real numbers.

   Vector3 Unit() const;
   // Unit vector parallel to this.

   inline Vector3 Orthogonal() const;
   // Vector orthogonal to this (Geant4).

   inline float Dot(const Vector3 &) const;
   // Scalar product.

   inline Vector3 Cross(const Vector3 &) const;
   // Cross product.

   float Angle(const Vector3 &) const;
   // The angle w.r.t. another 3-vector.

   float PseudoRapidity() const;
   // Returns the pseudo-rapidity, i.e. -ln(tan(theta/2))

   inline float Eta() const;

   void RotateX(float);
   // Rotates the Hep3Vector around the x-axis.

   void RotateY(float);
   // Rotates the Hep3Vector around the y-axis.

   void RotateZ(float);
   // Rotates the Hep3Vector around the z-axis.

   void RotateUz(const Vector3&);
   // Rotates reference frame from Uz to newUz (unit vector) (Geant4).

//    void Rotate(float, const Vector3 &);
   // Rotates around the axis specified by another Hep3Vector.

//    Vector3 & operator *= (const TRotation &);
//    Vector3 & Transform(const TRotation &);
   // Transformation with a Rotation matrix.

   inline Vector2 XYvector() const;

//    void Print(Option_t* option="") const;

private:

   float x_, y_, z_;
   // The components.

};


Vector3 operator + (const Vector3 &, const Vector3 &);
// Addition of 3-vectors.

Vector3 operator - (const Vector3 &, const Vector3 &);
// Subtraction of 3-vectors.

float operator * (const Vector3 &, const Vector3 &);
// Scalar product of 3-vectors.

Vector3 operator * (const Vector3 &, float a);
Vector3 operator * (float a, const Vector3 &);
// Scaling of 3-vectors with a real number

Vector3 operator * (const TMatrix &, const Vector3 &);


float & Vector3::operator[] (int i)       { return operator()(i); }
float   Vector3::operator[] (int i) const { return operator()(i); }

inline float Vector3::x()  const { return x_; }
inline float Vector3::y()  const { return y_; }
inline float Vector3::z()  const { return z_; }
inline float Vector3::X()  const { return x_; }
inline float Vector3::Y()  const { return y_; }
inline float Vector3::Z()  const { return z_; }
inline float Vector3::Px() const { return x_; }
inline float Vector3::Py() const { return y_; }
inline float Vector3::Pz() const { return z_; }

inline void Vector3::SetX(float xx) { x_ = xx; }
inline void Vector3::SetY(float yy) { y_ = yy; }
inline void Vector3::SetZ(float zz) { z_ = zz; }

inline void Vector3::SetXYZ(float xx, float yy, float zz) {
   x_ = xx;
   y_ = yy;
   z_ = zz;
}

inline void Vector3::GetXYZ(float *carray) const {
   carray[0] = x_;
   carray[1] = y_;
   carray[2] = z_;
}

// inline void Vector3::GetXYZ(float *carray) const {
//    carray[0] = x_;
//    carray[1] = y_;
//    carray[2] = z_;
// }


inline Vector3 & Vector3::operator = (const Vector3 & p) {
   x_ = p.x_;
   y_ = p.y_;
   z_ = p.z_;
   return *this;
}

inline bool Vector3::operator == (const Vector3& v) const {
   return (v.x_==x_ && v.y_==y_ && v.z_==z_) ? true : false;
}

inline bool Vector3::operator != (const Vector3& v) const {
   return (v.x_!=x_ || v.y_!=y_ || v.z_!=z_) ? true : false;
}

inline Vector3& Vector3::operator += (const Vector3 & p) {
   x_ += p.x_;
   y_ += p.y_;
   z_ += p.z_;
   return *this;
}

inline Vector3& Vector3::operator -= (const Vector3 & p) {
   x_ -= p.x_;
   y_ -= p.y_;
   z_ -= p.z_;
   return *this;
}

inline Vector3 Vector3::operator - () const {
   return Vector3(-x_, -y_, -z_);
}

inline Vector3& Vector3::operator *= (float a) {
   x_ *= a;
   y_ *= a;
   z_ *= a;
   return *this;
}

inline float Vector3::Dot(const Vector3 & p) const {
   return x_*p.x_ + y_*p.y_ + z_*p.z_;
}

inline Vector3 Vector3::Cross(const Vector3 & p) const {
   return Vector3(y_*p.z_-p.y_*z_, z_*p.x_-p.z_*x_, x_*p.y_-p.x_*y_);
}

inline float Vector3::Mag2() const { return x_*x_ + y_*y_ + z_*z_; }


inline Vector3 Vector3::Orthogonal() const {
   float xx = x_ < 0.0 ? -x_ : x_;
   float yy = y_ < 0.0 ? -y_ : y_;
   float zz = z_ < 0.0 ? -z_ : z_;
   if (xx < yy) {
      return xx < zz ? Vector3(0,z_,-y_) : Vector3(y_,-x_,0);
   } else {
      return yy < zz ? Vector3(-z_,0,x_) : Vector3(y_,-x_,0);
   }
}

inline float Vector3::Perp2() const { return x_*x_ + y_*y_; }


inline float Vector3::Pt() const { return Perp(); }

inline float Vector3::Perp2(const Vector3 & p)  const {
   float tot = p.Mag2();
   float ss  = Dot(p);
   float per = Mag2();
   if (tot > 0.0) per -= ss*ss/tot;
   if (per < 0)   per = 0;
   return per;
}

inline float Vector3::Pt(const Vector3 & p) const {
   return Perp(p);
}

inline float Vector3::CosTheta() const {
   float ptot = Mag();
   return ptot == 0.0 ? 1.0 : z_/ptot;
}

inline void Vector3::SetMag(float ma) {
   float factor = Mag();
   if (factor == 0) {
//       Warning("SetMag","zero vector can't be stretched");
   } else {
      factor = ma/factor;
      SetX(x_*factor);
      SetY(y_*factor);
      SetZ(z_*factor);
   }
}

inline void Vector3::SetPerp(float r) {
   float p = Perp();
   if (p != 0.0) {
      x_ *= r/p;
      y_ *= r/p;
   }
}

inline float Vector3::DeltaPhi(const Vector3 & v) const {
   return Vector2::Phi_mpi_pi(Phi()-v.Phi());
}

inline float Vector3::Eta() const {
   return PseudoRapidity();
}

inline float Vector3::DrEtaPhi(const Vector3 & v) const{
   return DeltaR(v);
}


inline Vector2 Vector3::EtaPhiVector() const {
   return Vector2 (Eta(),Phi());
}

inline Vector2 Vector3::XYvector() const {
   return Vector2(x_,y_);
}
}

