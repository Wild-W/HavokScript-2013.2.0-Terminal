int __cdecl hksL_loadstring(struct lua_State * __ptr64,struct HksCompilerSettings const &,char const * __ptr64);
void __cdecl hksL_register(struct lua_State * __ptr64,char const * __ptr64,struct luaL_Reg const * __ptr64,int);
void __cdecl hksL_tostring(struct lua_State * __ptr64,int);
void __cdecl hksL_totable(struct lua_State * __ptr64);
void __cdecl hks_combine(struct lua_State * __ptr64,int,char const * __ptr64);
int __cdecl hks_debugbreakpoint(struct lua_State * __ptr64,char const * __ptr64);
int __cdecl hks_debugprint(struct lua_State * __ptr64,int);
int __cdecl hks_dump(struct lua_State * __ptr64,int (__cdecl*)(struct lua_State * __ptr64,void const * __ptr64,unsigned __int64,void * __ptr64),void * __ptr64,enum HksBytecodeStrippingLevel);
void __cdecl hks_dumpstats(struct lua_State * __ptr64);
int __cdecl hks_error(struct lua_State * __ptr64,enum HksError);
char const * __ptr64 __cdecl hks_getname(struct lua_State * __ptr64);
void __cdecl hks_graphheap(struct lua_State * __ptr64,char const * __ptr64);
int __cdecl hks_isstruct(struct lua_State * __ptr64,int);
int __cdecl hks_load(struct lua_State * __ptr64,struct HksCompilerSettings const &,char const * __ptr64 (__cdecl*)(struct lua_State * __ptr64,void * __ptr64,unsigned __int64 * __ptr64),void * __ptr64,char const * __ptr64);
void __cdecl hks_memorystats(struct lua_State * __ptr64,char const * __ptr64);
struct lua_State * __ptr64 __cdecl hks_newstate(class HksStateSettings const &);
void __cdecl hks_newstruct(struct lua_State * __ptr64,char const * __ptr64,int);
int __cdecl hks_next_placeholder(struct lua_State * __ptr64);
void __cdecl hks_obj_assertCanUseForReffing(struct lua_State * __ptr64,struct HksObject const * __ptr64);
int __cdecl hks_obj_equal(struct lua_State * __ptr64,struct HksObject const * __ptr64,struct HksObject const * __ptr64);
int __cdecl hks_obj_lessthan(struct lua_State * __ptr64,struct HksObject const * __ptr64,struct HksObject const * __ptr64);
int __cdecl hks_obj_markUsedForReffing(struct lua_State * __ptr64,struct HksObject const * __ptr64);
struct HksObject __cdecl hks_obj_newlstringhashed(struct lua_State * __ptr64,char const * __ptr64,unsigned __int64,unsigned int);
void __cdecl hks_obj_next(struct lua_State * __ptr64,struct HksObject const * __ptr64,struct HksObject * __ptr64,struct HksObject * __ptr64);
unsigned __int64 __cdecl hks_obj_objlen(struct lua_State * __ptr64,struct HksObject const * __ptr64);
int __cdecl hks_obj_rawequal(struct lua_State * __ptr64,struct HksObject const * __ptr64,struct HksObject const * __ptr64);
void __cdecl hks_obj_rawget(struct lua_State * __ptr64,struct HksObject const * __ptr64,struct HksObject const * __ptr64,struct HksObject * __ptr64);
struct HksObject __cdecl hks_obj_rawget_array(struct lua_State * __ptr64,struct HksObject const * __ptr64,int);
void __cdecl hks_obj_rawgeti(struct lua_State * __ptr64,struct HksObject const * __ptr64,int,struct HksObject * __ptr64);
void __cdecl hks_obj_rawgetslot_outofline(struct lua_State * __ptr64,class hks::StructInst const * __ptr64,class hks::InternString * __ptr64);
void __cdecl hks_obj_rawsetslot_outofline(struct lua_State * __ptr64,class hks::StructInst * __ptr64,class hks::InternString * __ptr64);
int __cdecl hks_obj_setfenv(struct lua_State * __ptr64,struct HksObject const * __ptr64,struct HksObject const * __ptr64);
int __cdecl hks_obj_setmetatable(struct lua_State * __ptr64,struct HksObject const * __ptr64,struct HksObject const * __ptr64);
void __cdecl hks_obj_settable(struct lua_State * __ptr64,struct HksObject const * __ptr64,struct HksObject const * __ptr64,struct HksObject const * __ptr64);
char const * __ptr64 __cdecl hks_obj_tolstring(struct lua_State * __ptr64,struct HksObject * __ptr64,unsigned __int64 * __ptr64);
double __cdecl hks_obj_tonumber(struct lua_State * __ptr64,struct HksObject const * __ptr64);
void __cdecl hks_persist(struct lua_State * __ptr64,int (__cdecl*)(struct lua_State * __ptr64,void const * __ptr64,unsigned __int64,void * __ptr64),void * __ptr64);
void __cdecl hks_profile(struct lua_State * __ptr64,int);
void __cdecl hks_pushcclosure(struct lua_State * __ptr64,int (__cdecl*)(struct lua_State * __ptr64),int,char const * __ptr64,int,int);
void __cdecl hks_pushnamedcclosure(struct lua_State * __ptr64,int (__cdecl*)(struct lua_State * __ptr64),int,char const * __ptr64,int);
void __cdecl hksi_luaL_pushresult(struct luaL_Buffer * __ptr64);
int __cdecl hksi_luaL_ref(struct lua_State * __ptr64,int);
char const * __ptr64 __cdecl hksi_luaL_typename(struct lua_State * __ptr64,int);
int __cdecl hksi_luaL_typerror(struct lua_State * __ptr64,int,char const * __ptr64);
void __cdecl hksi_luaL_unref(struct lua_State * __ptr64,int,int);
void __cdecl hksi_luaL_where(struct lua_State * __ptr64,int);
int (__cdecl*__cdecl hksi_lua_atpanic(struct lua_State * __ptr64,int (__cdecl*)(struct lua_State * __ptr64)))(struct lua_State * __ptr64);
void __cdecl hksi_lua_call(struct lua_State * __ptr64,int,int);
void __cdecl hksi_lua_close(struct lua_State * __ptr64);
void __cdecl hksi_lua_concat(struct lua_State * __ptr64,int);
void * __ptr64 (__cdecl*__cdecl hksi_lua_getallocf(struct lua_State * __ptr64,void * __ptr64 * __ptr64))(void * __ptr64,void * __ptr64,unsigned __int64,unsigned __int64);
void __cdecl hksi_lua_getfenv(struct lua_State * __ptr64,int);
void __cdecl hksi_lua_getfield(struct lua_State * __ptr64,int,char const * __ptr64);
void (__cdecl*__cdecl hksi_lua_gethook(struct lua_State * __ptr64))(struct lua_State * __ptr64,struct lua_Debug * __ptr64);
int __cdecl hksi_lua_gethookcount(struct lua_State * __ptr64);
int __cdecl hksi_lua_gethookmask(struct lua_State * __ptr64);
int __cdecl hksi_lua_getinfo(struct lua_State * __ptr64,char const * __ptr64,struct lua_Debug * __ptr64);
char const * __ptr64 __cdecl hksi_lua_getlocal(struct lua_State * __ptr64,struct lua_Debug * __ptr64,int);
int __cdecl hksi_lua_getmetatable(struct lua_State * __ptr64,int);
int __cdecl hksi_lua_getstack(struct lua_State * __ptr64,int,struct lua_Debug * __ptr64);
int __cdecl hksi_lua_isstring(struct lua_State * __ptr64,int);
int __cdecl hksi_lua_isuserdata(struct lua_State * __ptr64,int);
int __cdecl hksi_lua_lessthan(struct lua_State * __ptr64,int,int);
int __cdecl hksi_lua_load(struct lua_State * __ptr64,char const * __ptr64 (__cdecl*)(struct lua_State * __ptr64,void * __ptr64,unsigned __int64 * __ptr64),void * __ptr64,char const * __ptr64);
struct lua_State * __ptr64 __cdecl hksi_lua_newthread(struct lua_State * __ptr64);
void * __ptr64 __cdecl hksi_lua_newuserdata(struct lua_State * __ptr64,unsigned __int64);
int __cdecl hksi_lua_next(struct lua_State * __ptr64,int);
unsigned __int64 __cdecl hksi_lua_objlen(struct lua_State * __ptr64,int);
int __cdecl hksi_lua_pcall(struct lua_State * __ptr64,int,int,int);
char const * __ptr64 __cdecl hksi_lua_pushfstring(struct lua_State * __ptr64,char const * __ptr64,...);
char const * __ptr64 __cdecl hksi_lua_pushvfstring(struct lua_State * __ptr64,char const * __ptr64,char * __ptr64);
int __cdecl hksi_lua_rawequal(struct lua_State * __ptr64,int,int);
void __cdecl hksi_lua_rawget(struct lua_State * __ptr64,int);
void * __ptr64 __cdecl hksi_lua_rawget_array_lud(struct lua_State * __ptr64,int,int);
void __cdecl hksi_lua_rawgeti(struct lua_State * __ptr64,int,int);
unsigned __int64 __cdecl hksi_lua_rawlength(struct lua_State * __ptr64,int);
void __cdecl hksi_lua_rawset(struct lua_State * __ptr64,int);
void __cdecl hksi_lua_rawset_array(struct lua_State * __ptr64,int,int);
void __cdecl hksi_lua_rawset_array_lud(struct lua_State * __ptr64,int,int,void * __ptr64);
void __cdecl hksi_lua_rawseti(struct lua_State * __ptr64,int,int);
int __cdecl hksi_lua_sethook(struct lua_State * __ptr64,void (__cdecl*)(struct lua_State * __ptr64,struct lua_Debug * __ptr64),int,int);
char const * __ptr64 __cdecl hksi_lua_setlocal(struct lua_State * __ptr64,struct lua_Debug * __ptr64,int);
int __cdecl hksi_lua_setmetatable(struct lua_State * __ptr64,int);
void __cdecl hksi_lua_settop(struct lua_State * __ptr64,int);
char const * __ptr64 __cdecl hksi_lua_setupvalue(struct lua_State * __ptr64,int,int);
int __cdecl hksi_lua_toboolean(struct lua_State * __ptr64,int);
int (__cdecl*__cdecl hksi_lua_tocfunction(struct lua_State * __ptr64,int))(struct lua_State * __ptr64);
int __cdecl hksi_lua_tointeger(struct lua_State * __ptr64,int);
char const * __ptr64 __cdecl hksi_lua_tolstring(struct lua_State * __ptr64,int,unsigned __int64 * __ptr64);
double __cdecl hksi_lua_tonumber(struct lua_State * __ptr64,int);
void __cdecl luaI_openlib(struct lua_State * __ptr64,char const * __ptr64,struct luaL_Reg const * __ptr64,int);
void __cdecl luaL_addchar(struct luaL_Buffer * __ptr64,char);
void __cdecl luaL_addlstring(struct luaL_Buffer * __ptr64,char const * __ptr64,unsigned __int64);
void __cdecl luaL_addsize(struct luaL_Buffer * __ptr64,unsigned __int64);
void __cdecl luaL_addstring(struct luaL_Buffer * __ptr64,char const * __ptr64);
void __cdecl luaL_addvalue(struct luaL_Buffer * __ptr64);
void __cdecl luaL_argcheck(struct lua_State * __ptr64,int,int,char const * __ptr64);
double __cdecl luaL_checknumber(struct lua_State * __ptr64,int);
int __cdecl luaL_checkoption(struct lua_State * __ptr64,int,char const * __ptr64,char const * __ptr64 const * __ptr64 const);
void __cdecl luaL_checkstack(struct lua_State * __ptr64,int,char const * __ptr64);
void __cdecl luaL_checktype(struct lua_State * __ptr64,int,int);
void * __ptr64 __cdecl luaL_checkudata(struct lua_State * __ptr64,int,char const * __ptr64);
int __cdecl luaL_error(struct lua_State * __ptr64,char const * __ptr64,...);
char const * __ptr64 __cdecl luaL_findtable(struct lua_State * __ptr64,int,char const * __ptr64,int);
int __cdecl luaL_getmetafield(struct lua_State * __ptr64,int,char const * __ptr64);
void __cdecl luaL_getmetatable(struct lua_State * __ptr64,char const * __ptr64);
char const * __ptr64 __cdecl luaL_gsub(struct lua_State * __ptr64,char const * __ptr64,char const * __ptr64,char const * __ptr64);
int __cdecl luaL_optinteger(struct lua_State * __ptr64,int,int);
char const * __ptr64 __cdecl luaL_optlstring(struct lua_State * __ptr64,int,char const * __ptr64,unsigned __int64 * __ptr64);
double __cdecl luaL_optnumber(struct lua_State * __ptr64,int,double);
char * __ptr64 __cdecl luaL_prepbuffer(struct luaL_Buffer * __ptr64);
void __cdecl luaL_pushresult(struct luaL_Buffer * __ptr64);
int __cdecl luaL_ref(struct lua_State * __ptr64,int);
void __cdecl luaL_register(struct lua_State * __ptr64,char const * __ptr64,struct luaL_Reg const * __ptr64);
char const * __ptr64 __cdecl luaL_typename(struct lua_State * __ptr64,int);
int __cdecl luaL_typerror(struct lua_State * __ptr64,int,char const * __ptr64);
void __cdecl luaL_unref(struct lua_State * __ptr64,int,int);
void __cdecl lua_createtable(struct lua_State * __ptr64,int,int);
int __cdecl lua_dump(struct lua_State * __ptr64,int (__cdecl*)(struct lua_State * __ptr64,void const * __ptr64,unsigned __int64,void * __ptr64),void * __ptr64);
int __cdecl lua_equal(struct lua_State * __ptr64,int,int);
int __cdecl lua_error(struct lua_State * __ptr64);
int __cdecl lua_gc(struct lua_State * __ptr64,int,int);
void * __ptr64 (__cdecl*__cdecl lua_getallocf(struct lua_State * __ptr64,void * __ptr64 * __ptr64))(void * __ptr64,void * __ptr64,unsigned __int64,unsigned __int64);
void __cdecl lua_getfenv(struct lua_State * __ptr64,int);
void __cdecl lua_getfield(struct lua_State * __ptr64,int,char const * __ptr64);
void (__cdecl*__cdecl lua_gethook(struct lua_State * __ptr64))(struct lua_State * __ptr64,struct lua_Debug * __ptr64);
int __cdecl lua_gethookcount(struct lua_State * __ptr64);
int __cdecl lua_gettop(struct lua_State * __ptr64);
char const * __ptr64 __cdecl lua_getupvalue(struct lua_State * __ptr64,int,int);
void __cdecl lua_insert(struct lua_State * __ptr64,int);
int __cdecl lua_iscfunction(struct lua_State * __ptr64,int);
int __cdecl lua_isnumber(struct lua_State * __ptr64,int);
int __cdecl lua_isstring(struct lua_State * __ptr64,int);
int __cdecl lua_isuserdata(struct lua_State * __ptr64,int);
int __cdecl lua_lessthan(struct lua_State * __ptr64,int,int);
int __cdecl lua_load(struct lua_State * __ptr64,char const * __ptr64 (__cdecl*)(struct lua_State * __ptr64,void * __ptr64,unsigned __int64 * __ptr64),void * __ptr64,char const * __ptr64);
struct lua_State * __ptr64 __cdecl lua_newstate(void * __ptr64 (__cdecl*)(void * __ptr64,void * __ptr64,unsigned __int64,unsigned __int64),void * __ptr64);
namespace hks {
    class HeapAssertions {
        public:
        __cdecl HeapAssertions(struct lua_State * __ptr64);
        __cdecl ~HeapAssertions(void);
        HeapAssertions & __cdecl operator=(class hks::HeapAssertions const &);
    };
    class ApiStackCheck {
        public:
        __cdecl ApiStackCheck(struct lua_State * __ptr64,int,int,int);
        __cdecl ~ApiStackCheck(void);
    };
    class MemoryBuffer {
        public:
        __cdecl MemoryBuffer(struct lua_State * __ptr64);
        void __cdecl grow(void);
    };
    class StringTable {
        public:
        hks::InternString * __ptr64 __cdecl internHashed(struct lua_State * __ptr64,char const * __ptr64,unsigned __int64,unsigned int);
    };
    class StructInst;
    class InternString;
}
namespace LuaPlus {
    void __cdecl RegisterErrorCallback(void (__cdecl*)(struct lua_State * __ptr64,char const * __ptr64));
    void __cdecl ReportError(struct lua_State * __ptr64);
    void __cdecl ReportStackTrace(struct lua_State * __ptr64,char const * __ptr64);
    class LuaObject {
        public:
        __cdecl LuaObject(class LuaPlus::LuaObject const &);
        __cdecl LuaObject(class LuaPlus::LuaStackObject const &);
        __cdecl LuaObject(class LuaPlus::LuaState * __ptr64);
        __cdecl LuaObject(class LuaPlus::LuaState * __ptr64,int);
        __cdecl LuaObject(void);
        __cdecl ~LuaObject(void);
        LuaObject & __cdecl operator=(class LuaPlus::LuaObject const &);
        LuaObject __cdecl operator[](char const * __ptr64)const;
        void __cdecl AssignBoolean(class LuaPlus::LuaState * __ptr64,bool);
        void __cdecl AssignInteger(class LuaPlus::LuaState * __ptr64,int);
        void __cdecl AssignLightUserData(class LuaPlus::LuaState * __ptr64,void * __ptr64);
        void __cdecl AssignNewTable(class LuaPlus::LuaState * __ptr64,int,int);
        void __cdecl AssignNil(class LuaPlus::LuaState * __ptr64);
        void __cdecl AssignNumber(class LuaPlus::LuaState * __ptr64,double);
        void __cdecl AssignObject(class LuaPlus::LuaObject &);
        void __cdecl AssignString(class LuaPlus::LuaState * __ptr64,char const * __ptr64);
        void __cdecl AssignThread(class LuaPlus::LuaState * __ptr64);
        LuaObject __cdecl CreateTable(class LuaPlus::LuaObject const &);
        LuaObject __cdecl CreateTable(int);
        LuaObject __cdecl CreateTable(char const * __ptr64);
        LuaObject __cdecl GetByObject(class LuaPlus::LuaObject const &);
        lua_State * __ptr64 __cdecl GetCState(void)const;
        int __cdecl GetCount(void)const;
        float __cdecl GetFloat(void)const;
        int __cdecl GetInteger(void)const;
        void * __ptr64 __cdecl GetLightUserData(void)const;
        void * __ptr64 __cdecl GetLightUserData(void)const;
        LuaObject __cdecl GetMetaTable(void)const;
        LuaObject __cdecl RawGetByIndex(int);
        LuaObject __cdecl RawGetByName(char const * __ptr64);
        LuaObject __cdecl RawGetByObject(class LuaPlus::LuaObject const &);
        void __cdecl Register(char const * __ptr64,int (__cdecl*)(struct lua_State * __ptr64),int);
        void __cdecl Register(char const * __ptr64,int (__cdecl*)(class LuaPlus::LuaState * __ptr64),int);
        void __cdecl Reset(void);
        void __cdecl SetBoolean(class LuaPlus::LuaObject const &,bool);
        void __cdecl SetBoolean(int,bool);
        void __cdecl SetBoolean(char const * __ptr64,bool);
        void __cdecl SetInvalidObject(void);
        void __cdecl SetLightUserData(class LuaPlus::LuaObject const &,void * __ptr64);
        void __cdecl SetLightUserData(int,void * __ptr64);
        void __cdecl SetLightUserData(char const * __ptr64,void * __ptr64);
        void __cdecl SetMetaTable(class LuaPlus::LuaObject const &);
        void __cdecl SetNumber(class LuaPlus::LuaObject const &,double);
        void __cdecl SetNumber(int,double);
        void __cdecl SetNumber(char const * __ptr64,double);
        void __cdecl SetObject(class LuaPlus::LuaObject const &,class LuaPlus::LuaObject const &);
        void __cdecl SetObject(int,class LuaPlus::LuaObject const &);
        void __cdecl SetObject(char const * __ptr64,class LuaPlus::LuaObject const &);
        void __cdecl SimplePush(void)const;
        void __cdecl Sort(void);
        unsigned __int64 __cdecl StrLen(void)const;
        double __cdecl ToNumber(void)const;
        char const * __ptr64 __cdecl ToString(void);
    };
    class LuaStackObject {
        public:
        LuaStackObject & __cdecl operator=(class LuaPlus::LuaStackObject const &);
        LuaStackObject __cdecl operator[](int)const;
        LuaStackObject __cdecl operator[](char const * __ptr64)const;
        LuaStackObject __cdecl CreateTable(int,int,int);
        LuaStackObject __cdecl CreateTable(char const * __ptr64,int,int);
        LuaStackObject __cdecl GetByName(char const * __ptr64);
        int (__cdecl*__cdecl GetCFunction(void)const)(struct lua_State * __ptr64);
        lua_State * __ptr64 __cdecl GetCState(void)const;
        int __cdecl GetCount(void)const;
        double __cdecl GetDouble(void)const;
        int __cdecl GetInteger(void)const;
        void * __ptr64 __cdecl GetLightUserData(void)const;
        void __cdecl SetBoolean(int,bool);
        void __cdecl SetBoolean(char const * __ptr64,bool);
        void __cdecl SetLightUserData(int,void * __ptr64);
        void __cdecl SetLightUserData(char const * __ptr64,void * __ptr64);
        void __cdecl SetMetaTable(class LuaPlus::LuaStackObject);
        void __cdecl SetMetaTable(void);
        void __cdecl SetNumber(int,double);
        void __cdecl SetNumber(char const * __ptr64,double);
        void __cdecl SetObject(int,class LuaPlus::LuaStackObject &);
        void __cdecl SetObject(char const * __ptr64,class LuaPlus::LuaStackObject &);
        unsigned __int64 __cdecl StrLen(void)const;
    };
    class LuaStateOutFile {
        public:
        __cdecl LuaStateOutFile(class LuaPlus::LuaStateOutFile const &);
        __cdecl LuaStateOutFile(struct lua_State * __ptr64,char const * __ptr64);
        __cdecl LuaStateOutFile(void);
        bool __cdecl Assign(struct HksFile * __ptr64);
    };
    class LuaStackTableIterator {
        public:
        LuaStackTableIterator & __cdecl operator++(void);
        LuaStackObject __cdecl GetKey(void);
        void __cdecl Reset(void);
        class LuaPlus::LuaStackTableIterator & __cdecl LuaStackTableIterator::operator++(void);
    };
    class LuaStack {
        public:
        LuaStack & __cdecl operator=(class LuaPlus::LuaStack const &);
        LuaStackObject __cdecl operator[](int);
    };
    class LuaState {
        public:
        __cdecl LuaState(struct lua_State * __ptr64);
        void __cdecl CheckAny(int);
        int __cdecl CheckInt(int);
        int __cdecl CheckInteger(int);
        char const * __ptr64 __cdecl CheckLString(int,unsigned __int64 * __ptr64);
        long __cdecl CheckLong(int);
        double __cdecl CheckNumber(int);
        int __cdecl CheckOption(int,char const * __ptr64,char const * __ptr64 const * __ptr64 const);
        int __cdecl CheckStack(int);
        void __cdecl CheckStack(int,char const * __ptr64);
        char const * __ptr64 __cdecl CheckString(int);
        int __cdecl CollectGarbage(int,int);
        void __cdecl Concat(int);
        LuaState * __ptr64 __cdecl Create(class HksStateSettings &,bool);
        LuaState * __ptr64 __cdecl Create(bool);
        LuaStackObject __cdecl CreateTable(int,int);
        int __cdecl Dump(int (__cdecl*)(struct lua_State * __ptr64,void const * __ptr64,unsigned __int64,void * __ptr64),void * __ptr64,int,char);
        bool __cdecl DumpGlobals(class LuaPlus::LuaStateOutFile &,unsigned int,unsigned int);
        bool __cdecl DumpGlobals(char const * __ptr64,unsigned int,unsigned int);
        bool __cdecl DumpObject(class LuaPlus::LuaStateOutFile &,class LuaPlus::LuaObject &,class LuaPlus::LuaObject &,unsigned int,int,unsigned int);
        int __cdecl Equal(class LuaPlus::LuaObject const &,class LuaPlus::LuaObject const &);
        int __cdecl Equal(int,int);
        int __cdecl Error(char const * __ptr64,...);
        int __cdecl Error(void);
        char const * __ptr64 __cdecl FindTable(int,char const * __ptr64,int);
        int __cdecl GC(int,int);
        lua_State * __ptr64 __cdecl GetCState(void)const;
        char const * __ptr64 __cdecl GetLocal(struct lua_Debug * __ptr64,int);
        LuaStackObject __cdecl GetMetaTable(int);
        void __cdecl RawGetI(int,int);
        void __cdecl RawSet(int);
        void __cdecl RawSetI(int,int);
        int __cdecl Ref(int);
        char const * __ptr64 __cdecl SetLocal(struct lua_Debug * __ptr64,int);
        void __cdecl SetTop(int);
        char const * __ptr64 __cdecl SetUpValue(int,int);
        LuaStackObject __cdecl Stack(int);
        LuaStackObject __cdecl StackTop(void);
        void __cdecl Where(int);
        void __cdecl XMove(class LuaPlus::LuaState * __ptr64,int);
    };
    class LuaTableIterator {
        public:
        __cdecl LuaTableIterator(class LuaPlus::LuaTableIterator const &);
        __cdecl LuaTableIterator(class LuaPlus::LuaObject const &);
        class LuaPlus::LuaObject & __cdecl GetKey(void);
        void __cdecl Reset(void);
        class LuaPlus::LuaTableIterator & __cdecl operator++(void);
    };
}
/* Missing:
__cdecl LuaPlus::LuaObject::operator struct LuaPlus::LuaPlusBoolType const volatile * __ptr64(void)const __ptr64
__cdecl LuaPlus::LuaStackObject::operator int(void)const __ptr64
__cdecl LuaPlus::LuaStackTableIterator::operator bool(void)const __ptr64
__cdecl LuaPlus::LuaState::operator struct lua_State * __ptr64(void) __ptr64
__cdecl LuaPlus::LuaTableIterator::operator bool(void)const __ptr64
*/
class HksFixedHeapSettings {
    public:
    HksFixedHeapSettings & __cdecl operator=(class HksFixedHeapSettings const &);
};
class HksStateSettings {
    public:
    HksFixedHeapSettings & __cdecl operator=(class HksStateSettings const &);
    HksCompilerSettings * __cdecl getDefaultCompilerSettings(void);
};
class HksCompilerSettings {
    public:
    __cdecl HksCompilerSettings(void);
    enum IntLiteralOptions;
    enum BytecodeSharingFormat;
    struct HksCompilerSettings & __cdecl operator=(struct HksCompilerSettings &&);
    struct HksCompilerSettings & __cdecl operator=(struct HksCompilerSettings const &);
    int __cdecl _isHksGlobalMemoTestingMode(void)const;
    void __cdecl _setHksGlobalMemoTestingMode(int);
    enum HksCompilerSettings::BytecodeSharingFormat __cdecl getBytecodeSharingFormat(void)const;
    enum HksCompilerSettings::IntLiteralOptions __cdecl getIntLiteralsEnabled(void)const;
    char const * __ptr64 * __ptr64 __cdecl getStrip(void)const;
    unsigned __int64 __cdecl getStripSize(void)const;
    int __cdecl isEmitStruct(void)const;
    int __cdecl isGlobalMemoization(void)const;
};
