/*************************************************************************************/
/* Solve a pair of events with two decay chains, each containing 3 visible particles */
/* Reference arXiv: 0802.4290                                                        */
/* Maintained by Zhenyu Han                                                          */
/*************************************************************************************/


/*************************************************************************************
                              
                                USAGE

   The program solves for the momenta of the invisible particles by combining two 
   events with the same kind of decay chains. Each decay chain contains 3 visible 
   particles, and one invisible particle at the end of the decay chain. 
 
   The visible 4-momenta and the missing transverse momentum are stored in the
   structure:
   struct event33
   {
      double p3[4], p4[4], p5[4], p6[4], p7[4], p8[4];
      double pmiss[4];
   }; 
  
   The particles are labled such that particles 1,3,5,7 are in the same decay 
   chain, with particle 1 denoting the invisible dark matter particle. 
   Particles 3, 5 and 7 are visible paritcles ordered from downstream to upstream
   (i.e., 3 is the one ajacent to the invisible particle). Similarly, particles 
   2, 4, 6, 8 are in the other decay chain with particle 2 the other invisible 
   particle and so forth.
 
   The 4-momenta of the two events are solved by using the following subroutine.

   void solve33(event33 & evt1, event33 & evt2, int & nsols, double p1[9][4],
                double p2[9][4], double q1[9][4], double q2[9][4])
 

   The inputs are the two events evt1 and evt2. The outputs are "nsols", the 
   number of real solutions, not exceeding 9; "p1[0..nsols-1][0..3], 
   p2[0..nsols-1][0..3]", solutions of the 4-momenta of the invisible particles
   in the first event and "q1[0..nsols-1][0..3], q2[0..nsols-1][0..3]" , the 
   4-momenta of the invisible particles in the second event. 

   See examples/example33.cpp for an example.

********************************************************************************/


#include "WIMPMASS.h"
#include <math.h>
#include "TMatrixD.h"
#include "TVectorD.h"
#include "TDecompLU.h"
#include "rpoly_ak1.cpp"
#include <iostream>

using namespace std;

int solve3quad(double* coeff,double* solutions);

inline double mass2(double E,double px,double py,double pz)
{
    double m = E*E - px*px - py*py - pz*pz;
    return m;
};

