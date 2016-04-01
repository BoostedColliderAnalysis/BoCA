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

struct event22 {
    double p3[4], p4[4], p5[4], p6[4];
    double pmiss[4];
};


void solve22(event22& evt, double mn, double mx, double my, int& nsols, double p1[][4], double p2[][4]);

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
//   //squark pair production.
//   //each squark decays squark->neutralni2-> slepton->neutralino 1, giving 4 lepton + 2 jet per event
//   //the jet information is not used in the 22 topology.
//
//   ifstream datafile("sqsq_pythia_events.lhe");
//   event22 evt[10000];
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
//     for (int j = 0; j < npar; j ++)
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
//       //read the momenta of the four leptons
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
//       //read missing momentum
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
//   cout << "Number of events  = " << nevent << endl<<endl;
//   datafile.close();
//
//   //test the first two events by solve22()
//   cout << "Now test the 22 algorithm with known masses: 100.4, 143.7, 181.2." <<endl;
//   cout << "Only test the first two events." << endl;
//   double mn = 100.42479, mx = 143.70998, my = 181.23681;
//   int nsols;
//   double p1[4][4], p2[4][4];
//
//   //loop over events
//   for ( ievent = 0; ievent < 2; ievent ++ )
//   {
//
//     cout << endl << "event " << ievent << endl << endl;
//     cout << "Visible momenta and the missing transverse momentum:" << endl;
//     cout << "p3 = " << evt[ievent].p3[0] << "   " << evt[ievent].p3[1] << "   "
//     << evt[ievent].p3[2] << "   " << evt[ievent].p3[3] << endl;
//     cout << "p4 = " << evt[ievent].p4[0] << "   " << evt[ievent].p4[1] << "   "
//     << evt[ievent].p4[2] << "   " << evt[ievent].p4[3] << endl;
//     cout << "p5 = " << evt[ievent].p5[0] << "   " << evt[ievent].p5[1] << "   "
//     << evt[ievent].p5[2] << "   " << evt[ievent].p5[3] << endl;
//     cout << "p6 = " << evt[ievent].p6[0] << "   " << evt[ievent].p6[1] << "   "
//     << evt[ievent].p6[2] << "   " << evt[ievent].p6[3] << endl;
//     cout << "pmiss x,y = " << "   " << evt[ievent].pmiss[1] << "   " << evt[ievent].pmiss[2] << endl;
//
//     solve22( evt[ievent], mn, mx, my, nsols, p1, p2 );
//     cout << endl;
//     cout << "number of solutions = " << nsols << endl;
//
//     for (int isol = 0; isol < nsols; isol ++)
//     {
//       cout << endl <<"solution " << isol << endl;
//       cout << "p1 = " << p1[isol][0] << "  " << p1[isol][1]<< "  "
//       << p1[isol][2] << "  " << p1[isol][3] << endl;
//       cout << "p2 = " << p2[isol][0] << "  " << p2[isol][1]<< "  "
//       << p2[isol][2] << "  " << p2[isol][3] << endl;
//     }
//     cout << endl;
//   }
// }
