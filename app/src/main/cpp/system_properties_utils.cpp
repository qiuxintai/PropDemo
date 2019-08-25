#include <jni.h>
#include <string>
#include <android/log.h>
#include <sys/system_properties.h>

#define TAG    "SystemPropertiesUtils"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

/*extern "C"
JNIEXPORT jstring JNICALL
Java_com_qiuxintai_prop_SystemPropertiesUtils_nativeGet(JNIEnv *env, jclass clazz, jstring key,
                                                             jstring defaultValue) {
    const char *_key = env->GetStringUTFChars(key, nullptr);
    const char *_defaultValue = env->GetStringUTFChars(defaultValue, nullptr);
    char value[PROP_VALUE_MAX] = {0};
    int ret = __system_property_get(_key, value);
    LOGD("get key:%s, defaultValue:%s, ret:%d", _key, _defaultValue, ret);
    if (ret <= 0) {
        return env->NewStringUTF(_defaultValue);
    } else {
        return env->NewStringUTF(value);
    }
}*/

jstring get(JNIEnv *env, jclass clazz, jstring key, jstring defaultValue) {
    const char *_key = env->GetStringUTFChars(key, nullptr);
    const char *_defaultValue = env->GetStringUTFChars(defaultValue, nullptr);
    char value[PROP_VALUE_MAX] = {0};
    int ret = __system_property_get(_key, value);
    LOGD("get key:%s, defaultValue:%s, ret:%d", _key, _defaultValue, ret);
    if (ret <= 0) {
        return env->NewStringUTF(_defaultValue);
    } else {
        return env->NewStringUTF(value);
    }
}

jint set(JNIEnv *env, jclass clazz, jstring key, jstring value) {
    const char *_key = env->GetStringUTFChars(key, nullptr);
    const char *_value = env->GetStringUTFChars(value, nullptr);
    int ret = __system_property_set(_key, _value);
    LOGD("set ret:%d", ret);
    return ret;
}

static int registerNatives(JNIEnv *env) {
    //要注册的java类的路径(完整的包名和类名)
    const char *className = "com/qiuxintai/prop/SystemPropertiesUtils";
    /*
     * 要注册的函数列表
     * 参数：
     * 1.java中用native关键字声明的函数名
     * 2.函数签名，格式：(参数类型)返回类型, 可以使用javap -s xx.class查看
     * 3.C/C++中对应函数的函数名（地址）
     * */
    const JNINativeMethod nativeMethods[] = {
            {"nativeGet", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;", (void *) get},
            {"nativeSet", "(Ljava/lang/String;Ljava/lang/String;)I", (void *) set},
    };

    jclass clazz = nullptr;
    clazz = env->FindClass(className);
    if (clazz == nullptr) {
        return JNI_FALSE;
    }
    int methodsCount = sizeof(nativeMethods) / sizeof(nativeMethods[0]);
    //注册函数 参数：java类名， 要注册的函数数组 ，要注册函数的数量
    if (env->RegisterNatives(clazz, nativeMethods, methodsCount) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = nullptr;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    assert(env != nullptr);
    if (!registerNatives(env)) {//registerNatives -> env->RegisterNatives
        return -1;
    }

    return JNI_VERSION_1_6;
}