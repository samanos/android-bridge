### Building

1. Create a symlink `libusb` that points to the [libusb](https://github.com/libusb/libusb) source code. Current code is compiled and ran with libusb version `1.0.19`.
2. Create a `local.properties` file that contains path to Android SDK and Android NDK:

        sdk.dir=/path/to/android-sdk-linux
        ndk.dir=/path/to/android-ndk-r10d

3. Run `ndk-build` to compile C code.
4. Run `gradle` to compile Java code and build an APK.
