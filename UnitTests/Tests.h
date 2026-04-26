#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define CheckSame(a, b, c) _Generic((a), \
    uint8_t:  CheckSame8, \
    uint16_t: CheckSame16 \
)(a, b, c)

#define CheckRSH(a, b, c) _Generic((a), \
    uint8_t:  CheckRSH8, \
    uint16_t: CheckRSH16 \
)(a, b, c)

#define CheckLSH(a, b, c) _Generic((a), \
    uint8_t:  CheckLSH8, \
    uint16_t: CheckLSH16 \
)(a, b, c)

#define CheckAddition(a,b,result,d) _Generic((a), \
    uint8_t:  CheckAdd8, \
    uint16_t: CheckAdd16 \
)(a,b,result,d)

#define CheckSubtraction(a,b,result,d) _Generic((a), \
    uint8_t:  CheckSub8, \
    uint16_t: CheckSub16 \
)(a,b,result,d)

// Checks to see if the Z flag was set on a zero result
#define CheckZFlagDefault(prev, curr, result) _Generic((result), \
    uint8_t: CheckZFlagForZero8, \
    uint16_t: CheckZFlagForZero16 \
)(prev, curr, result)

// Checks to see if the N flag was set on a negative result
#define CheckNFlagDefault(prev, curr, result) _Generic((result), \
    uint8_t: CheckNFlag8, \
    uint16_t: CheckNFlag16 \
)(prev, curr, result)

void EnVerbose();
bool PASS();
bool WARN();
bool WARN_I();
bool FAIL();
const char* flagToStr(uint8_t flag);

bool __check_sub_carry(uint8_t a, uint8_t b);
bool __check_sub_overflow(uint8_t a, uint8_t b);

bool CheckSame8(uint8_t a, uint8_t b, const char *str);
bool CheckSame16(uint16_t a, uint16_t b, const char *str);

bool CheckRSH8(uint8_t a, uint8_t b, const char *str);
bool CheckRSH16(uint16_t a, uint16_t b, const char *str);

bool CheckLSH8(uint8_t a, uint8_t b, const char *str);
bool CheckLSH16(uint16_t a, uint16_t b, const char *str);

bool CheckAdd8(uint8_t a, uint8_t b, uint8_t result, const char *str);
bool CheckAdd16(uint16_t a, uint16_t b, uint16_t result, const char *str);

bool CheckSub8(uint8_t a, uint8_t b, uint8_t result, const char *str);
bool CheckSub16(uint16_t a, uint16_t b, uint16_t result, const char *str);

bool CheckPC(uint16_t a, uint16_t b, int expectedStep);

bool checkImplemented(uint8_t flags);
bool checkVerified(uint8_t flags);
bool verifyUnknownMnemonic(uint16_t ExecResult);

bool CheckFlagSet(uint8_t a, uint8_t b, uint8_t flag);
bool CheckFlagUnset(uint8_t a, uint8_t b, uint8_t flag);
bool CheckFlagSame(uint8_t a, uint8_t b, uint8_t flag);

bool CheckZFlagForZero8(uint8_t prev, uint8_t curr, uint8_t result);
bool CheckZFlagForZero16(uint8_t prev, uint8_t curr, uint16_t result);

bool CheckNFlag8(uint8_t prev, uint8_t curr, uint8_t result);
bool CheckNFlag16(uint8_t prev, uint8_t curr, uint16_t result);