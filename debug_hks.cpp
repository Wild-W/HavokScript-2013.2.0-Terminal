#include <Windows.h>
#include <iostream>
#include <string>
#include <stdio.h>

#define ERR_LIB 1
#define ERR_FUNC 2
#define LUA_OK 0

#define PushLuaMethod(L, func, cclosurename, stackOffset, name) \
    hks::pushnamedcclosure(L, func, 0, cclosurename, 0); \
    hks::setfield(L, stackOffset, name);

namespace hks {
	namespace {
		HMODULE hksDll;
	}
	constexpr int LUA_GLOBAL = -10002;
	constexpr int LUA_REGISTRYINDEX = -10000;

	typedef struct lua_State lua_State;

	typedef int(__cdecl* luaFunc)(lua_State*);

	typedef void(__cdecl* hks_pushnamedcclosureType)(lua_State*, luaFunc, int, const char*, int);
	hks_pushnamedcclosureType pushnamedcclosure;
	typedef int(__cdecl* luaL_checkintegerType)(lua_State*, int);
	luaL_checkintegerType checkinteger;
	typedef double(__cdecl* luaL_checknumberType)(lua_State*, int);
	luaL_checknumberType checknumber;
	typedef void(__cdecl* hksi_lua_setfieldType)(lua_State*, int, const char*);
	hksi_lua_setfieldType setfield;
	typedef int(__thiscall* GetTopType)(lua_State*);
	GetTopType gettop;
	typedef int(__thiscall* DoStringType)(lua_State*, const char*);
	DoStringType dostring;
	typedef int(__cdecl* hksi_lua_tobooleanType)(lua_State*, int);
	hksi_lua_tobooleanType toboolean;
	typedef void(__cdecl* hksi_lua_pushnumberType)(lua_State*, double);
	hksi_lua_pushnumberType pushnumber;
	typedef void(__cdecl* hksi_lua_pushintegerType)(lua_State*, int);
	hksi_lua_pushintegerType pushinteger;
	typedef void(__cdecl* hksi_luaL_errorType)(lua_State*, char const*, ...);
	hksi_luaL_errorType error;
	typedef char const* (__cdecl* hksi_lua_pushfstringType)(lua_State*, char const*, ...);
	hksi_lua_pushfstringType pushfstring;
	typedef char const* (__cdecl* CheckLStringType)(lua_State*, int, unsigned __int64*);
	CheckLStringType checklstring;
	typedef void* (__cdecl* hksi_lua_touserdataType)(lua_State*, int);
	hksi_lua_touserdataType touserdata;
	typedef void(__cdecl* hksi_lua_getfieldType)(lua_State*, int, char const*);
	hksi_lua_getfieldType getfield;
	typedef void(__thiscall* PopType)(lua_State*, int);
	PopType pop;
	typedef void(__cdecl* hksi_lua_createtableType)(lua_State*, int, int);
	hksi_lua_createtableType createtable;
	typedef luaFunc(__cdecl* lua_tocfunctionType)(lua_State*, int);
	lua_tocfunctionType tocfunction;
	typedef void(__cdecl* hksL_checktableType)(lua_State*, int);
	hksL_checktableType checktable;
	typedef unsigned long long(__cdecl* hks_lua_objlenType)(lua_State*, int);
	hks_lua_objlenType objlen;
	typedef void(__cdecl* hks_lua_gettableType)(lua_State*, int);
	hks_lua_gettableType gettable;
	typedef void(__cdecl* hksi_lua_cpcallType)(lua_State*, int, luaFunc, int);
	hksi_lua_cpcallType cpcall;
	typedef int(__cdecl* RefType)(lua_State*, int);
	RefType ref;
	typedef int(__cdecl* hksi_lua_pcallType)(lua_State*, int, int, int);
	hksi_lua_pcallType pcall;
	typedef void(__cdecl* hski_lua_pushvalueType)(lua_State*, int);
	hski_lua_pushvalueType pushvalue;
	typedef void(__cdecl* hksi_lua_rawgetiType)(lua_State*, int, int);
	hksi_lua_rawgetiType rawgeti;
	typedef void(__cdecl* hksi_lua_unrefType)(hks::lua_State*, int, int);
	hksi_lua_unrefType unref;
	typedef void(__cdecl* hksi_lua_settableType)(hks::lua_State*, int);
	hksi_lua_settableType settable;
	typedef int(__cdecl* hksi_lua_isnumberType)(hks::lua_State*, int);
	hksi_lua_isnumberType isnumber;
	typedef double(__cdecl* hksi_lua_tonumberType)(hks::lua_State*, int);
	hksi_lua_tonumberType tonumber;
	typedef int(__cdecl* hksi_lua_isuserdataType)(hks::lua_State*, int);
	hksi_lua_isuserdataType isuserdata;
	typedef int(__cdecl* luaopen_debugType)(hks::lua_State*);
	luaopen_debugType luaopen_debug;
	typedef int(__cdecl* hksi_lua_tointegerType)(hks::lua_State*, int);
	hksi_lua_tointegerType tointeger;
	typedef int(__cdecl* hksi_lua_typeType)(lua_State*, int);
	hksi_lua_typeType type;
	typedef int(__cdecl* luaL_optintegerType)(lua_State*, int, int);
	luaL_optintegerType optinteger;
	typedef int(__cdecl* hksi_lua_sethookType)(lua_State*, void*, int, int);
	hksi_lua_sethookType sethook;
	typedef void* (__cdecl* hksi_lua_gethookType)(lua_State*);
	hksi_lua_gethookType gethook;
	typedef int(__cdecl* hksi_lua_gethookmaskType)(lua_State*);
	hksi_lua_gethookmaskType gethookmask;
	typedef int(__cdecl* hksi_lua_gethookcountType)(lua_State*);
	hksi_lua_gethookcountType gethookcount;
	typedef lua_State* (__cdecl* luaL_newstateType)();
	luaL_newstateType newstate;
	typedef void (__cdecl* luaL_openlibsType)(lua_State*);
	luaL_openlibsType openlibs;
	typedef char* (__cdecl *lua_tolstringType)(lua_State*, int, size_t*);
	lua_tolstringType tolstring;
	typedef lua_State* (__cdecl* luaL_closeType)(lua_State*);
	luaL_closeType close;
	typedef int (__thiscall *DoFileType)(lua_State*, char*);
	DoFileType dofile;

