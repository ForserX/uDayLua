#include "lua.hpp"
#include "Libs.h"
#include "xrCore.h"

#include "export.h"

#include <Windows.h>
#include <fstream>
#include <ctime>
#include <process.h>

#pragma comment(lib, "xrCore")
#pragma comment(lib, "user32") 

/*****/
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
/*****/
int arr[256];

int GetKB(lua_State *L){
	lua_newtable(L);
	for(int i=0; i<256; ++i){
		lua_pushinteger(L, i);
		lua_pushboolean(L, arr[i]);
		lua_settable(L, -3);
	}
	return 1;
}

void upd(void *arg){
	while(1){
		for(int i=0; i<256; ++i){
			arr[i] = GetKeyState(i) & 0x8000;
		}
		Sleep(25);
	}
}

bool thread = true;

void kb_start(){
	if(thread){
		memset(&arr[0], 0, 256);
		_beginthread(upd, 0, 0);
	}
	thread = false;
}
/*****/

int open(lua_State *L){
	kb_start();
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
	lua_register(L, "GetKB",  GetKB);
	return 0;
}

extern "C" int Myluaopen_string(lua_State *L){
	luaopen_string(L);
	lua_register(L, "RvP", open);
	return 0;
}