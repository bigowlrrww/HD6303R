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

void EnVerbose();
bool PASS();
bool WARN();
bool WARN_I();
bool FAIL();
const char* flagToStr(uint8_t flag);

bool CheckSame8(uint8_t a, uint8_t b, const char *str);
bool CheckSame16(uint16_t a, uint16_t b, const char *str);

bool CheckRSH8(uint8_t a, uint8_t b, const char *str);
bool CheckRSH16(uint16_t a, uint16_t b, const char *str);

bool CheckLSH8(uint8_t a, uint8_t b, const char *str);
bool CheckLSH16(uint16_t a, uint16_t b, const char *str);

bool checkPC(uint16_t a, uint16_t b, uint8_t expectedStep);

bool checkImplemented(uint8_t flags);
bool checkVerified(uint8_t flags);
bool verifyUnknownMnemonic(uint16_t ExecResult);

bool CheckFlagSet(uint8_t a, uint8_t b, uint8_t flag);
bool CheckFlagUnset(uint8_t a, uint8_t b, uint8_t flag);
bool CheckFlagSame(uint8_t a, uint8_t b, uint8_t flag);