void solve33(event33 & evt1, event33 & evt2, int & nsols, double p1[][4],
                double p2[][4], double q1[][4], double q2[][4])

	     //double*p1,double*p2,double*p3,double*p4,double*p5,double*p6,
	     //double*p7,double*p8,double*pmiss1,double*pa,double*pb,double*pc,double*pd,
	     //double*pe,double*pf,double*pg,double*ph,double*pmiss2)
{   
    double *p3, *p4, *p5, *p6, *p7, *p8;
    double *pc, *pd, *pe, *pf, *pg, *ph;
    double *pmiss1, *pmiss2;
    
    p3 = evt1.p3;
    p4 = evt1.p4;
    p5 = evt1.p5;
    p6 = evt1.p6;
    p7 = evt1.p7;
    p8 = evt1.p8;

    pc = evt2.p3;
    pd = evt2.p4;
    pe = evt2.p5;
    pf = evt2.p6;
    pg = evt2.p7;
    ph = evt2.p8;

    pmiss1 = evt1.pmiss;
    pmiss2 = evt2.pmiss;

    double E1,  E2,  E3,  E4,  E5,  E6,  E7,  E8; 
    double p1x, p2x, p3x, p4x, p5x, p6x, p7x, p8x;
    double p1y, p2y, p3y, p4y, p5y, p6y, p7y, p8y;
    double p1z, p2z, p3z, p4z, p5z, p6z, p7z, p8z;
    double Ea,  Eb,  Ec,  Ed,  Ee,  Ef,  Eg,  Eh; 
    double pax, pbx, pcx, pdx, pex, pfx, pgx, phx;
    double pay, pby, pcy, pdy, pey, pfy, pgy, phy;
    double paz, pbz, pcz, pdz, pez, pfz, pgz, phz;

    E3 = p3[0]; p3x = p3[1]; p3y = p3[2]; p3z = p3[3];
    E4 = p4[0]; p4x = p4[1]; p4y = p4[2]; p4z = p4[3];
    E5 = p5[0]; p5x = p5[1]; p5y = p5[2]; p5z = p5[3];
    E6 = p6[0]; p6x = p6[1]; p6y = p6[2]; p6z = p6[3];
    E7 = p7[0]; p7x = p7[1]; p7y = p7[2]; p7z = p7[3];
    E8 = p8[0]; p8x = p8[1]; p8y = p8[2]; p8z = p8[3];
    Ec = pc[0]; pcx = pc[1]; pcy = pc[2]; pcz = pc[3];
    Ed = pd[0]; pdx = pd[1]; pdy = pd[2]; pdz = pd[3]; 
    Ee = pe[0]; pex = pe[1]; pey = pe[2]; pez = pe[3];
    Ef = pf[0]; pfx = pf[1]; pfy = pf[2]; pfz = pf[3];
    Eg = pg[0]; pgx = pg[1]; pgy = pg[2]; pgz = pg[3];
    Eh = ph[0]; phx = ph[1]; phy = ph[2]; phz = ph[3];

    double PmissEvt1x = pmiss1[1];
    double PmissEvt1y = pmiss1[2];
    double PmissEvt2x = pmiss2[1];
    double PmissEvt2y = pmiss2[2];

    double m3 = mass2(E3, p3x, p3y, p3z);
    double m4 = mass2(E4, p4x, p4y, p4z);
    double m5 = mass2(E5, p5x, p5y, p5z);
    double m6 = mass2(E6, p6x, p6y, p6z);
    double m7 = mass2(E7, p7x, p7y, p7z);
    double m8 = mass2(E8, p8x, p8y, p8z);
    double mc = mass2(Ec, pcx, pcy, pcz);
    double md = mass2(Ed, pdx, pdy, pdz);
    double me = mass2(Ee, pex, pey, pez);
    double mf = mass2(Ef, pfx, pfy, pfz);
    double mg = mass2(Eg, pgx, pgy, pgz);
    double mh = mass2(Eh, phx, phy, phz);
    
    double array13by4[52] = {(m4-m3)/2,-E3,E4,0,(mc-m3)/2,-E3,0,Ec,(md-m3)/2,-E3,0,0,(m4+m6-m3-m5)/2+E4*E6-E3*E5-p4x*p6x-p4y*p6y-p4z*p6z+p3x*p5x+p3y*p5y+p3z*p5z,-E3-E5,E4+E6,0,(mc+me-m3-m5)/2+Ec*Ee-E3*E5-pcx*pex-pcy*pey-pcz*pez+p3x*p5x+p3y*p5y+p3z*p5z,-E3-E5,0,Ec+Ee,(md+mf-m3-m5)/2+Ed*Ef-E3*E5-pdx*pfx-pdy*pfy-pdz*pfz+p3x*p5x+p3y*p5y+p3z*p5z,-E3-E5,0,0,(m4+m6+m8-m3-m5-m7)/2+E4*E6+E6*E8+E4*E8-E3*E5-E5*E7-E3*E7-p4x*p6x-p4y*p6y-p4z*p6z-p6x*p8x-p6y*p8y-p6z*p8z-p4x*p8x-p4y*p8y-p4z*p8z+p3x*p5x+p3y*p5y+p3z*p5z+p5x*p7x+p5y*p7y+p5z*p7z+p3x*p7x+p3y*p7y+p3z*p7z,-E3-E5-E7,E4+E6+E8,0,(mc+me+mg-m3-m5-m7)/2+Ec*Ee+Ee*Eg+Ec*Eg-E3*E5-E5*E7-E3*E7-pcx*pex-pcy*pey-pcz*pez-pex*pgx-pey*pgy-pez*pgz-pcx*pgx-pcy*pgy-pcz*pgz+p3x*p5x+p3y*p5y+p3z*p5z+p5x*p7x+p5y*p7y+p5z*p7z+p3x*p7x+p3y*p7y+p3z*p7z,-E3-E5-E7,0,Ec+Ee+Eg,(md+mf+mh-m3-m5-m7)/2+Ed*Ef+Ef*Eh+Ed*Eh-E3*E5-E5*E7-E3*E7-pdx*pfx-pdy*pfy-pdz*pfz-pfx*phx-pfy*phy-pfz*phz-pdx*phx-pdy*phy-pdz*phz+p3x*p5x+p3y*p5y+p3z*p5z+p5x*p7x+p5y*p7y+p5z*p7z+p3x*p7x+p3y*p7y+p3z*p7z,-E3-E5-E7,0,0,PmissEvt1x,0,0,0,PmissEvt1y,0,0,0,PmissEvt2x,0,0,0,PmissEvt2y,0,0,0};

    double array13by13[169] = {-p3x,-p3y,-p3z,p4x,p4y,p4z,0,0,0,0,0,0,0,-p3x,-p3y,-p3z,0,0,0,pcx,pcy,pcz,0,0,0,0,-p3x,-p3y,-p3z,0,0,0,0,0,0,pdx,pdy,pdz,-Ed,-p3x-p5x,-p3y-p5y,-p3z-p5z,p4x+p6x,p4y+p6y,p4z+p6z,0,0,0,0,0,0,0,-p3x-p5x,-p3y-p5y,-p3z-p5z,0,0,0,pcx+pex,pcy+pey,pcz+pez,0,0,0,0,-p3x-p5x,-p3y-p5y,-p3z-p5z,0,0,0,0,0,0,pdx+pfx,pdy+pfy,pdz+pfz,-Ed-Ef,-p3x-p5x-p7x,-p3y-p5y-p7y,-p3z-p5z-p7z,p4x+p6x+p8x,p4y+p6y+p8y,p4z+p6z+p8z,0,0,0,0,0,0,0,-p3x-p5x-p7x,-p3y-p5y-p7y,-p3z-p5z-p7z,0,0,0,pcx+pex+pgx,pcy+pey+pgy,pcz+pez+pgz,0,0,0,0,-p3x-p5x-p7x,-p3y-p5y-p7y,-p3z-p5z-p7z,0,0,0,0,0,0,pdx+pfx+phx,pdy+pfy+phy,pdz+pfz+phz,-Ed-Ef-Eh,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0};



    TMatrixT<double> mat13by4(13,4,array13by4);
    TMatrixT<double> mat13by13(13,13,array13by13);

    mat13by13.Invert();

    TMatrixT<double> transMat13by4(4,13);
    transMat13by4.Transpose(mat13by4);

    TMatrixT<double> L(13,4);
    L.MultT(mat13by13,transMat13by4); //The linear system matrix

//Construct energyMatA from equation E1^2-p1x^2-p1y^2-p1z^2-(E2^2-p2x^2-p2y^2-p2z^2)=0:
    TMatrixT<double> energyMatA(4,4);

//const
    energyMatA[3][3] = -pow(L[0][0],2)-pow(L[1][0],2)-pow(L[2][0],2)+pow(L[3][0],2)+pow(L[4][0],2)+pow(L[5][0],2);
//E1
    energyMatA[3][0] = -(L[0][0])*(L[0][1])-(L[1][0])*(L[1][1])-(L[2][0])*(L[2][1])+(L[3][0])*(L[3][1])+(L[4][0])*(L[4][1])+(L[5][0])*(L[5][1]);
//E2
    energyMatA[3][1] = -(L[0][0])*(L[0][2])-(L[1][0])*(L[1][2])-(L[2][0])*(L[2][2])+(L[3][0])*(L[3][2])+(L[4][0])*(L[4][2])+(L[5][0])*(L[5][2]);
//Ea
    energyMatA[3][2] = -(L[0][0])*(L[0][3])-(L[1][0])*(L[1][3])-(L[2][0])*(L[2][3])+(L[3][0])*(L[3][3])+(L[4][0])*(L[4][3])+(L[5][0])*(L[5][3]);
//E1*E2
    energyMatA[1][0] = -(L[0][1])*(L[0][2])-(L[1][1])*(L[1][2])-(L[2][1])*(L[2][2])+(L[3][1])*(L[3][2])+(L[4][1])*(L[4][2])+(L[5][1])*(L[5][2]);
//E1*Ea
    energyMatA[2][0] = -(L[0][1])*(L[0][3])-(L[1][1])*(L[1][3])-(L[2][1])*(L[2][3])+(L[3][1])*(L[3][3])+(L[4][1])*(L[4][3])+(L[5][1])*(L[5][3]);
//E2*Ea
    energyMatA[2][1] = -(L[0][2])*(L[0][3])-(L[1][2])*(L[1][3])-(L[2][2])*(L[2][3])+(L[3][2])*(L[3][3])+(L[4][2])*(L[4][3])+(L[5][2])*(L[5][3]);
//E1^2
    energyMatA[0][0] = 1-pow(L[0][1],2)-pow(L[1][1],2)-pow(L[2][1],2)+pow(L[3][1],2)+pow(L[4][1],2)+pow(L[5][1],2);
//E2^2
    energyMatA[1][1] = -1-pow(L[0][2],2)-pow(L[1][2],2)-pow(L[2][2],2)+pow(L[3][2],2)+pow(L[4][2],2)+pow(L[5][2],2);
//Ea^2
    energyMatA[2][2] = -pow(L[0][3],2)-pow(L[1][3],2)-pow(L[2][3],2)+pow(L[3][3],2)+pow(L[4][3],2)+pow(L[5][3],2);


//Symmetrize energyMatA
    energyMatA[0][1] = energyMatA[1][0]; 
    energyMatA[0][2] = energyMatA[2][0];
    energyMatA[0][3] = energyMatA[3][0];
    energyMatA[1][2] = energyMatA[2][1];
    energyMatA[1][3] = energyMatA[3][1];
    energyMatA[2][3] = energyMatA[3][2];

//*************************************************

//Construct energyMatB from equation E1^2-p1x^2-p1y^2-p1z^2-(Ea^2-pax^2-pay^2-paz^2)=0:
    TMatrixT<double> energyMatB(4,4);

//const
    energyMatB[3][3] = -pow(L[0][0],2)-pow(L[1][0],2)-pow(L[2][0],2)+pow(L[6][0],2)+pow(L[7][0],2)+pow(L[8][0],2);
//E1
    energyMatB[3][0] = -(L[0][0])*(L[0][1])-(L[1][0])*(L[1][1])-(L[2][0])*(L[2][1])+(L[6][0])*(L[6][1])+(L[7][0])*(L[7][1])+(L[8][0])*(L[8][1]);
//E2
    energyMatB[3][1] = -(L[0][0])*(L[0][2])-(L[1][0])*(L[1][2])-(L[2][0])*(L[2][2])+(L[6][0])*(L[6][2])+(L[7][0])*(L[7][2])+(L[8][0])*(L[8][2]);
//Ea
    energyMatB[3][2] = -(L[0][0])*(L[0][3])-(L[1][0])*(L[1][3])-(L[2][0])*(L[2][3])+(L[6][0])*(L[6][3])+(L[7][0])*(L[7][3])+(L[8][0])*(L[8][3]);
//E1*E2
    energyMatB[1][0] = -(L[0][1])*(L[0][2])-(L[1][1])*(L[1][2])-(L[2][1])*(L[2][2])+(L[6][1])*(L[6][2])+(L[7][1])*(L[7][2])+(L[8][1])*(L[8][2]);
//E1*Ea
    energyMatB[2][0] = -(L[0][1])*(L[0][3])-(L[1][1])*(L[1][3])-(L[2][1])*(L[2][3])+(L[6][1])*(L[6][3])+(L[7][1])*(L[7][3])+(L[8][1])*(L[8][3]);
//E2*Ea
    energyMatB[2][1] = -(L[0][2])*(L[0][3])-(L[1][2])*(L[1][3])-(L[2][2])*(L[2][3])+(L[6][2])*(L[6][3])+(L[7][2])*(L[7][3])+(L[8][2])*(L[8][3]);
//E1^2
    energyMatB[0][0] = 1-pow(L[0][1],2)-pow(L[1][1],2)-pow(L[2][1],2)+pow(L[6][1],2)+pow(L[7][1],2)+pow(L[8][1],2);
//E2^2
    energyMatB[1][1] = -pow(L[0][2],2)-pow(L[1][2],2)-pow(L[2][2],2)+pow(L[6][2],2)+pow(L[7][2],2)+pow(L[8][2],2);
//Ea^2
    energyMatB[2][2] = -1-pow(L[0][3],2)-pow(L[1][3],2)-pow(L[2][3],2)+pow(L[6][3],2)+pow(L[7][3],2)+pow(L[8][3],2);


//Symmetrize energyMatB
    energyMatB[0][1] = energyMatB[1][0]; 
    energyMatB[0][2] = energyMatB[2][0];
    energyMatB[0][3] = energyMatB[3][0];
    energyMatB[1][2] = energyMatB[2][1];
    energyMatB[1][3] = energyMatB[3][1];
    energyMatB[2][3] = energyMatB[3][2];


//*************************************************
//Construct energyMatC from equation E1^2-p1x^2-p1y^2-p1z^2-(Eb^2-pbx^2-pby^2-pbz^2)=0:
    TMatrixT<double> energyMatC(4,4);
//const
    energyMatC[3][3] = -pow(L[0][0],2)-pow(L[1][0],2)-pow(L[2][0],2)+pow(L[9][0],2)+pow(L[10][0],2)+pow(L[11][0],2)-pow(L[12][0],2);
//E1
    energyMatC[3][0] = -(L[0][0])*(L[0][1])-(L[1][0])*(L[1][1])-(L[2][0])*(L[2][1])+(L[9][0])*(L[9][1])+(L[10][0])*(L[10][1])+(L[11][0])*(L[11][1])-(L[12][0])*(L[12][1]);
//E2
    energyMatC[3][1] = -(L[0][0])*(L[0][2])-(L[1][0])*(L[1][2])-(L[2][0])*(L[2][2])+(L[9][0])*(L[9][2])+(L[10][0])*(L[10][2])+(L[11][0])*(L[11][2])-(L[12][0])*(L[12][2]);
//Ea
    energyMatC[3][2] = -(L[0][0])*(L[0][3])-(L[1][0])*(L[1][3])-(L[2][0])*(L[2][3])+(L[9][0])*(L[9][3])+(L[10][0])*(L[10][3])+(L[11][0])*(L[11][3])-(L[12][0])*(L[12][3]);
//E1*E2
    energyMatC[1][0] = -(L[0][1])*(L[0][2])-(L[1][1])*(L[1][2])-(L[2][1])*(L[2][2])+(L[9][1])*(L[9][2])+(L[10][1])*(L[10][2])+(L[11][1])*(L[11][2])-(L[12][1])*(L[12][2]);
//E1*Ea
    energyMatC[2][0] = -(L[0][1])*(L[0][3])-(L[1][1])*(L[1][3])-(L[2][1])*(L[2][3])+(L[9][1])*(L[9][3])+(L[10][1])*(L[10][3])+(L[11][1])*(L[11][3])-(L[12][1])*(L[12][3]);
//E2*Ea
    energyMatC[2][1] = -(L[0][2])*(L[0][3])-(L[1][2])*(L[1][3])-(L[2][2])*(L[2][3])+(L[9][2])*(L[9][3])+(L[10][2])*(L[10][3])+(L[11][2])*(L[11][3])-(L[12][2])*(L[12][3]);
//E1^2
    energyMatC[0][0] = 1-pow(L[0][1],2)-pow(L[1][1],2)-pow(L[2][1],2)+pow(L[9][1],2)+pow(L[10][1],2)+pow(L[11][1],2)-pow(L[12][1],2);
//E2^2
    energyMatC[1][1] = -pow(L[0][2],2)-pow(L[1][2],2)-pow(L[2][2],2)+pow(L[9][2],2)+pow(L[10][2],2)+pow(L[11][2],2)-pow(L[12][2],2);
//Ea^2
    energyMatC[2][2] = -pow(L[0][3],2)-pow(L[1][3],2)-pow(L[2][3],2)+pow(L[9][3],2)+pow(L[10][3],2)+pow(L[11][3],2)-pow(L[12][3],2);

   
//Symmetrize energyMatC
    energyMatC[0][1] = energyMatC[1][0]; 
    energyMatC[0][2] = energyMatC[2][0];
    energyMatC[0][3] = energyMatC[3][0];
    energyMatC[1][2] = energyMatC[2][1];
    energyMatC[1][3] = energyMatC[3][1];
    energyMatC[2][3] = energyMatC[3][2];


    double coeff[30];
    double p1a[3][48],p2a[3][48],paa[3][48],pba[3][48];

    int scheme,i,nallsols[3],npsols[3];

    npsols[0]=0;
    npsols[1]=0;
    npsols[2]=0;
//We solve the system three times, each time keeping a different variable for the polynomial equation, to avoid missing solutions

    for ( scheme = 0; scheme < 3; scheme ++ )
    {  
      if( scheme == 0)
      {     
         i = 0;
         coeff[i+0] = energyMatA[3][3];
         coeff[i+1] = 2*energyMatA[2][3];
         coeff[i+2] = energyMatA[2][2];
         coeff[i+3] = 2*energyMatA[1][3];
         coeff[i+4] = 2*energyMatA[1][2];
         coeff[i+5] = energyMatA[1][1];
         coeff[i+6] = 2*energyMatA[0][3];
         coeff[i+7] = 2*energyMatA[0][2];
         coeff[i+8] = 2*energyMatA[0][1];
         coeff[i+9] = energyMatA[0][0];
     
         i = 10;
         coeff[i+0] = energyMatB[3][3];
         coeff[i+1] = 2*energyMatB[2][3];
         coeff[i+2] = energyMatB[2][2];
         coeff[i+3] = 2*energyMatB[1][3];
         coeff[i+4] = 2*energyMatB[1][2];
         coeff[i+5] = energyMatB[1][1];
         coeff[i+6] = 2*energyMatB[0][3];
         coeff[i+7] = 2*energyMatB[0][2];
         coeff[i+8] = 2*energyMatB[0][1];
         coeff[i+9] = energyMatB[0][0];

         i = 20;
         coeff[i+0] = energyMatC[3][3];
         coeff[i+1] = 2*energyMatC[2][3];
         coeff[i+2] = energyMatC[2][2];
         coeff[i+3] = 2*energyMatC[1][3];
         coeff[i+4] = 2*energyMatC[1][2];
         coeff[i+5] = energyMatC[1][1];
         coeff[i+6] = 2*energyMatC[0][3];
         coeff[i+7] = 2*energyMatC[0][2];
         coeff[i+8] = 2*energyMatC[0][1];
         coeff[i+9] = energyMatC[0][0];
      }  
      if ( scheme == 1 )
      {
         i=0;
         coeff[i+0] = energyMatA[3][3];
         coeff[i+1] = 2*energyMatA[0][3];
         coeff[i+2] = energyMatA[0][0];
         coeff[i+3] = 2*energyMatA[1][3];
         coeff[i+4] = 2*energyMatA[1][0];
         coeff[i+5] = energyMatA[1][1];
         coeff[i+6] = 2*energyMatA[2][3];
         coeff[i+7] = 2*energyMatA[2][0];
         coeff[i+8] = 2*energyMatA[2][1];
         coeff[i+9] = energyMatA[2][2];

         i = 10;
         coeff[i+0] = energyMatB[3][3];
         coeff[i+1] = 2*energyMatB[0][3];
         coeff[i+2] = energyMatB[0][0];
         coeff[i+3] = 2*energyMatB[1][3];
         coeff[i+4] = 2*energyMatB[1][0];
         coeff[i+5] = energyMatB[1][1];
         coeff[i+6] = 2*energyMatB[2][3];
         coeff[i+7] = 2*energyMatB[2][0];
         coeff[i+8] = 2*energyMatB[2][1];
         coeff[i+9] = energyMatB[2][2];

         i = 20;
         coeff[i+0] = energyMatC[3][3];
         coeff[i+1] = 2*energyMatC[0][3];
         coeff[i+2] = energyMatC[0][0];
         coeff[i+3] = 2*energyMatC[1][3];
         coeff[i+4] = 2*energyMatC[1][0];
         coeff[i+5] = energyMatC[1][1];
         coeff[i+6] = 2*energyMatC[2][3];
         coeff[i+7] = 2*energyMatC[2][0];
         coeff[i+8] = 2*energyMatC[2][1];
         coeff[i+9] = energyMatC[2][2];
      }
      if( scheme == 2)
      {  
         i = 0;
         coeff[i+0] = energyMatA[3][3];
         coeff[i+1] = 2*energyMatA[1][3];
         coeff[i+2] = energyMatA[1][1];
         coeff[i+3] = 2*energyMatA[2][3];
         coeff[i+4] = 2*energyMatA[2][1];
         coeff[i+5] = energyMatA[2][2];
         coeff[i+6] = 2*energyMatA[0][3];
         coeff[i+7] = 2*energyMatA[0][1];
         coeff[i+8] = 2*energyMatA[0][2];
         coeff[i+9] = energyMatA[0][0];

         i = 10;
         coeff[i+0] = energyMatB[3][3];
         coeff[i+1] = 2*energyMatB[1][3];
         coeff[i+2] = energyMatB[1][1];
         coeff[i+3] = 2*energyMatB[2][3];
         coeff[i+4] = 2*energyMatB[2][1];
         coeff[i+5] = energyMatB[2][2];
         coeff[i+6] = 2*energyMatB[0][3];
         coeff[i+7] = 2*energyMatB[0][1];
         coeff[i+8] = 2*energyMatB[0][2];
         coeff[i+9] = energyMatB[0][0];

         i = 20;
         coeff[i+0] = energyMatC[3][3];
         coeff[i+1] = 2*energyMatC[1][3];
         coeff[i+2] = energyMatC[1][1];
         coeff[i+3] = 2*energyMatC[2][3];
         coeff[i+4] = 2*energyMatC[2][1];
         coeff[i+5] = energyMatC[2][2];
         coeff[i+6] = 2*energyMatC[0][3];
         coeff[i+7] = 2*energyMatC[0][1];
         coeff[i+8] = 2*energyMatC[0][2];
         coeff[i+9] = energyMatC[0][0];
      }
      double solutions[36];
      nallsols[scheme]  = solve3quad(coeff, solutions);
      npsols[scheme] = 0;
      
      for( int i = 0; i < nallsols[scheme]; i ++ ) 
      {
         if( scheme == 0)
         {
            E1 = solutions[i*3 + 2];
            E2 = solutions[i*3 + 1];
            Ea = solutions[i*3 + 0];
         }
         if( scheme == 1 )
         {
            E1 = solutions[i*3 + 0];
            E2 = solutions[i*3 + 1];
            Ea = solutions[i*3 + 2];
         }
         if( scheme == 2 )
         {
            E1 = solutions[i*3 + 2];
            E2 = solutions[i*3 + 0];
            Ea = solutions[i*3 + 1];
         }
         p1x = L[0][0] + L[0][1]*E1 + L[0][2]*E2 + L[0][3]*Ea;
         p1y = L[1][0] + L[1][1]*E1 + L[1][2]*E2 + L[1][3]*Ea;
         p1z = L[2][0] + L[2][1]*E1 + L[2][2]*E2 + L[2][3]*Ea;
         p2x = L[3][0] + L[3][1]*E1 + L[3][2]*E2 + L[3][3]*Ea;
         p2y = L[4][0] + L[4][1]*E1 + L[4][2]*E2 + L[4][3]*Ea;
         p2z = L[5][0] + L[5][1]*E1 + L[5][2]*E2 + L[5][3]*Ea;
         pax = L[6][0] + L[6][1]*E1 + L[6][2]*E2 + L[6][3]*Ea;
         pay = L[7][0] + L[7][1]*E1 + L[7][2]*E2 + L[7][3]*Ea;
         paz = L[8][0] + L[8][1]*E1 + L[8][2]*E2 + L[8][3]*Ea;
         pbx = L[9][0] + L[9][1]*E1 + L[9][2]*E2 + L[9][3]*Ea;
         pby = L[10][0] + L[10][1]*E1 + L[10][2]*E2 + L[10][3]*Ea;
         pbz = L[11][0] + L[11][1]*E1 + L[11][2]*E2 + L[11][3]*Ea;
         Eb  = L[12][0] + L[12][1]*E1 + L[12][2]*E2 + L[12][3]*Ea;
         double mn2 = mass2(E1, p1x, p1y, p1z);
        
         if( E1>0 && E2>0 && Ea>0 && Eb>0 && mn2>0 )
         { 
            int isol = npsols[scheme];
            p1a[scheme][isol*4] = E1; 
            p1a[scheme][isol*4+1] = p1x; 
            p1a[scheme][isol*4+2] = p1y; 
            p1a[scheme][isol*4+3] = p1z;

            p2a[scheme][isol*4] = E2;
            p2a[scheme][isol*4+1] = p2x; 
            p2a[scheme][isol*4+2] = p2y;
            p2a[scheme][isol*4+3] = p2z;

            paa[scheme][isol*4] = Ea; 
            paa[scheme][isol*4+1] = pax;
            paa[scheme][isol*4+2] = pay;
            paa[scheme][isol*4+3] = paz;

            pba[scheme][isol*4] = Eb;
            pba[scheme][isol*4+1] = pbx;
            pba[scheme][isol*4+2] = pby;
            pba[scheme][isol*4+3] = pbz;
            npsols[scheme]++;
         }
      }
    }
    if( npsols[0]>=npsols[1] && npsols[0]>=npsols[2] ) scheme = 0;
    else if( npsols[1]>=npsols[2]) scheme = 1;
    else scheme = 2;
    
    for( int isol = 0; isol < npsols[scheme]; isol ++ )
    {
       for( int i = 0; i < 4; i ++ ) 
       {
          p1[isol][i] = p1a[scheme][isol*4+i];
          p2[isol][i] = p2a[scheme][isol*4+i];
          q1[isol][i] = paa[scheme][isol*4+i];
          q2[isol][i] = pba[scheme][isol*4+i];
       }
    }   
    nsols = npsols[scheme];
    return;
}


