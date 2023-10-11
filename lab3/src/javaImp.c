#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <net/if.h>  
#include <net/if_arp.h>

#include <linux/if_packet.h>
#include <unistd.h>
#include <errno.h>

#include <jni.h>
#include <javaMain.h>
#include <ipv6.h>
#include <tcp.h>



struct sockaddr addr;
size_t addr_len;
int sock_d, result;

void jni_print(JNIEnv * env, char* str)
{
    #if 1
    jclass j_system = (*env)->FindClass(env, "java/lang/System");
    jfieldID j_outID = 
        (*env)->GetStaticFieldID(
            env,
            j_system,
            "out",
            "Ljava/io/PrintStream;"
        );
    jobject j_out = (*env)->GetStaticObjectField(env, j_system, j_outID); //!!!!

    jclass printstream = (*env)->FindClass(env, "java/io/PrintStream");
    jmethodID printlnID = (*env)->GetMethodID(env, printstream, "print", "(Ljava/lang/String;)V");
    jstring j_str = (*env)->NewStringUTF(env, str);
    (*env)->CallVoidMethod(env, j_out, printlnID, j_str);
    #endif
}

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

JNIEXPORT jboolean JNICALL Java_javaMain_init
(
    JNIEnv * env,
    jclass class,
    jstring interfaceName
)
{
    jboolean isCopy;
    size_t iface_siz = (*env)->GetStringUTFLength(env,interfaceName);
    if (iface_siz > IFNAMSIZ)
        return 0;
    const char *cstr_iface = (*env)->GetStringUTFChars(env, interfaceName, &isCopy);

    addr = *(struct sockaddr*)&(struct sockaddr_ll)
    {
        .sll_family = AF_PACKET,
        .sll_protocol = ETH_P_ALL,
        .sll_ifindex = if_nametoindex(cstr_iface),
        .sll_hatype = ARPHRD_RAWIP,
        .sll_pkttype = PACKET_HOST,
        .sll_halen = 6,
        .sll_addr = { 0 }
    };
    sock_d = socket (AF_PACKET, SOCK_RAW, htons (ETH_P_ALL));
    if (sock_d < 0){
        char buf[40] = { 0 };
        sprintf(buf, "%s,%d:\terrno: %d\n",__FILE__,__LINE__-3, errno);
        jni_print(env, buf);
    }

    (*env)->ReleaseStringUTFChars(env, interfaceName, cstr_iface);
    if (sock_d == -1)
        return JNI_FALSE;
    return JNI_TRUE;
    
}

JNIEXPORT void JNICALL Java_javaMain_deinit
(
    JNIEnv * env,
    jclass class
)
{
    addr = (struct sockaddr){ 0 };
    close(sock_d);
}

JNIEXPORT jint JNICALL Java_javaMain_sendTo
(
    JNIEnv * env,
    jclass class,
    jbyteArray buf
)
{
    jsize arr_len = (*env)->GetArrayLength(env, buf);
    int8_t* mbuf = malloc(arr_len);
    if (mbuf <= 0)
        return -1;
    (*env)->GetByteArrayRegion(env,buf,0,arr_len,mbuf);
    sendto(
        sock_d,
        mbuf,
        arr_len,
        0,
        &addr,
        sizeof(addr)
    );
    free(mbuf);
    return arr_len;
}

JNIEXPORT jbyteArray JNICALL Java_javaMain_recvFrom
(
    JNIEnv * env,
    jclass class,
    jbyteArray buf,
    jint offset
)
{
    jsize arr_len = (*env)->GetArrayLength(env, buf);
    jbyte* occur_buf = malloc(arr_len);
    jbyte* recv_buf = malloc(arr_len + offset);
    if (occur_buf <= 0)
        return NULL;
    (*env)->GetByteArrayRegion(env,buf,0,arr_len,occur_buf);
    do
    {
        recvfrom(sock_d,recv_buf,arr_len+offset,0,NULL,NULL);
    } while (memcmp(recv_buf + offset, occur_buf, arr_len));

    jbyteArray ret = (*env)->NewByteArray( env, arr_len + offset);
    (*env)->SetByteArrayRegion(env, ret,  0, arr_len + offset,recv_buf);
    free(occur_buf);
    free(recv_buf);
    return ret;
}