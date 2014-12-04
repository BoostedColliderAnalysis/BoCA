#ifndef DIM
#define DIM

#include "fastjet/PseudoJet.hh"

class event22 {

public:

    double p3[4], p4[4], p5[4], p6[4];
    
    double pmiss[4];

    void cubic ( double *a, double *x, int &l );

    void quartic ( double *dd, double *sol, double *soli, int &nsol );

    void solve22 ( event22 &evt, double mn, double mx, double my, int &nsols, double p1[][4], double p2[][4] );

    inline double dot ( double *p1, double *p2 ) {
        return p1[0]*p2[0]-p1[1]*p2[1]-p1[2]*p2[2]-p1[3]*p2[3];
    }

    void SetP3(fastjet::PseudoJet Jet){
      p3[0] = Jet.E();
      p3[1] = Jet.px();
      p3[2] = Jet.py();
      p3[3] = Jet.pz();
    }
    
    void SetP4(fastjet::PseudoJet Jet){
      p4[0] = Jet.E();
      p4[1] = Jet.px();
      p4[2] = Jet.py();
      p4[3] = Jet.pz();
    }
    
    void SetP5(fastjet::PseudoJet Jet){
      p5[0] = Jet.E();
      p5[1] = Jet.px();
      p5[2] = Jet.py();
      p5[3] = Jet.pz();
    }
    
    void SetP6(fastjet::PseudoJet Jet){
      p6[0] = Jet.E();
      p6[1] = Jet.px();
      p6[2] = Jet.py();
      p6[3] = Jet.pz();
    }
    
    void SetPMiss(fastjet::PseudoJet Jet){
      pmiss[0] = Jet.E();
      pmiss[1] = Jet.px();
      pmiss[2] = Jet.py();
      pmiss[3] = Jet.pz();
    }
    
};

// struct event33 {
//     double p3[4], p4[4], p5[4], p6[4], p7[4], p8[4];
//     double pmiss[4];
//     void solve33(event33 & evt1, event33 & evt2, int & nsols, double p1[][4],double p2[][4], double q1[][4], double q2[][4]);
// };
// 
// struct ArrayHolder
// {
//     double Momentum[4];
// };

#endif
