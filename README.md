webservicescppcon2014
=====================

Slides and demos from Using C++ to Connect to Web Services at CppCon 2014.

If you just want to look at the C++ code for the two demos look in each
of the jni folders: YodaSpeak/YodaSpeak/jni/, DropBoxDemo/DropBox/jni.
        
To build and run the demos use the following steps:

1. Have Eclipse, the Android SDK, and Android NDK installed.

2. Follow the instructions for how to setup and build the C++ Rest SDK:
       https://casablanca.codeplex.com/wikipage?title=Setup%20and%20Build%20on%20Android&referringTitle=Documentation

3. Setup the include path for the C++ Rest SDK and Boost in Android.mk file
   under the JNI folder. Replace both:
        PATH_TO_CPPREST_INCLUDE
        PATH_TO_BOOST_INCLUDE

4. Add the built libcpprest.so and libiconv.so to the JNI folder.

5. Fill in your own app keys for each of the services. Located in:
        YodaSpeak/YodaSpeak/jni/yoda_speak.cpp
        DropBoxDemo/DropBox/jni/drop_box.cpp

