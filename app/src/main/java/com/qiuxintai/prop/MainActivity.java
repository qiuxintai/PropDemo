package com.qiuxintai.prop;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

/**
 * @author qiuxintai
 * @github https://github.com/qiuxintai/
 * @QQ 695144933
 * Date: 2019/8/24
 */
public class MainActivity extends AppCompatActivity {
    TextView javaTv;
    TextView jniTv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        javaTv = findViewById(R.id.java);
        jniTv = findViewById(R.id.jni);
    }

    public void onClick(View view) {
        if (view != null) {
            switch (view.getId()) {
                case R.id.java_get:
                    javaTv.setText(SystemPropertiesUtils.get("net.bt.name", "unknown_java"));
                    break;
                case R.id.java_set:
                    SystemPropertiesUtils.set("net.bt.name", "Android_java");
                    break;
                case R.id.jni_get:
                    jniTv.setText(SystemPropertiesUtils.nativeGet("net.bt.name", "unknown_jni"));
                    break;
                case R.id.jni_set:
                    SystemPropertiesUtils.nativeSet("net.bt.name", "Android_jni");
                    break;
                default:
                    break;
            }
        }
    }
}
