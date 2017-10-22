extern "C"
{
#	include <lua.h>
#	include <lualib.h>
#	include <lauxlib.h>
}

extern "C"
{
	extern luaL_Reg strlib[];
}

extern "C" __declspec(dllexport) int luaopen_uday(lua_State *L)
{
	luaL_openlib(L, "uDay", strlib, 0);
	return 0;
}