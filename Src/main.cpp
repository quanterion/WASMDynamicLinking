#include "calc.h"
#include <iostream>
#include <dlfcn.h>

int main()
{
	std::cout << "Loading wasm lib" << '\n';
	
	void* dllHandle = dlopen("libcalc.so", RTLD_NOW|RTLD_GLOBAL);
	if(!dllHandle)
	{
		std::cout << dlerror() << '\n';
	}
	else
	{
		std::cout << "Handle: " << int(dllHandle) << '\n';
	}
	void* symbol = dlsym(dllHandle, "_ZN4Calc3addEii");
    if (symbol) {
        std::cout << "Found Symbol: " << "_ZN4Calc3addEii" << '\n';
    } else {
        printf("Symbol not found\n");
    }
	
	std::cout << "hello world" << '\n';
	std::cout << "Add 3 + 5 = " << Calc::add(3, 5) << '\n';
	std::cout << "subtract 5 - 3 = " << Calc::sub(5, 3) << '\n';
}
