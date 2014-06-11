#include "lua_super_anim_auto.hpp"
#include "SuperAnimNodeV2.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_sa_SuperAnimNodeListener_OnAnimSectionEnd(lua_State* tolua_S)
{
    int argc = 0;
    SuperAnim::SuperAnimNodeListener* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sa.SuperAnimNodeListener",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SuperAnim::SuperAnimNodeListener*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_sa_SuperAnimNodeListener_OnAnimSectionEnd'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        std::string arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->OnAnimSectionEnd(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "OnAnimSectionEnd",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNodeListener_OnAnimSectionEnd'.",&tolua_err);
#endif

    return 0;
}
int lua_sa_SuperAnimNodeListener_OnTimeEvent(lua_State* tolua_S)
{
    int argc = 0;
    SuperAnim::SuperAnimNodeListener* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sa.SuperAnimNodeListener",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SuperAnim::SuperAnimNodeListener*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_sa_SuperAnimNodeListener_OnTimeEvent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        int arg0;
        std::string arg1;
        int arg2;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1);

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2);
        if(!ok)
            return 0;
        cobj->OnTimeEvent(arg0, arg1, arg2);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "OnTimeEvent",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNodeListener_OnTimeEvent'.",&tolua_err);
#endif

    return 0;
}
static int lua_sa_SuperAnimNodeListener_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (SuperAnimNodeListener)");
    return 0;
}

int lua_register_sa_SuperAnimNodeListener(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"sa.SuperAnimNodeListener");
    tolua_cclass(tolua_S,"SuperAnimNodeListener","sa.SuperAnimNodeListener","",nullptr);

    tolua_beginmodule(tolua_S,"SuperAnimNodeListener");
        tolua_function(tolua_S,"OnAnimSectionEnd",lua_sa_SuperAnimNodeListener_OnAnimSectionEnd);
        tolua_function(tolua_S,"OnTimeEvent",lua_sa_SuperAnimNodeListener_OnTimeEvent);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(SuperAnim::SuperAnimNodeListener).name();
    g_luaType[typeName] = "sa.SuperAnimNodeListener";
    g_typeCast["SuperAnimNodeListener"] = "sa.SuperAnimNodeListener";
    return 1;
}

