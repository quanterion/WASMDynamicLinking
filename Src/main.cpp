#include "calc.h"
#include <iostream>
#include <dlfcn.h>

int main()
{
	std::cout << "Loading wasm lib" << '\n';
	
	// Wasm uses either wasm or so files for library, loading an so file here
	// RTLD_GLOBAL is required here, otherwise the library won't be accessible by linked functions after loading
	void* dllHandle = dlopen("libcalc.so", RTLD_NOW|RTLD_GLOBAL);
	if(!dllHandle)
	{
		std::cout << dlerror() << '\n';
	}
	else
	{
		std::cout << "Handle: " << int(dllHandle) << '\n';
	}
	
	// Finds the add symbol and prints if it was found\n
	// This name could be mangled in a different way, so might not be able to find the symbol even when it exists
	void* symbol = dlsym(dllHandle, "_ZN4Calc3addEii");
    if (symbol) {
        std::cout << "Found Symbol: " << "_ZN4Calc3addEii" << '\n';
    } else {
        printf("Symbol not found\n");
    }
	
	std::cout << "Finished loading, testing libraries!" << '\n';
	std::cout << "Add 3 + 5 = " << Calc::add(3, 5) << '\n';
	std::cout << "subtract 5 - 3 = " << Calc::sub(5, 3) << '\n';
}
