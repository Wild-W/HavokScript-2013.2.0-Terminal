#include <Windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>

typedef unsigned long long uint64_t;

#define ERR_LIB 1
#define ERR_FUNC 2
#define LUA_OK 0

#define LUA_TNONE (-1)
#define LUA_TNIL 0
#define LUA_TBOOLEAN 1
#define LUA_TLIGHTUSERDATA 2
#define LUA_TNUMBER 3
#define LUA_TSTRING 4
#define LUA_TTABLE 5
#define LUA_TFUNCTION 6
#define LUA_TUSERDATA 7
#define LUA_TTHREAD 8

#define LUA_MULTRET (-1)

#define PushLuaMethod(L, func, cclosurename, stackOffset, name) \
    hks::pushnamedcclosure(L, func, 0, cclosurename, 0);        \
    hks::setfield(L, stackOffset, name);

#define isnoneornil(L, n) (type(L, (n)) <= 0)

namespace hks
{
    namespace
    {
        HMODULE hksDll;
    }
    constexpr int LUA_GLOBAL = -10002;
    constexpr int LUA_REGISTRYINDEX = -10000;

    constexpr int LUA_MASKCALL = 0x1;
    constexpr int LUA_MASKRET = 0x2;
    constexpr int LUA_MASKLINE = 0x4;
    constexpr int LUA_MASKCOUNT = 0x8;

    typedef struct lua_State lua_State;
    typedef struct lua_Debug lua_Debug;

    // 5.1 Debug Reference:
    //
    // struct lua_Debug
    // {
    //     int event;
    //     const char *name;           /* (n) */
    //     const char *namewhat;       /* (n) `global', `local', `field', `method' */
    //     const char *what;           /* (S) `Lua', `C', `main', `tail' */
    //     const char *source;         /* (S) */
    //     int currentline;            /* (l) */
    //     int nups;                   /* (u) number of upvalues */
    //     int linedefined;            /* (S) */
    //     int lastlinedefined;        /* (S) */
    //     char short_src[LUA_IDSIZE]; /* (S) */
    //     /* private part */
    //     int i_ci; /* active function */
    // };

    namespace StateSettings
    {
        typedef struct HksCompilerSettings HksCompilerSettings;

        typedef HksCompilerSettings *(*_getDefaultCompilerSettings)(void);
        _getDefaultCompilerSettings getDefaultCompilerSettings;
    }

    typedef int (*luaFunc)(lua_State *);