	static void init_imports() {
		pushnamedcclosure = (hks_pushnamedcclosureType)GetProcAddress(hksDll, "?hks_pushnamedcclosure@@YAXPEAUlua_State@@P6AH0@ZHPEBDH@Z");
		setfield = (hksi_lua_setfieldType)GetProcAddress(hksDll, "?hksi_lua_setfield@@YAXPEAUlua_State@@HPEBD@Z");
		checkinteger = (luaL_checkintegerType)GetProcAddress(hksDll, "?luaL_checkinteger@@YAHPEAUlua_State@@H@Z");
		gettop = (GetTopType)GetProcAddress(hksDll, "?GetTop@LuaState@LuaPlus@@QEBAHXZ");
		dostring = (DoStringType)GetProcAddress(hksDll, "?DoString@LuaState@LuaPlus@@QEAAHPEBD@Z");
		toboolean = (hksi_lua_tobooleanType)GetProcAddress(hksDll, "?hksi_lua_toboolean@@YAHPEAUlua_State@@H@Z");
		pushinteger = (hksi_lua_pushintegerType)GetProcAddress(hksDll, "?hksi_lua_pushinteger@@YAXPEAUlua_State@@H@Z");
		pushnumber = (hksi_lua_pushnumberType)GetProcAddress(hksDll, "?hksi_lua_pushnumber@@YAXPEAUlua_State@@N@Z");
		error = (hksi_luaL_errorType)GetProcAddress(hksDll, "?hksi_luaL_error@@YAHPEAUlua_State@@PEBDZZ");
		checknumber = (luaL_checknumberType)GetProcAddress(hksDll, "?luaL_checknumber@@YANPEAUlua_State@@H@Z");
		pushfstring = (hksi_lua_pushfstringType)GetProcAddress(hksDll, "?hksi_lua_pushfstring@@YAPEBDPEAUlua_State@@PEBDZZ");
		checklstring = (CheckLStringType)GetProcAddress(hksDll, "?hksi_luaL_checklstring@@YAPEBDPEAUlua_State@@HPEA_K@Z");
		pop = (PopType)GetProcAddress(hksDll, "?Pop@LuaState@LuaPlus@@QEAAXH@Z");
		touserdata = (hksi_lua_touserdataType)GetProcAddress(hksDll, "?hksi_lua_touserdata@@YAPEAXPEAUlua_State@@H@Z");
		getfield = (hksi_lua_getfieldType)GetProcAddress(hksDll, "?hksi_lua_getfield@@YAXPEAUlua_State@@HPEBD@Z");
		createtable = (hksi_lua_createtableType)GetProcAddress(hksDll, "?lua_createtable@@YAXPEAUlua_State@@HH@Z");
		tocfunction = (lua_tocfunctionType)GetProcAddress(hksDll, "?lua_tocfunction@@YAP6AHPEAUlua_State@@@Z0H@Z");
		checktable = (hksL_checktableType)GetProcAddress(hksDll, "?hksL_checktable@@YAXPEAUlua_State@@H@Z");
		objlen = (hks_lua_objlenType)GetProcAddress(hksDll, "?hksi_lua_objlen@@YA_KPEAUlua_State@@H@Z");
		gettable = (hks_lua_gettableType)GetProcAddress(hksDll, "?hksi_lua_gettable@@YAXPEAUlua_State@@H@Z");
		cpcall = (hksi_lua_cpcallType)GetProcAddress(hksDll, "?hksi_lua_cpcall@@YAHPEAUlua_State@@P6AH0@ZPEAX@Z");
		ref = (RefType)GetProcAddress(hksDll, "?luaL_ref@@YAHPEAUlua_State@@H@Z");
		pcall = (hksi_lua_pcallType)GetProcAddress(hksDll, "?hksi_lua_pcall@@YAHPEAUlua_State@@HHH@Z");
		pushvalue = (hski_lua_pushvalueType)GetProcAddress(hksDll, "?hksi_lua_pushvalue@@YAXPEAUlua_State@@H@Z");
		rawgeti = (hksi_lua_rawgetiType)GetProcAddress(hksDll, "?hksi_lua_rawgeti@@YAXPEAUlua_State@@HH@Z");
		unref = (hksi_lua_unrefType)GetProcAddress(hksDll, "?hksi_luaL_unref@@YAXPEAUlua_State@@HH@Z");
		settable = (hksi_lua_settableType)GetProcAddress(hksDll, "?SetTable@LuaState@LuaPlus@@QEAAXH@Z");
		isnumber = (hksi_lua_isnumberType)GetProcAddress(hksDll, "?hksi_lua_isnumber@@YAHPEAUlua_State@@H@Z");
		tonumber = (hksi_lua_tonumberType)GetProcAddress(hksDll, "?hksi_lua_tonumber@@YANPEAUlua_State@@H@Z");
		isuserdata = (hksi_lua_isuserdataType)GetProcAddress(hksDll, "?hksi_lua_isuserdata@@YAHPEAUlua_State@@H@Z");
		luaopen_debug = (luaopen_debugType)GetProcAddress(hksDll, "?luaopen_debug@@YAHPEAUlua_State@@@Z");
		tointeger = (hksi_lua_tointegerType)GetProcAddress(hksDll, "?hksi_lua_tointeger@@YAHPEAUlua_State@@H@Z");
		type = (hksi_lua_typeType)GetProcAddress(hksDll, "?hksi_lua_type@@YAHPEAUlua_State@@H@Z");
		optinteger = (luaL_optintegerType)GetProcAddress(hksDll, "?luaL_optinteger@@YAHPEAUlua_State@@HH@Z");
		sethook = (hksi_lua_sethookType)GetProcAddress(hksDll, "?hksi_lua_sethook@@YAHPEAUlua_State@@P6AX0PEAUlua_Debug@@@ZHH@Z");
		gethook = (hksi_lua_gethookType)GetProcAddress(hksDll, "?hksi_lua_gethook@@YAP6AXPEAUlua_State@@PEAUlua_Debug@@@Z0@Z");
		gethookmask = (hksi_lua_gethookmaskType)GetProcAddress(hksDll, "?hksi_lua_gethookmask@@YAHPEAUlua_State@@@Z");
		gethookcount = (hksi_lua_gethookcountType)GetProcAddress(hksDll, "?hksi_lua_gethookcount@@YAHPEAUlua_State@@@Z");
    	newstate = (luaL_newstateType)GetProcAddress(hksDll, "?luaL_newstate@@YAPEAUlua_State@@XZ");
    	openlibs = (luaL_openlibsType)GetProcAddress(hksDll, "?luaL_openlibs@@YAXPEAUlua_State@@@Z");
    	close = (luaL_closeType)GetProcAddress(hksDll, "?lua_close@@YAXPEAUlua_State@@@Z");
    	tolstring = (lua_tolstringType)GetProcAddress(hksDll, "?lua_tolstring@@YAPEBDPEAUlua_State@@HPEA_K@Z");
    	dofile = (DoFileType)GetProcAddress(hksDll, "?DoString@LuaState@LuaPlus@@QEAAHPEBD@Z");
	}

