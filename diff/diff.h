#pragma once
#include <valarray>
#include <string>

using vector = std::valarray<double>;

class Case
{
public:
	int NumPoint;
	// 0 ������� - ���(V) | 1 ������� - ��(X) | 2 ������� -������ P(dP) | 3 ������� - ��(P)
	double* consts;
	double Lx;
	double dt;
	double h;
	//1 ���������
	vector v;
	vector dv;
	//2 ��������� 
	vector T;
	vector dT;
	Case(int NumPoint, double L);
	void setInitial(vector T, vector v);
	void step();
	void write(std::string);
	//���������� 
	~Case();
};
