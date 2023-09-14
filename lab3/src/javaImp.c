#include <javaMain.h>


JNIEXPORT jint JNICALL Java_javaMain_add
(
    JNIEnv * env,
    jobject obj,
    jint a,
    jint b
)
{
    return a + b;
}