	int l_sethook(lua_State* L) {
		void* hook = (void*)tocfunction(L, 1);
		int mask = checkinteger(L, 2);
		int count = optinteger(L, 3, 0);

		sethook(L, hook, mask, count);
		return 0;
	}
	
	static int hook_id = 0;
	int l_gethook(lua_State* L) {
		void* hook = gethook(L);
		if (hook == NULL) return 0;

		char hook_name[20] = "hook_";
		snprintf(hook_name + strlen(hook_name), sizeof(hook_name), "%d", hook_id++);

		pushnamedcclosure(L, (luaFunc)hook, 0, hook_name, 0);
		pushinteger(L, gethookmask(L));
		pushinteger(L, gethookcount(L));
		return 3;
	}
	
	void pushboolean(lua_State* L, bool value) {
		// Access the Lua stack top pointer
		int* stackTop = *(int**)((uintptr_t)L + 0x48);

		// Push a Lua boolean value onto the stack
		*stackTop = 1;
		stackTop[2] = static_cast<unsigned int>(value);

		// Increment the stack top pointer by 4 bytes
		*(int**)((uintptr_t)L + 0x48) = stackTop + 0x4;
	}

	// GameCore: 0x16a10
	void pushlightuserdata(lua_State* L, void* ptr) {
		int* luaStack = *(int**)((uintptr_t)L + 0x48);

		*(void**)(luaStack + 2) = ptr;
		*luaStack = 2;

		*(int**)((uintptr_t)L + 0x48) = luaStack + 0x4;
	}