    typedef void (*hks_pushnamedcclosure)(lua_State *, luaFunc, int, const char *, int);
    hks_pushnamedcclosure pushnamedcclosure;
    typedef int (*luaL_checkinteger)(lua_State *, int);
    luaL_checkinteger checkinteger;
    typedef double (*luaL_checknumber)(lua_State *, int);
    luaL_checknumber checknumber;
    typedef void (*hksi_lua_setfield)(lua_State *, int, const char *);
    hksi_lua_setfield setfield;
    typedef int (*GetTop)(lua_State *);
    GetTop gettop;
    typedef int (*DoString)(lua_State *, const char *);
    DoString dostring;
    typedef int (*hksi_lua_toboolean)(lua_State *, int);
    hksi_lua_toboolean toboolean;
    typedef void (*hksi_lua_pushnumber)(lua_State *, double);
    hksi_lua_pushnumber pushnumber;
    typedef void (*hksi_lua_pushinteger)(lua_State *, int);
    hksi_lua_pushinteger pushinteger;
    typedef void (*hksi_luaL_error)(lua_State *, char const *, ...);
    hksi_luaL_error error;
    typedef char const *(*hksi_lua_pushfstring)(lua_State *, char const *, ...);
    hksi_lua_pushfstring pushfstring;
    typedef char const *(*CheckLString)(lua_State *, int, unsigned __int64 *);
    CheckLString checklstring;
    typedef void *(*hksi_lua_touserdata)(lua_State *, int);
    hksi_lua_touserdata touserdata;
    typedef void (*hksi_lua_getfield)(lua_State *, int, char const *);
    hksi_lua_getfield getfield;
    typedef void (*Pop)(lua_State *, int);
    Pop pop;
    typedef void (*hksi_lua_createtable)(lua_State *, int, int);
    hksi_lua_createtable createtable;
    typedef luaFunc (*lua_tocfunction)(lua_State *, int);
    lua_tocfunction tocfunction;
    typedef void (*hksL_checktable)(lua_State *, int);
    hksL_checktable checktable;
    typedef unsigned long long (*hks_lua_objlen)(lua_State *, int);
    hks_lua_objlen objlen;
    typedef void (*hks_lua_gettable)(lua_State *, int);
    hks_lua_gettable gettable;
    typedef void (*hksi_lua_cpcall)(lua_State *, int, luaFunc, int);
    hksi_lua_cpcall cpcall;
    typedef int (*Ref)(lua_State *, int);
    Ref ref;
    typedef int (*hksi_lua_pcall)(lua_State *, int, int, int);
    hksi_lua_pcall pcall;
    typedef void (*hski_lua_pushvalue)(lua_State *, int);
    hski_lua_pushvalue pushvalue;
    typedef void (*hksi_lua_rawgeti)(lua_State *, int, int);
    hksi_lua_rawgeti rawgeti;
    typedef void (*hksi_lua_unref)(hks::lua_State *, int, int);
    hksi_lua_unref unref;
    typedef void (*hksi_lua_settable)(hks::lua_State *, int);
    hksi_lua_settable settable;
    typedef int (*hksi_lua_isnumber)(hks::lua_State *, int);
    hksi_lua_isnumber isnumber;
    typedef double (*hksi_lua_tonumber)(hks::lua_State *, int);
    hksi_lua_tonumber tonumber;
    typedef int (*hksi_lua_isuserdata)(hks::lua_State *, int);
    hksi_lua_isuserdata isuserdata;
    typedef int (*luaopen_debug)(hks::lua_State *);
    luaopen_debug open_debug;
    typedef int (*hksi_lua_tointeger)(hks::lua_State *, int);
    hksi_lua_tointeger tointeger;
    typedef int (*hksi_lua_type)(lua_State *, int);
    hksi_lua_type type;
    typedef int (*luaL_optinteger)(lua_State *, int, int);
    luaL_optinteger optinteger;
    typedef int (*hksi_lua_sethook)(lua_State *, void *, int, int);
    hksi_lua_sethook sethook;
    typedef void *(*hksi_lua_gethook)(lua_State *);
    hksi_lua_gethook gethook;
    typedef int (*hksi_lua_gethookmask)(lua_State *);
    hksi_lua_gethookmask gethookmask;
    typedef int (*hksi_lua_gethookcount)(lua_State *);
    hksi_lua_gethookcount gethookcount;
    typedef lua_State *(*luaL_newstate)();
    luaL_newstate newstate;
    typedef void (*luaL_openlibs)(lua_State *);
    luaL_openlibs openlibs;
    typedef char *(*lua_tolstring)(lua_State *, int, size_t *);
    lua_tolstring tolstring;
    typedef lua_State *(*luaL_close)(lua_State *);
    luaL_close close;
    typedef int (*DoFile)(lua_State *, char *);
    DoFile dofile;
    typedef int (*lua_isstring)(lua_State *, int);
    lua_isstring isstring;
    typedef lua_State *(*hksi_lua_tothread)(lua_State *, int);
    hksi_lua_tothread tothread;
    typedef void (*lua_settop)(lua_State *, int);
    lua_settop settop;
    typedef void (*hksi_luaL_checktype)(lua_State *, int, int);
    hksi_luaL_checktype checktype;
    typedef void (*hksi_lua_rawget)(lua_State *, int);
    hksi_lua_rawget rawget;
    typedef void (*lua_pushnil)(lua_State *);
    lua_pushnil pushnil;
    typedef int (*hks_lua_getinfo)(lua_State *, char *, void *);
    hks_lua_getinfo getinfo;
    typedef void (*lua_call)(lua_State *, int, int);
    lua_call call;
    typedef void (*XMove)(lua_State *, lua_State *, int);
    XMove xmove;
    typedef void (*lua_rawset)(lua_State *, int);
    lua_rawset rawset;
    typedef void (*lua_remove)(lua_State *, int);
    lua_remove remove;
    typedef int (*hksL_loadstring)(lua_State *, StateSettings::HksCompilerSettings *, char *);
    hksL_loadstring loadstring;
    typedef int (*LoadStringA)(lua_State *, char *);
    LoadStringA loadstringa;
    typedef void (*lua_insert)(lua_State *, int);
    lua_insert insert;

