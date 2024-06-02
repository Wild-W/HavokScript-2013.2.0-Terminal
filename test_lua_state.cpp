#include <windows.h>
#include <iostream>
#include <string>

#define ERR_LIB 1
#define ERR_FUNC 2
#define LUA_OK 0

typedef struct lua_State lua_State;
typedef lua_State* (__cdecl *LuaStateFunction)();
typedef void (__cdecl *LuaVoidFunction)(lua_State*);
typedef int (__thiscall *LuaDoStringFunction)(lua_State*, char*);
typedef char* (__cdecl *LuaGetStringFunction)(lua_State*, int, uint64_t*);
typedef void (__thiscall *LuaPopFunction)(lua_State*, int);

int main(int argc, char* argv[]) {
    HMODULE hDll = LoadLibrary(TEXT("HavokScript_FinalRelease.dll"));
    if (hDll == NULL) {
        std::cerr << "Failed to load HavokScript!\n";
        return ERR_LIB;
    }
    auto luaL_newstate = (LuaStateFunction)GetProcAddress(hDll, "?luaL_newstate@@YAPEAUlua_State@@XZ");
    auto luaL_openlibs = (LuaVoidFunction)GetProcAddress(hDll, "?luaL_openlibs@@YAXPEAUlua_State@@@Z");
    auto DoString = (LuaDoStringFunction)GetProcAddress(hDll, "?DoString@LuaState@LuaPlus@@QEAAHPEBD@Z");
    auto lua_close = (LuaVoidFunction)GetProcAddress(hDll, "?lua_close@@YAXPEAUlua_State@@@Z");
    auto lua_tolstring = (LuaGetStringFunction)GetProcAddress(hDll, "?lua_tolstring@@YAPEBDPEAUlua_State@@HPEA_K@Z");
    auto Pop = (LuaPopFunction)GetProcAddress(hDll, "?Pop@LuaState@LuaPlus@@QEAAXH@Z");
    auto DoFile = (LuaDoStringFunction)GetProcAddress(hDll, "?DoFile@LuaState@LuaPlus@@QEAAHPEBD@Z");

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    if (argc == 2) {
        if (DoFile(L, argv[1]) != LUA_OK) {
            std::cerr << lua_tolstring(L, -1, NULL) << std::endl;
            Pop(L, 1);
        }
    }
    else if (argc == 1) {
        std::string input;
        while (std::cout << "> " && std::getline(std::cin, input) && input != "exit") {
            if (DoString(L, input.data()) != LUA_OK) {
                std::cerr << lua_tolstring(L, -1, NULL) << std::endl;
                Pop(L, 1);
            }
        }
    }
    else {
        std::cerr << "Error: Improper arguments. Usage: " << argv[0] << " [fileName]" << std::endl;
    }

    lua_close(L);
    FreeLibrary(hDll);

    return 0;
}
