// Includes 
extern "C"
{
#	include <lua.h>
#	include <lualib.h>
#	include <lauxlib.h>
}
// Tables 
extern "C" extern	luaL_Reg strlib[];
extern				luaL_Reg bit[];
extern				luaL_Reg llog[];
// Lua-Open func
extern "C" __declspec(dllexport) int luaopen_uday(lua_State *l)
{
	luaL_openlib(l, "uDay", strlib, 0);
	luaL_openlib(l, "bit",  bit, 0);
	luaL_openlib(l, "log",	llog	, 0);

	return 0;
}