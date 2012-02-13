#include <lua.hpp>

#pragma comment(lib, "lua.JIT.1.1.4.lib")

extern "C" __declspec(dllexport) int luaopen_rvp(lua_State *L){
	/*
	do something
	*/
	lua_pushboolean(L, 1);
	return 0;
}