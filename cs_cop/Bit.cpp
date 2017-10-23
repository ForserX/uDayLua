extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include <random>

inline int irol(int a, int n) 
{
	int t1, t2;
	n = n % (sizeof(a) * 8);
	t1 = a << n;
	t2 = a >> (sizeof(a) * 8 - n);
	return t1 | t2;
}

inline int iror(int a, int n)
{
	int t1, t2;
	n = n % (sizeof(a) * 8);
	t1 = a >> n;
	t2 = a << (sizeof(a) * 8 - n);
	return t1 | t2;
}

int bit_tobit(lua_State *l)
{
	LUA_INTEGER n = luaL_checkinteger(l, 1);
	unsigned char len = sizeof(n) * 8;
	char *s = new char[len + 1];
	_itoa(n, s, 2);
	lua_pushfstring(l, s);
	return 1;
}

int bit_tohex(lua_State *l)
{
	LUA_INTEGER n = luaL_checkinteger(l, 1);
	unsigned char len = sizeof(n) * 2;
	char *s = new char[len + 1];
	_itoa(n, s, 16);
	lua_pushfstring(l, s);
	return 1;
}

int bit_not(lua_State *l)
{
	LUA_INTEGER n = luaL_checkinteger(l, 1);
	lua_pushinteger(l, ~n);
	return 1;
}

int bit_and(lua_State *l)
{
	LUA_INTEGER a = luaL_checkinteger(l, 1);
	LUA_INTEGER b = luaL_checkinteger(l, 2);
	lua_pushinteger(l, a & b);
	return 1;
}

int bit_or(lua_State *l)
{
	LUA_INTEGER a = luaL_checkinteger(l, 1);
	LUA_INTEGER b = luaL_checkinteger(l, 2);
	lua_pushinteger(l, a | b);
	return 1;
}

int bit_xor(lua_State *l)
{
	LUA_INTEGER a = luaL_checkinteger(l, 1);
	LUA_INTEGER b = luaL_checkinteger(l, 2);
	lua_pushinteger(l, a ^ b);
	return 1;
}

int bit_rol(lua_State *l) 
{
	LUA_INTEGER a = luaL_checkinteger(l, 1);
	LUA_INTEGER n = luaL_checkinteger(l, 2);
	lua_pushinteger(l, irol(a, n));
	return 1;
}

int bit_ror(lua_State *l) {
	LUA_INTEGER a = luaL_checkinteger(l, 1);
	LUA_INTEGER n = luaL_checkinteger(l, 2);
	lua_pushinteger(l, iror(a, n));
	return 1;
}

int bit_rshift(lua_State *l)
{
	LUA_INTEGER a = luaL_checkinteger(l, 1);
	LUA_INTEGER n = luaL_checkinteger(l, 2);
	lua_pushinteger(l, a >> n);
	return 1;
}

int bit_lshift(lua_State *l) 
{
	LUA_INTEGER a = luaL_checkinteger(l, 1);
	LUA_INTEGER n = luaL_checkinteger(l, 2);
	lua_pushinteger(l, a << n);
	return 1;
}


luaL_Reg bit[] = {
	{ "tobit",	bit_tobit },
	{ "tohex",	bit_tohex },
	{ "bnot",	bit_not },
	{ "band",	bit_and },
	{ "bor",	bit_or },
	{ "bxor",	bit_xor },
	{ "lshift",	bit_lshift },
	{ "rshift",	bit_rshift },
	{ "rol",	bit_rol },
	{ "ror",	bit_ror },
	{ NULL,		NULL }
};
