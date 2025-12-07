#include "Tests.h"

bool CheckSame8(uint8_t a, uint8_t b, const char *str)
{
    printf("%s",str);
    if (a == b) PASS();
    else FAIL();
}
bool CheckSame16(uint16_t a, uint16_t b, const char *str)
{
    printf("%s",str);
    if (a == b) PASS();
    else FAIL();
}

void PASS()
{
    printf("\033[50G"); 
    printf("\e[32mPASS\e[0m\n");
}

void FAIL()
{
    printf("\033[50G"); 
    printf("\e[31mFAIL\e[0m\n");
}