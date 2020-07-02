#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include "diff.h"

void diff_T(vector& T, vector& dT)
{
    for (size_t i = 1; i < T.size() - 2; ++i)
        dT[i] = T[i + 1] + T[i - 1] - 2 * T[i];
}
void diff_v(vector& v, vector& dv)
{
    for (size_t i = 1; i < v.size() - 2; ++i)
        dv[i] = v[i + 1] + v[i - 1] - 2 * v[i];
}
void init_consts(double* &consts)
{	
    srand(time(0));
    consts =  new double[4];
    // 0 элемент - нью(V)  
    consts[0] = (double)(rand()) / RAND_MAX;
    //1 элемент - хи(X)
    consts[1] = (double)(rand()) / RAND_MAX;
    //2 элемент -дельта P(dP)
    consts[2] = (double)(rand()) / RAND_MAX;
    //3 элемент -  3 элемент - ро(P)
    consts[3] = (double)(rand()) / RAND_MAX;
}
/*vector diff(vector& T)
{
    vector tmp(0.0, T.size());
    for (size_t i = 1; i < T.size() - 2; i++)
    {
        tmp[i] = T[i + 1] + T[i - 1] - 2 * T[i];
    }
    return tmp;
}*/

Case::Case(int N, double L)
{
    init_consts(consts);
    Lx = L;
    NumPoint = N;
    h = L / N;
    dt = h * h / 4.0;
    T = vector(0.0, NumPoint);
    dT = vector(0.0, NumPoint);
    v = vector(0.0, NumPoint);
    dv = vector(0.0, NumPoint);
};
void Case::step()
{
    double _Nu = consts[0] / (h * h);
    double _Hi = consts[1] / (h * h);
    double dth = dt * h;
    double _param = consts[2] / consts[3];
    diff_v(v, dv);
    v = v + dt * (dv * _Nu - _param);
    diff_T(T, dT);
    T = T + dt * (_Hi * dT + v * (T.shift(-1) - T.shift(1)) / (2 * h));
    
}
void Case::setInitial(vector T_in, vector v_in)
{
    T = T_in;
    v = v_in;
};
void Case::write(std::string name)
{
    std::ofstream out;
    out.open(name);
       
    out << std::setw(5) << "x";
    out << std::setw(15) << "v";
    out << std::setw(15) << "T";
    out << std::endl;
    for (int i = 0; i < NumPoint; i++)
    {
        out << std::setw(5) << i * h;
        out << std::setw(15) << v[i];
        out << std::setw(15) << T[i];
        out << std::endl;
    }
    out.close();
}
Case::~Case() { delete[] consts; }


