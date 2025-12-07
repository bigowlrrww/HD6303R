#include "Tests.h"
#include "libMC6803E.h"

bool Verbose = false;

void EnVerbose()
{
    Verbose = true;
}
bool PASS()
{
    printf("\033[50G"); 
    printf("\e[32mPASS\e[0m\n");
    return true;
}
bool WARN()
{
    printf("\033[50G"); 
    printf("\e[33mWARN\e[0m\n");
    return true;
}
bool FAIL()
{
    printf("\033[50G"); 
    printf("\e[31mFAIL\e[0m\n");
    return false;
}



bool CheckSame8(uint8_t a, uint8_t b, const char *str)
{
    printf("%s",str);
    if (Verbose) printf(" [0x%02X==0x%02X]", a, b);
    if (a == b) return PASS();
    else return FAIL();
}
bool CheckSame16(uint16_t a, uint16_t b, const char *str)
{
    printf("%s",str);
    if (Verbose) printf(" [0x%04X==0x%04X]", a, b);
    if (a == b) return PASS();
    else return FAIL();
}

bool checkPC(uint16_t a, uint16_t b, uint8_t expectedStep)
{
    printf("PC incremented correctly");
    if (Verbose) printf(" [0x%04X==0x%04X]", a, b);
    if (b - a == expectedStep) return PASS();
    else return FAIL();
}

bool checkImplemented(uint8_t flags)
{
    printf("Function Implemented");
    if (flags & MC6803E_FLAG_IMP) return PASS();
    else return FAIL();
}
bool checkVerified(uint8_t flags)
{
    printf("Function Verified");
    if (flags & MC6803E_FLAG_VERIFIED) return PASS();
    else return WARN();
}