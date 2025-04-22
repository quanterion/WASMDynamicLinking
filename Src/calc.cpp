#include "calc.h"
#include <iostream>
#include <map>
#include <vector>

static bool TestInit()
{
	std::cout << "Init during load" << '\n';
	return true;
}

static bool Init = TestInit();
int Calc::add(int a, int b)
{
	std::map<int, int> m;
	std::vector<double> n;
	n.push_back(1);
	n.push_back(b);
	m[a] = 2;
	m[b] = 3;
	return a + b + m.size() + n.size();
}
int Calc::sub(int a, int b)
{
	return a - b;
}
