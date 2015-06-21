#include "mt2_bisect.h"
#include <iostream>
using namespace std;
main()
{
  cout << " Example Event:" << endl;
  cout << endl; 
  
  //pa, pb = {mass, px, py}
  //pmiss  = {NULL, pxmiss, pymiss}
  //mn     = invisible particle mass
  double pa[3] = { 0.106, 39.0, 12.0 };
  double pb[3] = { 0.106, 119.0, -33.0 };
  double pmiss[3] = { 0, -29.9, 35.9 };
  double mn    = 50.;

  mt2_bisect::mt2 mt2_event;
  
  mt2_event.set_momenta(pa,pb,pmiss);
  mt2_event.set_mn(mn);
  mt2_event.print();

  cout << endl << " mt2 = " << mt2_event.get_mt2() << endl;

  return 1;
   
}