int solve_3_2(double a0,double a1,double a2,double a3,double a4,double a5,double a6,double a7,double a8,double * solutions)
{
    double a[21],wr[21],wi[21];
    a[0]=1.;a[1]=a8;a[2]=a7;a[3]=a6;a[4]=a5;a[5]=a4;a[6]=a3;
    a[7]=a2;a[8]=a1;a[9]=a0;
    int n=9;
    rpoly_ak1(a, &n, wr,wi);
    int nsols=0;
    /*if (debug==1) for (int i=0;i<n;i++)
    {
        cout.setf(ios::showpoint);
        cout.precision(15);
        cout.setf(ios::showpos);
        cout.width(18);
        if ((wr[i] != 0.0) || (wi[i] != 0.0))
            cout << wr[i] << " " << wi[i] << "I" << endl;
     }*/
    for (int i=0;i<n;i++)
       if (fabs(wi[i]) < 2)
       {   
          nsols++;  
          solutions[(nsols-1)*3]=wr[i];
       }
   

    return nsols;
   
}
int solve_2_2(double aa0,double aa1,double aa2,double aa3,double aa4,double aa5,double aa6,double aa7,double aa8,double bb0,double bb1,double bb2,double bb3,double bb4,double bb5,double bb6,double bb7,double * solutions)
{  
    /*if(debug==1) 
    {    
        cout<<"in function solve_2_2"<<endl;
        cout<<aa0<<"\t"<<aa1<<"\t"<<aa2<<"\t"<<aa3<<"\t"<<aa4<<"\t"<<
aa5<<"\t"<<aa6<<"\t"<<aa7<<"\t"<<aa8<<endl;
        cout<<bb0<<"\t"<<bb1<<"\t"<<bb2<<"\t"<<bb3<<"\t"<<bb4<<"\t"<<
bb5<<"\t"<<bb6<<"\t"<<bb7<<"\t"<<endl;
    }*/
    double a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12;
    double b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12;
    double c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12;
    a0=aa0;a1=aa1;a2=aa2;a3=aa3;a4=aa4;a5=aa5;a6=aa6;a7=aa7;a8=aa8;
    b0=bb0;b1=bb1;b2=bb2;b3=bb3;b4=bb4;b5=bb5;b6=bb6;b7=bb7;
    c0=b0*b0*b0 - a7*b0*b0*b4 + a4*b0*b4*b4 - a0*b4*b4*b4 - 2*a4*b0*b0*b7 + a7*a7*b0*b0*b7 + 
 3*a0*b0*b4*b7 - a4*a7*b0*b4*b7 + a0*a7*b4*b4*b7 + a4*a4*b0*b7*b7 - 
 2*a0*a7*b0*b7*b7 - a0*a4*b4*b7*b7 + a0*a0*b7*b7*b7;
    c1= -2*a4*b0*b0 + a7*a7*b0*b0 + 3*b0*b0*b1 + 3*a0*b0*b4 - a4*a7*b0*b4 - 
 a8*b0*b0*b4 - 2*a7*b0*b1*b4 + a0*a7*b4*b4 + a5*b0*b4*b4 + a4*b1*b4*b4 - 
 a1*b4*b4*b4 - a7*b0*b0*b5 + 2*a4*b0*b4*b5 - 3*a0*b4*b4*b5 + 2*a4*a4*b0*b7 - 
 4*a0*a7*b0*b7 - 2*a5*b0*b0*b7 + 2*a7*a8*b0*b0*b7 - 4*a4*b0*b1*b7 + 
 2*a7*a7*b0*b1*b7 - 2*a0*a4*b4*b7 + 3*a1*b0*b4*b7 - a5*a7*b0*b4*b7 - 
 a4*a8*b0*b4*b7 + 3*a0*b1*b4*b7 - a4*a7*b1*b4*b7 + a1*a7*b4*b4*b7 + 
 a0*a8*b4*b4*b7 + 3*a0*b0*b5*b7 - a4*a7*b0*b5*b7 + 2*a0*a7*b4*b5*b7 + 
 3*a0*a0*b7*b7 + 2*a4*a5*b0*b7*b7 - 2*a1*a7*b0*b7*b7 - 2*a0*a8*b0*b7*b7 + 
 a4*a4*b1*b7*b7 - 2*a0*a7*b1*b7*b7 - a1*a4*b4*b7*b7 - a0*a5*b4*b7*b7 - 
 a0*a4*b5*b7*b7 + 2*a0*a1*b7*b7*b7;
    c2= a4*a4*b0 - 2*a0*a7*b0 - 2*a5*b0*b0 + 2*a7*a8*b0*b0 - 4*a4*b0*b1 + 
 2*a7*a7*b0*b1 + 3*b0*b1*b1 + 3*b0*b0*b2 - a0*a4*b4 + 3*a1*b0*b4 - a5*a7*b0*b4 - 
 a4*a8*b0*b4 + 3*a0*b1*b4 - a4*a7*b1*b4 - 2*a8*b0*b1*b4 - a7*b1*b1*b4 - 
 2*a7*b0*b2*b4 + a1*a7*b4*b4 + a0*a8*b4*b4 + a6*b0*b4*b4 + a5*b1*b4*b4 + 
 a4*b2*b4*b4 - a2*b4*b4*b4 + 3*a0*b0*b5 - a4*a7*b0*b5 - a8*b0*b0*b5 - 
 2*a7*b0*b1*b5 + 2*a0*a7*b4*b5 + 2*a5*b0*b4*b5 + 2*a4*b1*b4*b5 - 
 3*a1*b4*b4*b5 + a4*b0*b5*b5 - 3*a0*b4*b5*b5 - a7*b0*b0*b6 + 2*a4*b0*b4*b6 - 
 3*a0*b4*b4*b6 + 3*a0*a0*b7 + 4*a4*a5*b0*b7 - 4*a1*a7*b0*b7 - 4*a0*a8*b0*b7 - 
 2*a6*b0*b0*b7 + a8*a8*b0*b0*b7 + 2*a4*a4*b1*b7 - 4*a0*a7*b1*b7 - 4*a5*b0*b1*b7 + 
 4*a7*a8*b0*b1*b7 - 2*a4*b1*b1*b7 + a7*a7*b1*b1*b7 - 4*a4*b0*b2*b7 + 
 2*a7*a7*b0*b2*b7 - 2*a1*a4*b4*b7 - 2*a0*a5*b4*b7 + 3*a2*b0*b4*b7 - 
 a6*a7*b0*b4*b7 - a5*a8*b0*b4*b7 + 3*a1*b1*b4*b7 - a5*a7*b1*b4*b7 - 
 a4*a8*b1*b4*b7 + 3*a0*b2*b4*b7 - a4*a7*b2*b4*b7 + a2*a7*b4*b4*b7 + 
 a1*a8*b4*b4*b7 - 2*a0*a4*b5*b7 + 3*a1*b0*b5*b7 - a5*a7*b0*b5*b7 - 
 a4*a8*b0*b5*b7 + 3*a0*b1*b5*b7 - a4*a7*b1*b5*b7 + 2*a1*a7*b4*b5*b7 + 
 2*a0*a8*b4*b5*b7 + a0*a7*b5*b5*b7 + 3*a0*b0*b6*b7 - a4*a7*b0*b6*b7 + 
 2*a0*a7*b4*b6*b7 + 6*a0*a1*b7*b7 + a5*a5*b0*b7*b7 + 2*a4*a6*b0*b7*b7 - 
 2*a2*a7*b0*b7*b7 - 2*a1*a8*b0*b7*b7 + 2*a4*a5*b1*b7*b7 - 2*a1*a7*b1*b7*b7 - 
 2*a0*a8*b1*b7*b7 + a4*a4*b2*b7*b7 - 2*a0*a7*b2*b7*b7 - a2*a4*b4*b7*b7 - 
 a1*a5*b4*b7*b7 - a0*a6*b4*b7*b7 - a1*a4*b5*b7*b7 - a0*a5*b5*b7*b7 - 
 a0*a4*b6*b7*b7 + a1*a1*b7*b7*b7 + 2*a0*a2*b7*b7*b7;
   c3= a0*a0 + 2*a4*a5*b0 - 2*a1*a7*b0 - 2*a0*a8*b0 - 2*a6*b0*b0 + a8*a8*b0*b0 + 
 a4*a4*b1 - 2*a0*a7*b1 - 4*a5*b0*b1 + 4*a7*a8*b0*b1 - 2*a4*b1*b1 + a7*a7*b1*b1 + 
 b1*b1*b1 - 4*a4*b0*b2 + 2*a7*a7*b0*b2 + 6*b0*b1*b2 + 3*b0*b0*b3 - a1*a4*b4 - 
 a0*a5*b4 + 3*a2*b0*b4 - a6*a7*b0*b4 - a5*a8*b0*b4 + 3*a1*b1*b4 - 
 a5*a7*b1*b4 - a4*a8*b1*b4 - a8*b1*b1*b4 + 3*a0*b2*b4 - a4*a7*b2*b4 - 
 2*a8*b0*b2*b4 - 2*a7*b1*b2*b4 - 2*a7*b0*b3*b4 + a2*a7*b4*b4 + a1*a8*b4*b4 + 
 a6*b1*b4*b4 + a5*b2*b4*b4 + a4*b3*b4*b4 - a3*b4*b4*b4 - a0*a4*b5 + 3*a1*b0*b5 - 
 a5*a7*b0*b5 - a4*a8*b0*b5 + 3*a0*b1*b5 - a4*a7*b1*b5 - 2*a8*b0*b1*b5 - 
 a7*b1*b1*b5 - 2*a7*b0*b2*b5 + 2*a1*a7*b4*b5 + 2*a0*a8*b4*b5 + 2*a6*b0*b4*b5 + 
 2*a5*b1*b4*b5 + 2*a4*b2*b4*b5 - 3*a2*b4*b4*b5 + a0*a7*b5*b5 + a5*b0*b5*b5 + 
 a4*b1*b5*b5 - 3*a1*b4*b5*b5 - a0*b5*b5*b5 + 3*a0*b0*b6 - a4*a7*b0*b6 - 
 a8*b0*b0*b6 - 2*a7*b0*b1*b6 + 2*a0*a7*b4*b6 + 2*a5*b0*b4*b6 + 2*a4*b1*b4*b6 - 
 3*a1*b4*b4*b6 + 2*a4*b0*b5*b6 - 6*a0*b4*b5*b6 + 6*a0*a1*b7 + 2*a5*a5*b0*b7 + 
 4*a4*a6*b0*b7 - 4*a2*a7*b0*b7 - 4*a1*a8*b0*b7 + 4*a4*a5*b1*b7 - 
 4*a1*a7*b1*b7 - 4*a0*a8*b1*b7 - 4*a6*b0*b1*b7 + 2*a8*a8*b0*b1*b7 - 
 2*a5*b1*b1*b7 + 2*a7*a8*b1*b1*b7 + 2*a4*a4*b2*b7 - 4*a0*a7*b2*b7 - 
 4*a5*b0*b2*b7 + 4*a7*a8*b0*b2*b7 - 4*a4*b1*b2*b7 + 2*a7*a7*b1*b2*b7 - 
 4*a4*b0*b3*b7 + 2*a7*a7*b0*b3*b7 - 2*a2*a4*b4*b7 - 2*a1*a5*b4*b7 - 
 2*a0*a6*b4*b7 + 3*a3*b0*b4*b7 - a6*a8*b0*b4*b7 + 3*a2*b1*b4*b7 - 
 a6*a7*b1*b4*b7 - a5*a8*b1*b4*b7 + 3*a1*b2*b4*b7 - a5*a7*b2*b4*b7 - 
 a4*a8*b2*b4*b7 + 3*a0*b3*b4*b7 - a4*a7*b3*b4*b7 + a3*a7*b4*b4*b7 + 
 a2*a8*b4*b4*b7 - 2*a1*a4*b5*b7 - 2*a0*a5*b5*b7 + 3*a2*b0*b5*b7 - 
 a6*a7*b0*b5*b7 - a5*a8*b0*b5*b7 + 3*a1*b1*b5*b7 - a5*a7*b1*b5*b7 - 
 a4*a8*b1*b5*b7 + 3*a0*b2*b5*b7 - a4*a7*b2*b5*b7 + 2*a2*a7*b4*b5*b7 + 
 2*a1*a8*b4*b5*b7 + a1*a7*b5*b5*b7 + a0*a8*b5*b5*b7 - 2*a0*a4*b6*b7 + 
 3*a1*b0*b6*b7 - a5*a7*b0*b6*b7 - a4*a8*b0*b6*b7 + 3*a0*b1*b6*b7 - 
 a4*a7*b1*b6*b7 + 2*a1*a7*b4*b6*b7 + 2*a0*a8*b4*b6*b7 + 2*a0*a7*b5*b6*b7 + 
 3*a1*a1*b7*b7 + 6*a0*a2*b7*b7 + 2*a5*a6*b0*b7*b7 - 2*a3*a7*b0*b7*b7 - 
 2*a2*a8*b0*b7*b7 + a5*a5*b1*b7*b7 + 2*a4*a6*b1*b7*b7 - 2*a2*a7*b1*b7*b7 - 
 2*a1*a8*b1*b7*b7 + 2*a4*a5*b2*b7*b7 - 2*a1*a7*b2*b7*b7 - 2*a0*a8*b2*b7*b7 + 
 a4*a4*b3*b7*b7 - 2*a0*a7*b3*b7*b7 - a3*a4*b4*b7*b7 - a2*a5*b4*b7*b7 - 
 a1*a6*b4*b7*b7 - a2*a4*b5*b7*b7 - a1*a5*b5*b7*b7 - a0*a6*b5*b7*b7 - 
 a1*a4*b6*b7*b7 - a0*a5*b6*b7*b7 + 2*a1*a2*b7*b7*b7 + 2*a0*a3*b7*b7*b7;
    c4= 2*a0*a1 + a5*a5*b0 + 2*a4*a6*b0 - 2*a2*a7*b0 - 2*a1*a8*b0 + 2*a4*a5*b1 - 
 2*a1*a7*b1 - 2*a0*a8*b1 - 4*a6*b0*b1 + 2*a8*a8*b0*b1 - 2*a5*b1*b1 + 
 2*a7*a8*b1*b1 + a4*a4*b2 - 2*a0*a7*b2 - 4*a5*b0*b2 + 4*a7*a8*b0*b2 - 
 4*a4*b1*b2 + 2*a7*a7*b1*b2 + 3*b1*b1*b2 + 3*b0*b2*b2 - 4*a4*b0*b3 + 
 2*a7*a7*b0*b3 + 6*b0*b1*b3 - a2*a4*b4 - a1*a5*b4 - a0*a6*b4 + 3*a3*b0*b4 - 
 a6*a8*b0*b4 + 3*a2*b1*b4 - a6*a7*b1*b4 - a5*a8*b1*b4 + 3*a1*b2*b4 - 
 a5*a7*b2*b4 - a4*a8*b2*b4 - 2*a8*b1*b2*b4 - a7*b2*b2*b4 + 3*a0*b3*b4 - 
 a4*a7*b3*b4 - 2*a8*b0*b3*b4 - 2*a7*b1*b3*b4 + a3*a7*b4*b4 + a2*a8*b4*b4 + 
 a6*b2*b4*b4 + a5*b3*b4*b4 - a1*a4*b5 - a0*a5*b5 + 3*a2*b0*b5 - a6*a7*b0*b5 - 
 a5*a8*b0*b5 + 3*a1*b1*b5 - a5*a7*b1*b5 - a4*a8*b1*b5 - a8*b1*b1*b5 + 
 3*a0*b2*b5 - a4*a7*b2*b5 - 2*a8*b0*b2*b5 - 2*a7*b1*b2*b5 - 2*a7*b0*b3*b5 + 
 2*a2*a7*b4*b5 + 2*a1*a8*b4*b5 + 2*a6*b1*b4*b5 + 2*a5*b2*b4*b5 + 
 2*a4*b3*b4*b5 - 3*a3*b4*b4*b5 + a1*a7*b5*b5 + a0*a8*b5*b5 + a6*b0*b5*b5 + 
 a5*b1*b5*b5 + a4*b2*b5*b5 - 3*a2*b4*b5*b5 - a1*b5*b5*b5 - a0*a4*b6 + 3*a1*b0*b6 - 
 a5*a7*b0*b6 - a4*a8*b0*b6 + 3*a0*b1*b6 - a4*a7*b1*b6 - 2*a8*b0*b1*b6 - 
 a7*b1*b1*b6 - 2*a7*b0*b2*b6 + 2*a1*a7*b4*b6 + 2*a0*a8*b4*b6 + 2*a6*b0*b4*b6 + 
 2*a5*b1*b4*b6 + 2*a4*b2*b4*b6 - 3*a2*b4*b4*b6 + 2*a0*a7*b5*b6 + 
 2*a5*b0*b5*b6 + 2*a4*b1*b5*b6 - 6*a1*b4*b5*b6 - 3*a0*b5*b5*b6 + a4*b0*b6*b6 - 
 3*a0*b4*b6*b6 + 3*a1*a1*b7 + 6*a0*a2*b7 + 4*a5*a6*b0*b7 - 4*a3*a7*b0*b7 - 
 4*a2*a8*b0*b7 + 2*a5*a5*b1*b7 + 4*a4*a6*b1*b7 - 4*a2*a7*b1*b7 - 
 4*a1*a8*b1*b7 - 2*a6*b1*b1*b7 + a8*a8*b1*b1*b7 + 4*a4*a5*b2*b7 - 
 4*a1*a7*b2*b7 - 4*a0*a8*b2*b7 - 4*a6*b0*b2*b7 + 2*a8*a8*b0*b2*b7 - 
 4*a5*b1*b2*b7 + 4*a7*a8*b1*b2*b7 - 2*a4*b2*b2*b7 + a7*a7*b2*b2*b7 + 
 2*a4*a4*b3*b7 - 4*a0*a7*b3*b7 - 4*a5*b0*b3*b7 + 4*a7*a8*b0*b3*b7 - 
 4*a4*b1*b3*b7 + 2*a7*a7*b1*b3*b7 - 2*a3*a4*b4*b7 - 2*a2*a5*b4*b7 - 
 2*a1*a6*b4*b7 + 3*a3*b1*b4*b7 - a6*a8*b1*b4*b7 + 3*a2*b2*b4*b7 - 
 a6*a7*b2*b4*b7 - a5*a8*b2*b4*b7 + 3*a1*b3*b4*b7 - a5*a7*b3*b4*b7 - 
 a4*a8*b3*b4*b7 + a3*a8*b4*b4*b7 - 2*a2*a4*b5*b7 - 2*a1*a5*b5*b7 - 
 2*a0*a6*b5*b7 + 3*a3*b0*b5*b7 - a6*a8*b0*b5*b7 + 3*a2*b1*b5*b7 - 
 a6*a7*b1*b5*b7 - a5*a8*b1*b5*b7 + 3*a1*b2*b5*b7 - a5*a7*b2*b5*b7 - 
 a4*a8*b2*b5*b7 + 3*a0*b3*b5*b7 - a4*a7*b3*b5*b7 + 2*a3*a7*b4*b5*b7 + 
 2*a2*a8*b4*b5*b7 + a2*a7*b5*b5*b7 + a1*a8*b5*b5*b7 - 2*a1*a4*b6*b7 - 
 2*a0*a5*b6*b7 + 3*a2*b0*b6*b7 - a6*a7*b0*b6*b7 - a5*a8*b0*b6*b7 + 
 3*a1*b1*b6*b7 - a5*a7*b1*b6*b7 - a4*a8*b1*b6*b7 + 3*a0*b2*b6*b7 - 
 a4*a7*b2*b6*b7 + 2*a2*a7*b4*b6*b7 + 2*a1*a8*b4*b6*b7 + 2*a1*a7*b5*b6*b7 + 
 2*a0*a8*b5*b6*b7 + a0*a7*b6*b6*b7 + 6*a1*a2*b7*b7 + 6*a0*a3*b7*b7 + 
 a6*a6*b0*b7*b7 - 2*a3*a8*b0*b7*b7 + 2*a5*a6*b1*b7*b7 - 2*a3*a7*b1*b7*b7 - 
 2*a2*a8*b1*b7*b7 + a5*a5*b2*b7*b7 + 2*a4*a6*b2*b7*b7 - 2*a2*a7*b2*b7*b7 - 
 2*a1*a8*b2*b7*b7 + 2*a4*a5*b3*b7*b7 - 2*a1*a7*b3*b7*b7 - 2*a0*a8*b3*b7*b7 - 
 a3*a5*b4*b7*b7 - a2*a6*b4*b7*b7 - a3*a4*b5*b7*b7 - a2*a5*b5*b7*b7 - 
 a1*a6*b5*b7*b7 - a2*a4*b6*b7*b7 - a1*a5*b6*b7*b7 - a0*a6*b6*b7*b7 + a2*a2*b7*b7*b7 + 
 2*a1*a3*b7*b7*b7;
    c5= a1*a1 + 2*a0*a2 + 2*a5*a6*b0 - 2*a3*a7*b0 - 2*a2*a8*b0 + a5*a5*b1 + 
 2*a4*a6*b1 - 2*a2*a7*b1 - 2*a1*a8*b1 - 2*a6*b1*b1 + a8*a8*b1*b1 + 2*a4*a5*b2 - 
 2*a1*a7*b2 - 2*a0*a8*b2 - 4*a6*b0*b2 + 2*a8*a8*b0*b2 - 4*a5*b1*b2 + 
 4*a7*a8*b1*b2 - 2*a4*b2*b2 + a7*a7*b2*b2 + 3*b1*b2*b2 + a4*a4*b3 - 2*a0*a7*b3 - 
 4*a5*b0*b3 + 4*a7*a8*b0*b3 - 4*a4*b1*b3 + 2*a7*a7*b1*b3 + 3*b1*b1*b3 + 
 6*b0*b2*b3 - a3*a4*b4 - a2*a5*b4 - a1*a6*b4 + 3*a3*b1*b4 - a6*a8*b1*b4 + 
 3*a2*b2*b4 - a6*a7*b2*b4 - a5*a8*b2*b4 - a8*b2*b2*b4 + 3*a1*b3*b4 - 
 a5*a7*b3*b4 - a4*a8*b3*b4 - 2*a8*b1*b3*b4 - 2*a7*b2*b3*b4 + a3*a8*b4*b4 + 
 a6*b3*b4*b4 - a2*a4*b5 - a1*a5*b5 - a0*a6*b5 + 3*a3*b0*b5 - a6*a8*b0*b5 + 
 3*a2*b1*b5 - a6*a7*b1*b5 - a5*a8*b1*b5 + 3*a1*b2*b5 - a5*a7*b2*b5 - 
 a4*a8*b2*b5 - 2*a8*b1*b2*b5 - a7*b2*b2*b5 + 3*a0*b3*b5 - a4*a7*b3*b5 - 
 2*a8*b0*b3*b5 - 2*a7*b1*b3*b5 + 2*a3*a7*b4*b5 + 2*a2*a8*b4*b5 + 
 2*a6*b2*b4*b5 + 2*a5*b3*b4*b5 + a2*a7*b5*b5 + a1*a8*b5*b5 + a6*b1*b5*b5 + 
 a5*b2*b5*b5 + a4*b3*b5*b5 - 3*a3*b4*b5*b5 - a2*b5*b5*b5 - a1*a4*b6 - a0*a5*b6 + 
 3*a2*b0*b6 - a6*a7*b0*b6 - a5*a8*b0*b6 + 3*a1*b1*b6 - a5*a7*b1*b6 - 
 a4*a8*b1*b6 - a8*b1*b1*b6 + 3*a0*b2*b6 - a4*a7*b2*b6 - 2*a8*b0*b2*b6 - 
 2*a7*b1*b2*b6 - 2*a7*b0*b3*b6 + 2*a2*a7*b4*b6 + 2*a1*a8*b4*b6 + 
 2*a6*b1*b4*b6 + 2*a5*b2*b4*b6 + 2*a4*b3*b4*b6 - 3*a3*b4*b4*b6 + 
 2*a1*a7*b5*b6 + 2*a0*a8*b5*b6 + 2*a6*b0*b5*b6 + 2*a5*b1*b5*b6 + 
 2*a4*b2*b5*b6 - 6*a2*b4*b5*b6 - 3*a1*b5*b5*b6 + a0*a7*b6*b6 + a5*b0*b6*b6 + 
 a4*b1*b6*b6 - 3*a1*b4*b6*b6 - 3*a0*b5*b6*b6 + 6*a1*a2*b7 + 6*a0*a3*b7 + 
 2*a6*a6*b0*b7 - 4*a3*a8*b0*b7 + 4*a5*a6*b1*b7 - 4*a3*a7*b1*b7 - 
 4*a2*a8*b1*b7 + 2*a5*a5*b2*b7 + 4*a4*a6*b2*b7 - 4*a2*a7*b2*b7 - 
 4*a1*a8*b2*b7 - 4*a6*b1*b2*b7 + 2*a8*a8*b1*b2*b7 - 2*a5*b2*b2*b7 + 
 2*a7*a8*b2*b2*b7 + 4*a4*a5*b3*b7 - 4*a1*a7*b3*b7 - 4*a0*a8*b3*b7 - 
 4*a6*b0*b3*b7 + 2*a8*a8*b0*b3*b7 - 4*a5*b1*b3*b7 + 4*a7*a8*b1*b3*b7 - 
 4*a4*b2*b3*b7 + 2*a7*a7*b2*b3*b7 - 2*a3*a5*b4*b7 - 2*a2*a6*b4*b7 + 
 3*a3*b2*b4*b7 - a6*a8*b2*b4*b7 + 3*a2*b3*b4*b7 - a6*a7*b3*b4*b7 - 
 a5*a8*b3*b4*b7 - 2*a3*a4*b5*b7 - 2*a2*a5*b5*b7 - 2*a1*a6*b5*b7 + 
 3*a3*b1*b5*b7 - a6*a8*b1*b5*b7 + 3*a2*b2*b5*b7 - a6*a7*b2*b5*b7 - 
 a5*a8*b2*b5*b7 + 3*a1*b3*b5*b7 - a5*a7*b3*b5*b7 - a4*a8*b3*b5*b7 + 
 2*a3*a8*b4*b5*b7 + a3*a7*b5*b5*b7 + a2*a8*b5*b5*b7 - 2*a2*a4*b6*b7 - 
 2*a1*a5*b6*b7 - 2*a0*a6*b6*b7 + 3*a3*b0*b6*b7 - a6*a8*b0*b6*b7 + 
 3*a2*b1*b6*b7 - a6*a7*b1*b6*b7 - a5*a8*b1*b6*b7 + 3*a1*b2*b6*b7 - 
 a5*a7*b2*b6*b7 - a4*a8*b2*b6*b7 + 3*a0*b3*b6*b7 - a4*a7*b3*b6*b7 + 
 2*a3*a7*b4*b6*b7 + 2*a2*a8*b4*b6*b7 + 2*a2*a7*b5*b6*b7 + 2*a1*a8*b5*b6*b7 + 
 a1*a7*b6*b6*b7 + a0*a8*b6*b6*b7 + 3*a2*a2*b7*b7 + 6*a1*a3*b7*b7 + a6*a6*b1*b7*b7 - 
 2*a3*a8*b1*b7*b7 + 2*a5*a6*b2*b7*b7 - 2*a3*a7*b2*b7*b7 - 2*a2*a8*b2*b7*b7 + 
 a5*a5*b3*b7*b7 + 2*a4*a6*b3*b7*b7 - 2*a2*a7*b3*b7*b7 - 2*a1*a8*b3*b7*b7 - 
 a3*a6*b4*b7*b7 - a3*a5*b5*b7*b7 - a2*a6*b5*b7*b7 - a3*a4*b6*b7*b7 - 
 a2*a5*b6*b7*b7 - a1*a6*b6*b7*b7 + 2*a2*a3*b7*b7*b7;
    c6= 2*a1*a2 + 2*a0*a3 + a6*a6*b0 - 2*a3*a8*b0 + 2*a5*a6*b1 - 2*a3*a7*b1 - 
 2*a2*a8*b1 + a5*a5*b2 + 2*a4*a6*b2 - 2*a2*a7*b2 - 2*a1*a8*b2 - 4*a6*b1*b2 + 
 2*a8*a8*b1*b2 - 2*a5*b2*b2 + 2*a7*a8*b2*b2 + b2*b2*b2 + 2*a4*a5*b3 - 2*a1*a7*b3 - 
 2*a0*a8*b3 - 4*a6*b0*b3 + 2*a8*a8*b0*b3 - 4*a5*b1*b3 + 4*a7*a8*b1*b3 - 
 4*a4*b2*b3 + 2*a7*a7*b2*b3 + 6*b1*b2*b3 + 3*b0*b3*b3 - a3*a5*b4 - a2*a6*b4 + 
 3*a3*b2*b4 - a6*a8*b2*b4 + 3*a2*b3*b4 - a6*a7*b3*b4 - a5*a8*b3*b4 - 
 2*a8*b2*b3*b4 - a7*b3*b3*b4 - a3*a4*b5 - a2*a5*b5 - a1*a6*b5 + 3*a3*b1*b5 - 
 a6*a8*b1*b5 + 3*a2*b2*b5 - a6*a7*b2*b5 - a5*a8*b2*b5 - a8*b2*b2*b5 + 
 3*a1*b3*b5 - a5*a7*b3*b5 - a4*a8*b3*b5 - 2*a8*b1*b3*b5 - 2*a7*b2*b3*b5 + 
 2*a3*a8*b4*b5 + 2*a6*b3*b4*b5 + a3*a7*b5*b5 + a2*a8*b5*b5 + a6*b2*b5*b5 + 
 a5*b3*b5*b5 - a3*b5*b5*b5 - a2*a4*b6 - a1*a5*b6 - a0*a6*b6 + 3*a3*b0*b6 - 
 a6*a8*b0*b6 + 3*a2*b1*b6 - a6*a7*b1*b6 - a5*a8*b1*b6 + 3*a1*b2*b6 - 
 a5*a7*b2*b6 - a4*a8*b2*b6 - 2*a8*b1*b2*b6 - a7*b2*b2*b6 + 3*a0*b3*b6 - 
 a4*a7*b3*b6 - 2*a8*b0*b3*b6 - 2*a7*b1*b3*b6 + 2*a3*a7*b4*b6 + 
 2*a2*a8*b4*b6 + 2*a6*b2*b4*b6 + 2*a5*b3*b4*b6 + 2*a2*a7*b5*b6 + 
 2*a1*a8*b5*b6 + 2*a6*b1*b5*b6 + 2*a5*b2*b5*b6 + 2*a4*b3*b5*b6 - 
 6*a3*b4*b5*b6 - 3*a2*b5*b5*b6 + a1*a7*b6*b6 + a0*a8*b6*b6 + a6*b0*b6*b6 + 
 a5*b1*b6*b6 + a4*b2*b6*b6 - 3*a2*b4*b6*b6 - 3*a1*b5*b6*b6 - a0*b6*b6*b6 + 
 3*a2*a2*b7 + 6*a1*a3*b7 + 2*a6*a6*b1*b7 - 4*a3*a8*b1*b7 + 4*a5*a6*b2*b7 - 
 4*a3*a7*b2*b7 - 4*a2*a8*b2*b7 - 2*a6*b2*b2*b7 + a8*a8*b2*b2*b7 + 2*a5*a5*b3*b7 + 
 4*a4*a6*b3*b7 - 4*a2*a7*b3*b7 - 4*a1*a8*b3*b7 - 4*a6*b1*b3*b7 + 
 2*a8*a8*b1*b3*b7 - 4*a5*b2*b3*b7 + 4*a7*a8*b2*b3*b7 - 2*a4*b3*b3*b7 + 
 a7*a7*b3*b3*b7 - 2*a3*a6*b4*b7 + 3*a3*b3*b4*b7 - a6*a8*b3*b4*b7 - 
 2*a3*a5*b5*b7 - 2*a2*a6*b5*b7 + 3*a3*b2*b5*b7 - a6*a8*b2*b5*b7 + 
 3*a2*b3*b5*b7 - a6*a7*b3*b5*b7 - a5*a8*b3*b5*b7 + a3*a8*b5*b5*b7 - 
 2*a3*a4*b6*b7 - 2*a2*a5*b6*b7 - 2*a1*a6*b6*b7 + 3*a3*b1*b6*b7 - 
 a6*a8*b1*b6*b7 + 3*a2*b2*b6*b7 - a6*a7*b2*b6*b7 - a5*a8*b2*b6*b7 + 
 3*a1*b3*b6*b7 - a5*a7*b3*b6*b7 - a4*a8*b3*b6*b7 + 2*a3*a8*b4*b6*b7 + 
 2*a3*a7*b5*b6*b7 + 2*a2*a8*b5*b6*b7 + a2*a7*b6*b6*b7 + a1*a8*b6*b6*b7 + 
 6*a2*a3*b7*b7 + a6*a6*b2*b7*b7 - 2*a3*a8*b2*b7*b7 + 2*a5*a6*b3*b7*b7 - 
 2*a3*a7*b3*b7*b7 - 2*a2*a8*b3*b7*b7 - a3*a6*b5*b7*b7 - a3*a5*b6*b7*b7 - 
 a2*a6*b6*b7*b7 + a3*a3*b7*b7*b7;
    c7= a2*a2 + 2*a1*a3 + a6*a6*b1 - 2*a3*a8*b1 + 2*a5*a6*b2 - 2*a3*a7*b2 - 
 2*a2*a8*b2 - 2*a6*b2*b2 + a8*a8*b2*b2 + a5*a5*b3 + 2*a4*a6*b3 - 2*a2*a7*b3 - 
 2*a1*a8*b3 - 4*a6*b1*b3 + 2*a8*a8*b1*b3 - 4*a5*b2*b3 + 4*a7*a8*b2*b3 + 
 3*b2*b2*b3 - 2*a4*b3*b3 + a7*a7*b3*b3 + 3*b1*b3*b3 - a3*a6*b4 + 3*a3*b3*b4 - 
 a6*a8*b3*b4 - a8*b3*b3*b4 - a3*a5*b5 - a2*a6*b5 + 3*a3*b2*b5 - a6*a8*b2*b5 + 
 3*a2*b3*b5 - a6*a7*b3*b5 - a5*a8*b3*b5 - 2*a8*b2*b3*b5 - a7*b3*b3*b5 + 
 a3*a8*b5*b5 + a6*b3*b5*b5 - a3*a4*b6 - a2*a5*b6 - a1*a6*b6 + 3*a3*b1*b6 - 
 a6*a8*b1*b6 + 3*a2*b2*b6 - a6*a7*b2*b6 - a5*a8*b2*b6 - a8*b2*b2*b6 + 
 3*a1*b3*b6 - a5*a7*b3*b6 - a4*a8*b3*b6 - 2*a8*b1*b3*b6 - 2*a7*b2*b3*b6 + 
 2*a3*a8*b4*b6 + 2*a6*b3*b4*b6 + 2*a3*a7*b5*b6 + 2*a2*a8*b5*b6 + 
 2*a6*b2*b5*b6 + 2*a5*b3*b5*b6 - 3*a3*b5*b5*b6 + a2*a7*b6*b6 + a1*a8*b6*b6 + 
 a6*b1*b6*b6 + a5*b2*b6*b6 + a4*b3*b6*b6 - 3*a3*b4*b6*b6 - 3*a2*b5*b6*b6 - 
 a1*b6*b6*b6 + 6*a2*a3*b7 + 2*a6*a6*b2*b7 - 4*a3*a8*b2*b7 + 4*a5*a6*b3*b7 - 
 4*a3*a7*b3*b7 - 4*a2*a8*b3*b7 - 4*a6*b2*b3*b7 + 2*a8*a8*b2*b3*b7 - 
 2*a5*b3*b3*b7 + 2*a7*a8*b3*b3*b7 - 2*a3*a6*b5*b7 + 3*a3*b3*b5*b7 - 
 a6*a8*b3*b5*b7 - 2*a3*a5*b6*b7 - 2*a2*a6*b6*b7 + 3*a3*b2*b6*b7 - 
 a6*a8*b2*b6*b7 + 3*a2*b3*b6*b7 - a6*a7*b3*b6*b7 - a5*a8*b3*b6*b7 + 
 2*a3*a8*b5*b6*b7 + a3*a7*b6*b6*b7 + a2*a8*b6*b6*b7 + 3*a3*a3*b7*b7 + 
 a6*a6*b3*b7*b7 - 2*a3*a8*b3*b7*b7 - a3*a6*b6*b7*b7;
    c8= 2*a2*a3 + a6*a6*b2 - 2*a3*a8*b2 + 2*a5*a6*b3 - 2*a3*a7*b3 - 2*a2*a8*b3 - 
 4*a6*b2*b3 + 2*a8*a8*b2*b3 - 2*a5*b3*b3 + 2*a7*a8*b3*b3 + 3*b2*b3*b3 - 
 a3*a6*b5 + 3*a3*b3*b5 - a6*a8*b3*b5 - a8*b3*b3*b5 - a3*a5*b6 - a2*a6*b6 + 
 3*a3*b2*b6 - a6*a8*b2*b6 + 3*a2*b3*b6 - a6*a7*b3*b6 - a5*a8*b3*b6 - 
 2*a8*b2*b3*b6 - a7*b3*b3*b6 + 2*a3*a8*b5*b6 + 2*a6*b3*b5*b6 + a3*a7*b6*b6 + 
 a2*a8*b6*b6 + a6*b2*b6*b6 + a5*b3*b6*b6 - 3*a3*b5*b6*b6 - a2*b6*b6*b6 + 3*a3*a3*b7 + 
 2*a6*a6*b3*b7 - 4*a3*a8*b3*b7 - 2*a6*b3*b3*b7 + a8*a8*b3*b3*b7 - 2*a3*a6*b6*b7 + 
 3*a3*b3*b6*b7 - a6*a8*b3*b6*b7 + a3*a8*b6*b6*b7;
    c9= a3*a3 + a6*a6*b3 - 2*a3*a8*b3 - 2*a6*b3*b3 + a8*a8*b3*b3 + b3*b3*b3 - a3*a6*b6 + 
 3*a3*b3*b6 - a6*a8*b3*b6 - a8*b3*b3*b6 + a3*a8*b6*b6 + a6*b3*b6*b6 - a3*b6*b6*b6;
    //cout<<"cs:"<<c0<<"  "<<c1<<"  "<<c2<<"  "<<c3<<"  "<<c4<<"  "<<c5<<"  "<<c6<<"  "<<c7<<"  "<<c8<<"  "<<c9<<endl;
    int nsols=solve_3_2(c0/c9,c1/c9,c2/c9,c3/c9,c4/c9,c5/c9,c6/c9,c7/c9,c8/c9,solutions);
       
    c0=-(a7*b0) + b0*b5 + a0*b7 - b0*b6*b7;
    c1=a0 - a8*b0 - a7*b1 + b1*b5 + b0*b6 + a1*b7 - b1*b6*b7;
    c2=a1 - a8*b1 - a7*b2 + b2*b5 + b1*b6 + a2*b7 - b2*b6*b7;
    c3=a2 - a8*b2 - a7*b3 + b3*b5 + b2*b6 + a3*b7 - b3*b6*b7;
    c4=a3 - a8*b3 + b3*b6;
    c5=-b0 - a7*b4 + b4*b5 + a4*b7 - b4*b6*b7;
    c6=a4 - b1 - a8*b4 - a7*b5 + b5*b5 + b4*b6 + a5*b7 - b5*b6*b7;
    c7=a5 - b2 - a8*b5 - a7*b6 + 2*b5*b6 + a6*b7 - b6*b6*b7;
    c8=a6 - b3 - a8*b6 + b6*b6;
    c9=-b4 + b5*b7 - b6*b7*b7;
    c0=c0/c9;c1=c1/c9;c2=c2/c9;c3=c3/c9;c4=c4/c9;c5=c5/c9;c6=c6/c9;c7=c7/c9;c8=c8/c9;
    a0=c0;a1=c1;a2=c2;a3=c3;a4=c4;a5=c5;a6=c6;a7=c7;a8=c8;
    
    c0=-b0 + a0*b7;
    c1=a0 - b1 + a1*b7;
    c2=a1 - b2 + a2*b7;
    c3=a2 - b3 + a3*b7;
    c4=a3 + a4*b7;
    c5=a4;
    c6=-b4 + a5*b7;
    c7=a5 - b5 + a6*b7;
    c8=a6 - b6 + a7*b7;
    c9=a7 + a8*b7;
    c10=a8;
    c0=c0/c10;c1=c1/c10;c2=c2/c10;c3=c3/c10;c4=c4/c10;c5=c5/c10;c6=c6/c10;c7=c7/c10;c8=c8/c10;
    c9=c9/c10;
    b0=c0;b1=c1;b2=c2;b3=c3;b4=c4;b5=c5;b6=c6;b7=c7;b8=c8;b9=c9;

    c0=-(a5*b0) + b0*b4 + a0*b6 - b0*b5*b9;
    c1=-(a6*b0) - a5*b1 + b1*b4 + b0*b5 + a1*b6 + a0*b7 - b1*b5*b9;
    c2=-(a7*b0) - a6*b1 - a5*b2 + b2*b4 + b1*b5 + a2*b6 + a1*b7 + a0*b8 - 
 b2*b5*b9;
    c3=-(a8*b0) - a7*b1 - a6*b2 - a5*b3 + b3*b4 + b2*b5 + a3*b6 + a2*b7 + 
 a1*b8 + a0*b9 - b3*b5*b9;
    c4=a0 - a8*b1 - a7*b2 - a6*b3 - a5*b4 + b4*b4 + b3*b5 + a4*b6 + a3*b7 + 
 a2*b8 + a1*b9 - b4*b5*b9;
    c5=a1 - a8*b2 - a7*b3 - a6*b4 - a5*b5 + 2*b4*b5 + a4*b7 + a3*b8 + a2*b9 - 
 b5*b5*b9;
    c6=a2 - a8*b3 - a7*b4 - a6*b5 + b5*b5 + a4*b8 + a3*b9;
    c7=a3 - a8*b4 - a7*b5 + a4*b9;
    c8=a4 - a8*b5;
    c9=-b0 + b4*b6 - b5*b6*b9;
    c10=-b1 + b5*b6 + b4*b7 - b5*b7*b9;
    c11=-b2 + b5*b7 + b4*b8 - b5*b8*b9;
    c12=-b3 + b5*b8 + b4*b9 - b5*b9*b9;
    c0=c0/c12;c1=c1/c12;c2=c2/c12;c3=c3/c12;c4=c4/c12;c5=c5/c12;c6=c6/c12;c7=c7/c12;c8=c8/c12;
    c9=c9/c12;c10=c10/c12;c11=c11/c12;
    a0=b0;a1=b1;a2=b2;a3=b3;a4=b4;a5=b5;a6=b6;a7=b7;a8=b8;a9=b9;
    b0=c0;b1=c1;b2=c2;b3=c3;b4=c4;b5=c5;b6=c6;b7=c7;b8=c8;b9=c9;b10=c10;b11=c11;

    for(int i=0;i<nsols;i++)
    { 
       double q1,q2;
       double x=solutions[i*3+0];
       //cout<<"yn= "<<(-a0 - a1*x - a2*x*x - a3*x*x*x - a4*x*x*x*x - a5*x*x*x*x*x)<<endl;
       //cout<<"yd= "<<(a6 + a7*x + a8*x*x + a9*x*x*x + x*x*x*x)<<endl;
       double y= (-a0 - a1*x - a2*x*x - a3*x*x*x - a4*x*x*x*x - a5*x*x*x*x*x)/
 (a6 + a7*x + a8*x*x + a9*x*x*x + x*x*x*x);
//apply a Newton's method
       for(int inewton=0;inewton<2;inewton++)
       {
        TMatrixD jacob(2,2);
        q1=aa0 + aa1*x + aa2*x*x + aa3*x*x*x + aa4*y + aa5*x*y + aa6*x*x*y + aa7*y*y + 
 aa8*x*y*y + y*y*y;
        q2=bb0 + bb1*x + bb2*x*x + bb3*x*x*x + bb4*y + bb5*x*y + bb6*x*x*y + bb7*y*y + 
 x*y*y;
        jacob(0,0)=aa1 + 2*aa2*x + 3*aa3*x*x + aa5*y + 2*aa6*x*y + aa8*y*y;
        jacob(0,1)=aa4 + aa5*x + aa6*x*x + 2*aa7*y + 2*aa8*x*y + 3*y*y;
        jacob(1,0)=bb1 + 2*bb2*x + 3*bb3*x*x + bb5*y + 2*bb6*x*y + y*y;
        jacob(1,1)=bb4 + bb5*x + bb6*x*x + 2*bb7*y + 2*x*y;
        TVectorD F(2);
        F(0)=-q1;
        F(1)=-q2;
        TDecompLU lu(2);
        lu.SetMatrix(jacob);
        lu.Decompose();
        Bool_t ok;
        ok=lu.Solve(F);
        if(ok)
        {
           x=x+F(0);
           y=y+F(1);
        }
       }    
       solutions[i*3+0]=x;
       solutions[i*3+1]=y;
       //cout<<"y= "<<y<<endl;
    }

    return nsols;
    
}

