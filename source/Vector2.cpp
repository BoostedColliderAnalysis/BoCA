#include "Vector2.hh"
#include <cmath>

float const  kPI        = M_PI;
float const  kTWOPI     = 2.*kPI;

// ClassImp(Vector2)

namespace analysis {

//______________________________________________________________________________
Vector2::Vector2()
{
   //constructor
   x_ = 0.;
   y_ = 0.;
}

//______________________________________________________________________________
Vector2::Vector2(float *v)
{
   //constructor
   x_ = v[0];
   y_ = v[1];
}

//______________________________________________________________________________
Vector2::Vector2(float x0, float y0)
{
   //constructor
   x_ = x0;
   y_ = y0;
}

//______________________________________________________________________________
// Vector2::~Vector2()
// {
// }

//______________________________________________________________________________
float Vector2::Mod() const
{
   // return modulo of this vector
   return std::sqrt(x_*x_+y_*y_);
}

//______________________________________________________________________________
Vector2 Vector2::Unit() const
{
   // return module normalized to 1
   return (Mod2()) ? *this/Mod() : Vector2();
}

//______________________________________________________________________________
float Vector2::Phi() const
{
   // return vector phi
   return M_PI+std::atan2(-y_,-x_);
}

//______________________________________________________________________________
float Vector2::Phi_0_2pi(float x) {
   // (static function) returns phi angle in the interval [0,2*PI)
   if(std::isnan(x)){
//       gROOT->Error("Vector2::Phi_0_2pi","function called with NaN");
      return x;
   }
   while (x >= kTWOPI) x -= kTWOPI;
   while (x <     0.)  x += kTWOPI;
   return x;
}

//______________________________________________________________________________
float Vector2::Phi_mpi_pi(float x) {
   // (static function) returns phi angle in the interval [-PI,PI)
  if(std::isnan(x)){
//       gROOT->Error("Vector2::Phi_mpi_pi","function called with NaN");
      return x;
   }
   while (x >= kPI) x -= kTWOPI;
   while (x < -kPI) x += kTWOPI;
   return x;
}

//______________________________________________________________________________
Vector2 Vector2::Rotate (float phi) const
{
   //rotation by phi
   return Vector2( x_*std::cos(phi)-y_*std::sin(phi), x_*std::sin(phi)+y_*std::cos(phi) );
}

//______________________________________________________________________________
void Vector2::SetMagPhi(float mag, float phi)
{
   //set vector using mag and phi
   float amag = std::abs(mag);
   x_ = amag * std::cos(phi);
   y_ = amag * std::sin(phi);
}
//______________________________________________________________________________
// void Vector2::Streamer(TBuffer &R__b)
// {
//    // Stream an object of class Vector2.
//
//    if (R__b.IsReading()) {
//       UInt_t R__s, R__c;
//       Version_t R__v = R__b.ReadVersion(&R__s, &R__c);
//       if (R__v > 2) {
//          R__b.ReadClassBuffer(Vector2::Class(), this, R__v, R__s, R__c);
//          return;
//       }
//       //====process old versions before automatic schema evolution
//       if (R__v < 2) TObject::Streamer(R__b);
//       R__b >> x_;
//       R__b >> y_;
//       R__b.CheckByteCount(R__s, R__c, Vector2::IsA());
//       //====end of old versions
//
//    } else {
//       R__b.WriteClassBuffer(Vector2::Class(),this);
//    }
// }

// void Vector2::Print(Option_t*)const
// {
//    //print vector parameters
//    Printf("%s %s (x,y)=(%f,%f) (rho,phi)=(%f,%f)",GetName(),GetTitle(),X(),Y(),
//                                           Mod(),Phi()*TMath::RadToDeg());
// }

}
