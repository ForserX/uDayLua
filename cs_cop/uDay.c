#include <lua.h>
#include <lualib.h>
#include <luaconf.h>
#include <lauxlib.h>

int isInit(lua_State* l)
{
	lua_pushlstring(l, "Work", 5);
	return 1;
}


luaL_Reg strlib[] = 
{
	{ "isWork", isInit },
	{ NULL, NULL }
};