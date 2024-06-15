// Lessons learned:
// Reverse engineering a header file does not necessarily work because you do not know enough about the alignment of bytes of custom types
// LoadLibrary will have to do

#include <iostream>
#include <string>
#include "HavokScript_FinalRelease.h"

#define ERR_LIB 1
#define ERR_FUNC 2
#define LUA_OK 0

int main(int argc, char* argv[]) {
    lua_State* L = luaL_newstate();
    LuaPlus::LuaState* luaPlusState = new LuaPlus::LuaState(L);
    LuaPlus::LuaStackObject* luaStackObject = new LuaPlus::LuaStackObject(*luaPlusState, 0);
    luaL_openlibs(L);

    if (argc == 2) {
        if (luaPlusState->DoFile(argv[1]) != LUA_OK) {
            std::cerr << lua_tolstring(L, -1, NULL) << std::endl;
            luaStackObject->Pop(1);
        }
    }
    else if (argc == 1) {
        std::string input;
        while (std::cout << "> " && std::getline(std::cin, input) && input != "exit") {
            if (luaPlusState->DoString(input.data()) != LUA_OK) {
                std::cerr << lua_tolstring(L, -1, NULL) << std::endl;
                luaStackObject->Pop(1);
            }
        }
    }
    else {
        std::cerr << "Error: Improper arguments. Usage: " << argv[0] << " [fileName]" << std::endl;
    }

    lua_close(L);
    return 0;
}
