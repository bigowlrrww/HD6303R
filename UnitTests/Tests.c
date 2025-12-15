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
bool WARN_I()
{
    printf("\033[55G"); 
    printf("\e[33m(WARN)\e[0m");
    return true;
}
bool FAIL()
{
    printf("\033[50G"); 
    printf("\e[31mFAIL\e[0m\n");
    return false;
}
//A soft failure, warn the user return false, but only show yellow on the FAIL
bool FAIL_S()
{
    printf("\033[50G"); 
    printf("\e[33mFAIL\e[0m\n");
    return false;
}

const char* flagToStr(uint8_t flag)
{
    switch(flag)
    {
    case(MC6803E_FLAG_C):
        return "FLAG_C";
    case(MC6803E_FLAG_V):
        return "FLAG_V";
    case(MC6803E_FLAG_Z):
        return "FLAG_Z";
    case(MC6803E_FLAG_N):
        return "FLAG_N";
    case(MC6803E_FLAG_I):
        return "FLAG_I";
    case(MC6803E_FLAG_H):
        return "FLAG_H";
    case(MC6803E_FLAG_VERIFIED):
        return "FLAG_VERIFIED";
    case(MC6803E_FLAG_IMP):
        return "FLAG_IMP";
    };
    return "BadFLAG";
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

bool CheckRSH8(uint8_t a, uint8_t b, const char *str)
{
    printf("%s",str);
    uint8_t result = ((uint8_t)a)>>1;
    if (Verbose) printf(" [(0x%02X>>1)0x%02X==0x%02X]", a, result, b);
    if (result == b) return PASS();
    else return FAIL();
}

bool CheckRSH16(uint16_t a, uint16_t b, const char *str)
{
    printf("%s",str);
    uint16_t result = ((uint16_t)a)>>1;
    if (Verbose) printf(" [(0x%04X>>1)0x%04X==0x%04X]", a, result, b);
    if (result == b) return PASS();
    else return FAIL();
}

bool CheckLSH8(uint8_t a, uint8_t b, const char *str)
{
    printf("%s",str);
    uint8_t result = ((uint8_t)a)<<1;
    if (Verbose) printf(" [(0x%02X<<1)0x%02X==0x%02X]", a, result, b);
    if (result == b) return PASS();
    else return FAIL();
}

bool CheckLSH16(uint16_t a, uint16_t b, const char *str)
{
    printf("%s",str);
    uint16_t result = ((uint16_t)a)<<1;
    if (Verbose) printf(" [(0x%04X<<1)0x%04X==0x%04X]", a, result, b);
    if (result == b) return PASS();
    else return FAIL();
}

bool CheckAdd8(uint8_t a, uint8_t b, uint8_t result, const char *str)
{
    printf("%s", str);
    if (Verbose) printf(" [0x%02X+0x%02X==0x%02X]", a, b, result);
    if ((uint8_t)(a + b) == result) return PASS();
    else return FAIL();
}

bool CheckAdd16(uint16_t a, uint16_t b, uint16_t result, const char *str)
{
    printf("%s", str);
    if (Verbose) printf(" [0x%04X+0x%04X==0x%04X]", a, b, result);
    if ((uint16_t)(a + b) == result) return PASS();
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
    else return FAIL_S();
}

/**
 * This should be called like:
 * verifyUnknownMnemonic(ALU_MC6803E_Execute(p, 0x00));
 */
bool verifyUnknownMnemonic(uint16_t ExecResult)
{
    if (ExecResult == 0xFFFF) return PASS();
    else return FAIL();
}

bool CheckFlagSet(uint8_t a, uint8_t b, uint8_t flag)
{
    printf("%s was set", flagToStr(flag));
    if (Verbose) printf(" [0x%02X->0x%02X]", a&flag, b&flag);
    if (a & flag) {printf(" Invalid a.%s", flagToStr(flag)); WARN_I();}
    if (b & flag) return PASS();
    else return FAIL();
}

bool CheckFlagUnset(uint8_t a, uint8_t b, uint8_t flag)
{
    printf("%s was unset", flagToStr(flag));
    if (Verbose) printf(" [0x%02X->0x%02X]", a&flag, b&flag);
    if (!(a & flag)) {printf(" Invalid a.%s", flagToStr(flag)); WARN_I();}
    if (!(b & flag)) return PASS();
    return FAIL();
}

bool CheckFlagSame(uint8_t a, uint8_t b, uint8_t flag)
{
    printf("%s is same", flagToStr(flag));
    if (Verbose) printf(" [0x%02X==0x%02X]", a&flag, b&flag);
    if ((a & flag)==(b & flag)) return PASS();
    else return FAIL();
}