    typedef int (*db_c_breakpoint)(lua_State *);
    db_c_breakpoint c_breakpoint;

    static void init_imports()
    {
        pushnamedcclosure = (hks_pushnamedcclosure)GetProcAddress(hksDll, "?hks_pushnamedcclosure@@YAXPEAUlua_State@@P6AH0@ZHPEBDH@Z");
        setfield = (hksi_lua_setfield)GetProcAddress(hksDll, "?hksi_lua_setfield@@YAXPEAUlua_State@@HPEBD@Z");
        checkinteger = (luaL_checkinteger)GetProcAddress(hksDll, "?luaL_checkinteger@@YAHPEAUlua_State@@H@Z");
        gettop = (GetTop)GetProcAddress(hksDll, "?GetTop@LuaState@LuaPlus@@QEBAHXZ");
        dostring = (DoString)GetProcAddress(hksDll, "?DoString@LuaState@LuaPlus@@QEAAHPEBD@Z");
        toboolean = (hksi_lua_toboolean)GetProcAddress(hksDll, "?hksi_lua_toboolean@@YAHPEAUlua_State@@H@Z");
        pushinteger = (hksi_lua_pushinteger)GetProcAddress(hksDll, "?hksi_lua_pushinteger@@YAXPEAUlua_State@@H@Z");
        pushnumber = (hksi_lua_pushnumber)GetProcAddress(hksDll, "?hksi_lua_pushnumber@@YAXPEAUlua_State@@N@Z");
        error = (hksi_luaL_error)GetProcAddress(hksDll, "?hksi_luaL_error@@YAHPEAUlua_State@@PEBDZZ");
        checknumber = (luaL_checknumber)GetProcAddress(hksDll, "?luaL_checknumber@@YANPEAUlua_State@@H@Z");
        pushfstring = (hksi_lua_pushfstring)GetProcAddress(hksDll, "?hksi_lua_pushfstring@@YAPEBDPEAUlua_State@@PEBDZZ");
        checklstring = (CheckLString)GetProcAddress(hksDll, "?hksi_luaL_checklstring@@YAPEBDPEAUlua_State@@HPEA_K@Z");
        pop = (Pop)GetProcAddress(hksDll, "?Pop@LuaState@LuaPlus@@QEAAXH@Z");
        touserdata = (hksi_lua_touserdata)GetProcAddress(hksDll, "?hksi_lua_touserdata@@YAPEAXPEAUlua_State@@H@Z");
        getfield = (hksi_lua_getfield)GetProcAddress(hksDll, "?hksi_lua_getfield@@YAXPEAUlua_State@@HPEBD@Z");
        createtable = (hksi_lua_createtable)GetProcAddress(hksDll, "?lua_createtable@@YAXPEAUlua_State@@HH@Z");
        tocfunction = (lua_tocfunction)GetProcAddress(hksDll, "?lua_tocfunction@@YAP6AHPEAUlua_State@@@Z0H@Z");
        checktable = (hksL_checktable)GetProcAddress(hksDll, "?hksL_checktable@@YAXPEAUlua_State@@H@Z");
        objlen = (hks_lua_objlen)GetProcAddress(hksDll, "?hksi_lua_objlen@@YA_KPEAUlua_State@@H@Z");
        gettable = (hks_lua_gettable)GetProcAddress(hksDll, "?hksi_lua_gettable@@YAXPEAUlua_State@@H@Z");
        cpcall = (hksi_lua_cpcall)GetProcAddress(hksDll, "?hksi_lua_cpcall@@YAHPEAUlua_State@@P6AH0@ZPEAX@Z");
        ref = (Ref)GetProcAddress(hksDll, "?luaL_ref@@YAHPEAUlua_State@@H@Z");
        pcall = (hksi_lua_pcall)GetProcAddress(hksDll, "?hksi_lua_pcall@@YAHPEAUlua_State@@HHH@Z");
        pushvalue = (hski_lua_pushvalue)GetProcAddress(hksDll, "?hksi_lua_pushvalue@@YAXPEAUlua_State@@H@Z");
        rawgeti = (hksi_lua_rawgeti)GetProcAddress(hksDll, "?hksi_lua_rawgeti@@YAXPEAUlua_State@@HH@Z");
        unref = (hksi_lua_unref)GetProcAddress(hksDll, "?hksi_luaL_unref@@YAXPEAUlua_State@@HH@Z");
        settable = (hksi_lua_settable)GetProcAddress(hksDll, "?SetTable@LuaState@LuaPlus@@QEAAXH@Z");
        isnumber = (hksi_lua_isnumber)GetProcAddress(hksDll, "?hksi_lua_isnumber@@YAHPEAUlua_State@@H@Z");
        tonumber = (hksi_lua_tonumber)GetProcAddress(hksDll, "?hksi_lua_tonumber@@YANPEAUlua_State@@H@Z");
        isuserdata = (hksi_lua_isuserdata)GetProcAddress(hksDll, "?hksi_lua_isuserdata@@YAHPEAUlua_State@@H@Z");
        open_debug = (luaopen_debug)GetProcAddress(hksDll, "?luaopen_debug@@YAHPEAUlua_State@@@Z");
        tointeger = (hksi_lua_tointeger)GetProcAddress(hksDll, "?hksi_lua_tointeger@@YAHPEAUlua_State@@H@Z");
        type = (hksi_lua_type)GetProcAddress(hksDll, "?hksi_lua_type@@YAHPEAUlua_State@@H@Z");
        optinteger = (luaL_optinteger)GetProcAddress(hksDll, "?luaL_optinteger@@YAHPEAUlua_State@@HH@Z");
        sethook = (hksi_lua_sethook)GetProcAddress(hksDll, "?hksi_lua_sethook@@YAHPEAUlua_State@@P6AX0PEAUlua_Debug@@@ZHH@Z");
        gethook = (hksi_lua_gethook)GetProcAddress(hksDll, "?hksi_lua_gethook@@YAP6AXPEAUlua_State@@PEAUlua_Debug@@@Z0@Z");
        gethookmask = (hksi_lua_gethookmask)GetProcAddress(hksDll, "?hksi_lua_gethookmask@@YAHPEAUlua_State@@@Z");
        gethookcount = (hksi_lua_gethookcount)GetProcAddress(hksDll, "?hksi_lua_gethookcount@@YAHPEAUlua_State@@@Z");
        newstate = (luaL_newstate)GetProcAddress(hksDll, "?luaL_newstate@@YAPEAUlua_State@@XZ");
        openlibs = (luaL_openlibs)GetProcAddress(hksDll, "?luaL_openlibs@@YAXPEAUlua_State@@@Z");
        close = (luaL_close)GetProcAddress(hksDll, "?lua_close@@YAXPEAUlua_State@@@Z");
        tolstring = (lua_tolstring)GetProcAddress(hksDll, "?lua_tolstring@@YAPEBDPEAUlua_State@@HPEA_K@Z");
        dofile = (DoFile)GetProcAddress(hksDll, "?DoFile@LuaState@LuaPlus@@QEAAHPEBD@Z");
        isstring = (lua_isstring)GetProcAddress(hksDll, "?lua_isstring@@YAHPEAUlua_State@@H@Z");
        tothread = (hksi_lua_tothread)GetProcAddress(hksDll, "?hksi_lua_tothread@@YAPEAUlua_State@@PEAU1@H@Z");
        settop = (lua_settop)GetProcAddress(hksDll, "?lua_settop@@YAXPEAUlua_State@@H@Z");
        checktype = (hksi_luaL_checktype)GetProcAddress(hksDll, "?hksi_luaL_checktype@@YAXPEAUlua_State@@HH@Z");
        rawget = (hksi_lua_rawget)GetProcAddress(hksDll, "?hksi_lua_rawget@@YAXPEAUlua_State@@H@Z");
        pushnil = (lua_pushnil)GetProcAddress(hksDll, "?lua_pushnil@@YAXPEAUlua_State@@@Z");
        getinfo = (hks_lua_getinfo)GetProcAddress(hksDll, "?hksi_lua_getinfo@@YAHPEAUlua_State@@PEBDPEAUlua_Debug@@@Z");
        call = (lua_call)GetProcAddress(hksDll, "?lua_call@@YAXPEAUlua_State@@HH@Z");
        xmove = (XMove)GetProcAddress(hksDll, "?XMove@LuaState@LuaPlus@@QEAAXPEAV12@H@Z");
        rawset = (lua_rawset)GetProcAddress(hksDll, "?lua_rawset@@YAXPEAUlua_State@@H@Z");
        remove = (lua_remove)GetProcAddress(hksDll, "?lua_remove@@YAXPEAUlua_State@@H@Z");
        loadstring = (hksL_loadstring)GetProcAddress(hksDll, "?hksL_loadstring@@YAHPEAUlua_State@@AEBUHksCompilerSettings@@PEBD@Z");
        loadstringa = (LoadStringA)GetProcAddress(hksDll, "?luaL_loadstring@@YAHPEAUlua_State@@PEBD@Z");
        insert = (lua_insert)GetProcAddress(hksDll, "?lua_insert@@YAXPEAUlua_State@@H@Z");

        c_breakpoint = (db_c_breakpoint)((uintptr_t)hksDll + 0x9760);

        StateSettings::getDefaultCompilerSettings = (StateSettings::_getDefaultCompilerSettings)
            GetProcAddress(hksDll, "?getDefaultCompilerSettings@HksStateSettings@@SAAEAUHksCompilerSettings@@XZ");
    }

