#include "lua.hpp"
#include "Libs.h"

#include "export036.h"
//#include "export45.h"

int open(lua_State *L){
	luaopen_os(L);
	luaopen_io(L);
	luaopen_package(L);
	luaopen_debug(L);
	open_string(L);
	open_math(L);
	open_table(L);
	luaopen_lfs(L);
	return 0;
}

extern "C" int Myluaopen_string(lua_State *L){
	luaopen_string(L);
	lua_register(L, "RvP", open);
	return 0;
}