#include <stdio.h>
#include <stdlib.h>
#include <cmake_var.h>
#include "../../include.h"

int exec_verbose(char* cmd, char* prefix)
{
    if (prefix == NULL)
        prefix = "";
    printf("%s %s:", prefix, cmd);
    printf("\n");
    return system(cmd);
}

int main(int argc, char const *argv[])
{
    printf(
        "Вариант %s\t%s\n%s\n",
        F_len % 3 == 0 ? "ping":
        F_len % 3 == 1 ? "udp" :
                         "tcp",
        I_len % 2 == 0 ? "IPv4": "IPv6",
        "Для \"tcp\" отправить запрос на установку соединения TCP на MAC-адрес и IP-адрес сервера на порт 43522, получить подтверждение успешной установки соединения и вывести ответный пакет."
    );
    exec_verbose("cd "CMAKE_CURRENT_BUILD_DIR, "[C/C++ RT]");
    exec_verbose("java -Djava.library.path="CMAKE_CURRENT_BUILD_DIR" -verbose:jni -Xcheck:jni javaMain", "[C/C++ RT]");
    return 0;
}
