#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

class Calc
{
public:
	EMSCRIPTEN_KEEPALIVE static int add(int a, int b);
	EMSCRIPTEN_KEEPALIVE static int sub(int a, int b);
};