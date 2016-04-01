#pragma once

// *********************************************************************************
// WIMPMASS
// version 1.00
//
// Authors: Hsin-Chia Cheng, John Gunion, Zhenyu Han, Bob McElrath, Dalit Engelhardt
//
// *********************************************************************************
// This package contains two C++ subroutines useful for event
// reconstruction in events with missing particles. The references
// are arXiv: 0707.0030 and arXiv: 0802.4290.
//
// The two functions are given in "topology22.cpp" and "topology33.cpp"
// in the "src/" directory. See the header of the source file for usage.
// "ROOT" (http://root.cern.ch/drupal/) is required for compiling
// topology33.cpp. The directory "examples/" contains a couple of examples
// calling these subroutines. You need to modify the Makefile in the "src"
// directory and "examples" directory to point to the correct ROOT location.

namespace wimpmass{

struct event33 {
    double p3[4], p4[4], p5[4], p6[4], p7[4], p8[4];
    double pmiss[4];
};

void solve33(event33& evt1, event33& evt2, int& nsols, double p1[][4], double p2[][4], double q1[][4], double q2[][4]);

inline double dot(double* p1, double* p2)
{
    return p1[0] * p2[0] - p1[1] * p2[1] - p1[2] * p2[2] - p1[3] * p2[3];
}

}

