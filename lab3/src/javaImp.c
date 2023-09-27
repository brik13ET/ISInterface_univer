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

#include <linux/if_packet.h>
#include <unistd.h>
#include <errno.h>

#include <jni.h>
#include <javaMain.h>
#include <ipv6.h>
#include <tcp.h>



struct sockaddr addr;
int sock_d, result;

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
    size_t iface_siz = GetStringUTFLength(env,interfaceName);
    if (iface_siz > IFNAMSIZ)
        return 0;
    char *cstr_iface,*cstr_iface_ = GetStringUTFChars(env, interfaceName, &isCopy);
    if (!isCopy)
    {
        cstr_iface = malloc(iface_siz);
        memcpy(cstr_iface, cstr_iface_, iface_siz);
    }
    else
        cstr_iface = cstr_iface_;
    ReleaseStringUTFChars(env, interfaceName, cstr_iface_);

    addr = *(struct sockaddr*)&(struct sockaddr_in)
    {
        .sin_family = AF_INET,
        .sin_port = htons(43522),
        .sin_addr.s_addr = INADDR_LOOPBACK
    };
    sock_d = socket (PF_PACKET, SOCK_RAW, htons (ETH_P_ALL));
    setsockopt(sock_d, SOL_SOCKET,SO_BINDTODEVICE, cstr_iface, IFNAMSIZ);

    if (!isCopy)
        free(cstr_iface);
    if (sock_d == -1)
        return 0;
    return 1;
    
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
    jsize arr_len = GetArrayLength(env, buf);
    uint8_t* mbuf = malloc(arr_len);
    if (mbuf <= 0)
        return -1;
    GetByteArrayRegion(env,buf,0,arr_len,mbuf);
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
    jsize arr_len = GetArrayLength(env, buf);
    uint8_t* occur_buf = malloc(arr_len);
    uint8_t* recv_buf = malloc(arr_len + offset);
    if (occur_buf <= 0)
        return NULL;
    GetByteArrayRegion(env,buf,0,arr_len,occur_buf);
    do
    {
        recvfrom(sock_d,recv_buf,arr_len+offset,0,NULL,NULL);
    } while (memcmp(recv_buf + offset, occur_buf, arr_len));

    jbyteArray ret = NewByteArray( *env, arr_len + offset);
    SetByteArrayRegion( ret,  0, arr_len + offset,recv_buf);
    free(occur_buf);
    free(recv_buf);
    return ret;
}
