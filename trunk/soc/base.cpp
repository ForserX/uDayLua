#include "lua.hpp"
#include "Libs.h"
#include "export.h"

#pragma comment(lib, "xrCore")
#pragma comment(lib, "user32")

int open(lua_State *L){
	luaopen_os(L);
	luaopen_io(L);
	luaopen_package(L);
	luaopen_debug(L);
	open_string(L);
	open_math(L);
	open_table(L);
	luaopen_lfs(L);
	open_kb(L);
	open_log(L);
	return 0;
}

extern "C" int Myluaopen_string(lua_State *L){
	luaopen_string(L);
	lua_register(L, "RvP", open);
	return 0;
}