// #include "WIMPMASS.h"
// #include <iostream>
// #include <fstream>
// #include <string.h>
// #include <math.h>
// #include <stdlib.h>
// using namespace std;
//
// int main()
// {
//   //read a data file in the lhe format
//   //squark pair production, 4 lepton + 2 jet decay channel
//   //each squark decays squark->neutralni2-> slepton->neutralino 1, giving 4 lepton + 2 jet per event
//
//   ifstream datafile("sqsq_pythia_events.lhe");
//   event33 evt[10000];
//
//   int ievent;
//   int MAXEVENT = 2;
//   for( ievent = 0; ievent < MAXEVENT; ievent ++ )
//   {
//
//
//     //find the line containing <event>
//     int i = 0;
//     char line [1000];
//     while( i == 0 )
//     {
//       datafile.getline( line, 999 );
//       if( datafile.eof() ) break;
//       if( strstr(line, "<event>") ) i = 1;
//     }
//
//
//     if(datafile.eof()) break;
//
//
//     int    npar, itemp;
//     double dtemp1, dtemp2, dtemp3, dtemp4;
//
//     //read the first line of an event
//
//     datafile >> npar >> itemp >> dtemp1 >> dtemp2 >> dtemp3 >> dtemp4;
//
//     //read npar lines
//     int ic1, ic2, ic3, ic4, ic5, ic6;
//     double ic7;
//     double p[6];
//     int njet = 0;
//     int nlep = 0;
//     for (int j=0;j<npar;j++)
//     {
//
//       datafile >> ic1 >> ic6 >> ic2 >> ic3 >> ic4 >> ic5 >>
//       p[1] >> p[2] >> p[3] >> p[0] >> p[4] >> p[5] >> ic7;
//
//       //ic1 is particle ID
//       //ic6=1, stable
//       p[0]=sqrt(p[1]*p[1]+p[2]*p[2]+p[3]*p[3]+p[4]*p[4]);
//
//       //if ( ic6 != 1 ) continue;
//
//       if ( abs(ic1) == 2 && ic6 == 2 )
//       {
//         if ( ic2 == 3 )
//         {
//           for (int i = 0; i < 4; i ++)
//             evt[ievent].p7[i] = p[i];
//         }
//         else if( ic2 == 4 )
//         {
//           for (int i = 0; i < 4; i ++)
//             evt[ievent].p8[i] = p[i];
//         }
//         njet ++;
//       }
//
//       if (abs(ic1) == 11 || abs(ic1) == 13)
//       {
//         if ( nlep == 0 )
//         {
//           for (int i = 0; i < 4; i ++)
//             evt[ievent].p5[i] = p[i];
//         }
//         else if( nlep == 1 )
//         {
//           for (int i = 0; i < 4; i ++)
//             evt[ievent].p3[i] = p[i];
//         }
//         else if( nlep == 2 )
//         {
//           for (int i = 0; i < 4; i ++)
//             evt[ievent].p6[i] = p[i];
//         }
//         else if( nlep == 3 )
//         {
//           for (int i = 0; i < 4; i ++)
//             evt[ievent].p4[i] = p[i];
//         }
//         nlep ++;
//       }
//
//       if (abs(ic1) == 12)
//       {
//         for (int i = 0; i < 4; i ++)
//           evt[ievent].pmiss[i] = p[i];
//
//       }
//     }
//   }
//
//   int nevent = ievent;
//   cout << "Read from data file: sqsq_pythia_events.lhe" << endl;
//   cout << "Number of events  = " << nevent << endl;
//   datafile.close();
//
//   //test the first pair of events by solve33
//   cout << endl << "Now test the 33 algorithm." << endl;
//   cout << "Test the first pair of events." << endl;
//   cout << endl;
//   //loop over events
//   nevent = 2;
//   for (int ievent1 = 0; ievent1 < nevent -1; ievent1 ++)
//     for (int ievent2 = ievent + 1; ievent1 < nevent; ievent2 ++)
//     {
//
//       cout << "Visible momenta and the missing transverse momentum:" << endl << endl;
//       cout << "event 0" << endl;
//       ievent = ievent1;
//       cout << "p3 = " << evt[ievent].p3[0] << "   " << evt[ievent].p3[1] << "   "
//       << evt[ievent].p3[2] << "   " << evt[ievent].p3[3] << endl;
//       cout << "p4 = " << evt[ievent].p4[0] << "   " << evt[ievent].p4[1] << "   "
//       << evt[ievent].p4[2] << "   " << evt[ievent].p4[3] << endl;
//       cout << "p5 = " << evt[ievent].p5[0] << "   " << evt[ievent].p5[1] << "   "
//       << evt[ievent].p5[2] << "   " << evt[ievent].p5[3] << endl;
//       cout << "p6 = " << evt[ievent].p6[0] << "   " << evt[ievent].p6[1] << "   "
//       << evt[ievent].p6[2] << "   " << evt[ievent].p6[3] << endl;
//       cout << "p7 = " << evt[ievent].p7[0] << "   " << evt[ievent].p7[1] << "   "
//       << evt[ievent].p7[2] << "   " << evt[ievent].p7[3] << endl;
//       cout << "p8 = " << evt[ievent].p8[0] << "   " << evt[ievent].p8[1] << "   "
//       << evt[ievent].p8[2] << "   " << evt[ievent].p8[3] << endl;
//       cout << "pmiss x,y = " << "   " << evt[ievent].pmiss[1] << "   " << evt[ievent].pmiss[2] << endl;
//       cout << "event 1" << endl;
//       ievent = ievent2;
//       cout << "q3 = " << evt[ievent].p3[0] << "   " << evt[ievent].p3[1] << "   "
//       << evt[ievent].p3[2] << "   " << evt[ievent].p3[3] << endl;
//       cout << "q4 = " << evt[ievent].p4[0] << "   " << evt[ievent].p4[1] << "   "
//       << evt[ievent].p4[2] << "   " << evt[ievent].p4[3] << endl;
//       cout << "q5 = " << evt[ievent].p5[0] << "   " << evt[ievent].p5[1] << "   "
//       << evt[ievent].p5[2] << "   " << evt[ievent].p5[3] << endl;
//       cout << "q6 = " << evt[ievent].p6[0] << "   " << evt[ievent].p6[1] << "   "
//       << evt[ievent].p6[2] << "   " << evt[ievent].p6[3] << endl;
//       cout << "q7 = " << evt[ievent].p7[0] << "   " << evt[ievent].p7[1] << "   "
//       << evt[ievent].p7[2] << "   " << evt[ievent].p7[3] << endl;
//       cout << "q8 = " << evt[ievent].p8[0] << "   " << evt[ievent].p6[1] << "   "
//       << evt[ievent].p8[2] << "   " << evt[ievent].p8[3] << endl;
//       cout << "qmiss x,y = " << "   " << evt[ievent].pmiss[1] << "   " << evt[ievent].pmiss[2] << endl;
//
//       double P1[9][4], P2[9][4], Q1[9][4], Q2[9][4];
//       int nsols;
//       solve33(evt[0], evt[1], nsols, P1, P2, Q1, Q2);
//       cout << endl << "number of solutions = " << nsols << endl;
//       for (int isol = 0; isol < nsols; isol ++)
//       {
//         cout << endl <<"solution " << isol << endl;
//
//         cout << "p1 = " << P1[isol][0] << "  " << P1[isol][1]<< "  "
//         << P1[isol][2] << "  " << P1[isol][3] << endl;
//         cout << "p2 = " << P2[isol][0] << "  " << P2[isol][1]<< "  "
//         << P2[isol][2] << "  " << P2[isol][3] << endl;
//         cout << "q1 = " << Q1[isol][0] << "  " << Q1[isol][1]<< "  "
//         << Q1[isol][2] << "  " << Q1[isol][3] << endl;
//         cout << "q2 = " << Q2[isol][0] << "  " << Q2[isol][1]<< "  "
//         << Q2[isol][2] << "  " << Q2[isol][3] << endl;
//         double mn, mx, my, mz;
//
//         double p31[4], p531[4], p7531[4];
//         for (int i = 0; i < 4; i ++)
//         {
//           p31[i] = P1[isol][i] + evt[0].p3[i];
//           p531[i] = p31[i] + evt[0].p5[i];
//           p7531[i] = p531[i] + evt[0].p7[i];
//         }
//         mn = sqrt(dot(P1[isol], P1[isol]));
//         mx = sqrt(dot(p31, p31));
//         my = sqrt(dot(p531, p531));
//         mz = sqrt(dot(p7531, p7531));
//         cout << "mn = " << mn << "   mx = " << mx << "   my = " << my << "   mz = " << mz << endl;
//       }
//     }
// }
