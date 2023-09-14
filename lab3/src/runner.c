#include <stdio.h>
#include <stdlib.h>
#include <cmake_var.h>

#ifndef getcwd
    #ifdef WIN32
        #include <windows.h>

    #elif __linux__
        #include <unistd.h>
        #define getcwd(X) readlink()

    #endif // __linux__ || WIN32
#endif // getcwd

int exec_verbose(char* cmd)
{
    printf("\"%s\":", cmd);
    printf("\n");
    return system(cmd);
}

int main(int argc, char const *argv[])
{
    printf(
        "PROJECT_SOURCE_DIR: %s\n"
        "CMAKE_BINARY_DIR: %s\n",
        PROJECT_SOURCE_DIR,
        CMAKE_BINARY_DIR
    );
    
    exec_verbose("pwd");
    exec_verbose("java -Djava.library.path="CMAKE_BINARY_DIR" javaMain");
    return 0;
}
