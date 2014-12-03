#ifndef DIM
#define DIM

struct event22
{
    double p3[4], p4[4], p5[4], p6[4];
    double pmiss[4];
};

struct event33
{
    double p3[4], p4[4], p5[4], p6[4], p7[4], p8[4];
    double pmiss[4];
};

void solve22(event22 & evt, double mn, double mx, double my, int & nsols, double p1[][4], double p2[][4]);

void solve33(event33 & evt1, event33 & evt2, int & nsols, double p1[][4],
             double p2[][4], double q1[][4], double q2[][4]);

inline double dot(double* p1, double* p2)
{
    return p1[0]*p2[0]-p1[1]*p2[1]-p1[2]*p2[2]-p1[3]*p2[3];
}

#endif