int lua_sa_SuperAnimNode_draw(lua_State* tolua_S)
{
    int argc = 0;
    SuperAnim::SuperAnimNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sa.SuperAnimNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SuperAnim::SuperAnimNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_sa_SuperAnimNode_draw'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::Renderer* arg0;
        cocos2d::Mat4 arg1;
        bool arg2;

        ok &= luaval_to_object<cocos2d::Renderer>(tolua_S, 2, "cc.Renderer",&arg0);

        ok &= luaval_to_mat4(tolua_S, 3, &arg1);

        ok &= luaval_to_boolean(tolua_S, 4,&arg2);
        if(!ok)
            return 0;
        cobj->draw(arg0, arg1, arg2);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "draw",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNode_draw'.",&tolua_err);
#endif

    return 0;
}
int lua_sa_SuperAnimNode_onDraw(lua_State* tolua_S)
{
    int argc = 0;
    SuperAnim::SuperAnimNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sa.SuperAnimNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SuperAnim::SuperAnimNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_sa_SuperAnimNode_onDraw'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Mat4 arg0;
        bool arg1;

        ok &= luaval_to_mat4(tolua_S, 2, &arg0);

        ok &= luaval_to_boolean(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->onDraw(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "onDraw",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNode_onDraw'.",&tolua_err);
#endif

    return 0;
}
int lua_sa_SuperAnimNode_replaceSprite(lua_State* tolua_S)
{
    int argc = 0;
    SuperAnim::SuperAnimNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sa.SuperAnimNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SuperAnim::SuperAnimNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_sa_SuperAnimNode_replaceSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->replaceSprite(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "replaceSprite",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNode_replaceSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_sa_SuperAnimNode_removeTimeEvent(lua_State* tolua_S)
{
    int argc = 0;
    SuperAnim::SuperAnimNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sa.SuperAnimNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SuperAnim::SuperAnimNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_sa_SuperAnimNode_removeTimeEvent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        int arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        if(!ok)
            return 0;
        cobj->removeTimeEvent(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeTimeEvent",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNode_removeTimeEvent'.",&tolua_err);
#endif

    return 0;
}
int lua_sa_SuperAnimNode_Resume(lua_State* tolua_S)
{
    int argc = 0;
    SuperAnim::SuperAnimNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sa.SuperAnimNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SuperAnim::SuperAnimNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_sa_SuperAnimNode_Resume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->Resume();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "Resume",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNode_Resume'.",&tolua_err);
#endif

    return 0;
}
int lua_sa_SuperAnimNode_registerTimeEvent(lua_State* tolua_S)
{
    int argc = 0;
    SuperAnim::SuperAnimNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sa.SuperAnimNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SuperAnim::SuperAnimNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_sa_SuperAnimNode_registerTimeEvent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        std::string arg0;
        double arg1;
        int arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_number(tolua_S, 3,&arg1);

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2);
        if(!ok)
            return 0;
        cobj->registerTimeEvent(arg0, arg1, arg2);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "registerTimeEvent",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNode_registerTimeEvent'.",&tolua_err);
#endif

    return 0;
}
int lua_sa_SuperAnimNode_setFlipY(lua_State* tolua_S)
{
    int argc = 0;
    SuperAnim::SuperAnimNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sa.SuperAnimNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SuperAnim::SuperAnimNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_sa_SuperAnimNode_setFlipY'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setFlipY(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setFlipY",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNode_setFlipY'.",&tolua_err);
#endif

    return 0;
}
int lua_sa_SuperAnimNode_setFlipX(lua_State* tolua_S)
{
    int argc = 0;
    SuperAnim::SuperAnimNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sa.SuperAnimNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SuperAnim::SuperAnimNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_sa_SuperAnimNode_setFlipX'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setFlipX(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setFlipX",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNode_setFlipX'.",&tolua_err);
#endif

    return 0;
}
int lua_sa_SuperAnimNode_update(lua_State* tolua_S)
{
    int argc = 0;
    SuperAnim::SuperAnimNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sa.SuperAnimNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SuperAnim::SuperAnimNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_sa_SuperAnimNode_update'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->update(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "update",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNode_update'.",&tolua_err);
#endif

    return 0;
}
int lua_sa_SuperAnimNode_GetId(lua_State* tolua_S)
{
    int argc = 0;
    SuperAnim::SuperAnimNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sa.SuperAnimNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SuperAnim::SuperAnimNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_sa_SuperAnimNode_GetId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->GetId();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GetId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNode_GetId'.",&tolua_err);
#endif

    return 0;
}
int lua_sa_SuperAnimNode_GetCurSectionName(lua_State* tolua_S)
{
    int argc = 0;
    SuperAnim::SuperAnimNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sa.SuperAnimNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SuperAnim::SuperAnimNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_sa_SuperAnimNode_GetCurSectionName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->GetCurSectionName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GetCurSectionName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNode_GetCurSectionName'.",&tolua_err);
#endif

    return 0;
}
int lua_sa_SuperAnimNode_Init(lua_State* tolua_S)
{
    int argc = 0;
    SuperAnim::SuperAnimNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sa.SuperAnimNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SuperAnim::SuperAnimNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_sa_SuperAnimNode_Init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        std::string arg0;
        int arg1;
        SuperAnim::SuperAnimNodeListener* arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);

        ok &= luaval_to_object<SuperAnim::SuperAnimNodeListener>(tolua_S, 4, "sa.SuperAnimNodeListener",&arg2);
        if(!ok)
            return 0;
        bool ret = cobj->Init(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "Init",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNode_Init'.",&tolua_err);
#endif

    return 0;
}
int lua_sa_SuperAnimNode_Pause(lua_State* tolua_S)
{
    int argc = 0;
    SuperAnim::SuperAnimNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sa.SuperAnimNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SuperAnim::SuperAnimNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_sa_SuperAnimNode_Pause'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->Pause();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "Pause",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNode_Pause'.",&tolua_err);
#endif

    return 0;
}
int lua_sa_SuperAnimNode_PlaySection(lua_State* tolua_S)
{
    int argc = 0;
    SuperAnim::SuperAnimNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sa.SuperAnimNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SuperAnim::SuperAnimNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_sa_SuperAnimNode_PlaySection'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        bool ret = cobj->PlaySection(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        bool arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_boolean(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        bool ret = cobj->PlaySection(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "PlaySection",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNode_PlaySection'.",&tolua_err);
#endif

    return 0;
}
int lua_sa_SuperAnimNode_HasSection(lua_State* tolua_S)
{
    int argc = 0;
    SuperAnim::SuperAnimNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sa.SuperAnimNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SuperAnim::SuperAnimNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_sa_SuperAnimNode_HasSection'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        bool ret = cobj->HasSection(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "HasSection",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNode_HasSection'.",&tolua_err);
#endif

    return 0;
}
int lua_sa_SuperAnimNode_IsPause(lua_State* tolua_S)
{
    int argc = 0;
    SuperAnim::SuperAnimNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sa.SuperAnimNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SuperAnim::SuperAnimNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_sa_SuperAnimNode_IsPause'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->IsPause();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "IsPause",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNode_IsPause'.",&tolua_err);
#endif

    return 0;
}
int lua_sa_SuperAnimNode_setSpeedFactor(lua_State* tolua_S)
{
    int argc = 0;
    SuperAnim::SuperAnimNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sa.SuperAnimNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SuperAnim::SuperAnimNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_sa_SuperAnimNode_setSpeedFactor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setSpeedFactor(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setSpeedFactor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNode_setSpeedFactor'.",&tolua_err);
#endif

    return 0;
}
int lua_sa_SuperAnimNode_IsPlaying(lua_State* tolua_S)
{
    int argc = 0;
    SuperAnim::SuperAnimNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sa.SuperAnimNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SuperAnim::SuperAnimNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_sa_SuperAnimNode_IsPlaying'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->IsPlaying();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "IsPlaying",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNode_IsPlaying'.",&tolua_err);
#endif

    return 0;
}
int lua_sa_SuperAnimNode_GetCurFrame(lua_State* tolua_S)
{
    int argc = 0;
    SuperAnim::SuperAnimNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sa.SuperAnimNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SuperAnim::SuperAnimNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_sa_SuperAnimNode_GetCurFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->GetCurFrame();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GetCurFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNode_GetCurFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_sa_SuperAnimNode_resumeSprite(lua_State* tolua_S)
{
    int argc = 0;
    SuperAnim::SuperAnimNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sa.SuperAnimNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SuperAnim::SuperAnimNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_sa_SuperAnimNode_resumeSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->resumeSprite(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "resumeSprite",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNode_resumeSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_sa_SuperAnimNode_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sa.SuperAnimNode",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        std::string arg0;
        int arg1;
        SuperAnim::SuperAnimNodeListener* arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        ok &= luaval_to_object<SuperAnim::SuperAnimNodeListener>(tolua_S, 4, "sa.SuperAnimNodeListener",&arg2);
        if(!ok)
            return 0;
        SuperAnim::SuperAnimNode* ret = SuperAnim::SuperAnimNode::create(arg0, arg1, arg2);
        object_to_luaval<SuperAnim::SuperAnimNode>(tolua_S, "sa.SuperAnimNode",(SuperAnim::SuperAnimNode*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNode_create'.",&tolua_err);
#endif
    return 0;
}
int lua_sa_SuperAnimNode_constructor(lua_State* tolua_S)
{
    int argc = 0;
    SuperAnim::SuperAnimNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new SuperAnim::SuperAnimNode();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"sa.SuperAnimNode");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "SuperAnimNode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_sa_SuperAnimNode_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_sa_SuperAnimNode_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (SuperAnimNode)");
    return 0;
}

int lua_register_sa_SuperAnimNode(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"sa.SuperAnimNode");
    tolua_cclass(tolua_S,"SuperAnimNode","sa.SuperAnimNode","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"SuperAnimNode");
        tolua_function(tolua_S,"draw",lua_sa_SuperAnimNode_draw);
        tolua_function(tolua_S,"onDraw",lua_sa_SuperAnimNode_onDraw);
        tolua_function(tolua_S,"replaceSprite",lua_sa_SuperAnimNode_replaceSprite);
        tolua_function(tolua_S,"removeTimeEvent",lua_sa_SuperAnimNode_removeTimeEvent);
        tolua_function(tolua_S,"Resume",lua_sa_SuperAnimNode_Resume);
        tolua_function(tolua_S,"registerTimeEvent",lua_sa_SuperAnimNode_registerTimeEvent);
        tolua_function(tolua_S,"setFlipY",lua_sa_SuperAnimNode_setFlipY);
        tolua_function(tolua_S,"setFlipX",lua_sa_SuperAnimNode_setFlipX);
        tolua_function(tolua_S,"update",lua_sa_SuperAnimNode_update);
        tolua_function(tolua_S,"GetId",lua_sa_SuperAnimNode_GetId);
        tolua_function(tolua_S,"GetCurSectionName",lua_sa_SuperAnimNode_GetCurSectionName);
        tolua_function(tolua_S,"Init",lua_sa_SuperAnimNode_Init);
        tolua_function(tolua_S,"Pause",lua_sa_SuperAnimNode_Pause);
        tolua_function(tolua_S,"PlaySection",lua_sa_SuperAnimNode_PlaySection);
        tolua_function(tolua_S,"HasSection",lua_sa_SuperAnimNode_HasSection);
        tolua_function(tolua_S,"IsPause",lua_sa_SuperAnimNode_IsPause);
        tolua_function(tolua_S,"setSpeedFactor",lua_sa_SuperAnimNode_setSpeedFactor);
        tolua_function(tolua_S,"IsPlaying",lua_sa_SuperAnimNode_IsPlaying);
        tolua_function(tolua_S,"GetCurFrame",lua_sa_SuperAnimNode_GetCurFrame);
        tolua_function(tolua_S,"resumeSprite",lua_sa_SuperAnimNode_resumeSprite);
        tolua_function(tolua_S,"new",lua_sa_SuperAnimNode_constructor);
        tolua_function(tolua_S,"create", lua_sa_SuperAnimNode_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(SuperAnim::SuperAnimNode).name();
    g_luaType[typeName] = "sa.SuperAnimNode";
    g_typeCast["SuperAnimNode"] = "sa.SuperAnimNode";
    return 1;
}
TOLUA_API int register_all_sa(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"sa",0);
	tolua_beginmodule(tolua_S,"sa");

	lua_register_sa_SuperAnimNodeListener(tolua_S);
	lua_register_sa_SuperAnimNode(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

