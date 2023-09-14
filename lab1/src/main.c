#include <stdio.h>
#include <string.h>

char* FIO[] = {
    "Алеев",
    "Ибрагим",
    "Ильясович"
};
int group = 6304;

int main(int argc, char const *argv[])
{
    printf("Введите числа  a1, a2 и a3 разделяя их пробелами: ");
    int a1, a2, a3;
    scanf("%d %d %d", &a1, &a2, &a3);

    int b1 = strlen(FIO[0]);
    int b2 = strlen(FIO[1]);
    int b3 = strlen(FIO[2]);
    int b4 = 1 ? a1 / b1 : a1 % b1;
    int b5 = 1 ? a2 / b2 : a2 % b2;
    int b6 = 1 ? a3 / b3 : a3 % b3;
    int ret = (group + b6) % 2;
    printf(
        "b1: %d\n"
        "b2: %d\n"
        "b3: %d\n"
        "b4: %d\n"
        "b5: %d\n"
        "b6: %d\n"
        "return code",
        b1,
        b2,
        b3,
        b4,
        b5,
        b6,
        ret
    );
    return ret;
}
