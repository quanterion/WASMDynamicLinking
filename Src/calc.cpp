#include "calc.h"
#include <iostream>

static bool TestInit()
{
	std::cout << "Init during load" << '\n';
	return true;
}

static bool Init = TestInit();
int Calc::add(int a, int b)
{
	return a + b;
}
int Calc::sub(int a, int b)
{
	return a - b;
}