int solve_1(double a0,double a1,double a2,double a3,double a4,double a5,double a6,double a7,double a8,double b0,double b1,double b2,double b3,double b4,double b5,double b6,double b7,double c0,double c1,double c2,double c3,double c4,double c5,double c6,double * solutions)
{
    /*cout<<a0<<"+x*"<<a1<<"+x*x*"<<a2<<"+y*"<<a3<<"+x*y*"
            <<a4<<"+y*y*"<<a5<<"+z*"<<a6<<"+z*x*"<<a7<<"+z*y*"<<a8<<"+z*z"<<endl;
    cout<<b0<<"+x*"<<b1<<"+x*x*"<<b2<<"+y*"<<b3<<"+x*y*"
            <<b4<<"+y*y*"<<b5<<"+z*"<<b6<<"+z*x*"<<b7<<"+z*y*"<<endl;
    cout<<c0<<"+x*"<<c1<<"+x*x*"<<c2<<"+y*"<<c3<<"+x*y*"
            <<c4<<"+y*y*"<<c5<<"+z*"<<c6<<"+z*x*"<<endl;*/
    /*if(debug==1) 
    {
       cout<<"in function solve_1"<<endl;
       cout<<a0<<"\t"<<a1<<"\t"<<a2<<"\t"<<a3<<"\t"<<a4<<"\t"<<
a5<<"\t"<<a6<<"\t"<<a7<<"\t"<<a8<<endl;
       cout<<b0<<"\t"<<b1<<"\t"<<b2<<"\t"<<b3<<"\t"<<b4<<"\t"<<
b5<<"\t"<<b6<<"\t"<<b7<<"\t"<<endl;
       cout<<c0<<"\t"<<c1<<"\t"<<c2<<"\t"<<c3<<"\t"<<c4<<"\t"<<
c5<<"\t"<<c6<<"\t"<<endl;
    }*/
    double d0,d1,d2,d3,d4,d5,d6,d7,d8,d9,d10;   
    d0=-(a6*b0) + b0*b3 + a0*b6 - b0*b5*b6 + b1*c0 - b4*b6*c0 - b3*b7*c0 + 
 2*b5*b6*b7*c0 - b2*c0*c6 + b4*b7*c0*c6 - b5*b7*b7*c0*c6;
    d1=-(a7*b0) - a6*b1 + b1*b3 + b0*b4 + a1*b6 - b1*b5*b6 + a0*b7 - b0*b5*b7 + 
 b2*c0 - b4*b7*c0 + b5*b7*b7*c0 + b1*c1 - b4*b6*c1 - b3*b7*c1 + 
 2*b5*b6*b7*c1 - b2*c1*c6 + b4*b7*c1*c6 - b5*b7*b7*c1*c6;
    d2=-(a7*b1) - a6*b2 + b2*b3 + b1*b4 + a2*b6 - b2*b5*b6 + a1*b7 - b1*b5*b7 + 
 b2*c1 - b4*b7*c1 + b5*b7*b7*c1 + b1*c2 - b4*b6*c2 - b3*b7*c2 + 
 2*b5*b6*b7*c2 - b2*c2*c6 + b4*b7*c2*c6 - b5*b7*b7*c2*c6;
    d3=-(a7*b2) + b2*b4 + a2*b7 - b2*b5*b7 + b2*c2 - b4*b7*c2 + b5*b7*b7*c2;
    d4=a0 - a8*b0 - a6*b3 + b3*b3 + b0*b5 + a3*b6 - b3*b5*b6 + b1*c3 - 
 b4*b6*c3 - b3*b7*c3 + 2*b5*b6*b7*c3 - b2*c3*c6 + b4*b7*c3*c6 - b5*b7*b7*c3*c6;
    d5=a1 - a8*b1 - a7*b3 - a6*b4 + 2*b3*b4 + b1*b5 + a4*b6 - b4*b5*b6 + 
 a3*b7 - b3*b5*b7 + b2*c3 - b4*b7*c3 + b5*b7*b7*c3 + b1*c4 - b4*b6*c4 - 
 b3*b7*c4 + 2*b5*b6*b7*c4 - b2*c4*c6 + b4*b7*c4*c6 - b5*b7*b7*c4*c6;
    d6=a2 - a8*b2 - a7*b4 + b4*b4 + b2*b5 + a4*b7 - b4*b5*b7 + b2*c4 - 
 b4*b7*c4 + b5*b7*b7*c4;
    d7=a3 - a8*b3 - a6*b5 + 2*b3*b5 + a5*b6 - b5*b5*b6 + b1*c5 - b4*b6*c5 - 
 b3*b7*c5 + 2*b5*b6*b7*c5 - b2*c5*c6 + b4*b7*c5*c6 - b5*b7*b7*c5*c6;
    d8=a4 - a8*b4 - a7*b5 + 2*b4*b5 + a5*b7 - b5*b5*b7 + b2*c5 - b4*b7*c5 + 
 b5*b7*b7*c5;
    d9=a5 - a8*b5 + b5*b5;
    d10=-b0 + b3*b6 - b5*b6*b6 + b1*c6 - b4*b6*c6 - b3*b7*c6 + 2*b5*b6*b7*c6 - 
 b2*c6*c6 + b4*b7*c6*c6 - b5*b7*b7*c6*c6;
   
    double e0,e1,e2,e3,e4,e5,e6,e7,e8,e9,e10;
    double f0,f1,f2,f3,f4,f5,f6,f7,f8,f9;
    e0=-(a6*c0) + a8*b6*c0 + c0*c1 + b0*c3 - b7*c0*c3 - b6*c0*c4 - b0*b6*c5 + 
 2*b6*b7*c0*c5 + a0*c6 - a8*b0*c6 - c0*c2*c6 + b7*c0*c4*c6 - b7*b7*c0*c5*c6;
    e1=a0 - a8*b0 - a7*c0 + a8*b7*c0 - a6*c1 + a8*b6*c1 + c1*c1 + c0*c2 + 
 b1*c3 - b7*c1*c3 + b0*c4 - b7*c0*c4 - b6*c1*c4 - b1*b6*c5 - b0*b7*c5 + 
 b7*b7*c0*c5 + 2*b6*b7*c1*c5 + a1*c6 - a8*b1*c6 - c1*c2*c6 + b7*c1*c4*c6 - 
 b7*b7*c1*c5*c6;
    e2=a1 - a8*b1 - a7*c1 + a8*b7*c1 - a6*c2 + a8*b6*c2 + 2*c1*c2 + b2*c3 - 
 b7*c2*c3 + b1*c4 - b7*c1*c4 - b6*c2*c4 - b2*b6*c5 - b1*b7*c5 + b7*b7*c1*c5 + 
 2*b6*b7*c2*c5 + a2*c6 - a8*b2*c6 - c2*c2*c6 + b7*c2*c4*c6 - b7*b7*c2*c5*c6;
    e3=a2 - a8*b2 - a7*c2 + a8*b7*c2 + c2*c2 + b2*c4 - b7*c2*c4 - b2*b7*c5 + 
 b7*b7*c2*c5;
    e4=-(a6*c3) + b3*c3 + a8*b6*c3 + c1*c3 - b7*c3*c3 - b6*c3*c4 + b0*c5 - 
 b3*b6*c5 + 2*b6*b7*c3*c5 + a3*c6 - a8*b3*c6 - c2*c3*c6 + b7*c3*c4*c6 - 
 b7*b7*c3*c5*c6;
    e5=a3 - a8*b3 - a7*c3 + b4*c3 + a8*b7*c3 + c2*c3 - a6*c4 + b3*c4 + 
 a8*b6*c4 + c1*c4 - 2*b7*c3*c4 - b6*c4*c4 + b1*c5 - b4*b6*c5 - b3*b7*c5 + 
 b7*b7*c3*c5 + 2*b6*b7*c4*c5 + a4*c6 - a8*b4*c6 - c2*c4*c6 + b7*c4*c4*c6 - 
 b7*b7*c4*c5*c6;
    e6=a4 - a8*b4 - a7*c4 + b4*c4 + a8*b7*c4 + c2*c4 - b7*c4*c4 + b2*c5 - 
 b4*b7*c5 + b7*b7*c4*c5;
    e7=b5*c3 - a6*c5 + b3*c5 + a8*b6*c5 - b5*b6*c5 + c1*c5 - b7*c3*c5 - 
 b6*c4*c5 + 2*b6*b7*c5*c5 + a5*c6 - a8*b5*c6 - c2*c5*c6 + b7*c4*c5*c6 - 
 b7*b7*c5*c5*c6;
    e8=a5 - a8*b5 + b5*c4 - a7*c5 + b4*c5 + a8*b7*c5 - b5*b7*c5 + c2*c5 - 
 b7*c4*c5 + b7*b7*c5*c5;
    e9=b5*c5;
    e10=-c0 + b6*c3 - b6*b6*c5 + c1*c6 - b7*c3*c6 - b6*c4*c6 + 2*b6*b7*c5*c6 - 
 c2*c6*c6 + b7*c4*c6*c6 - b7*b7*c5*c6*c6;
    /*cout<<d0<<"\t"<<d1<<"\t"<<d2<<"\t"<<d3<<"\t"<<d4<<"\t"<<
d5<<"\t"<<d6<<"\t"<<d7<<"\t"<<d8<<"\t"<<d9<<"\t"<<d10<<endl;
    cout<<e0<<"\t"<<e1<<"\t"<<e2<<"\t"<<e3<<"\t"<<e4<<"\t"<<
e5<<"\t"<<e6<<"\t"<<e7<<"\t"<<e8<<"\t"<<e9<<"\t"<<e10<<endl;*/
  
    d0=d0/d10;d1=d1/d10;d2=d2/d10;d3=d3/d10;d4=d4/d10;d5=d5/d10;
    d6=d6/d10;d7=d7/d10;d8=d8/d10;d9=d9/d10;
    e0=e0/e10;e1=e1/e10;e2=e2/e10;e3=e3/e10;e4=e4/e10;e5=e5/e10;
    e6=e6/e10;e7=e7/e10;e8=e8/e10;e9=e9/e10;
    f0=d0-e0;f1=d1-e1;f2=d2-e2;f3=d3-e3;f4=d4-e4;f5=d5-e5;f6=d6-e6;f7=d7-e7;
    f8=d8-e8;f9=d9-e9;
    f0=f0/f9;f1=f1/f9;f2=f2/f9;f3=f3/f9;f4=f4/f9;f5=f5/f9;f6=f6/f9;f7=f7/f9;f8=f8/f9;
    
    double g0,g1,g2,g3,g4,g5,g6,g7,g8,g9;
    double h0,h1,h2,h3,h4,h5,h6,h7,h8;
    g0=-(b6*c0) + b0*c6;
    g1=b0 - b7*c0 - b6*c1 + b1*c6;
    g2=b1 - b7*c1 - b6*c2 + b2*c6;
    g3=b2 - b7*c2;
    g4=-c0 - b6*c3 + b3*c6;
    g5=b3 - c1 - b7*c3 - b6*c4 + b4*c6;
    g6=b4 - c2 - b7*c4;
    g7=-c3 - b6*c5 + b5*c6;
    g8=b5 - c4 - b7*c5;
    g9=-c5;
    //cout<<g0<<"\t"<<g1<<"\t"<<g2<<"\t"<<g3<<"\t"<<g4<<"\t"<<g5<<"\t"<<g6<<"\t"<<g7<<"\t"<<g8<<"\t"<<g9<<endl;
    g0=g0/g9;g1=g1/g9;g2=g2/g9;g3=g3/g9;g4=g4/g9;g5=g5/g9;g6=g6/g9;g7=g7/g9;g8=g8/g9;
    h0=f0-g0;h1=f1-g1;h2=f2-g2;h3=f3-g3;h4=f4-g4;h5=f5-g5;h6=f6-g6;h7=f7-g7;h8=f8-g8;
    h0=h0/h8;h1=h1/h8;h2=h2/h8;h3=h3/h8;h4=h4/h8;h5=h5/h8;h6=h6/h8;h7=h7/h8;
    int nsols=solve_2_2(f0,f1,f2,f3,f4,f5,f6,f7,f8,h0,h1,h2,h3,h4,h5,h6,h7,solutions);
    for (int i=0;i<nsols;i++) 
    {
      double x=solutions[i*3+0];
      double y=solutions[i*3+1];
      double z=(-(a6*c0) + a8*b6*c0 + c0*c1 + b0*c3 - b7*c0*c3 - b6*c0*c4 - b0*b6*c5 + 
  2*b6*b7*c0*c5 + a0*c6 - a8*b0*c6 - c0*c2*c6 + b7*c0*c4*c6 - b7*b7*c0*c5*c6 + 
  a0*x - a8*b0*x - a7*c0*x + a8*b7*c0*x - a6*c1*x + a8*b6*c1*x + c1*c1*x + 
  c0*c2*x + b1*c3*x - b7*c1*c3*x + b0*c4*x - b7*c0*c4*x - b6*c1*c4*x - 
  b1*b6*c5*x - b0*b7*c5*x + b7*b7*c0*c5*x + 2*b6*b7*c1*c5*x + a1*c6*x - 
  a8*b1*c6*x - c1*c2*c6*x + b7*c1*c4*c6*x - b7*b7*c1*c5*c6*x + a1*x*x - 
  a8*b1*x*x - a7*c1*x*x + a8*b7*c1*x*x - a6*c2*x*x + a8*b6*c2*x*x + 
  2*c1*c2*x*x + b2*c3*x*x - b7*c2*c3*x*x + b1*c4*x*x - b7*c1*c4*x*x - 
  b6*c2*c4*x*x - b2*b6*c5*x*x - b1*b7*c5*x*x + b7*b7*c1*c5*x*x + 
  2*b6*b7*c2*c5*x*x + a2*c6*x*x - a8*b2*c6*x*x - c2*c2*c6*x*x + 
  b7*c2*c4*c6*x*x - b7*b7*c2*c5*c6*x*x + a2*x*x*x - a8*b2*x*x*x - a7*c2*x*x*x + 
  a8*b7*c2*x*x*x + c2*c2*x*x*x + b2*c4*x*x*x - b7*c2*c4*x*x*x - b2*b7*c5*x*x*x + 
  b7*b7*c2*c5*x*x*x - a6*c3*y + b3*c3*y + a8*b6*c3*y + c1*c3*y - b7*c3*c3*y - 
  b6*c3*c4*y + b0*c5*y - b3*b6*c5*y + 2*b6*b7*c3*c5*y + a3*c6*y - 
  a8*b3*c6*y - c2*c3*c6*y + b7*c3*c4*c6*y - b7*b7*c3*c5*c6*y + a3*x*y - 
  a8*b3*x*y - a7*c3*x*y + b4*c3*x*y + a8*b7*c3*x*y + c2*c3*x*y - a6*c4*x*y + 
  b3*c4*x*y + a8*b6*c4*x*y + c1*c4*x*y - 2*b7*c3*c4*x*y - b6*c4*c4*x*y + 
  b1*c5*x*y - b4*b6*c5*x*y - b3*b7*c5*x*y + b7*b7*c3*c5*x*y + 
  2*b6*b7*c4*c5*x*y + a4*c6*x*y - a8*b4*c6*x*y - c2*c4*c6*x*y + 
  b7*c4*c4*c6*x*y - b7*b7*c4*c5*c6*x*y + a4*x*x*y - a8*b4*x*x*y - a7*c4*x*x*y + 
  b4*c4*x*x*y + a8*b7*c4*x*x*y + c2*c4*x*x*y - b7*c4*c4*x*x*y + b2*c5*x*x*y - 
  b4*b7*c5*x*x*y + b7*b7*c4*c5*x*x*y + b5*c3*y*y - a6*c5*y*y + b3*c5*y*y + 
  a8*b6*c5*y*y - b5*b6*c5*y*y + c1*c5*y*y - b7*c3*c5*y*y - b6*c4*c5*y*y + 
  2*b6*b7*c5*c5*y*y + a5*c6*y*y - a8*b5*c6*y*y - c2*c5*c6*y*y + 
  b7*c4*c5*c6*y*y - b7*b7*c5*c5*c6*y*y + a5*x*y*y - a8*b5*x*y*y + b5*c4*x*y*y - 
  a7*c5*x*y*y + b4*c5*x*y*y + a8*b7*c5*x*y*y - b5*b7*c5*x*y*y + c2*c5*x*y*y - 
  b7*c4*c5*x*y*y + b7*b7*c5*c5*x*y*y + b5*c5*y*y*y)/
 (c0 - b6*c3 + b6*b6*c5 - c1*c6 + b7*c3*c6 + b6*c4*c6 - 2*b6*b7*c5*c6 + 
  c2*c6*c6 - b7*c4*c6*c6 + b7*b7*c5*c6*c6);
     solutions[i*3+2]=z;
   }
   return nsols;
};
int solve3quad(double* coeff,double* solutions)
{
   double a0,a1,a2,a3,a4,a5,a6,a7,a8,a9;
   double b0,b1,b2,b3,b4,b5,b6,b7,b8,b9;
   double c0,c1,c2,c3,c4,c5,c6,c7,c8,c9;
   double solutions1[36];
   int i;
   a9=coeff[9]; 
   //cout<<"a9= "<<a9<<endl;
   a0=coeff[0]/a9;a1=coeff[1]/a9;a2=coeff[2]/a9;a3=coeff[3]/a9;a4=coeff[4]/a9;
   a5=coeff[5]/a9;a6=coeff[6]/a9;a7=coeff[7]/a9;a8=coeff[8]/a9;a9=1.;
   i=10;
   b9=coeff[19];
   //cout<<"b9= "<<b9<<endl;
   b0=coeff[i+0]/b9;b1=coeff[i+1]/b9;b2=coeff[i+2]/b9;b3=coeff[i+3]/b9;b4=coeff[i+4]/b9;
   b5=coeff[i+5]/b9;b6=coeff[i+6]/b9;b7=coeff[i+7]/b9;b8=coeff[i+8]/b9;b9=1.;
   i=20;
   c9=coeff[29];
   //cout<<"c9= "<<c9<<endl;
   c0=coeff[i+0]/c9;c1=coeff[i+1]/c9;c2=coeff[i+2]/c9;c3=coeff[i+3]/c9;c4=coeff[i+4]/c9;
   c5=coeff[i+5]/c9;c6=coeff[i+6]/c9;c7=coeff[i+7]/c9;c8=coeff[i+8]/c9;c9=1.;
   /*if(debug==1)
   {
       cout<<a0<<"\t"<<a1<<"\t"<<a2<<"\t"<<a3<<"\t"<<a4<<"\t"<<
a5<<"\t"<<a6<<"\t"<<a7<<"\t"<<a8<<endl;
       cout<<"a9= "<<a9<<endl;
       cout<<"b9= "<<b9<<endl;
       cout<<"c9= "<<c9<<endl;
       cout<<b0<<"\t"<<b1<<"\t"<<b2<<"\t"<<b3<<"\t"<<b4<<"\t"<<
b5<<"\t"<<b6<<"\t"<<b7<<"\t"<<b8<<endl;
       cout<<c0<<"\t"<<c1<<"\t"<<c2<<"\t"<<c3<<"\t"<<c4<<"\t"<<
c5<<"\t"<<c6<<"\t"<<c7<<"\t"<<c8<<endl;
   }*/
   double d0,d1,d2,d3,d4,d5,d6,d7,d8;
   d0=a0-b0;d1=a1-b1;d2=a2-b2;d3=a3-b3;
   d4=a4-b4;d5=a5-b5;d6=a6-b6;d7=a7-b7;d8=a8-b8;
   d0=d0/d8;d1=d1/d8;d2=d2/d8;d3=d3/d8;d4=d4/d8;d5=d5/d8;d6=d6/d8;d7=d7/d8;
   double e0,e1,e2,e3,e4,e5,e6,e7,e8;
   e0=c0-b0;e1=c1-b1;e2=c2-b2;e3=c3-b3;
   e4=c4-b4;e5=c5-b5;e6=c6-b6;e7=c7-b7;e8=c8-b8;
   e0=e0/e8;e1=e1/e8;e2=e2/e8;e3=e3/e8;e4=e4/e8;e5=e5/e8;e6=e6/e8;e7=e7/e8;
   double f0,f1,f2,f3,f4,f5,f6,f7;
   f0=d0-e0;f1=d1-e1;f2=d2-e2;f3=d3-e3;f4=d4-e4;f5=d5-e5;f6=d6-e6;f7=d7-e7;
   f0=f0/f7;f1=f1/f7;f2=f2/f7;f3=f3/f7;f4=f4/f7;f5=f5/f7;f6=f6/f7;
   int nsols=solve_1(a0,a1,a2,a3,a4,a5,a6,a7,a8,d0,d1,d2,d3,d4,d5,d6,d7,f0,f1,f2,f3,f4,f5,f6,solutions1);
   int isol=0;
   double ratio;
   for(int i=0;i<nsols;i++) 
   {  
      double x,y,z;
      x=solutions1[i*3+0];
      y=solutions1[i*3+1];
      z=solutions1[i*3+2];
      double q1,q2,q3;
      //if(debug==1) cout<<"solutions "<<i<<endl;
      q1=a0+a1*x+a2*x*x+a3*y+a4*y*x+a5*y*y+a6*z+a7*z*x+a8*z*y+a9*z*z;
      q2=b0+b1*x+b2*x*x+b3*y+b4*y*x+b5*y*y+b6*z+b7*z*x+b8*z*y+b9*z*z;
      q3=c0+c1*x+c2*x*x+c3*y+c4*y*x+c5*y*y+c6*z+c7*z*x+c8*z*y+c9*z*z;
      ratio=(q1*q1+q2*q2+q3*q3)/((z*z+x*x+y*y)*(z*z+x*x+y*y));
      /*if(debug==1)
      {
           cout<<"step 0 "<<endl;
           cout<<"quadratic 1: "<<q1<<endl;
           cout<<"quadratic 2: "<<q2<<endl;
           cout<<"quadratic 3: "<<q3<<endl;
           cout<<"x,y,z= "<<x<<"  "<<y<<"  "<<z<<endl;
      }*/
      for(int ii=0;ii<20;ii++)
      {
        
        
        
        TMatrixD jacob(3,3);
        jacob(0,0)=a1+2*a2*x+a4*y+a7*z;
        jacob(0,1)=a3+a4*x+2*a5*y+a8*z;
        jacob(0,2)=a6+a7*x+a8*y+2*a9*z;
        jacob(1,0)=b1+2*b2*x+b4*y+b7*z;
        jacob(1,1)=b3+b4*x+2*b5*y+b8*z;
        jacob(1,2)=b6+b7*x+b8*y+2*b9*z;
        jacob(2,0)=c1+2*c2*x+c4*y+c7*z;
        jacob(2,1)=c3+c4*x+2*c5*y+c8*z;
        jacob(2,2)=c6+c7*x+c8*y+2*c9*z;
        TVectorD F(3);
        F(0)=-q1;
        F(1)=-q2;
        F(2)=-q3;
        TDecompLU lu(3);
        lu.SetMatrix(jacob);
        lu.Decompose();
        Bool_t ok;
        ok=lu.Solve(F);
        if(ok)
        {
           x=x+F(0);
           y=y+F(1);
           z=z+F(2);
        }
        q1=a0+a1*x+a2*x*x+a3*y+a4*y*x+a5*y*y+a6*z+a7*z*x+a8*z*y+a9*z*z;
        q2=b0+b1*x+b2*x*x+b3*y+b4*y*x+b5*y*y+b6*z+b7*z*x+b8*z*y+b9*z*z;
        q3=c0+c1*x+c2*x*x+c3*y+c4*y*x+c5*y*y+c6*z+c7*z*x+c8*z*y+c9*z*z;
        ratio=(q1*q1+q2*q2+q3*q3)/((z*z+x*x+y*y)*(z*z+x*x+y*y));
        /*if(debug==1)
        {
           cout<<"step "<<ii+1<<endl;
           cout<<"quadratic 1: "<<q1<<endl;
           cout<<"quadratic 2: "<<q2<<endl;
           cout<<"quadratic 3: "<<q3<<endl;
           cout<<"x,y,z= "<<x<<"  "<<y<<"  "<<z<<endl;
        }*/
        //if(debug==1) cout<<"ratio= "<<ratio<<endl;
        if(ratio<1e-24) break;
        if (ratio>0.1) break;
      } 
 
      //if(fabs(q1)<10&&fabs(q2)<10&&fabs(q3)<10)
      if(ratio<1e-24)
      { 
         solutions[isol*3+0]=x;
         solutions[isol*3+1]=y;
         solutions[isol*3+2]=z;
         double temp;int ok=1;
         //cout<<"passed x,y,z= "<<x<<"  "<<y<<"  "<<z<<endl;
         double x0,y0,z0;
         x0=solutions1[i*3+0];
         y0=solutions1[i*3+1];
         z0=solutions1[i*3+2];
         //for(int itemp=0;itemp<nsols;itemp++)
           //if(itemp!=i) if(fabs(x-solutions1[itemp*3+0])+fabs(y-solutions1[itemp*3+1])+fabs(z-solutions1[itemp*3+2])<fabs(x-x0)+fabs(y-y0)+fabs(z-z0)) ok=0;
         for(int itemp=0;itemp<isol;itemp++)
           if(fabs(x-solutions[itemp*3+0])+fabs(y-solutions[itemp*3+1])+fabs(z-solutions[itemp*3+2])<0.1) ok=0;
         //cout<<"q1,q2,q3= "<<q1<<"  "<<q2<<"  "<<q3<<endl;
         if (ok==1) isol++;
      }
   }
   return isol;
};    
