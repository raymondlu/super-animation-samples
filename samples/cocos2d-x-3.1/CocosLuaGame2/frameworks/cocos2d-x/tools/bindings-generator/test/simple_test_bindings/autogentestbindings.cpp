#include "autogentestbindings.hpp"
#include "cocos2d_specifics.hpp"
#include "simple_class.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    JSObject* global = ScriptingCore::getInstance()->getGlobalObject();
	isNewValid = JS_GetProperty(cx, global, "initializing", &initializing) && JSVAL_TO_BOOLEAN(initializing);
	if (isNewValid)
	{
		TypeTest<T> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");

		JSObject *_tmp = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));
		return true;
	}

    JS_ReportError(cx, "Don't use `new cc.XXX`, please use `cc.XXX.create` instead! ");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	return false;
}

static bool js_is_native_obj(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
	vp.set(BOOLEAN_TO_JSVAL(true));
	return true;	
}
JSClass  *jsb_SimpleNativeClass_class;
JSObject *jsb_SimpleNativeClass_prototype;

bool js_autogentestbindings_SimpleNativeClass_getAnotherMoreComplexField(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autogentestbindings_SimpleNativeClass_getAnotherMoreComplexField : Invalid Native Object");
	if (argc == 0) {
		const char* ret = cobj->getAnotherMoreComplexField();
		jsval jsret = JSVAL_NULL;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autogentestbindings_SimpleNativeClass_getAnotherMoreComplexField : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autogentestbindings_SimpleNativeClass_setSomeField(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;

	JSObject *obj = NULL;
	SimpleNativeClass* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autogentestbindings_SimpleNativeClass_setSomeField : Invalid Native Object");
	do {
		if (argc == 0) {
			cobj->setSomeField();
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return true;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = true; break; }
			cobj->setSomeField(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return true;
		}
	} while(0);

	JS_ReportError(cx, "js_autogentestbindings_SimpleNativeClass_setSomeField : wrong number of arguments");
	return false;
}
bool js_autogentestbindings_SimpleNativeClass_receivesLongLong(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autogentestbindings_SimpleNativeClass_receivesLongLong : Invalid Native Object");
	if (argc == 1) {
		long long arg0;
		ok &= jsval_to_long_long(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_autogentestbindings_SimpleNativeClass_receivesLongLong : Error processing arguments");
		long long ret = cobj->receivesLongLong(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = long_long_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autogentestbindings_SimpleNativeClass_receivesLongLong : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_autogentestbindings_SimpleNativeClass_thisReturnsALongLong(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autogentestbindings_SimpleNativeClass_thisReturnsALongLong : Invalid Native Object");
	if (argc == 0) {
		long long ret = cobj->thisReturnsALongLong();
		jsval jsret = JSVAL_NULL;
		jsret = long_long_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autogentestbindings_SimpleNativeClass_thisReturnsALongLong : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autogentestbindings_SimpleNativeClass_getObjectType(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autogentestbindings_SimpleNativeClass_getObjectType : Invalid Native Object");
	if (argc == 0) {
		unsigned int ret = cobj->getObjectType();
		jsval jsret = JSVAL_NULL;
		jsret = uint32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autogentestbindings_SimpleNativeClass_getObjectType : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autogentestbindings_SimpleNativeClass_setAnotherMoreComplexField(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autogentestbindings_SimpleNativeClass_setAnotherMoreComplexField : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_autogentestbindings_SimpleNativeClass_setAnotherMoreComplexField : Error processing arguments");
		cobj->setAnotherMoreComplexField(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autogentestbindings_SimpleNativeClass_setAnotherMoreComplexField : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_autogentestbindings_SimpleNativeClass_setSomeOtherField(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autogentestbindings_SimpleNativeClass_setSomeOtherField : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_autogentestbindings_SimpleNativeClass_setSomeOtherField : Error processing arguments");
		cobj->setSomeOtherField(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autogentestbindings_SimpleNativeClass_setSomeOtherField : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_autogentestbindings_SimpleNativeClass_getSomeOtherField(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autogentestbindings_SimpleNativeClass_getSomeOtherField : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getSomeOtherField();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autogentestbindings_SimpleNativeClass_getSomeOtherField : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autogentestbindings_SimpleNativeClass_returnsACString(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autogentestbindings_SimpleNativeClass_returnsACString : Invalid Native Object");
	if (argc == 0) {
		const char* ret = cobj->returnsACString();
		jsval jsret = JSVAL_NULL;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autogentestbindings_SimpleNativeClass_returnsACString : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autogentestbindings_SimpleNativeClass_doSomeProcessing(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autogentestbindings_SimpleNativeClass_doSomeProcessing : Invalid Native Object");
	if (argc == 2) {
		std::string arg0;
		std::string arg1;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		ok &= jsval_to_std_string(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, false, "js_autogentestbindings_SimpleNativeClass_doSomeProcessing : Error processing arguments");
		int ret = cobj->doSomeProcessing(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autogentestbindings_SimpleNativeClass_doSomeProcessing : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_autogentestbindings_SimpleNativeClass_getSomeField(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autogentestbindings_SimpleNativeClass_getSomeField : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getSomeField();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autogentestbindings_SimpleNativeClass_getSomeField : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autogentestbindings_SimpleNativeClass_returnsAString(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autogentestbindings_SimpleNativeClass_returnsAString : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->returnsAString();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autogentestbindings_SimpleNativeClass_returnsAString : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autogentestbindings_SimpleNativeClass_func(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	
	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = true; break; }
			SimpleNativeClass::func(arg0);
			return true;
		}
	} while (0);
	
	do {
		if (argc == 0) {
			SimpleNativeClass::func();
			return true;
		}
	} while (0);
	
	do {
		if (argc == 2) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = true; break; }
			double arg1;
			ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[1]), &arg1);
			if (!ok) { ok = true; break; }
			SimpleNativeClass::func(arg0, arg1);
			return true;
		}
	} while (0);
	JS_ReportError(cx, "js_autogentestbindings_SimpleNativeClass_func : wrong number of arguments");
	return false;
}
bool js_autogentestbindings_SimpleNativeClass_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;

	JSObject *obj = NULL;
	SimpleNativeClass* cobj = NULL;
	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = true; break; }
			cobj = new SimpleNativeClass(arg0);
			cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
			if (_ccobj) {
				_ccobj->autorelease();
			}
			TypeTest<SimpleNativeClass> t;
			js_type_class_t *typeClass = nullptr;
			std::string typeName = t.s_name();
			auto typeMapIter = _js_global_type_map.find(typeName);
			CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
			typeClass = typeMapIter->second;
			CCASSERT(typeClass, "The value is null.");
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t* p = jsb_new_proxy(cobj, obj);
			JS_AddNamedObjectRoot(cx, &p->obj, "SimpleNativeClass");
		}
	} while(0);

	do {
		if (argc == 0) {
			cobj = new SimpleNativeClass();
			cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
			if (_ccobj) {
				_ccobj->autorelease();
			}
			TypeTest<SimpleNativeClass> t;
			js_type_class_t *typeClass = nullptr;
			std::string typeName = t.s_name();
			auto typeMapIter = _js_global_type_map.find(typeName);
			CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
			typeClass = typeMapIter->second;
			CCASSERT(typeClass, "The value is null.");
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t* p = jsb_new_proxy(cobj, obj);
			JS_AddNamedObjectRoot(cx, &p->obj, "SimpleNativeClass");
		}
	} while(0);

	do {
		if (argc == 2) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = true; break; }
			int arg1;
			ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
			if (!ok) { ok = true; break; }
			cobj = new SimpleNativeClass(arg0, arg1);
			cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
			if (_ccobj) {
				_ccobj->autorelease();
			}
			TypeTest<SimpleNativeClass> t;
			js_type_class_t *typeClass = nullptr;
			std::string typeName = t.s_name();
			auto typeMapIter = _js_global_type_map.find(typeName);
			CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
			typeClass = typeMapIter->second;
			CCASSERT(typeClass, "The value is null.");
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t* p = jsb_new_proxy(cobj, obj);
			JS_AddNamedObjectRoot(cx, &p->obj, "SimpleNativeClass");
		}
	} while(0);

	if (cobj) {
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return true;
	}
	JS_ReportError(cx, "js_autogentestbindings_SimpleNativeClass_constructor : wrong number of arguments");
	return false;
}



void js_SimpleNativeClass_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (SimpleNativeClass)", obj);
}

void js_register_autogentestbindings_SimpleNativeClass(JSContext *cx, JSObject *global) {
	jsb_SimpleNativeClass_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_SimpleNativeClass_class->name = "SimpleNativeClass";
	jsb_SimpleNativeClass_class->addProperty = JS_PropertyStub;
	jsb_SimpleNativeClass_class->delProperty = JS_DeletePropertyStub;
	jsb_SimpleNativeClass_class->getProperty = JS_PropertyStub;
	jsb_SimpleNativeClass_class->setProperty = JS_StrictPropertyStub;
	jsb_SimpleNativeClass_class->enumerate = JS_EnumerateStub;
	jsb_SimpleNativeClass_class->resolve = JS_ResolveStub;
	jsb_SimpleNativeClass_class->convert = JS_ConvertStub;
	jsb_SimpleNativeClass_class->finalize = js_SimpleNativeClass_finalize;
	jsb_SimpleNativeClass_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getAnotherMoreComplexField", js_autogentestbindings_SimpleNativeClass_getAnotherMoreComplexField, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setSomeField", js_autogentestbindings_SimpleNativeClass_setSomeField, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("receivesLongLong", js_autogentestbindings_SimpleNativeClass_receivesLongLong, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("thisReturnsALongLong", js_autogentestbindings_SimpleNativeClass_thisReturnsALongLong, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getObjectType", js_autogentestbindings_SimpleNativeClass_getObjectType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setAnotherMoreComplexField", js_autogentestbindings_SimpleNativeClass_setAnotherMoreComplexField, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setSomeOtherField", js_autogentestbindings_SimpleNativeClass_setSomeOtherField, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getSomeOtherField", js_autogentestbindings_SimpleNativeClass_getSomeOtherField, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("returnsACString", js_autogentestbindings_SimpleNativeClass_returnsACString, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("doSomeProcessing", js_autogentestbindings_SimpleNativeClass_doSomeProcessing, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getSomeField", js_autogentestbindings_SimpleNativeClass_getSomeField, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("returnsAString", js_autogentestbindings_SimpleNativeClass_returnsAString, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("func", js_autogentestbindings_SimpleNativeClass_func, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_SimpleNativeClass_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_SimpleNativeClass_class,
		js_autogentestbindings_SimpleNativeClass_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "SimpleNativeClass", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<SimpleNativeClass> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_SimpleNativeClass_class;
		p->proto = jsb_SimpleNativeClass_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

void register_all_autogentestbindings(JSContext* cx, JSObject* obj) {

	js_register_autogentestbindings_SimpleNativeClass(cx, obj);
}