	// Should only ever be called once.
    void init() {
        hksDll = LoadLibrary(TEXT("HavokScript_FinalRelease.dll"));
        if (hksDll == NULL) {
            std::cout << "Failed to load HavokScript! " << GetLastError() << '\n';
            return;
        }
    }

	void uninit() {
    	FreeLibrary(hksDll);
	}
}

int main(int argc, char* argv[]) {
	hks::init();
	hks::init_imports();

	hks::lua_State* L = hks::newstate();
    hks::openlibs(L);
    hks::getfield(L, hks::LUA_GLOBAL, "debug");
    PushLuaMethod(L, hks::l_gethook, "l_gethook", -2, "gethook");
    PushLuaMethod(L, hks::l_sethook, "l_sethook", -2, "sethook");

    if (argc == 2) {
        if (hks::dofile(L, argv[1]) != LUA_OK) {
            std::cerr << hks::tolstring(L, -1, NULL) << std::endl;
            hks::pop(L, 1);
        }
    }
    else if (argc == 1) {
        std::string input;
        while (std::cout << "> " && std::getline(std::cin, input) && input != "exit") {
            if (hks::dostring(L, input.data()) != LUA_OK) {
                std::cerr << hks::tolstring(L, -1, NULL) << std::endl;
                hks::pop(L, 1);
            }
        }
    }
    else {
        std::cerr << "Error: Improper arguments. Usage: " << argv[0] << " [fileName]" << std::endl;
    }

    hks::close(L);
	hks::uninit();

    return 0;
}