    int isnil(lua_State *L, int index)
    {
        byte *pbVar1;

        if (LUA_REGISTRYINDEX < index)
        {
            if (index < 1)
            {
                if ((index < 0) &&
                    (pbVar1 = (byte *)((uint64_t)index * 0x10 + *(void ***)((void ***)L + 0x48)),
                     *(byte **)((byte *)L + 0x50) <= pbVar1))
                    goto lab_end;
            }
            else
            {
                pbVar1 = (byte *)(*(byte **)((void **)L + 0x50) + -0x10 + (uint64_t)index * 0x10);
                if (pbVar1 < *(byte **)((void **)L + 0x48))
                {
                    return (int)((*pbVar1 & 0xf) == 0);
                }
            }
            return 0;
        }
        if (index == LUA_REGISTRYINDEX)
        {
            return (int)((*(byte *)(*(byte **)((void **)L + 0x10) + 0x1c8) & 0xf) == 0);
        }
        if (index == LUA_GLOBAL)
        {
            return (int)(((byte)((byte *)L)[0x70] & 0xf) == 0);
        }
        if (index == LUA_GLOBAL)
        {
            *(uint64_t *)((uint64_t *)L + 0x88) = *(uint64_t *)(*(uint64_t **)(*(void ***)((void ***)L + 0x50) + -8) + 0x18);
            *(int *)((int *)L + 0x80) = 5;
            return (int)((*(byte *)((byte *)L + 0x80) & 0xf) == 0);
        }
        pbVar1 = (byte *)(((uint64_t)(-0x2713 - index) + 3) * 0x10 + *(uint64_t *)(*(uint64_t *)((uint64_t *)L + 0x50) + -8));
    lab_end:
        return (int)((*pbVar1 & 0xf) == 0);
    }

