#pragma once
#include <valarray>
#include <string>

using vector = std::valarray<double>;

class Case
{
public:
	int NumPoint;
	// 0 элемент - нью(V) | 1 элемент - хи(X) | 2 элемент -дельта P(dP) | 3 элемент - ро(P)
	double* consts;
	double Lx;
	double dt;
	double h;
	//1 уравнение
	vector v;
	vector dv;
	//2 уравнение 
	vector T;
	vector dT;
	Case(int NumPoint, double L);
	void setInitial(vector T, vector v);
	void step();
	void write(std::string);
	//Деструктор 
	~Case();
};
