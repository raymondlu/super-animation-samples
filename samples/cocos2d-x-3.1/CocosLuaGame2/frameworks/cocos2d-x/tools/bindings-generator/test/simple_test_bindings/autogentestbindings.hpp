#ifndef __autogentestbindings_h__
#define __autogentestbindings_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_SimpleNativeClass_class;
extern JSObject *jsb_SimpleNativeClass_prototype;

bool js_autogentestbindings_SimpleNativeClass_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_autogentestbindings_SimpleNativeClass_finalize(JSContext *cx, JSObject *obj);
void js_register_autogentestbindings_SimpleNativeClass(JSContext *cx, JSObject *global);
void register_all_autogentestbindings(JSContext* cx, JSObject* obj);
bool js_autogentestbindings_SimpleNativeClass_getAnotherMoreComplexField(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autogentestbindings_SimpleNativeClass_setSomeField(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autogentestbindings_SimpleNativeClass_receivesLongLong(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autogentestbindings_SimpleNativeClass_thisReturnsALongLong(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autogentestbindings_SimpleNativeClass_getObjectType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autogentestbindings_SimpleNativeClass_setAnotherMoreComplexField(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autogentestbindings_SimpleNativeClass_setSomeOtherField(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autogentestbindings_SimpleNativeClass_getSomeOtherField(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autogentestbindings_SimpleNativeClass_returnsACString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autogentestbindings_SimpleNativeClass_doSomeProcessing(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autogentestbindings_SimpleNativeClass_getSomeField(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autogentestbindings_SimpleNativeClass_returnsAString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autogentestbindings_SimpleNativeClass_func(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autogentestbindings_SimpleNativeClass_SimpleNativeClass(JSContext *cx, uint32_t argc, jsval *vp);
#endif

