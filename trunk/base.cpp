#include "lua.hpp"
#include "Libs.h"
#include "xrCore.h"

#include "export036.h"
//#include "export45.h"


#include <Windows.h>
#include <fstream>
#include <ctime>

#pragma comment(lib, "xrCore")
#pragma comment(lib, "user32") 

std::ofstream LogFile;

char fmt[64];
char fmt_def[] = "[%x %X]\t";

void _cdecl Logger(const char *s){
	time_t t = time(NULL);
	tm* ti = localtime(&t);
	char buf[64];
	strftime(buf, 64, fmt, ti);

	LogFile << buf << s << "\n";
	LogFile.flush();
}

int SetLog(lua_State *L){
	if(!LogFile.is_open()){
		switch(lua_gettop(L)){
			case 1:
				LogFile.open(luaL_checkstring(L, 1));
				strcpy(fmt, fmt_def);
				break;
			case 2:
				LogFile.open(luaL_checkstring(L, 1));
				strcpy(fmt, luaL_checkstring(L, 2));
				break;
			default: return luaL_error(L, "SetLog: wrong number of arguments");
		}
		if(!LogFile.is_open()){
			MessageBox(0, "Cannot open log file", "Error", MB_OK);
		}
	}
	SetLogCB(Logger);
	return 0;
}

int log123(lua_State *L){
	int n = lua_gettop(L);
	for(int i=0; i<n; ++i){
		Log(luaL_checkstring(L, i+1));
	}
	return 0;
}

int GetKey(lua_State *L){
	lua_pushboolean(L, GetKeyState(luaL_checkint(L, 1)) & 0x8000);
	return 1;
}

int open(lua_State *L){
	luaopen_os(L);
	luaopen_io(L);
	luaopen_package(L);
	luaopen_debug(L);
	open_string(L);
	open_math(L);
	open_table(L);
	luaopen_lfs(L);
	lua_register(L, "SetLog", SetLog);
	lua_register(L, "log123", log123);
	lua_register(L, "GetKey", GetKey);
	return 0;
}

extern "C" int Myluaopen_string(lua_State *L){
	luaopen_string(L);
	lua_register(L, "RvP", open);
	return 0;
}