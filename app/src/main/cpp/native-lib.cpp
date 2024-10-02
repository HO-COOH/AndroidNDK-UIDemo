#include <jni.h>
#include <string>
#include <concepts>

extern "C"
{
    JNIEXPORT jstring JNICALL
    Java_com_example_myapplication_MainActivity_stringFromJNI(
            JNIEnv *env,
            jobject /* this */) {
        std::string hello = "Hello from C++";
        return env->NewStringUTF(hello.c_str());
    }

    JNIEXPORT void JNICALL
    Java_com_example_myapplication_MainActivity_onLaunchCpp(JNIEnv *env, jobject mainActivity, jobject mainLayout)
    {
        auto linearLayoutClass = env->GetObjectClass(mainLayout);

        auto addViewId = env->GetMethodID(linearLayoutClass, "addView", "(Landroid/view/View;)V");

        auto buttonClass = env->FindClass("android/widget/Button");
        auto buttonConstructorId = env->GetMethodID(buttonClass, "<init>", "(Landroid/content/Context;)V");
        auto setTextId = env->GetMethodID(buttonClass, "setText", "(Ljava/lang/CharSequence;)V");

        auto button = env->NewObject(buttonClass, buttonConstructorId, mainActivity);
        env->CallVoidMethod(button, setTextId, env->NewStringUTF("button created in C++"));

        env->CallVoidMethod(mainLayout, addViewId, button);
    }

}
