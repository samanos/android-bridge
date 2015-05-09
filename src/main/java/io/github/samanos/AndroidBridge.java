package io.github.samanos;

import android.app.Activity;
import android.widget.TextView;
import android.os.Bundle;

public class AndroidBridge extends Activity
{
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        TextView tv = new TextView(this);
        tv.setText(queryForData());
        setContentView(tv);
    }

    public native String queryForData();

    static {
        System.loadLibrary("android_bridge");
    }
}