    static int get_debug_mask(lua_State *L, const char *str)
    {
        int mask = 0;
        for (; *str != '\0'; str++)
        {
            switch (*str)
            {
            case 'c':
                mask |= LUA_MASKCALL;
                break;
            case 'r':
                mask |= LUA_MASKRET;
                break;
            case 'l':
                mask |= LUA_MASKLINE;
                break;
            case 'C':
                mask |= LUA_MASKCOUNT;
                break;
            default:
                hks::error(L, "invalid hook mask character: %c", *str);
                break;
            }
        }
        return mask;
    }

    void pushboolean(lua_State *L, bool value)
    {
        // Access the Lua stack top pointer
        int *stackTop = *(int **)((uintptr_t)L + 0x48);

        // Push a Lua boolean value onto the stack
        *stackTop = 1;
        stackTop[2] = static_cast<unsigned int>(value);

        // Increment the stack top pointer by 4 bytes
        *(int **)((uintptr_t)L + 0x48) = stackTop + 0x4;
    }

    // GameCore: 0x16a10
    void pushlightuserdata(lua_State *L, void *ptr)
    {
        int *luaStack = *(int **)((uintptr_t)L + 0x48);

        *(void **)(luaStack + 2) = ptr;
        *luaStack = 2;

        *(int **)((uintptr_t)L + 0x48) = luaStack + 0x4;
    }

