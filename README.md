### Building

1. Create a `local.properties` file that contains path to Android SDK:

        sdk.dir=/path/to/android-sdk-linux

2. Run `gradle build` to compile Java code and build an APK.
3. To install built APK to the device run:

        adb install -r build/outputs/apk/android-bridge-debug-unaligned.apk
