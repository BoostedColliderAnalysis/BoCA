#pragma once

namespace polynomialroots
{

class PolynomialRoots
{

    static const int MAXDEGREE = 100;

    static const int MDP1 = MAXDEGREE + 1;

public:

    void rpoly(double op[MDP1], int* Degree, double zeror[MAXDEGREE], double zeroi[MAXDEGREE]);

private:

    void Fxshfr(int L2, int* NZ, double sr, double v, double K[MDP1], int N, double p[MDP1], int NN, double qp[MDP1], double u, double* lzi, double* lzr, double* szi, double* szr);

    void QuadSD(int NN, double u, double v, double p[MDP1], double q[MDP1], double* a, double* b);

    int calcSC(int N, double a, double b, double* a1, double* a3, double* a7, double* c, double* d, double* e, double* f, double* g, double* h, double K[MDP1], double u, double v, double qk[MDP1]);

    void nextK(int N, int tFlag, double a, double b, double a1, double* a3, double* a7, double K[MDP1], double qk[MDP1], double qp[MDP1]);

    void newest(int tFlag, double* uu, double* vv, double a, double a1, double a3, double a7, double b, double c, double d, double f, double g, double h, double u, double v, double K[MDP1], int N, double p[MDP1]);

    void QuadIT(int N, int* NZ, double uu, double vv, double* szr, double* szi, double* lzr, double* lzi, double qp[MDP1], int NN, double* a, double* b, double p[MDP1], double qk[MDP1], double* a1, double* a3, double* a7, double* c, double* d, double* e, double* f, double* g, double* h, double K[MDP1]);

    void RealIT(int* iFlag, int* NZ, double* sss, int N, double p[MDP1], int NN, double qp[MDP1], double* szr, double* szi, double K[MDP1], double qk[MDP1]);

    void Quadratic(double quadratic, double linear, double constant, double* sr, double* si, double* lr, double* li);

};

}