    static lua_State *getthread(lua_State *L, int *arg)
    {
        if (type(L, 1) == LUA_TTHREAD)
        {
            *arg = 1;
            return tothread(L, 1);
        }
        else
        {
            *arg = 0;
            return L;
        }
    }

    static int makemask(const char *smask, int count)
    {
        int mask = 0;
        if (strchr(smask, 'c'))
            mask |= LUA_MASKCALL;
        if (strchr(smask, 'r'))
            mask |= LUA_MASKRET;
        if (strchr(smask, 'l'))
            mask |= LUA_MASKLINE;
        if (count > 0)
            mask |= LUA_MASKCOUNT;
        return mask;
    }

    static char *unmakemask(int mask, char *smask)
    {
        int i = 0;
        if (mask & LUA_MASKCALL)
            smask[i++] = 'c';
        if (mask & LUA_MASKRET)
            smask[i++] = 'r';
        if (mask & LUA_MASKLINE)
            smask[i++] = 'l';
        smask[i] = '\0';
        return smask;
    }

    static const char KEY_HOOK = 'h';

    static void hookf(lua_State *L, void *ar)
    {
        static const char *const hooknames[] =
            {"call", "return", "line", "count", "tail return"};
        pushlightuserdata(L, (void *)&KEY_HOOK);
        rawget(L, LUA_REGISTRYINDEX);
        pushlightuserdata(L, L);
        rawget(L, -2);
        if (type(L, -1) == LUA_TFUNCTION)
        {
            pushfstring(L, hooknames[*(int *)ar]);   // ar->0x0 - event
            if (*(int *)((uintptr_t)ar + 0x40) >= 0) // ar->0x64 - currentline
                pushinteger(L, *(int *)((uintptr_t)ar + 0x40));
            else
                pushnil(L);
            getinfo(L, (char *)"lS", ar);
            call(L, 2, 0);
        }
    }

