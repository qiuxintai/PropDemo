package com.qiuxintai.prop;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

/**
 * @author qiuxintai
 * @github https://github.com/qiuxintai/
 * @QQ 695144933
 * Date: 2019/8/24
 */
public class SystemPropertiesUtils {
    static {
        System.loadLibrary("SystemPropertiesUtils");
    }

    public static native String nativeGet(String key, String defaultValue);

    /**
     * Must be able to set property(platform app or priv-app),
     * otherwise nativeSet will be forbidden by SELinux(avc: denied).
     *
     * @param key key of system property
     * @param value new value to set
     * @return 0 if success, otherwise return -1.
     */
    public static native int nativeSet(String key, String value);

    public static String get(String key, String defaultValue) {
        String value;
        try {
            final Class<?> systemProperties = Class.forName("android.os.SystemProperties");
            final Method get = systemProperties.getMethod("get", String.class, String.class);
            value = (String) get.invoke(null, key, defaultValue);
        } catch (ClassNotFoundException | NoSuchMethodException
                | IllegalAccessException | InvocationTargetException e) {
            e.printStackTrace();
            value = defaultValue;
        }
        return value;
    }

    public static void set(String key, String value) {
        try {
            final Class<?> systemProperties = Class.forName("android.os.SystemProperties");
            final Method set = systemProperties.getMethod("set", String.class, String.class);
            set.invoke(null, key, value);
        } catch (ClassNotFoundException | NoSuchMethodException
                | IllegalAccessException | InvocationTargetException e) {
            e.printStackTrace();
        }
    }
}
