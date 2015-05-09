package io.github.samanos;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbDeviceConnection;
import android.hardware.usb.UsbInterface;
import android.hardware.usb.UsbManager;
import android.util.Log;
import android.widget.TextView;
import android.os.Bundle;
import static android.hardware.usb.UsbConstants.*;

import java.util.HashMap;

public class AndroidBridge extends Activity
{
    private TextView tv = null;

    private static final String TAG = "AndroidBridge";

    private static final String ACTION_USB_PERMISSION = "com.android.example.USB_PERMISSION";
    private final BroadcastReceiver permissionReceiver = new BroadcastReceiver() {
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            if (ACTION_USB_PERMISSION.equals(action)) {
                synchronized (this) {
                    UsbDevice device = intent.getParcelableExtra(UsbManager.EXTRA_DEVICE);

                    if (intent.getBooleanExtra(UsbManager.EXTRA_PERMISSION_GRANTED, false)) {
                        if (device != null) {

                            UsbManager manager = (UsbManager) getSystemService(Context.USB_SERVICE);
                            UsbInterface intf = device.getInterface(0);
                            UsbDeviceConnection connection = manager.openDevice(device);
                            connection.claimInterface(intf, true);

                            int requestType = USB_TYPE_VENDOR | USB_DIR_IN;
                            final byte[] buf = new byte[256];
                            final int length = connection.controlTransfer(requestType, 1, 0, 0, buf, buf.length, 1000);

                            AndroidBridge.this.runOnUiThread(new Runnable() {
                                public void run() {
                                    tv.setText("Length: " + length + "Resp: " + bytesToHex(buf));
                                }
                            });

                            connection.releaseInterface(intf);
                            connection.close();
                        }
                    }
                    else {
                        Log.d(TAG, "permission denied for device " + device);
                    }
                }
            }
        }
    };

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        tv = new TextView(this);
        setContentView(tv);

        UsbManager manager = (UsbManager) getSystemService(Context.USB_SERVICE);
        HashMap<String, UsbDevice> deviceList = manager.getDeviceList();
        UsbDevice device = deviceList.values().iterator().next();

        PendingIntent permissionIntent = PendingIntent.getBroadcast(this, 0, new Intent(ACTION_USB_PERMISSION), 0);
        IntentFilter filter = new IntentFilter(ACTION_USB_PERMISSION);
        registerReceiver(permissionReceiver, filter);

        manager.requestPermission(device, permissionIntent);
    }

    final protected static char[] hexArray = "0123456789ABCDEF".toCharArray();
    private static String bytesToHex(byte[] bytes) {
        char[] hexChars = new char[bytes.length * 2];
        for ( int j = 0; j < bytes.length; j++ ) {
            int v = bytes[j] & 0xFF;
            hexChars[j * 2] = hexArray[v >>> 4];
            hexChars[j * 2 + 1] = hexArray[v & 0x0F];
        }
        return new String(hexChars);
    }
}