    static void gethooktable(lua_State *L)
    {
        pushlightuserdata(L, (void *)&KEY_HOOK);
        rawget(L, LUA_REGISTRYINDEX);
        if (type(L, -1) != LUA_TTABLE)
        {
            pop(L, 1);
            createtable(L, 0, 1);
            pushlightuserdata(L, (void *)&KEY_HOOK);
            pushvalue(L, -2);
            rawset(L, LUA_REGISTRYINDEX);
        }
    }

    int db_sethook(lua_State *L)
    {
        int arg;
        lua_State *L1 = getthread(L, &arg);
        if (int test = isnoneornil(L, arg + 1))
        {
            settop(L, arg + 1);
            sethook(L1, NULL, 0, 0);
        }
        else
        {
            const char *smask = checklstring(L, arg + 2, NULL);
            int count = optinteger(L, arg + 3, 0);
            checktype(L, arg + 1, LUA_TFUNCTION);
            sethook(L1, (void *)hookf, makemask(smask, count), count);
        }
        gethooktable(L1);
        pushlightuserdata(L1, L1);
        pushvalue(L, arg + 1);
        xmove(L, L1, 1);
        rawset(L1, -3);
        pop(L1, 1);
        return 0;
    }

    static int hook_id = 0;
    int db_gethook(lua_State *L)
    {
        int arg;
        lua_State *L1 = getthread(L, &arg);
        char buff[5];
        int mask = gethookmask(L1);
        void *hook = gethook(L1);
        if (hook != NULL && hook != hookf)
        {
            pushfstring(L, "external hook");
        }
        else
        {
            gethooktable(L1);
            pushlightuserdata(L1, L1);
            rawget(L1, -2);
            remove(L, 1);
            xmove(L1, L, 1);
        }
        pushfstring(L, unmakemask(mask, buff));
        pushinteger(L, gethookcount(L1));
        return 3;
    }

    // Should only ever be called once.
    void init()
    {
        hksDll = LoadLibrary(TEXT("HavokScript_FinalRelease.dll"));
        if (hksDll == NULL)
        {
            std::cout << "Failed to load HavokScript! " << GetLastError() << '\n';
            return;
        }
    }

    void uninit()
    {
        FreeLibrary(hksDll);
    }
}

int main(int argc, char *argv[])
{
    hks::init();
    hks::init_imports();

    hks::lua_State *L = hks::newstate();
    hks::openlibs(L);

    const char *lua_path = getenv("LUA_PATH");
    std::stringstream lua_path_stream(".\\?.lua;!\\?.lua;!\\init.lua;");
    if (lua_path != NULL)
    {
        lua_path_stream << lua_path;
    }

    hks::getfield(L, hks::LUA_GLOBAL, "package");
    hks::pushfstring(L, lua_path_stream.str().c_str());
    hks::setfield(L, -2, "path");
    hks::pop(L, 1);

    hks::getfield(L, hks::LUA_GLOBAL, "debug");
    PushLuaMethod(L, hks::db_gethook, "db_gethook", -2, "gethook");
    PushLuaMethod(L, hks::db_sethook, "db_sethook", -2, "sethook");
    hks::pop(L, 1);

    if (argc == 2)
    {
        if (hks::dofile(L, argv[1]) != LUA_OK)
        {
            std::cerr << hks::tolstring(L, -1, NULL) << std::endl;
            hks::pop(L, 1);
        }
    }
    else if (argc == 1)
    {
        std::string input;
        while (std::cout << "> " && std::getline(std::cin, input) && input != "exit")
        {
            if (hks::dostring(L, input.data()) != LUA_OK)
            {
                std::cerr << hks::tolstring(L, -1, NULL) << std::endl;
                hks::pop(L, 1);
            }
        }
    }
    else
    {
        std::cerr << "Error: Improper arguments. Usage: " << argv[0] << " [fileName]" << std::endl;
    }

    hks::close(L);
    hks::uninit();

    return 0;
}